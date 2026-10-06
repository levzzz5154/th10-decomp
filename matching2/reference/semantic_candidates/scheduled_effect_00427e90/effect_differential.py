#!/usr/bin/env python3
"""Compare complete raw retail/native effect updates with scripted callbacks.

All six native supporting helpers execute from the native PE. Both runs use
the original raw polar, angle and CRT math code at the shared boundaries.
No machine instructions are patched. This is bounded behavioral evidence,
not a byte-equality gate or a real-game integration test.
"""
import argparse
from dataclasses import dataclass, replace
import hashlib
import json
from pathlib import Path
import random
import struct
import sys

ROOT = Path.cwd()
sys.path[:0] = [str(ROOT), str(ROOT / 'matching2/build/experiments/joystick_binding_reader_0044a190_2026_10_06/dependencies')]
from matching2.tools.common.pe import PEImage
from matching2.tools.matching.equivalence import MAP_SYMBOL
from unicorn import Uc, UC_ARCH_X86, UC_MODE_32, UC_HOOK_CODE
from unicorn.x86_const import (
    UC_X86_REG_EAX, UC_X86_REG_EBX, UC_X86_REG_ECX, UC_X86_REG_EDX,
    UC_X86_REG_ESI, UC_X86_REG_EDI, UC_X86_REG_EBP, UC_X86_REG_ESP,
    UC_X86_REG_EIP, UC_X86_REG_FPCW, UC_X86_REG_FPTAG, UC_X86_REG_FPSW,
)

PLAYER, POOL, CONTEXT, STACK = 0x1000000, 0x2000000, 0x3000000, 0x4000000
API, STOP, CALLBACK = 0x600000, 0x600000, 0x600100
SPEED, FRONT = API + 0x1000, POOL + 0x92000
PRESERVED = {UC_X86_REG_EBX: 0x12345678, UC_X86_REG_ESI: 0x23456789,
             UC_X86_REG_EDI: 0x3456789a, UC_X86_REG_EBP: 0x456789ab}


@dataclass(frozen=True)
class Case:
    indices: tuple = (0,)
    state: int = 1
    kind: int = 0
    ordinal: int = 1
    stage_frame: int = 10
    familiar_level: int = 3
    script_present: bool = False
    stage_present: bool = True
    touched: int = 0
    started: int = 0
    primary_present: bool = True
    secondary_present: bool = True
    child_previous: bool = False
    rotating_sprite: bool = False
    callback: str = ''
    position: tuple = (0.0, 100.0, 3.0)
    orbit: bool = False
    motion_speed: float = 0.0
    angle: float = 0.0
    radius: float = 5.0
    radius_step: float = 1.0
    frame: int = 0
    elapsed: float = 0.0
    timer_speed: float = 1.0


