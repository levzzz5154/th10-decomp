#!/usr/bin/env python3
"""Execute retail and a native MSVC candidate with scripted joystick APIs.

The complete native PE is loaded without patching its instructions. WinMM,
DirectInput and the security-cookie check are emulated at their call boundaries.
This checks behavior and ABI; it is not a replacement for byte equality.
Requires Unicorn 2.1.2, available through the experiment's dependency directory.
"""
import argparse
from dataclasses import dataclass, replace
import hashlib
import json
from pathlib import Path
import random
import struct
import sys

ROOT = Path(__file__).resolve().parents[4]
WORK = ROOT / 'matching2/build/experiments/joystick_binding_reader_0044a190_2026_10_06'
sys.path[:0] = [str(ROOT), str(WORK / 'dependencies')]
from matching2.tools.common.pe import PEImage
from matching2.tools.matching.equivalence import MAP_SYMBOL
from unicorn import Uc, UC_ARCH_X86, UC_MODE_32, UC_HOOK_CODE
from unicorn.x86_const import (
    UC_X86_REG_EAX, UC_X86_REG_EBX, UC_X86_REG_ECX, UC_X86_REG_EDX,
    UC_X86_REG_ESI, UC_X86_REG_EDI, UC_X86_REG_EBP, UC_X86_REG_ESP,
    UC_X86_REG_EIP,
)

API = 0x600000
STOP, JOY, POLL, ACQUIRE, GET_STATE = (API + i * 0x100 for i in range(5))
STACK, DEVICES, VTABLE = 0x2300000, (0x610000, 0x610100, 0x610200), 0x610300
COOKIE = 0x13579bdf
LOST = 0x8007001e
PRESERVED = {UC_X86_REG_EBX: 0x34567890, UC_X86_REG_ESI: 0x45678901,
             UC_X86_REG_EDI: 0x56789012, UC_X86_REG_EBP: 0x67890123}


@dataclass(frozen=True)
class Case:
    backend: str = 'directinput'
    flags: int = 0x8200
    binding_set: int = 0
    device: int = 0
    bindings: tuple = (0, 1, 2, 3, 4)  # fire, bomb, slow, escape, control
    buttons: bytes = bytes([0x80] * 128)
    axes: tuple = (0, 0)
    thresholds: tuple = (128, 256)
    caps: tuple = (0, 65535, 0, 65535)
    winmm_buttons: int = 0x1f
    joy_result: int = 0
    poll_result: int = 0
    state_result: int = 0
    acquire_results: tuple = (0,)
    replace_device_after_poll: bool = False


