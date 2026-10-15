"""Check that equivalent-model bodies call unchanged retail code with retail's register arguments.

An equivalent model is compiled in its own LTCG cluster, where a stand-in for a retail callee can get
a private register convention that differs from the installed retail body. The layout gate compares
instructions, not conventions, so such a call can pass review yet hand the callee garbage. This tool
pairs each direct call from a model region to a target outside it with retail's call to the same
target (by occurrence order), finds the registers the retail callee reads at entry, and compares the
provenance of each of those registers before both calls: the absolute addresses and constants of the
defining instruction chain.

    callsite_abi.py [--retail build/oracle/th10.exe] [--build build/msvc/th10.exe] [region ...]

Mismatches reviewed by hand (same value, different provenance) are listed with their reason in
callsite_abi_reviewed.json, keyed by model and callee. Exit status 1 when any other call site mismatches.
"""
import argparse
import json
import struct
import sys
from collections import Counter
from pathlib import Path

import capstone
from capstone import x86

ROOT = Path(__file__).resolve().parents[2]
GPR = ('eax', 'ecx', 'edx', 'ebx', 'esi', 'edi', 'ebp')
SUB = {'ax': 'eax', 'al': 'eax', 'ah': 'eax', 'cx': 'ecx', 'cl': 'ecx', 'ch': 'ecx', 'dx': 'edx', 'dl': 'edx',
       'dh': 'edx', 'bx': 'ebx', 'bl': 'ebx', 'bh': 'ebx', 'si': 'esi', 'di': 'edi', 'bp': 'ebp'}


class Image:
    def __init__(self, path):
        self.data = Path(path).read_bytes()
        pe = struct.unpack_from('<I', self.data, 0x3C)[0]
        count = struct.unpack_from('<H', self.data, pe + 6)[0]
        optional = struct.unpack_from('<H', self.data, pe + 20)[0]
        self.sections = [struct.unpack_from('<IIII', self.data, pe + 24 + optional + 40 * i + 8)
                         for i in range(count)]

    def read(self, address, size):
        for vsize, va, rsize, raw in self.sections:
            if 0x400000 + va <= address < 0x400000 + va + vsize:
                offset = address - 0x400000 - va + raw
                return self.data[offset:offset + size]
        raise ValueError(hex(address))


md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
md.detail = True


def disasm(image, address, size):
    return list(md.disasm(image.read(address, size), address))


def full(reg):
    return SUB.get(reg, reg)


def regs_rw(insn):
    read, write = insn.regs_access()
    return ({full(insn.reg_name(r)) for r in read}, {full(insn.reg_name(r)) for r in write})


def callee_inputs(image, target):
    """Registers the callee reads before writing them, along its entry path (first block)."""
    inputs, written = set(), set()
    for insn in disasm(image, target, 96):
        read, write = regs_rw(insn)
        if insn.mnemonic == 'push' and insn.operands[0].type == x86.X86_OP_REG:
            read = set()                      # callee-saved register being preserved, not an argument
        if insn.mnemonic in ('xor', 'sub') and len(insn.operands) == 2 and \
                insn.operands[0].type == insn.operands[1].type == x86.X86_OP_REG and \
                insn.operands[0].reg == insn.operands[1].reg:
            read = set()                      # zeroing idiom
        inputs |= {r for r in read if r in GPR and r not in written}
        written |= write
        if insn.group(capstone.CS_GRP_JUMP) or insn.group(capstone.CS_GRP_RET) or insn.group(capstone.CS_GRP_CALL):
            break
    return inputs


def provenance(insns, index, reg, depth=3):
    """Constants and absolute addresses in the chain defining `reg` before insns[index]."""
    found = set()
    for i in range(index - 1, max(-1, index - 40), -1):
        insn = insns[i]
        if insn.group(capstone.CS_GRP_CALL) or insn.group(capstone.CS_GRP_RET) or insn.mnemonic == 'jmp':
            return found | {'?unknown'}
        read, write = regs_rw(insn)
        if reg not in write:
            continue
        for op in insn.operands:
            if op.type == x86.X86_OP_IMM and not insn.group(capstone.CS_GRP_JUMP):
                found.add(f'#{op.imm & 0xffffffff:#x}')
            elif op.type == x86.X86_OP_MEM:
                if op.mem.disp and (op.mem.base == 0 or abs(op.mem.disp) >= 0x400000):
                    found.add(f'[{op.mem.disp & 0xffffffff:#x}]')
                if op.mem.base and insn.reg_name(op.mem.base) == 'esp' and insn.mnemonic != 'lea':
                    found.add('stack')
        if insn.mnemonic in ('xor', 'sub') and len(insn.operands) == 2 and \
                insn.operands[0].type == insn.operands[1].type == x86.X86_OP_REG and \
                insn.operands[0].reg == insn.operands[1].reg:
            return found | {'#0x0'}
        if depth:
            for src in read - {reg, 'esp'}:
                if src in GPR:
                    found |= provenance(insns, i, src, depth - 1)
        if insn.mnemonic.startswith('mov') or insn.mnemonic == 'lea':
            return found
    return found | {'?unknown'}


