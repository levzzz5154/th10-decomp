#!/usr/bin/env python3
"""Execute DAT decoding, sound preload publication and WAVE consumption together.

The cached-archive loader and chunk walker are freshly compiled maintained
C++; the other recovered bodies are semantic candidates. Only allocation,
file/COM operations, critical-section imports, Sleep and logging are scripted.
A register/stack adapter connects the cached loader to the DAT read candidate.
The schedule publishes all available buffers before consuming them; this is
not a Windows thread scheduler or a native MSVC byte-equivalence test.
"""

import argparse
from dataclasses import dataclass
from pathlib import Path
import struct
import subprocess
import tempfile

from unicorn import UC_HOOK_CODE
from unicorn.x86_const import UC_X86_REG_EAX, UC_X86_REG_ECX, UC_X86_REG_EDX, UC_X86_REG_ESP, UC_X86_REG_EIP
from dat_archive_integration_differential import (
    Execution, Entry, fixture, compile_modules, ROOT, CANDIDATE, OUTPUT, STATE,
    STOP, READ, PEImage, load_manifest, load_oracle, load_candidate)
from sound_preload_worker_differential import (
    compile_candidates as compile_preload, GLOBAL, NAMES, SHUTDOWN, PENDING)
from sound_wave_load_differential import compile_candidates as compile_wave, wave

CACHE, PRODUCER, CONSUMER = CANDIDATE + 0x10000, CANDIDATE + 0x20000, CANDIDATE + 0x30000
READ_ADAPTER, READ_RETURN = CANDIDATE + 0xB200, CANDIDATE + 0xB300
ARCHIVE = 0x497990
ENTER, LEAVE, LOG, SLEEP, CREATE, LOCK, UNLOCK, RELEASE = (STOP + 0x100 * i for i in range(1, 9))
DEVICE, OWNER, BUFFER_TABLE, DEVICE_TABLE = (STATE + i for i in (0x4000, 0x4100, 0x4200, 0x4300))
BUFFERS, PATHS = STATE + 0x5000, STATE + 0x9000
DEPTH, CRITICAL = 0x49231E, 0x4922A4


@dataclass(frozen=True)
class Case:
    label: str = "all-mixed"
    compression: str = "mixed"
    missing: object = None
    empty: object = None
    allocation_failure: object = None
    reader_allocation_failure: object = None
    stop_after: object = None
    initial_shutdown: int = 1
    sleep_count: int = 1
    path_style: str = "plain"
    depth: int = 0
    consumer_failure: object = None


def compile_candidates(directory, config):
    modules = compile_modules(directory, config)
    obj = directory / "cached-archive-load.obj"
    subprocess.run([
        "clang++", "--target=i686-pc-windows-msvc", "-std=c++03", "-O2", "-mno-sse", "-mno-sse2",
        "-fno-exceptions", "-fno-rtti", "-fno-stack-protector", "-fno-builtin", "-ffunction-sections",
        "-I", str(ROOT / "matching2/msvc/include"), "-c",
        str(ROOT / "matching2/msvc/src/platform/fun_0044b360_0044b360.cpp"), "-o", str(obj)],
        check=True, timeout=60)
    bindings = {"?Read@ArchiveReader@@QAEPADPBXPAD@Z": READ_ADAPTER}
    bindings.update((f"_data_{address:08x}", address) for address in (
        0x497990, 0x497994, DEPTH, CRITICAL, 0x4660B0, 0x4660B4, 0x4660C4,
        0x4660CC, 0x4660D0, 0x4660D8))
    modules[CACHE] = load_candidate(obj, config, "Archive_LoadFile", bindings, code_address=CACHE)
    producers = compile_preload(directory, config, PRODUCER, {
        "_Archive_LoadFile@12": CACHE, "?Append@TextLog_0044b810@@QAAPADPADZZ": LOG})
    modules.update((module.base, module.data) for module in producers.values())
    consumer, bodies = compile_wave(directory, config, {
        "?Append@TextLog_0044b810@@QAAPADPADZZ": LOG}, code_base=CONSUMER)
    modules.update(bodies)
    return modules, producers, consumer


def names_from_image(image):
    return tuple(image.read(struct.unpack("<I", image.read(NAMES + 4 * i, 4))[0], 128).split(b"\0")[0]
                 for i in range(37))


def make_fixture(case, names, parameters):
    waves = tuple(wave(str(i), bytes((j * 17 + i) & 255 for j in range(9 + i * 5)),
                       format_size=16 if i & 1 else 18) for i in range(37))
    entries = [Entry(name, b"" if i == case.empty else waves[i].data,
                     i != case.empty and (case.compression == "all" or
                                           (case.compression == "mixed" and i & 1)))
               for i, name in enumerate(names) if i != case.missing]
    return fixture(case.label, entries, parameters), waves