def run(image, entry, case):
    machine = Uc(UC_ARCH_X86, UC_MODE_32)
    machine.mem_map(0x400000, 0x100000)
    for section in image.sections:
        if section['raw_size']:
            machine.mem_write(section['address'], image.read(section['address'], section['raw_size']))
    machine.mem_map(API, 0x20000)
    machine.mem_map(STACK, 0x10000)
    machine.mem_write(STACK, b'\xa5' * 0x10000)
    write = lambda address, value: machine.mem_write(address, struct.pack('<I', value & 0xffffffff))
    read = lambda address: struct.unpack('<I', machine.mem_read(address, 4))[0]
    for device in DEVICES:
        write(device, VTABLE)
    for offset, address in [(0x64, POLL), (0x1c, ACQUIRE), (0x24, GET_STATE)]:
        write(VTABLE + offset, address)
    write(0x466280, JOY)
    write(0x473660, COOKIE)
    write(0x491ff4, 0 if case.backend == 'winmm' else 0x400)
    for index in range(2):
        write(0x491c3c + index * 4, DEVICES[index])
        machine.mem_write(0x4918b8 + index * 0x194 + 0x24, struct.pack('<4I', *case.caps))
        machine.mem_write(0x474e30 + index * 0x6a + 0x58, struct.pack('<4h', *case.bindings[:4]))
        machine.mem_write(0x474e30 + index * 0x6a + 0x68, struct.pack('<h', case.bindings[4]))
    machine.mem_write(0x491d5e, struct.pack('<2h', *case.thresholds))
    sp = STACK + 0x8000
    machine.mem_write(sp, struct.pack('<3I', STOP, case.binding_set, case.device))
    machine.reg_write(UC_X86_REG_ESP, sp)
    machine.reg_write(UC_X86_REG_ECX, case.flags)
    machine.reg_write(UC_X86_REG_EDX, 0xdeadbeef)
    for register, value in PRESERVED.items():
        machine.reg_write(register, value)
    calls, cookies = [], []
    acquire_count = 0

    def return_from_api(result, arguments):
        current_sp = machine.reg_read(UC_X86_REG_ESP)
        machine.reg_write(UC_X86_REG_EAX, result & 0xffffffff)
        machine.reg_write(UC_X86_REG_ECX, 0xc1c1c1c1)
        machine.reg_write(UC_X86_REG_EDX, 0xd2d2d2d2)
        machine.reg_write(UC_X86_REG_EIP, read(current_sp))
        machine.reg_write(UC_X86_REG_ESP, current_sp + 4 + arguments * 4)

    def api_hook(uc, address, size, user_data):
        nonlocal acquire_count
        current_sp = uc.reg_read(UC_X86_REG_ESP)
        if address == 0x458ea5:
            assert uc.reg_read(UC_X86_REG_ECX) == COOKIE, 'security cookie differs'
            cookies.append(COOKIE)
            uc.reg_write(UC_X86_REG_EIP, read(current_sp))
            uc.reg_write(UC_X86_REG_ESP, current_sp + 4)
            return
        if address == JOY:
            device, destination = read(current_sp + 4), read(current_sp + 8)
            initial = bytes(uc.mem_read(destination, 0x34))
            assert initial == struct.pack('<2I', 0x34, 0xff) + bytes(0x2c), 'JOYINFOEX initialization differs'
            assert device == int(case.device != 0)
            position = [0x34, 0xff, case.axes[0] & 0xffffffff, case.axes[1] & 0xffffffff,
                        0, 0, 0, 0, case.winmm_buttons, 0, 0, 0, 0]
            uc.mem_write(destination, struct.pack('<13I', *position))
            calls.append(('joy', device))
            return_from_api(case.joy_result, 2)
            return
        device = read(current_sp + 4)
        assert device in DEVICES, 'COM receiver differs'
        if address == POLL:
            calls.append(('poll', device))
            if case.replace_device_after_poll:
                write(0x491c3c + case.device * 4, DEVICES[2])
            return_from_api(case.poll_result, 1)
        elif address == ACQUIRE:
            calls.append(('acquire', device))
            result = case.acquire_results[min(acquire_count, len(case.acquire_results) - 1)]
            acquire_count += 1
            return_from_api(result, 1)
        elif address == GET_STATE:
            count, destination = read(current_sp + 8), read(current_sp + 12)
            assert count == 0x110
            assert bytes(uc.mem_read(destination, count)) == bytes(count), 'DIJOYSTATE2 initialization differs'
            state = bytearray(count)
            struct.pack_into('<2i', state, 0, *case.axes)
            state[0x30:0xb0] = case.buttons
            uc.mem_write(destination, bytes(state))
            calls.append(('state', device, count))
            return_from_api(case.state_result, 3)
        else:
            raise AssertionError(f'unexpected API address {address:#x}')

    machine.hook_add(UC_HOOK_CODE, api_hook, begin=JOY, end=GET_STATE)
    machine.hook_add(UC_HOOK_CODE, api_hook, begin=0x458ea5, end=0x458ea5)
    machine.emu_start(entry, STOP, count=200000)
    assert machine.reg_read(UC_X86_REG_EIP) == STOP, 'instruction limit exhausted'
    assert machine.reg_read(UC_X86_REG_ESP) == sp + 12, 'RET 8 cleanup differs'
    for register, value in PRESERVED.items():
        assert machine.reg_read(register) == value, 'callee-saved register differs'
    assert cookies == [COOKIE]
    assert acquire_count <= 401, 'retry limit differs'
    return {'flags': machine.reg_read(UC_X86_REG_EAX) & 0xffff, 'calls': calls}


