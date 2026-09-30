#!/usr/bin/env python3
"""Compare the pending WAVE loader and compiled chunk walker with retail.

DirectSound calls, Sleep, logging and free are scripted. Both runs execute
the real CRT strncmp; candidate chunk traversal uses maintained C++ source.
No audio device, Windows dispatch or native MSVC byte match is claimed.
"""

import argparse
from dataclasses import dataclass
from itertools import product
from pathlib import Path
import random
import struct
import subprocess
import tempfile

from unicorn import (Uc, UcError, UC_ARCH_X86, UC_MODE_32, UC_HOOK_CODE,
                     UC_HOOK_MEM_READ, UC_HOOK_MEM_INVALID)
from unicorn.x86_const import (UC_X86_REG_EAX, UC_X86_REG_ECX, UC_X86_REG_EDX,
                              UC_X86_REG_EDI, UC_X86_REG_ESP, UC_X86_REG_EIP)
from lzss_compressor_differential import (
    ROOT, CANDIDATE, OUTPUT, STACK, STOP, PRESERVED, PEImage,
    load_manifest, load_oracle, load_candidate, region_directory)
from coff_module import load_module

STATE, DATA = 0x2500000, 0x2600000
MANAGER, NAME = STATE + 0x100, STATE + 0x9000
DEVICE, OLD, BUFFER, OTHER = (STATE + 0x8000 + i * 0x100 for i in range(4))
DEVICE_TABLE, BUFFER_TABLE = STATE + 0x8800, STATE + 0x8900
WAVE, ALTERNATE = DATA + 0x1000, DATA + 0x8000
CHUNK = CANDIDATE + 0x8000
SLEEP, RELEASE, CREATE, LOCK, UNLOCK, LOG = (STOP + 0x100 + i * 0x100 for i in range(6))
OTHER_SLEEP = STOP + 0x700
SHUTDOWN = 0x4977B4


@dataclass(frozen=True)
class Wave:
    label: str
    data: bytes
    pcm_offset: int = 0
    pcm_size: int = 0


def chunk(tag, payload):
    return tag + struct.pack("<I", len(payload)) + payload


def wave(label="normal", pcm=bytes(range(37)), format_size=18, prefix=b"", complete_count=False):
    format = struct.pack("<HHIIHHH", 1, 2, 44100, 176400, 4, 16, 0)
    format = (format + bytes(range(32)))[:format_size]
    body = prefix + chunk(b"fmt ", format) + chunk(b"data", pcm)
    data = b"RIFF" + struct.pack("<I", len(body) + (12 if complete_count else 4)) + b"WAVE" + body
    return Wave(label, data, 12 + len(prefix) + 8 + len(format) + 8, len(pcm))


@dataclass(frozen=True)
class Case:
    source: Wave = wave()
    index: int = 0
    enabled: bool = True
    old_buffer: bool = True
    ready_after: int = 0
    cancel_after: object = None
    initial_shutdown: int = 0
    handoff_clear: bool = False
    release_changes_pending: bool = False
    create_result: int = 0
    create_output: int = BUFFER
    lock_result: int = 0
    first_bytes: object = None
    second_bytes: int = 0
    first_delta: object = None
    second_delta: object = None
    swap_slot_at: object = None
    change_description: bool = False
    free_changes_pending: bool = False
    change_sleep_import: bool = False


