#!/usr/bin/env python3
"""Run archived WAVE production/consumption through recovered sound shutdown.

The preceding archive integration provides actual DAT parsing, decryption,
decompression and WAVE copying. This extends its sequential schedule through
cleanup, MIDI stop and the maintained interface aggregator. OS, allocation and
COM boundaries remain scripted; this is not live audio or Windows dispatch.
"""

import argparse
from dataclasses import dataclass
from itertools import product
from pathlib import Path
import struct
import tempfile

from unicorn import UC_HOOK_CODE
from unicorn.x86_const import UC_X86_REG_EAX, UC_X86_REG_ECX
import sound_archive_preload_integration as preload
from sound_shutdown_differential import compile_candidates as compile_shutdown

SHUTDOWN_BASE = preload.CANDIDATE + 0x40000
CLEANUP = SHUTDOWN_BASE + 0x2000
AGGREGATE = SHUTDOWN_BASE + 0x8000
STREAM, MIDI, MIDI_TABLE, AGG_TABLE, ENTRIES = (preload.STATE + 0x6000 + i * 0x100 for i in range(5))
KILL, STOP_STREAM, DESTROY, POST, WAIT, CLOSE, AGG_STOP, AGG_QUERY = (
    preload.STOP + 0x900 + i * 0x100 for i in range(8))


@dataclass(frozen=True)
class Case:
    consumed: int = 0
    midi: bool = False
    thread: bool = False
    owner: bool = True
    stop_after: object = None


class LifecycleExecution(preload.PreloadExecution):
    def __init__(self, image, modules, producers, consumer, cleanup_entry, source, waves, names, case):
        parent_case = preload.Case(stop_after=case.stop_after)
        super().__init__(image, modules, producers, consumer, source, waves, names, parent_case)
        self.lifecycle = case
        self.cleanup_entry = cleanup_entry
        self.wait_count = 0
        self.words(STREAM, preload.BUFFER_TABLE)
        self.words(preload.BUFFER_TABLE + 72, STOP_STREAM)
        self.words(preload.DEVICE_TABLE + 8, preload.RELEASE)
        self.words(preload.GLOBAL + 0x608, STREAM)
        self.words(preload.GLOBAL + 0x614, 0x1234)
        self.words(preload.GLOBAL + 0x618, 0x12345678 if case.thread else 0)
        self.words(preload.GLOBAL + 0x5208, MIDI if case.midi else 0)
        self.words(preload.GLOBAL + 0x520C, 0xCC001122)
        self.words(MIDI, MIDI_TABLE, ENTRIES)
        self.words(MIDI + 0x10, 2)
        self.words(MIDI + 0x1C, 1)
        self.words(MIDI + 0x30, 1)
        self.words(MIDI_TABLE, DESTROY)
        self.words(AGG_TABLE + 72, AGG_STOP)
        self.words(AGG_TABLE + 52, AGG_QUERY)
        for index in range(2):
            pointer = preload.STATE + 0x6800 + index * 16
            self.words(ENTRIES + 4 * index, pointer)
            self.words(pointer, AGG_TABLE)
        for slot, address in ((0x466214, KILL), (0x466210, POST), (0x46611C, WAIT), (0x4660CC, CLOSE)):
            self.words(slot, address)
        for address in (KILL, STOP_STREAM, DESTROY, POST, WAIT, CLOSE, AGG_STOP, AGG_QUERY):
            self.uc.hook_add(UC_HOOK_CODE, self.hook, begin=address, end=address)

    def hook(self, uc, address, size, context):
        if address == KILL:
            window, timer = self.args(2)
            assert timer == 1
            self.events.append(("kill-timer", window, timer))
            self.finish(0, 8)
        elif address == STOP_STREAM:
            pointer, = self.args(1)
            assert pointer == STREAM and self.read_words(preload.GLOBAL)[0] == 0
            self.events.append(("stop-stream", pointer))
            self.finish(0x80004005, 4)
        elif address == DESTROY:
            pointer = uc.reg_read(UC_X86_REG_ECX)
            flags, = self.args(1)
            assert (pointer, flags) == (MIDI, 1)
            self.events.append(("destroy-midi", pointer, flags))
            self.finish(0xBAD00001, 4)
        elif address == POST:
            args = self.args(4)
            assert args == (0x1234, 0x12, 0, 0)
            self.events.append(("post-quit", *args))
            self.finish(0, 16)
        elif address == WAIT:
            handle, milliseconds = self.args(2)
            assert (handle, milliseconds) == (0x12345678, 256)
            assert self.wait_count < 2
            result = 258 if self.wait_count == 0 else 0
            self.wait_count += 1
            self.events.append(("wait-worker", handle, milliseconds, result))
            self.finish(result, 8)
        elif address == CLOSE:
            handle, = self.args(1)
            self.events.append(("close-worker", handle))
            self.finish(0, 4)
        elif address == AGG_STOP:
            pointer, = self.args(1)
            self.events.append(("aggregate-stop", pointer))
            self.finish(0x80004005, 4)
        elif address == AGG_QUERY:
            pointer, zero = self.args(2)
            assert zero == 0
            self.events.append(("aggregate-query", pointer, zero))
            self.finish(1, 8)
        else:
            super().hook(uc, address, size, context)

    def cleanup(self):
        if self.recovered:
            return self.call(self.cleanup_entry, [preload.GLOBAL])
        return self.call(0x43D120, [], {UC_X86_REG_EAX: preload.GLOBAL})

    def snapshot(self):
        result = super().snapshot()
        result.update(midi=bytes(self.uc.mem_read(MIDI, 0x600)), waits=self.wait_count,
                      owner=bytes(self.uc.mem_read(preload.OWNER, 4)))
        return result