class PreloadExecution(Execution):
    def __init__(self, image, modules, producers, consumer, source, waves, names, case):
        self.producers, self.consumer, self.case = producers, consumer, case
        self.waves, self.names = waves, names
        self.read_frames = []
        self.cached_calls = []
        self.current_load = None
        self.current_consumer = None
        self.sleeps = 0
        super().__init__(image, modules, source, archive_address=ARCHIVE)
        uc = self.uc
        uc.mem_write(GLOBAL, bytes(0x5400))
        uc.mem_write(OUTPUT, b"\xA5" * 0x10000)
        uc.mem_write(DEPTH, bytes([case.depth]))
        self.words(SHUTDOWN, case.initial_shutdown)
        self.words(GLOBAL, DEVICE)
        self.words(GLOBAL + 0x610, OWNER)
        self.words(OWNER, DEVICE)
        self.words(DEVICE, DEVICE_TABLE)
        self.words(DEVICE_TABLE + 12, CREATE)
        for offset, address in ((8, RELEASE), (44, LOCK), (76, UNLOCK)):
            self.words(BUFFER_TABLE + offset, address)
        for index, name in enumerate(names):
            if case.path_style == "forward":
                name = b"directory/" + name.swapcase()
            elif case.path_style == "backward":
                name = b"directory\\" + name
            elif case.path_style == "mixed":
                name = b"before\\directory/" + name.swapcase()
            elif case.path_style == "forward-before-backward":
                name = b"directory/before\\" + name
            address = PATHS + index * 128
            uc.mem_write(address, name + b"\0")
            self.words(NAMES + index * 4, address)
            self.words(BUFFERS + index * 16, BUFFER_TABLE)
        for slot, address in ((0x4660B0, ENTER), (0x4660B4, LEAVE), (0x4660AC, SLEEP)):
            self.words(slot, address)
        for address in (CACHE, 0x44B360, READ_ADAPTER, READ_RETURN, ENTER, LEAVE, LOG,
                        0x44B810, SLEEP, CREATE, LOCK, UNLOCK, RELEASE):
            uc.hook_add(UC_HOOK_CODE, self.hook, begin=address, end=address)

    def read_words(self, address, count=1):
        return struct.unpack("<" + "I" * count, self.uc.mem_read(address, count * 4))

    def hook(self, uc, address, size, context):
        if address in (CACHE, 0x44B360):
            if address == CACHE:
                name, out_size, mode = self.args(3)
            else:
                name = uc.reg_read(UC_X86_REG_EAX)
                out_size, mode = self.args(2)
            self.current_load = len(self.cached_calls)
            self.cached_calls.append((self.string(name), bool(out_size), mode))
            assert out_size == mode == 0
            if self.current_load == self.case.allocation_failure:
                self.fail_allocation = len(self.allocations)
            elif self.current_load == self.case.reader_allocation_failure:
                # The cached loader's output allocation succeeds, but the
                # compressed reader's next (stored-byte) allocation fails.
                self.fail_allocation = len(self.allocations) + 1
        elif address == READ_ADAPTER:
            archive, output = self.args(2)
            name = uc.reg_read(UC_X86_REG_ECX)
            sp = uc.reg_read(UC_X86_REG_ESP)
            self.read_frames.append((sp, self.read_words(sp)[0]))
            self.words(sp - 4, READ_RETURN, archive, name, output)
            uc.reg_write(UC_X86_REG_ESP, sp - 4)
            uc.reg_write(UC_X86_REG_EIP, READ)
        elif address == READ_RETURN:
            sp, ret = self.read_frames.pop()
            assert uc.reg_read(UC_X86_REG_ESP) == sp + 12
            uc.reg_write(UC_X86_REG_EIP, ret)
        elif address in (ENTER, LEAVE):
            critical, = self.args(1)
            depth = uc.mem_read(DEPTH, 1)[0]
            self.events.append(("enter" if address == ENTER else "leave", critical, depth))
            assert critical == CRITICAL
            assert depth == (self.case.depth + int(address == LEAVE)) & 255
            if address == LEAVE and self.current_load == self.case.stop_after:
                self.words(SHUTDOWN, 2)
            self.finish(0xBAD00001, 4)
        elif address in (LOG, 0x44B810):
            if address == LOG:
                log, format, name = self.args(3)
            else:
                log = uc.reg_read(UC_X86_REG_ECX)
                format, name = self.args(2)
            self.events.append(("log", log, format, self.string(name)))
            self.finish(0xBAD00002)
        elif address == SLEEP:
            milliseconds, = self.args(1)
            assert milliseconds == 1 and self.current_consumer is None
            self.sleeps += 1
            self.events.append(("sleep", milliseconds))
            assert self.sleeps <= self.case.sleep_count
            if self.sleeps == self.case.sleep_count:
                self.words(SHUTDOWN, 1)
            self.finish(0xBAD00003, 4)
        elif address == CREATE:
            device, desc, output, outer = self.args(4)
            fields = self.read_words(desc, 9)
            format = bytes(uc.mem_read(fields[4], 18))
            index = self.current_consumer
            source = self.waves[index]
            assert (device, output, outer) == (DEVICE, GLOBAL + 8 + index * 4, 0)
            assert fields[:4] == (36, 0x80C8, source.pcm_size, 0) and fields[5:] == (0, 0, 0, 0)
            assert format == source.data[20:38]
            self.events.append(("create-buffer", index, fields[:4], format))
            self.words(output, BUFFERS + index * 16)
            self.finish(0x80004005 if self.case.consumer_failure == (index, "create") else 0, 16)
        elif address == LOCK:
            buffer, offset, count, first, first_size, second, second_size, flags = self.args(8)
            index = self.current_consumer
            assert (buffer, offset, count, flags) == (BUFFERS + index * 16, 0, self.waves[index].pcm_size, 0)
            split = count * (index % 3) // 2
            self.words(first, OUTPUT + index * 0x400 + 32)
            self.words(first_size, split)
            self.words(second, OUTPUT + index * 0x400 + 0x220)
            self.words(second_size, count - split)
            self.events.append(("lock-buffer", index, count, split))
            self.finish(0x80004005 if self.case.consumer_failure == (index, "lock") else 0, 32)
        elif address == UNLOCK:
            buffer, first, first_size, second, second_size = self.args(5)
            index = self.current_consumer
            source = self.waves[index]
            assert buffer == BUFFERS + index * 16
            data = bytes(uc.mem_read(first, first_size)) + bytes(uc.mem_read(second, second_size))
            assert data == source.data[source.pcm_offset:source.pcm_offset + source.pcm_size]
            for pointer, count in ((first, first_size), (second, second_size)):
                assert bytes(uc.mem_read(pointer - 16, 16)) == b"\xA5" * 16
                assert bytes(uc.mem_read(pointer + count, 16)) == b"\xA5" * 16
            self.events.append(("unlock-buffer", index, first_size, second_size, data))
            self.finish(0x80004005, 20)  # ignored by both bodies
        elif address == RELEASE:
            buffer, = self.args(1)
            self.events.append(("release-buffer", buffer))
            self.finish(0, 4)
        else:
            super().hook(uc, address, size, context)

    def produce(self):
        entry = (self.producers["sound_preload_worker"].symbols["_Sound_PreloadWorker_0043d080@0"]
                 if self.recovered else 0x43D080)
        self.call(entry, [])
        assert not self.read_frames
        assert self.uc.mem_read(DEPTH, 1)[0] == self.case.depth
        return self.read_words(PENDING, 37)

    def consume(self, index):
        self.current_consumer = index
        entry = self.consumer.symbols["@SoundWave_LoadPending_0043d390@12"] if self.recovered else 0x43D390
        result = self.call(entry, [PATHS + index * 128], {UC_X86_REG_ECX: index, UC_X86_REG_EDX: GLOBAL})
        assert self.read_words(PENDING + index * 4)[0] == 0
        self.current_consumer = None
        return result

    def load_slot(self, index):
        name = PATHS + index * 128
        if self.recovered:
            entry = self.producers["unassigned_0043d640"].symbols["_Sound_LoadPendingSlot_0043d640@12"]
            result = self.call(entry, [name, GLOBAL, index])
        else:
            result = self.call(0x43D640, [GLOBAL, index], {UC_X86_REG_EAX: name})
        assert not self.read_frames
        return result

    def snapshot(self):
        result = super().snapshot()
        result.update(manager=bytes(self.uc.mem_read(GLOBAL, 0x5400)),
                      output=bytes(self.uc.mem_read(OUTPUT, 0x10000)),
                      depth=self.uc.mem_read(DEPTH, 1)[0],
                      cached_calls=tuple(self.cached_calls), sleeps=self.sleeps)
        return result