def cases():
    base = Case()
    for backend in ('winmm', 'directinput'):
        for binding_set in range(2):
            for device in range(2):
                for flags in (0, 0x8200, 0xffffffff):
                    yield replace(base, backend=backend, binding_set=binding_set, device=device, flags=flags)
    for backend in ('winmm', 'directinput'):
        for index in range(5):
            for value in (0, 1, 0x40, 0x7f, 0x80, 0xc0, 0xff):
                buttons = bytearray(128)
                buttons[index] = value
                yield replace(base, backend=backend, buttons=bytes(buttons), winmm_buttons=1 << index)
        for bindings in ((-1,) * 5, (127,) * 5, (0, -1, 31, 3, -1)):
            yield replace(base, backend=backend, bindings=bindings)
    for threshold in (0, 1, 128, 32767, -1, -32768):
        values = {-2147483648, 2147483647, 0, -threshold-1, -threshold, -threshold+1,
                  threshold-1, threshold, threshold+1}
        for x in sorted(values):
            for y in sorted(values):
                yield replace(base, axes=(x, y), thresholds=(threshold, threshold))
    for caps in ((0, 65535, 0, 65535), (100, 1100, 50, 2050),
                 (0xffffffff, 0xffffffff, 0, 0), (0x80000000, 0xffffffff, 0, 0x80000000)):
        for axis in (0, 16383, 16384, 32767, 49150, 49151, 65535, 0xffffffff):
            yield replace(base, backend='winmm', axes=(axis, axis), caps=caps)
    for result in (1, 0x80004005):
        yield replace(base, backend='winmm', joy_result=result)
        yield replace(base, state_result=result)
    for sequence in ((0,), (LOST,), (LOST, 0), (LOST, 0x80004005),
                     (LOST,) * 400 + (0,), (LOST,) * 399 + (0,)):
        for device in range(2):
            yield replace(base, poll_result=0x80004005, acquire_results=sequence, device=device)
    for poll_result in (0, 0x80004005):
        for device in range(2):
            yield replace(base, poll_result=poll_result, device=device, replace_device_after_poll=True)
    rng = random.Random(0x44a190)
    for _ in range(200):
        yield replace(base, backend=rng.choice(('winmm', 'directinput')),
                      flags=rng.getrandbits(32), binding_set=rng.randrange(2), device=rng.randrange(2),
                      bindings=tuple(rng.choice((-1, rng.randrange(32))) for _ in range(5)),
                      buttons=bytes(rng.randrange(256) for _ in range(128)), winmm_buttons=rng.getrandbits(32),
                      axes=(rng.randrange(-2147483648, 2147483648), rng.randrange(-2147483648, 2147483648)),
                      thresholds=(rng.randrange(-32768, 32768), rng.randrange(-32768, 32768)))


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--candidate', type=Path, required=True)
    parser.add_argument('--output', type=Path)
    args = parser.parse_args()
    retail = PEImage((ROOT / 'matching2/build/oracle/th10.exe').read_bytes())
    native = PEImage(args.candidate.read_bytes())
    link_map = args.candidate.with_suffix('.map').read_text()
    symbols = {name: int(address, 16) for name, address, _ in MAP_SYMBOL.findall(link_map)}
    entry = symbols['@JoystickReadBindings@12']
    observations = []
    for index, case in enumerate(cases()):
        expected = run(retail, 0x44a190, case)
        actual = run(native, entry, case)
        assert actual == expected, f'case {index}: {case!r}: {actual!r} != {expected!r}'
        observations.append(expected)
    report = {'cases': len(observations), 'passed': True, 'instruction_patches': 0,
              'native_pe_sha256': hashlib.sha256(native.data).hexdigest(),
              'retail_body_sha256': hashlib.sha256(retail.read(0x44a190, 833)).hexdigest(),
              'observation_sha256': hashlib.sha256(json.dumps(observations, sort_keys=True).encode()).hexdigest(),
              'scripted_boundaries': ['joyGetPosEx', 'Poll', 'Acquire', 'GetDeviceState', 'security_check_cookie'],
              'scope': 'Returned flags, API receivers and order, initialization, retry limit, stack cleanup and callee-saved registers.'}
    if args.output:
        args.output.write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))


if __name__ == '__main__':
    main()