def compile_candidates(directory, config, extra_bindings=None, code_base=CANDIDATE):
    chunk_address = code_base + 0x8000
    bindings = region_directory(config, config["regions"])
    bindings.update({"_strncmp": 0x452F80, "_memcpy": 0x45BFC0,
                     "_entry_free_00452422": 0x452422, "_g_sound_sleep": 0x4660AC,
                     "_g_sound_shutdown_state": SHUTDOWN, "_g_wave_error_log": 0x474F70,
                     "_g_wave_invalid_riff_message": 0x46FD88,
                     "_g_wave_invalid_format_message": 0x46FD64,
                     "_g_wave_riff_tag": 0x46FDA4, "_g_wave_wave_tag": 0x46FD80,
                     "_g_wave_format_tag": 0x46FD5C, "_g_wave_data_tag": 0x46FD54,
                     "?Append@TextLog_0044b810@@QAAPADPADZZ": LOG,
                     "?Resource_FindChunk@@YAPBEPBEIQBDPAI@Z": chunk_address})
    bindings.update(extra_bindings or {})
    objects = {}
    for name, source in (("wave", ROOT / "matching2/reference/semantic_candidates/sound_wave_load.cpp"),
                         ("chunk", ROOT / "matching2/msvc/src/platform/resource_chunks.cpp")):
        obj = directory / (name + ".obj")
        subprocess.run([
            "clang++", "--target=i686-pc-windows-msvc", "-std=c++03", "-O2", "-mno-sse", "-mno-sse2",
            "-fno-exceptions", "-fno-rtti", "-fno-stack-protector", "-fno-builtin", "-ffunction-sections",
            "-I", str(ROOT / "matching2/msvc/include"), "-c", str(source), "-o", str(obj)],
            check=True, timeout=60)
        objects[name] = obj
    module = load_module(objects["wave"], code_base, bindings)
    body = load_candidate(objects["chunk"], config, "Resource_FindChunk", bindings, code_address=chunk_address)
    return module, {code_base: module.data, chunk_address: body}