def cases():
    for consumed, midi, thread in product((0, 1, 18, 37), (False, True), (False, True)):
        yield Case(consumed=consumed, midi=midi, thread=thread)
    for consumed, stop in product((0, 1, 19), (0, 18, 36)):
        yield Case(consumed=consumed, midi=True, thread=True, stop_after=stop)
    for consumed in (0, 18, 37):
        yield Case(consumed=consumed, midi=True, thread=True, owner=False)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--oracle", type=Path, default=preload.ROOT / "matching2/build/oracle/th10.exe")
    options = parser.parse_args()
    config = preload.load_manifest(preload.ROOT / "matching2/msvc/regions.json")
    preload.load_oracle(options.oracle, config)
    image = preload.PEImage(options.oracle.read_bytes())
    names = preload.names_from_image(image)
    parameters = [struct.unpack("<BB2xii", image.read(0x474BD8 + index * 12, 12)) for index in range(8)]
    source, waves = preload.make_fixture(preload.Case(), names, parameters)
    with tempfile.TemporaryDirectory(prefix="th10-sound-lifecycle-") as temporary:
        directory = Path(temporary)
        modules, producers, consumer = preload.compile_candidates(directory, config)
        shutdown, aggregate = compile_shutdown(directory, config, SHUTDOWN_BASE)
        # Only the linked cleanup/MIDI variants and real aggregator execute.
        for address in (CLEANUP, SHUTDOWN_BASE + 0x6000):
            modules[address] = shutdown[address].data
        modules[AGGREGATE] = aggregate
        cleanup_entry = shutdown[CLEANUP].symbols["_Sound_Cleanup_0043d120@4"]
        scenarios = loaded = consumed = freed_pending = shutdown_calls = 0
        for case in cases():
            retail = LifecycleExecution(image, {}, {}, None, None, source, waves, names, case)
            recovered = LifecycleExecution(image, modules, producers, consumer, cleanup_entry, source, waves, names, case)
            assert retail.open("disk") == recovered.open("disk") == 1
            pending = retail.produce()
            assert recovered.produce() == pending
            preload.compare(retail, recovered, (case, "produce"))
            available = [index for index, pointer in enumerate(pending) if pointer]
            loaded += len(available)
            for index in available[:case.consumed]:
                assert retail.consume(index) == recovered.consume(index) == 0
                consumed += 1
            preload.compare(retail, recovered, (case, "consume"))
            remaining = retail.read_words(preload.PENDING, 37)
            freed_pending += sum(bool(pointer) for pointer in remaining)
            if not case.owner:
                for execution in (retail, recovered):
                    execution.words(preload.GLOBAL + 0x610, 0)
            assert retail.cleanup() == recovered.cleanup() == 0
            shutdown_calls += 1
            preload.compare(retail, recovered, (case, "cleanup"))
            for execution in (retail, recovered):
                assert execution.read_words(preload.PENDING, 37) == (0,) * 37
                assert execution.read_words(preload.GLOBAL + 8, 256) == (0,) * 256
                for pointer in pending:
                    if pointer:
                        assert execution.events.count(("free", pointer)) == 1
                assert execution.read_words(preload.GLOBAL + 0x610)[0] == 0
                assert execution.read_words(preload.GLOBAL + 0x608)[0] == (0 if case.owner else STREAM)
                assert execution.read_words(preload.GLOBAL)[0] == (0 if case.owner else preload.DEVICE)
                assert execution.events.count(("free", preload.OWNER)) == int(case.owner)
                assert execution.wait_count == (2 if case.owner and case.midi and case.thread else 0)
            # Once the first cleanup has cleared owned slots, a second call
            # must be a no-op even though its original stream was mandatory.
            before = retail.snapshot()
            assert retail.cleanup() == recovered.cleanup() == 0
            shutdown_calls += 1
            assert retail.snapshot() == before
            preload.compare(retail, recovered, (case, "repeated-cleanup"))
            for execution in (retail, recovered):
                execution.close()
            preload.compare(retail, recovered, (case, "archive-close"))
            scenarios += 1
        print(f"PASS: {scenarios} archive-to-sound shutdown scenarios; {loaded} published buffers, "
              f"{consumed} WAVE consumptions, {freed_pending} unconsumed pending frees and {shutdown_calls} "
              "cleanup calls agree with retail. Actual MIDI stop and interface aggregation execute. "
              "Native MSVC bytes, Windows concurrency and live audio remain unverified.")


if __name__ == "__main__":
    main()