def run(retail, native, entry, case, helpers):
    uc = Uc(UC_ARCH_X86, UC_MODE_32)
    uc.mem_map(0x400000, 0x100000)
    if native is not None and native.image_base < 0x400000:
        uc.mem_map(native.image_base, 0x100000)
    for image in (retail, native):
        if image is not None:
            for section in image.sections:
                if section['raw_size']:
                    uc.mem_write(section['address'], image.read(section['address'], section['raw_size']))
    for address, size in [(PLAYER, 0x5000), (POOL, 0xa0000), (CONTEXT, 0x730000),
                          (STACK, 0x10000), (API, 0x2000)]:
        uc.mem_map(address, size)
    uc.mem_write(STACK, b'\xa5' * 0x10000)
    def word(address, value):
        uc.mem_write(address, struct.pack('<I', value & 0xffffffff))
    def read(address):
        return struct.unpack('<I', uc.mem_read(address, 4))[0]
    def floats(address, values):
        uc.mem_write(address, struct.pack('<' + 'f' * len(values), *values))
    word(0x491c10, CONTEXT)
    word(0x47770c, FRONT if case.script_present else 0)
    word(FRONT + 0x9eb8, 0x13572468 if case.script_present else 0)
    word(0x477704, 0x24681357 if case.stage_present else 0)
    word(PLAYER + 0x464, case.stage_frame)
    word(PLAYER + 0x3500, case.familiar_level)
    for index in range(6):
        word(PLAYER + 0x42f4 + index * 4, 100 + index)
    floats(SPEED, [case.timer_speed])
    objects, primary_nodes, secondary_nodes = [], [], []
    for index in case.indices:
        effect = PLAYER + 0x49c + index * 0x5c
        descriptor = POOL + 0x90000 + index * 0x30
        word(effect + 0x40, case.state)
        word(effect + 0x44, 1000 + index * 2)
        word(effect + 0x48, 1001 + index * 2)
        word(effect + 0x50, case.touched)
        word(effect + 0x54, case.started)
        word(effect + 0x58, descriptor)
        uc.mem_write(descriptor + 0x1c, bytes([case.ordinal, case.kind]))
        word(descriptor + 0x28, CALLBACK if case.callback else 0)
        word(effect, case.frame - 1)
        word(effect + 4, case.frame)
        floats(effect + 8, [case.elapsed])
        word(effect + 0xc, SPEED)
        word(effect + 0x10, 1)
        floats(effect + 0x14, case.position)
        floats(effect + 0x20, [1.0, 2.0, 0.0])
        floats(effect + 0x2c, [case.motion_speed, case.angle, case.radius, case.radius_step])
        uc.mem_write(effect + 0x3c, bytes([int(case.orbit)]))
        for secondary in range(2):
            ordinal = index * 4 + secondary
            obj = POOL + ordinal * 0x400
            child = obj + 0x800
            node, child_node = POOL + 0x85000 + ordinal * 0x20, POOL + 0x85010 + ordinal * 0x20
            sprite = POOL + 0x8c000 + index * 0x40
            word(obj, 1000 + index * 2 + secondary)
            word(obj + 0x14, child_node)
            word(obj + 0x18, 1 if case.child_previous else 0)
            word(child_node, child)
            word(child_node + 4, 0)
            floats(obj + 0x3c, [1.0, 1.0])
            floats(obj + 0x340, [-777.0, -888.0, -999.0])
            word(obj + 0x35c, 0x8000000 if case.rotating_sprite else 0)
            word(obj + 0x394, sprite)
            floats(sprite + 0x30, [16.0, 32.0])
            objects.extend([obj, child])
            word(node, obj)
            if case.secondary_present if secondary else case.primary_present:
                (secondary_nodes if secondary else primary_nodes).append(node)
    for offset, nodes in [(0x72dad4, primary_nodes), (0x72dadc, secondary_nodes)]:
        word(CONTEXT + offset, nodes[0] if nodes else 0)
        for a, b in zip(nodes, [*nodes[1:], 0]):
            word(a + 4, b)
    sp = STACK + 0x8000
    uc.mem_write(sp, struct.pack('<2I', STOP, PLAYER))
    uc.reg_write(UC_X86_REG_ESP, sp)
    uc.reg_write(UC_X86_REG_ECX, 0xc1c1c1c1)
    uc.reg_write(UC_X86_REG_EDX, 0xd2d2d2d2)
    uc.reg_write(UC_X86_REG_FPCW, 0x37f)
    uc.reg_write(UC_X86_REG_FPTAG, 0xffff)
    uc.reg_write(UC_X86_REG_FPSW, 0)
    for register, value in PRESERVED.items():
        uc.reg_write(register, value)
    callbacks = []
    helper_calls = {name: 0 for name in helpers.values()}
    def record_helper(machine, address, size, user_data):
        helper_calls[helpers[address]] += 1
    for address in helpers:
        uc.hook_add(UC_HOOK_CODE, record_helper, begin=address, end=address)
    def callback(machine, address, size, user_data):
        player, effect = machine.reg_read(UC_X86_REG_ECX), machine.reg_read(UC_X86_REG_EDX)
        assert player == PLAYER
        assert effect >= PLAYER + 0x49c and (effect - PLAYER - 0x49c) % 0x5c == 0
        callbacks.append({'index': (effect - PLAYER - 0x49c) // 0x5c,
                          'state': read(effect + 0x40), 'touched': read(effect + 0x50)})
        if case.callback == 'replace_primary':
            word(effect + 0x44, 0)
        elif case.callback == 'clear_secondary':
            word(effect + 0x48, 0)
        elif case.callback == 'move_outside':
            floats(effect + 0x14, [1000.0, 1000.0, 5.0])
        elif case.callback == 'clear_state':
            word(effect + 0x40, 0)
        current_sp = machine.reg_read(UC_X86_REG_ESP)
        machine.reg_write(UC_X86_REG_EIP, read(current_sp))
        machine.reg_write(UC_X86_REG_ESP, current_sp + 4)
        for register, value in [(UC_X86_REG_EAX, 0xa0a0a0a0),
                                (UC_X86_REG_ECX, 0xc1c1c1c1), (UC_X86_REG_EDX, 0xd2d2d2d2)]:
            machine.reg_write(register, value)
    uc.hook_add(UC_HOOK_CODE, callback, begin=CALLBACK, end=CALLBACK)
    uc.emu_start(entry, STOP, count=500000)
    assert uc.reg_read(UC_X86_REG_EIP) == STOP, 'instruction limit exhausted'
    assert uc.reg_read(UC_X86_REG_ESP) == sp + 8, 'RET4 cleanup differs'
    assert uc.reg_read(UC_X86_REG_EAX) == 0, 'return value differs'
    for register, value in PRESERVED.items():
        assert uc.reg_read(register) == value, 'callee-saved register differs'
    assert (uc.reg_read(UC_X86_REG_FPSW) >> 11) & 7 == 0, 'x87 stack is not balanced'
    return {'player_sha256': hashlib.sha256(uc.mem_read(PLAYER, 0x4478)).hexdigest(),
            'pool_sha256': hashlib.sha256(uc.mem_read(POOL, 0xa0000)).hexdigest(),
            'callbacks': callbacks, 'helper_calls': helper_calls, 'fpcw': uc.reg_read(UC_X86_REG_FPCW),
            'fpu_tags': uc.reg_read(UC_X86_REG_FPTAG)}


