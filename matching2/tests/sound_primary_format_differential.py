#!/usr/bin/env python3
"""Compare primary DirectSound format setup with the original 260-byte body."""

import argparse
from dataclasses import dataclass
from itertools import product
from pathlib import Path
import random
import struct
import subprocess
import tempfile

from unicorn import Uc, UcError, UC_ARCH_X86, UC_MODE_32, UC_HOOK_CODE, UC_HOOK_MEM_INVALID
from unicorn.x86_const import (UC_X86_REG_EAX, UC_X86_REG_EBX, UC_X86_REG_ECX, UC_X86_REG_EDI,
                              UC_X86_REG_ESP, UC_X86_REG_EIP)
from lzss_compressor_differential import (
    ROOT, CANDIDATE, STACK, STOP, PRESERVED, PEImage, load_manifest, load_oracle)
from coff_module import load_module

STATE, OWNER, DEVICE, BUFFER, OTHER = 0x2500000, 0x2500100, 0x2500200, 0x2500300, 0x2500400
DEVICE_TABLE, BUFFER_TABLE = STATE + 0x1000, STATE + 0x1100
CREATE, FORMAT, RELEASE = STOP + 0x100, STOP + 0x200, STOP + 0x300


@dataclass(frozen=True)
class Case:
    bits: int = 16
    channels: int = 2
    rate: int = 44100
    owner_present: bool = True
    device_present: bool = True
    create_result: int = 0
    format_result: int = 0
    create_output: int = BUFFER
    replace_output: object = None
    clear_owner: bool = False


def compile_candidate(path, code_address=CANDIDATE):
    subprocess.run([
        "clang++", "--target=i686-pc-windows-msvc", "-std=c++03", "-O2", "-mno-sse", "-mno-sse2",
        "-fno-exceptions", "-fno-rtti", "-fno-stack-protector", "-fno-builtin", "-ffunction-sections",
        "-c", str(ROOT / "matching2/reference/semantic_candidates/sound_primary_format.cpp"),
        "-o", str(path)], check=True, timeout=60)
    return load_module(path, code_address, {})


def execute(image, module, case):
    uc = Uc(UC_ARCH_X86, UC_MODE_32)
    uc.mem_map(0x400000, 0x100000)
    for section in image.sections:
        uc.mem_write(section["address"], image.read(section["address"], section["raw_size"]))
    for address in (CANDIDATE, STACK, STOP, STATE):
        uc.mem_map(address, 0x10000)
    if module:
        uc.mem_write(module.base, module.data)

    def words(address, *values):
        uc.mem_write(address, struct.pack("<" + "I" * len(values), *(v & 0xFFFFFFFF for v in values)))

    def read_words(address, count):
        return struct.unpack("<" + "I" * count, uc.mem_read(address, count * 4))

    def args(count):
        return read_words(uc.reg_read(UC_X86_REG_ESP) + 4, count)

    def finish(value, cleanup):
        sp = uc.reg_read(UC_X86_REG_ESP)
        uc.reg_write(UC_X86_REG_EIP, read_words(sp, 1)[0])
        uc.reg_write(UC_X86_REG_ESP, sp + 4 + cleanup)
        uc.reg_write(UC_X86_REG_EAX, value & 0xFFFFFFFF)

    words(OWNER, DEVICE if case.device_present else 0)
    words(DEVICE, DEVICE_TABLE)
    words(BUFFER, BUFFER_TABLE)
    words(OTHER, BUFFER_TABLE)
    words(DEVICE_TABLE + 12, CREATE)
    words(BUFFER_TABLE + 56, FORMAT)
    words(BUFFER_TABLE + 8, RELEASE)
    events, faults = [], []
    output_slot = None

    def hook(machine, address, size, context):
        nonlocal output_slot
        if address == CREATE:
            device, description, output_slot, outer = args(4)
            fields = read_words(description, 9)
            events.append(("create", device, fields, outer, read_words(output_slot, 1)[0]))
            assert fields == (36, 1, 0, 0, 0, 0, 0, 0, 0) and outer == 0
            assert read_words(output_slot, 1)[0] == 0
            words(output_slot, case.create_output)
            if case.clear_owner:
                words(OWNER, 0)
            finish(case.create_result, 16)
        elif address == FORMAT:
            buffer, format = args(2)
            raw_format = bytes(uc.mem_read(format, 18))
            events.append(("format", buffer, raw_format))
            alignment = (((case.bits & 0xFFFF) >> 3) * (case.channels & 0xFFFF)) & 0xFFFF
            assert raw_format == struct.pack("<HHIIHHH", 1, case.channels & 0xFFFF, case.rate,
                                              (alignment * case.rate) & 0xFFFFFFFF,
                                              alignment, case.bits & 0xFFFF, 0)
            if case.replace_output is not None:
                words(output_slot, case.replace_output)
            finish(case.format_result, 8)
        elif address == RELEASE:
            buffer, = args(1)
            events.append(("release", buffer))
            finish(0xBAD00001, 4)
        else:
            raise AssertionError(hex(address))

    def fault(machine, kind, address, size, value, context):
        faults.append((kind, address, size, value))
        return False

    for address in (CREATE, FORMAT, RELEASE):
        uc.hook_add(UC_HOOK_CODE, hook, begin=address, end=address)
    uc.hook_add(UC_HOOK_MEM_INVALID, fault)
    owner = OWNER if case.owner_present else 0
    arguments = [case.bits, case.channels, case.rate, owner] if module else [owner]
    sp = STACK + 0x8000
    words(sp, STOP, *arguments)
    uc.reg_write(UC_X86_REG_ESP, sp)
    preserved = dict(PRESERVED)
    if not module:
        preserved.update({UC_X86_REG_EBX: case.channels, UC_X86_REG_EDI: case.rate})
        uc.reg_write(UC_X86_REG_ECX, case.bits)
    for register, value in preserved.items():
        uc.reg_write(register, value)
    entry = module.symbols["_Sound_SetPrimaryFormat_0044c7e0@16"] if module else 0x44C7E0
    try:
        uc.emu_start(entry, STOP, count=10000)
    except UcError:
        if not faults:
            raise
    if not faults:
        assert uc.reg_read(UC_X86_REG_EIP) == STOP
        assert uc.reg_read(UC_X86_REG_ESP) == sp + 4 * (1 + len(arguments))
        assert all(uc.reg_read(register) == value for register, value in preserved.items())
    return {"result": uc.reg_read(UC_X86_REG_EAX) if not faults else None,
            "events": events, "faults": faults, "state": bytes(uc.mem_read(STATE, 0x2000))}