def execute(image, compiled, case):
    module, bodies = compiled if compiled else (None, {})
    uc = Uc(UC_ARCH_X86, UC_MODE_32)
    uc.mem_map(0x400000, 0x100000)
    for section in image.sections:
        uc.mem_write(section["address"], image.read(section["address"], section["raw_size"]))
    for address in (CANDIDATE, OUTPUT, STACK, STOP, STATE, DATA):
        uc.mem_map(address, 0x10000)
    for address, body in bodies.items():
        uc.mem_write(address, body)

    def words(address, *values):
        uc.mem_write(address, struct.pack("<" + "I" * len(values), *(v & 0xFFFFFFFF for v in values)))

    def read_words(address, count):
        return struct.unpack("<" + "I" * count, uc.mem_read(address, count * 4))

    def args(count):
        return read_words(uc.reg_read(UC_X86_REG_ESP) + 4, count)

    def finish(value, cleanup=0):
        sp = uc.reg_read(UC_X86_REG_ESP)
        uc.reg_write(UC_X86_REG_EIP, read_words(sp, 1)[0])
        uc.reg_write(UC_X86_REG_ESP, sp + 4 + cleanup)
        uc.reg_write(UC_X86_REG_EAX, value & 0xFFFFFFFF)

    def string(address):
        result = bytearray()
        while True:
            byte = uc.mem_read(address + len(result), 1)[0]
            if not byte:
                return bytes(result)
            result.append(byte)
            assert len(result) < 512

    slot = MANAGER + 8 + case.index * 4
    pending = MANAGER + 0x5230 + case.index * 4
    uc.mem_write(MANAGER, b"\xA5" * 0x5400)
    uc.mem_write(DATA, b"\xA5" * 0x10000)
    uc.mem_write(OUTPUT, b"\xA5" * 0x10000)
    uc.mem_write(WAVE, case.source.data)
    uc.mem_write(ALTERNATE, case.source.data)
    uc.mem_write(NAME, b"se_test.wav\0")
    words(MANAGER, DEVICE)
    words(MANAGER + 0x610, 0x1234 if case.enabled else 0)
    words(slot, OLD if case.old_buffer else 0)
    words(pending, WAVE if case.ready_after == 0 else 0)
    words(SHUTDOWN, case.initial_shutdown)
    words(0x4660AC, SLEEP)
    words(DEVICE, DEVICE_TABLE)
    for address in (OLD, BUFFER, OTHER):
        words(address, BUFFER_TABLE)
    words(DEVICE_TABLE + 12, CREATE)
    for offset, address in ((8, RELEASE), (44, LOCK), (76, UNLOCK)):
        words(BUFFER_TABLE + offset, address)
    events, faults, reads = [], [], []
    sleeps = 0

    def state():
        return read_words(slot, 1)[0], read_words(pending, 1)[0]

    def swap(stage):
        if case.swap_slot_at == stage:
            words(slot, OTHER)

    def hook(machine, address, size, context):
        nonlocal sleeps
        if address in (SLEEP, OTHER_SLEEP):
            milliseconds, = args(1)
            events.append(("sleep" if address == SLEEP else "changed-sleep", milliseconds, state()))
            assert milliseconds == 10
            sleeps += 1
            assert sleeps <= 8, "fixture did not publish/cancel"
            if case.change_sleep_import:
                words(0x4660AC, OTHER_SLEEP)
            if sleeps == case.ready_after:
                words(pending, WAVE)
            if sleeps == case.cancel_after:
                words(SHUTDOWN, 2)
            finish(0xBAD00001, 4)
        elif address == RELEASE:
            buffer, = args(1)
            events.append(("release", buffer, state()))
            swap("release")
            if case.release_changes_pending:
                words(pending, ALTERNATE)
            finish(17, 4)
        elif address in (0x43D250, CHUNK):
            if address == CHUNK:
                data, available, tag, out_size = args(4)
            else:
                tag, = args(1)
                data, available, out_size = (uc.reg_read(register) for register in
                                             (UC_X86_REG_ECX, UC_X86_REG_EAX, UC_X86_REG_EDI))
            events.append(("chunk", data, available, bytes(uc.mem_read(tag, 4)), state()))
        elif address == CREATE:
            device, description, output, outer = args(4)
            fields = read_words(description, 9)
            format = bytes(uc.mem_read(fields[4], 18))
            events.append(("create", device, fields[:4], fields[5:], format, output, outer, state()))
            assert fields[0:2] == (36, 0x80C8) and fields[3] == 0 and fields[5:] == (0, 0, 0, 0)
            assert output == slot and outer == 0
            words(output, case.create_output)
            swap("create")
            if case.change_description:
                words(description + 8, 0xF00DF00D)
            finish(case.create_result, 16)
        elif address == LOCK:
            buffer, offset, count, first, first_size, second, second_size, flags = args(8)
            first_count = case.source.pcm_size if case.first_bytes is None else case.first_bytes
            source = (ALTERNATE if case.release_changes_pending else WAVE) + case.source.pcm_offset
            first_target = OUTPUT + 0x1000 if case.first_delta is None else source + case.first_delta
            second_target = OUTPUT + 0x5000 if case.second_delta is None else source + case.second_delta
            events.append(("lock", buffer, offset, count, flags, first_target, first_count,
                           second_target, case.second_bytes, state()))
            words(first, first_target)
            words(first_size, first_count)
            words(second, second_target)
            words(second_size, case.second_bytes)
            swap("lock")
            finish(case.lock_result, 32)
        elif address == UNLOCK:
            buffer, first, first_size, second, second_size = args(5)
            events.append(("unlock", buffer, first, first_size, second, second_size,
                           bytes(uc.mem_read(first, first_size)), bytes(uc.mem_read(second, second_size)), state()))
            swap("unlock")
            finish(0x80004005, 20)
        elif address in (LOG, 0x44B810):
            if address == LOG:
                log, format, filename = args(3)
            else:
                log = uc.reg_read(UC_X86_REG_ECX)
                format, filename = args(2)
            events.append(("log", log, format, string(filename), state()))
            finish(0xBAD00002)
        elif address == 0x452422:
            allocation, = args(1)
            events.append(("free", allocation, state()))
            swap("free")
            if case.free_changes_pending:
                words(pending, ALTERNATE)
            finish(0xBAD00003)
        else:
            raise AssertionError(hex(address))

    def pending_read(machine, kind, address, size, value, context):
        if case.handoff_clear and len(reads) == 1:
            words(pending, 0)
        reads.append(read_words(pending, 1)[0])

    def fault(machine, kind, address, size, value, context):
        faults.append((kind, address, size, value))
        return False

    for address in (SLEEP, OTHER_SLEEP, RELEASE, CREATE, LOCK, UNLOCK, LOG, 0x44B810, 0x452422, 0x43D250, CHUNK):
        uc.hook_add(UC_HOOK_CODE, hook, begin=address, end=address)
    uc.hook_add(UC_HOOK_MEM_READ, pending_read, begin=pending, end=pending + 3)
    uc.hook_add(UC_HOOK_MEM_INVALID, fault)
    sp = STACK + 0x8000
    words(sp, STOP, NAME)
    uc.reg_write(UC_X86_REG_ESP, sp)
    uc.reg_write(UC_X86_REG_ECX, case.index)
    uc.reg_write(UC_X86_REG_EDX, MANAGER)
    for register, value in PRESERVED.items():
        uc.reg_write(register, value)
    entry = module.symbols["@SoundWave_LoadPending_0043d390@12"] if module else 0x43D390
    try:
        uc.emu_start(entry, STOP, count=2000000)
    except UcError:
        if not faults:
            raise
    if not faults:
        assert uc.reg_read(UC_X86_REG_EIP) == STOP, "instruction budget exhausted"
        assert uc.reg_read(UC_X86_REG_ESP) == sp + 8
        assert all(uc.reg_read(register) == value for register, value in PRESERVED.items())
    return {"result": uc.reg_read(UC_X86_REG_EAX) if not faults else None,
            "events": events, "faults": faults, "pending_reads": reads,
            "manager": bytes(uc.mem_read(MANAGER, 0x5400)),
            "wave": bytes(uc.mem_read(DATA, 0x10000)),
            "output": bytes(uc.mem_read(OUTPUT, 0x10000)),
            "shutdown": read_words(SHUTDOWN, 1)[0]}


