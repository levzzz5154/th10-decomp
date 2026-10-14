"""Bounded comparisons of the installed replay/result submenu and retail.

Exercises phases 6, 7, 8 and 13 with real animation lookup, child references,
stop frames, timers, input and sound callees. Score-maximum calculation and
name-entry preparation are scripted boundaries. The fixture checks return
stack balance, preserved registers, memory and meaningful call arguments;
it does not exercise replay file serialization or the whole keyboard editor.
"""
import sys
import struct
import json
import hashlib
from pathlib import Path
ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT))
from matching2.tools.common.pe import PEImage
from unicorn import Uc, UC_ARCH_X86, UC_MODE_32, UC_HOOK_CODE
from unicorn.x86_const import *
STATE, ANM, POOL, FRONT, STACK, STOP = (0x1000000, 0x2000000, 0x3000000, 0x3100000, 0x4000000, 0x7f000000)

def run(retail, image, phase, key=0, noentry=1, selection=2):
    u = Uc(UC_ARCH_X86, UC_MODE_32)
    u.mem_map(0x400000, 0x100000)
    for s in retail.sections:
        u.mem_write(s['address'], retail.read(s['address'], s['raw_size']))
    u.mem_write(0x4236f0, image.read(0x4236f0, 0xcbc))
    for a, n in [(STATE, 0x10000), (ANM, 0x740000), (POOL, 0x10000), (FRONT, 0x10000), (STACK, 0x10000), (STOP, 0x1000)]:
        u.mem_map(a, n)

    def w(a, v):
        u.mem_write(a, struct.pack('<I', v & 0xffffffff))

    def rd(a):
        return struct.unpack('<I', u.mem_read(a, 4))[0]

    def reg(n):
        return u.reg_read(globals()['UC_X86_REG_' + n.upper()])

    def ret(clean=0, value=0):
        sp = reg('esp')
        u.reg_write(UC_X86_REG_EIP, rd(sp))
        u.reg_write(UC_X86_REG_ESP, sp + 4 + clean)
        u.reg_write(UC_X86_REG_EAX, value)
    w(STATE + 4, phase)
    w(STATE + 20, 20)
    w(STATE + 28, 0x476f78)
    w(STATE + 32, 1)
    w(STATE + 36, selection)
    w(STATE + 44, 3)
    w(STATE + 244, 1)
    w(STATE + 0x1e8, noentry)
    w(STATE + 0x1d4, 42)
    w(0x491c10, ANM)
    w(0x47770c, FRONT)
    w(0x474e34, 0)
    w(0x474e36, key)
    w(0x474ca0, 0)
    w(0x474c7c, 1)
    w(ANM + 0x72dad4, POOL + 0x5000)
    for i in range(4):
        obj = POOL + i * 0x1000
        node = POOL + 0x5000 + i * 32
        w(obj, 42 + i)
        w(obj + 16, obj)
        w(obj + 0x35c, 2)
        w(node, obj)
        w(node + 4, node + 32 if i < 3 else 0)
        u.mem_write(obj + 0x38a, struct.pack('<h', 120 + i + 3))
    w(POOL + 20, POOL + 0x6000)
    for i in range(3):
        node = POOL + 0x6000 + i * 32
        w(node, POOL + (i + 1) * 0x1000)
        w(node + 4, node + 32 if i < 2 else 0)
    calls = []

    def hook(uc, a, n, data):
        if a == 0x423570:
            w(STATE + 0x1e8, noentry)
            calls.append(('prepare', rd(reg('esp') + 4)))
            ret(4)
            return
        if a == 0x421f60:
            calls.append(('frame', reg('eax')))
            ret()
            return
        if a == 0x4497d0:
            calls.append(('child', reg('esi'), reg('ebx')))
        if a == 0x449470:
            calls.append(('stop', rd(reg('eax')), reg('esi') & 0xffff))
        if a in [0x4243f0, 0x40c4d0, 0x4495e0, 0x449590]:
            calls.append((hex(a), rd(reg('eax'))))
        if a == 0x43dc90:
            calls.append(('sound', reg('ecx'), reg('edi'), rd(reg('esp') + 4)))
    for a in [0x423570, 0x421f60, 0x4497d0, 0x449470, 0x4243f0, 0x40c4d0, 0x4495e0, 0x449590, 0x43dc90]:
        u.hook_add(UC_HOOK_CODE, hook, begin=a, end=a)
    sp = STACK + 0x8000
    w(sp, STOP)
    w(sp + 4, STATE)
    u.reg_write(UC_X86_REG_ESP, sp)
    preserved = {UC_X86_REG_EBX: 0x12345678, UC_X86_REG_ESI: 0x23456789, UC_X86_REG_EDI: 0x34567890, UC_X86_REG_EBP: 0x45678901}
    for a, v in preserved.items():
        u.reg_write(a, v)
    u.reg_write(UC_X86_REG_FPCW, 0x37f)
    u.reg_write(UC_X86_REG_FPTAG, 0xffff)
    try:
        u.emu_start(0x4236f0, STOP, count=0x186a0)
    except Exception as e:
        return {'error': str(e), 'pc': hex(reg('eip')), 'calls': calls}
    assert reg('eip') == STOP, 'instruction limit'
    assert ((reg('fpsw') >> 11) & 7) == 0, 'x87 stack balance'
    assert reg('esp') == sp + 8
    for a, v in preserved.items():
        assert u.reg_read(a) == v
    return {'state': bytes(u.mem_read(STATE, 0x2c8)).hex(), 'pool': hashlib.sha256(u.mem_read(POOL, 0x10000)).hexdigest(), 'data': hashlib.sha256(u.mem_read(0x473000, 0x26000)).hexdigest(), 'calls': calls}

def main():
    import argparse
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--oracle', type=Path, default=ROOT / 'matching2/build/oracle/th10.exe')
    parser.add_argument('--candidate', type=Path, default=ROOT / 'matching2/build/msvc/th10.exe')
    parser.add_argument('--report', type=Path, default=ROOT / 'matching2/build/behavior/replay-submenu.json')
    args = parser.parse_args()
    retail = PEImage(args.oracle.read_bytes())
    candidate = PEImage(args.candidate.read_bytes())
    failures = []
    count = 0
    for phase in [6, 7, 8, 13]:
        for key in [0, 8, 0x1001]:
            for noentry in [0, 1]:
                for selection in [0, 2]:
                    count += 1
                    observations = []
                    for image in [retail, candidate]:
                        try:
                            observations.append(run(retail, image, phase, key, noentry, selection))
                        except Exception as error:
                            observations.append({'error': repr(error)})
                    expected, actual = observations
                    if expected != actual or 'error' in expected or 'error' in actual:
                        failures.append(dict(phase=phase, key=key, noentry=noentry, selection=selection, retail=expected, candidate=actual))
    report = dict(scope=__doc__, cases=count, passed=count - len(failures), failed=len(failures), oracle_sha256=hashlib.sha256(retail.data).hexdigest(), candidate_sha256=hashlib.sha256(candidate.data).hexdigest(), body_sha256=hashlib.sha256(candidate.read(0x4236f0, 0xcbc)).hexdigest(), failures=failures)
    args.report.parent.mkdir(parents=True, exist_ok=True)
    args.report.write_text(json.dumps(report, indent=2) + '\n')
    print(f'{count - len(failures)}/{count} passed; report: {args.report}')
    return int(bool(failures))
if __name__ == '__main__':
    sys.exit(main())