def cases():
    for owner, device, create, format in product((False, True), (False, True),
            (0, 1, 0x7FFFFFFF, -1, -0x80000000), (0, 1, 0x7FFFFFFF, -1, -0x80000000)):
        yield Case(owner_present=owner, device_present=device, create_result=create, format_result=format)
    for bits, channels, rate in product((0, 1, 7, 8, 16, 24, 32, 0xFFFF, 0xFFFF0010),
                                        (0, 1, 2, 0xFFFF, 0xFFFF0002),
                                        (0, 1, 44100, 0x7FFFFFFF, 0xFFFFFFFF)):
        yield Case(bits=bits, channels=channels, rate=rate)
    for result, output in product((0, 1, -1), (None, 0, OTHER)):
        yield Case(format_result=result, replace_output=output)
    yield Case(create_output=0)
    yield Case(clear_owner=True)
    randomizer = random.Random(0x44C7E0)
    for trial in range(100):
        yield Case(bits=randomizer.getrandbits(32), channels=randomizer.getrandbits(32), rate=randomizer.getrandbits(32))


def verify_observations(case, result):
    if result["faults"]:
        return
    events = result["events"]
    if not case.device_present:
        assert result["result"] == 0x800401F0 and not events
    elif case.create_result < 0:
        assert result["result"] == case.create_result & 0xFFFFFFFF
        assert [event[0] for event in events] == ["create"]
    elif case.format_result < 0:
        assert result["result"] == case.format_result & 0xFFFFFFFF
        assert [event[0] for event in events] == ["create", "format"]
    else:
        assert result["result"] == 0
        released = case.create_output if case.replace_output is None else case.replace_output
        assert [event for event in events if event[0] == "release"] == ([("release", released)] if released else [])


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--oracle", type=Path, default=ROOT / "matching2/build/oracle/th10.exe")
    options = parser.parse_args()
    config = load_manifest(ROOT / "matching2/msvc/regions.json")
    load_oracle(options.oracle, config)
    image = PEImage(options.oracle.read_bytes())
    with tempfile.TemporaryDirectory(prefix="th10-primary-format-") as temporary:
        module = compile_candidate(Path(temporary) / "primary.obj")
        count = faults = 0
        for case in cases():
            expected, actual = execute(image, None, case), execute(image, module, case)
            assert expected == actual, (case, expected, actual)
            verify_observations(case, actual)
            count += 1
            faults += bool(actual["faults"])
        print(f"PASS: {count} primary-format comparisons, including {faults} matching faults; "
              f"{len(module.data)} candidate bytes. Private ABI and native MSVC frame/bytes remain unverified.")


if __name__ == "__main__":
    main()