def cases():
    for enabled, old, ready, shutdown, index in product((False, True), (False, True),
            (0, 1, 3), (0, 1, 2, 3), (0, 1, 36)):
        yield Case(enabled=enabled, old_buffer=old, ready_after=ready,
                   initial_shutdown=shutdown, index=index)
    for ready, cancel in product((1, 2, 3), (1, 2)):
        yield Case(ready_after=ready, cancel_after=cancel)
    yield Case(handoff_clear=True)
    yield Case(release_changes_pending=True)
    for create, lock in product((0, 1, 0x7FFFFFFF, -1, -0x80000000), repeat=2):
        yield Case(create_result=create, lock_result=lock)
    yield Case(create_output=0)
    for stage in ("release", "create", "lock", "unlock", "free"):
        yield Case(swap_slot_at=stage)
    yield Case(change_description=True)
    yield Case(free_changes_pending=True)
    yield Case(ready_after=3, change_sleep_import=True)
    for size in (*range(10), 17, 31, 32, 33, 255, 8193):
        for split in (0, size // 2, size):
            source = wave(f"split-{size}-{split}", bytes(i & 255 for i in range(size)), complete_count=True)
            yield Case(source=source, first_bytes=split, second_bytes=size - split)
    for first, second in product((0, 1, 3, 4, 7, 40), (0, 1, 3, 9)):
        yield Case(first_bytes=first, second_bytes=second)
    for first, second in product((0, -3, -1, 1, 3, 4, 7), (None, 0, 1, 4, 9)):
        yield Case(first_bytes=11, second_bytes=13, first_delta=first, second_delta=second)
    for size in (*range(19), 24, 32):
        yield Case(source=wave(f"fmt-{size}", format_size=size))
    for prefix_size in (0, 1, 2, 3, 4, 7, 8, 15):
        yield Case(source=wave(f"unknown-{prefix_size}", prefix=chunk(b"JUNK", b"x" * prefix_size)))
    for source in (Wave("bad-riff", b"NOPE"), Wave("bad-wave", b"RIFF" + struct.pack("<I", 12) + b"NOPE"),
                   Wave("empty-chunks", b"RIFF" + struct.pack("<I", 12) + b"WAVE"),
                   wave("empty-pcm-conventional", pcm=b"")):
        yield Case(source=source)
    for tag in (b"fmt ", b"data", b"JUNK"):
        body = chunk(tag, bytes(range(18)))
        yield Case(source=Wave("missing-" + tag.decode(), b"RIFF" + struct.pack("<I", len(body) + 12) + b"WAVE" + body))
    for counter in (0, 1, 4, 8, 11, 13, 0xFFFFFFFF):
        yield Case(source=Wave("underflow-" + str(counter), b"RIFF" + struct.pack("<I", counter) + b"WAVE"))
    randomizer = random.Random(0x43D390)
    for trial in range(60):
        payload = randomizer.randbytes(randomizer.randrange(1, 2048))
        split = randomizer.randrange(len(payload) + 1)
        yield Case(source=wave(f"random-{trial}", payload, randomizer.randrange(32)),
                   first_bytes=split, second_bytes=len(payload) - split, old_buffer=bool(trial & 1))


def verify_observations(case, result):
    events = result["events"]
    assert not any(event[0] == "changed-sleep" for event in events), "Sleep import must stay cached"
    if not case.enabled:
        assert result["result"] == 0 and not events and not result["pending_reads"]
        return
    for event in events:
        if event[0] == "chunk":
            stored_size, = struct.unpack_from("<I", case.source.data, 4)
            assert event[2] == (stored_size - 12) & 0xFFFFFFFF
    if case.handoff_clear:
        assert result["result"] == 0xFFFFFFFF and result["pending_reads"] == [WAVE, 0]
        assert not any(event[0] in ("log", "free", "chunk") for event in events)
    creation = next((event for event in events if event[0] == "create"), None)
    if creation:
        # Find the packed fixture's fmt bytes independently, then require the
        # full 18-byte snapshot even when the chunk's declared size is smaller.
        offset = 12
        while case.source.data[offset:offset + 4] != b"fmt ":
            length, = struct.unpack_from("<I", case.source.data, offset + 4)
            offset += 8 + length
        expected_format = (case.source.data[offset + 8:] + b"\xA5" * 18)[:18]
        assert creation[4] == expected_format
        assert creation[2][2] == case.source.pcm_size
    locked = next((event for event in events if event[0] == "lock"), None)
    if locked:
        assert locked[2:5] == (0, case.source.pcm_size, 0)
    unlocked = next((event for event in events if event[0] == "unlock"), None)
    if unlocked and case.first_delta is None and case.second_delta is None:
        available = case.source.data[case.source.pcm_offset:] + b"\xA5" * 128
        first_size, second_size = unlocked[3], unlocked[5]
        assert unlocked[6] == available[:first_size]
        assert unlocked[7] == available[first_size:first_size + second_size]
    if unlocked:
        assert result["result"] == 0, "Unlock failure must be ignored"
        if case.swap_slot_at == "lock":
            assert unlocked[1] == OTHER, "Unlock must reload the manager slot"
    frees = [event for event in events if event[0] == "free"]
    if frees:
        assert len(frees) == 1 and frees[0][1] == (ALTERNATE if case.release_changes_pending else WAVE)
    if creation and not result["faults"]:
        assert len(frees) == 1, "Create/Lock failures must also release the wave"


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--oracle", type=Path, default=ROOT / "matching2/build/oracle/th10.exe")
    options = parser.parse_args()
    config = load_manifest(ROOT / "matching2/msvc/regions.json")
    load_oracle(options.oracle, config)
    image = PEImage(options.oracle.read_bytes())
    with tempfile.TemporaryDirectory(prefix="th10-wave-load-") as temporary:
        compiled = compile_candidates(Path(temporary), config)
        comparisons = faults = 0
        for index, case in enumerate(cases()):
            expected = execute(image, None, case)
            actual = execute(image, compiled, case)
            differences = tuple(key for key in expected if expected[key] != actual[key])
            assert not differences, (index, case, differences, expected["events"], actual["events"],
                                     expected["faults"], actual["faults"], expected["pending_reads"], actual["pending_reads"])
            verify_observations(case, actual)
            comparisons += 1
            faults += bool(expected["faults"])
        print(f"PASS: {comparisons} pending-WAVE loader comparisons, including {faults} matching faults; "
              f"{len(compiled[0].data)} candidate module bytes and {len(compiled[1][CHUNK])} chunk-walker bytes. "
              "Native MSVC frame/byte matching and live audio remain unverified.")


if __name__ == "__main__":
    main()