def cases():
    base = Case()
    yield replace(base, indices=())
    for state in (0, 1, 2, 3, -1):
        for index in (0, 63, 127):
            yield replace(base, state=state, indices=(index,))
    for primary in (False, True):
        for secondary in (False, True):
            for children in (False, True):
                yield replace(base, primary_present=primary, secondary_present=secondary,
                              child_previous=children)
    for stage_frame in (-1, 0, 10):
        for level in (0, 1, 3):
            for ordinal in (0, 1, 5):
                yield replace(base, kind=3, stage_frame=stage_frame, familiar_level=level, ordinal=ordinal)
    for script in (False, True):
        for stage in (False, True):
            for touched in (0, 1):
                for started in (0, 1):
                    yield replace(base, kind=3, script_present=script, stage_present=stage,
                                  touched=touched, started=started)
    for position in ((-210.0, 100.0, 3.0), (-208.0, 100.0, 3.0),
                     (208.0, 100.0, 3.0), (210.0, 100.0, 3.0),
                     (0.0, -10.0, 0.0), (0.0, 500.0, -0.0), (0.0, 100.0, 3.0)):
        for frame in (9, 10, 11):
            yield replace(base, position=position, frame=frame)
    for speed in (0.0, 0.5, 0.99, 1.0, 1.01, 1.5, -0.5, float('nan'), float('inf'), -float('inf')):
        yield replace(base, timer_speed=speed, frame=1, elapsed=1.75)
    for angle in (0.0, 0.5, 3.0, -3.0):
        for orbit in (False, True):
            yield replace(base, angle=angle, orbit=orbit, motion_speed=0.1,
                          rotating_sprite=True)
    for callback in ('record', 'replace_primary', 'clear_secondary', 'move_outside', 'clear_state'):
        yield replace(base, callback=callback, touched=1, frame=10, indices=(0, 63, 127))
    for index_set in (tuple(range(128)), tuple(range(0, 128, 2))):
        for primary in (True, False):
            yield replace(base, indices=index_set, primary_present=primary, frame=10, callback='record')
    rng = random.Random(0x428280)
    for _ in range(100):
        yield replace(base, state=rng.choice((0, 1, 2)), kind=rng.choice((0, 1, 3)),
                      ordinal=rng.randrange(6), familiar_level=rng.randrange(6),
                      stage_frame=rng.choice((-1, 0, 10)),
                      primary_present=rng.choice((True, False)),
                      secondary_present=rng.choice((True, False)),
                      frame=rng.randrange(20), elapsed=rng.randrange(20) + 0.25,
                      timer_speed=rng.choice((0.0, 0.5, 1.0, 1.5)),
                      position=(rng.uniform(-300, 300), rng.uniform(-50, 500), rng.uniform(-5, 5)),
                      motion_speed=rng.uniform(-2, 2), angle=rng.uniform(-3, 3),
                      orbit=rng.choice((True, False)))


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--candidate', required=True, type=Path)
    parser.add_argument('--output', type=Path)
    parser.add_argument('--limit', type=int)
    args = parser.parse_args()
    retail = PEImage((ROOT / 'matching2/build/oracle/th10.exe').read_bytes())
    native = PEImage(args.candidate.read_bytes())
    symbols = {name: int(address, 16) for name, address, _ in
               MAP_SYMBOL.findall(args.candidate.with_suffix('.map').read_text())}
    entry = symbols['_EffectPoolUpdate@4']
    layout = json.loads((Path(__file__).with_name('layout.json')).read_text())
    retail_helpers = {address: symbol for symbol, _, address, _ in layout['functions'] if address in (0x409e50,0x40c4d0,0x4491c0,0x4492a0,0x44c2a0,0x428d70)}
    native_helpers = {symbols[symbol]: symbol for symbol in retail_helpers.values()}
    for name, address in [('SetPolar', 0x44c5d0), ('NormalizeAngle', 0x44bc70), ('floor', 0x452ff0), ('_ftol2', 0x463b2c)]:
        retail_helpers[address] = native_helpers[address] = name
    observations = []
    for index, case in enumerate(cases()):
        if args.limit is not None and index >= args.limit:
            break
        expected = run(retail, None, 0x428280, case, retail_helpers)
        actual = run(retail, native, entry, case, native_helpers)
        assert actual == expected, f'case {index}: {case!r}: {actual!r} != {expected!r}'
        observations.append(expected)
    report = {'cases': len(observations), 'passed': True, 'instruction_patches': 0,
              'native_pe_sha256': hashlib.sha256(native.data).hexdigest(),
              'retail_body_sha256': hashlib.sha256(retail.read(0x428280, 876)).hexdigest(),
              'observation_sha256': hashlib.sha256(json.dumps(observations, sort_keys=True).encode()).hexdigest(),
              'scope': 'Complete player/pool state, callback ABI/order, six native helpers, return, callee-saved registers, RET4 and x87 stack balance.',
              'shared_raw_retail_boundaries': ['SetPolar', 'NormalizeAngle', 'floor', '_ftol2'],
              'scripted_boundaries': ['descriptor callback'], 'limited_run': args.limit is not None,
              'executed_helper_calls': {name: sum(o['helper_calls'][name] for o in observations) for name in retail_helpers.values()}}
    if args.limit is None:
        assert all(report['executed_helper_calls'].values()), 'an advertised helper was not executed'
    if args.output:
        artifact=args.output.with_name('effect_observations.json')
        artifact.write_text(json.dumps(observations, sort_keys=True) + '\n')
        report['observations_file_sha256']=hashlib.sha256(artifact.read_bytes()).hexdigest()
        args.output.write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))


if __name__ == '__main__':
    main()