def calls(insns, lo, hi):
    out = []
    for i, insn in enumerate(insns):
        if insn.mnemonic == 'call' and insn.operands[0].type == x86.X86_OP_IMM:
            target = insn.operands[0].imm
            if not lo <= target < hi:
                out.append((i, target))
    return out


import sys as _project_sys
from pathlib import Path as _ProjectPath
_project_sys.path.insert(0, str(_ProjectPath(__file__).resolve().parents[3]))
from matching2.tools.common.project_paths import project_support
def regions():
    layout = project_support(ROOT / 'msvc', 'layout') / 'equivalent'
    table = {r['name']: r for r in json.loads((project_support(ROOT / 'msvc', 'regions.json')).read_text())['regions']}
    for path in sorted(layout.glob('*.json')):
        meta = json.loads(path.read_text())
        region = table[meta['region']]
        yield meta['name'], int(region['address'], 16), meta.get('code_bytes', region['size'])


def main(argv):
    ap = argparse.ArgumentParser()
    ap.add_argument('--retail', default=str(ROOT / 'build' / 'oracle' / 'th10.exe'))
    ap.add_argument('--build', default=str(ROOT / 'build' / 'msvc' / 'th10.exe'))
    ap.add_argument('names', nargs='*')
    args = ap.parse_args(argv)
    retail, build = Image(args.retail), Image(args.build)
    reviewed = json.loads((Path(__file__).with_name('callsite_abi_reviewed.json')).read_text())
    bad = 0
    for name, address, size in regions():
        if args.names and name not in args.names:
            continue
        a = disasm(retail, address, size)
        b = disasm(build, address, size)
        ca, cb = calls(a, address, address + size), calls(b, address, address + size)
        by_target = {}
        for i, t in ca:
            by_target.setdefault(t, [[], []])[0].append(i)
        for i, t in cb:
            by_target.setdefault(t, [[], []])[1].append(i)
        problems, accepted = [], []
        for target, (ia, ib) in sorted(by_target.items()):
            inputs = sorted(callee_inputs(retail, target))
            # Layout-independent: compare the multiset of argument-register provenances per target.
            def sig(insns, i):
                return tuple((reg, tuple(sorted(provenance(insns, i, reg) - {'?unknown'}))) for reg in inputs)
            sa = sorted(sig(a, i) for i in ia)
            sb = sorted(sig(b, i) for i in ib)
            if len(ia) != len(ib):
                problems.append(f'  call {target:#x}: retail {len(ia)} call sites, model {len(ib)}')
            if sa != sb:
                only_a = sorted((Counter(sa) - Counter(sb)).elements())
                only_b = sorted((Counter(sb) - Counter(sa)).elements())
                where = [f'{b[i].address:#x}' for i in ib if sig(b, i) in only_b]
                problems.append(f'  call {target:#x} (inputs {inputs}): retail-only {only_a[:4]} model-only '
                                f'{only_b[:4]} at model {where[:4]}')
        allowed = reviewed.get(name, {})
        accepted = [p for p in problems if p.split()[1].rstrip(':') in allowed]
        problems = [p for p in problems if p not in accepted]
        status = 'MISMATCH' if problems else ('REVIEWED' if accepted else 'OK')
        print(f'{status:8} {name} ({len(ca)} retail / {len(cb)} model external calls)')
        for p in problems:
            print(p)
        for target in sorted({p.split()[1].rstrip(':') for p in accepted}):
            print(f'  reviewed call {target}: {allowed[target]}')
        bad += bool(problems)
    return 1 if bad else 0


if __name__ == '__main__':
    sys.exit(main(sys.argv[1:]))