def compare(retail, recovered, label):
    expected, actual = retail.snapshot(), recovered.snapshot()
    differences = tuple(key for key in expected if expected[key] != actual[key])
    assert not differences, (label, differences)


def cases():
    for compression in ("none", "mixed", "all"):
        yield Case(label="all-" + compression, compression=compression)
    for style in ("forward", "backward", "mixed", "forward-before-backward"):
        yield Case(label="path-" + style, path_style=style)
    yield Case(label="depth-wrap", depth=255)
    yield Case(label="final-wait", initial_shutdown=0, sleep_count=3)
    yield Case(label="already-stopped", initial_shutdown=2)
    for index in (0, 1, 18, 36):
        yield Case(label="missing-" + str(index), missing=index)
        yield Case(label="empty-" + str(index), empty=index)
        yield Case(label="allocation-" + str(index), allocation_failure=index)
        yield Case(label="stop-" + str(index), stop_after=index)
    for stage in ("create", "lock"):
        yield Case(label="consumer-failure-" + stage, consumer_failure=(18, stage))
    for index in (1, 18, 36):
        yield Case(label="reader-allocation-" + str(index), compression="all", reader_allocation_failure=index)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--oracle", type=Path, default=ROOT / "matching2/build/oracle/th10.exe")
    options = parser.parse_args()
    config = load_manifest(ROOT / "matching2/msvc/regions.json")
    load_oracle(options.oracle, config)
    image = PEImage(options.oracle.read_bytes())
    names = names_from_image(image)
    parameters = [struct.unpack("<BB2xii", image.read(0x474BD8 + index * 12, 12)) for index in range(8)]
    with tempfile.TemporaryDirectory(prefix="th10-sound-archive-") as temporary:
        modules, producers, consumer = compile_candidates(Path(temporary), config)
        scenarios = loads = consumes = slots = 0
        for case in cases():
            source, waves = make_fixture(case, names, parameters)
            retail = PreloadExecution(image, {}, {}, None, source, waves, names, case)
            recovered = PreloadExecution(image, modules, producers, consumer, source, waves, names, case)
            assert retail.open("disk") == recovered.open("disk") == 1
            for execution in (retail, recovered):
                execution.verify_index("disk")
            compare(retail, recovered, (case.label, "open"))
            pending = retail.produce()
            assert recovered.produce() == pending
            compare(retail, recovered, (case.label, "producer"))
            for index, pointer in enumerate(pending):
                if not pointer:
                    continue
                for execution in (retail, recovered):
                    expected_data = (b"\xA5" * len(waves[index].data) if case.reader_allocation_failure == index
                                     else waves[index].data)
                    assert bytes(execution.uc.mem_read(pointer, len(waves[index].data))) == expected_data
                    assert not any(event == ("free", pointer) for event in execution.events)
                failed = (case.reader_allocation_failure == index or
                          (case.consumer_failure and case.consumer_failure[0] == index))
                expected = 0xFFFFFFFF if failed else 0
                assert retail.consume(index) == recovered.consume(index) == expected
                compare(retail, recovered, (case.label, "consumer", index))
                for execution in (retail, recovered):
                    assert execution.events.count(("free", pointer)) == 1
                consumes += 1
            if case.label == "all-mixed":
                # Reload populated secondary slots through the single-slot
                # helper. A second publication overwrites an unconsumed wave
                # without releasing that older archive allocation.
                for index in (0, 1, 18, 36):
                    assert retail.load_slot(index) == recovered.load_slot(index) == 0
                    slots += 1
                    old = retail.read_words(PENDING + index * 4)[0]
                    compare(retail, recovered, ("slot", index))
                    if index == 0:
                        assert retail.load_slot(index) == recovered.load_slot(index) == 0
                        slots += 1
                        compare(retail, recovered, ("slot-overwrite", index))
                        assert retail.read_words(PENDING)[0] != old
                        for execution in (retail, recovered):
                            assert ("free", old) not in execution.events
                    pointer = retail.read_words(PENDING + index * 4)[0]
                    assert retail.consume(index) == recovered.consume(index) == 0
                    compare(retail, recovered, ("slot-consumer", index))
                    for execution in (retail, recovered):
                        assert execution.events.count(("free", pointer)) == 1
                    consumes += 1
            loads += len(retail.cached_calls)
            for execution in (retail, recovered):
                execution.close()
            compare(retail, recovered, (case.label, "close"))
            scenarios += 1
        print(f"PASS: {scenarios} DAT/sound producer-consumer scenarios; {loads} actual cached-archive loads, "
              f"{consumes} actual WAVE handoffs, {slots} direct slot loads and {scenarios} archive cleanup calls "
              "agree with retail. "
              "Native MSVC byte matching, Windows threads and live audio remain unverified.")


if __name__ == "__main__":
    main()
