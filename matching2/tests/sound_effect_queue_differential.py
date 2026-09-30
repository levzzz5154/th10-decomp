#!/usr/bin/env python3
"""Compare pan/stop producers and execute their requests through the dispatcher."""
import argparse
from dataclasses import dataclass
from itertools import product
from pathlib import Path
import struct
import subprocess
import tempfile

from unicorn.x86_const import UC_X86_REG_EBX, UC_X86_REG_ESI, UC_X86_REG_EDI, UC_X86_REG_FPCW, UC_X86_REG_FPTAG, UC_X86_REG_FPSW
from sound_commands_differential import (
    Case as CommandCase, Execution as CommandExecution, compile_candidates as compile_commands,
    ROOT, COMMON, CANDIDATE, STATE, MANAGER, DISPATCH_SYMBOL, BUFFER,
    PEImage, load_manifest, load_oracle, difference)
from music_cursor_differential import DATA, OUTPUT
from coff_module import load_module

PLAY_SYMBOL = "_Sound_QueueEffect_0043dd10@12"
STOP_SYMBOL = "_Sound_QueueEffectStop_0043ddb0@8"


def float_bits(value):
    return struct.unpack("<I", struct.pack("<f", value))[0]


@dataclass(frozen=True)
class Case(CommandCase):
    requests: tuple = (("play", 0, float_bits(192)),)
    consume: bool = False
    effect_priority: int = -37
    initial_counts: tuple = ()


def compile_candidates(directory):
    commands = compile_commands(directory)
    obj = directory / "effect-queue.obj"
    subprocess.run([*COMMON, "-mlong-double-80", "-c",
                    str(ROOT / "matching2/reference/semantic_candidates/sound_effect_queue.cpp"), "-o", str(obj)],
                   check=True, timeout=60)
    producer = load_module(obj, CANDIDATE + 0x2C000,
                           {"_g_sound_pan_scale": 0x470B20, "_g_sound_effect_settings": 0x4749C8, "__ftol2": 0x463B2C})
    return commands, producer


class Execution(CommandExecution):
    def __init__(self, image, compiled=None):
        super().__init__(image, compiled[0] if compiled else None)
        self.producer = compiled[1] if compiled else None
        if self.producer:
            self.uc.mem_write(self.producer.base, self.producer.data)

    def initialize(self, case):
        super().initialize(case)
        for index in range(47):
            self.uc.mem_write(0x4749CE + index * 8, struct.pack("<h", case.effect_priority))
        if case.initial_counts:
            self.words(MANAGER + 0x650, *case.initial_counts)

    def execute(self, case):
        self.prepare(case)
        returns = []
        for operation, index, bits in case.requests:
            if self.producer:
                symbol = PLAY_SYMBOL if operation == "play" else STOP_SYMBOL
                args = (case.manager, index, bits) if operation == "play" else (case.manager, index)
                observed = self.run(self.producer.symbols[symbol], args)
            else:
                observed = self.run(0x43DD10 if operation == "play" else 0x43DDB0,
                    (bits,) if operation == "play" else (),
                    {UC_X86_REG_ESI: case.manager, UC_X86_REG_EBX if operation == "play" else UC_X86_REG_EDI: index})
            # The pan producer is void in the saved Ghidra signature/callers;
            # its incidental EAX varies by branch and is not an API result.
            returns.append(observed["result"] if operation == "stop" else None)
            if self.faults:
                break
            assert (self.uc.reg_read(UC_X86_REG_FPSW) >> 11) & 7 == 0
            assert self.uc.reg_read(UC_X86_REG_FPTAG) == 0xFFFF
            self.event("queued", operation, index, bits, returns[-1])
        if case.consume and not self.faults:
            entry = self.dispatchers[int(case.integrated)].symbols[DISPATCH_SYMBOL] if self.dispatchers else 0x43DDF0
            observed = self.run(entry, (case.manager,), budget=1000000)
            returns.append(observed["result"])
        return {"events": self.events, "faults": self.faults, "returns": returns,
                "memory": tuple(bytes(self.uc.mem_read(address, 0x10000)) for address in (STATE, DATA, OUTPUT)),
                "manager": bytes(self.uc.mem_read(MANAGER, 0x10000)),
                "fpcw": self.uc.reg_read(UC_X86_REG_FPCW),
                # At an invalid settings read the retail x87 value is still
                # live. No equivalence of partial FPU stacks is claimed.
                "fpu_stack": None if self.faults else
                    (self.uc.reg_read(UC_X86_REG_FPTAG), (self.uc.reg_read(UC_X86_REG_FPSW) >> 11) & 7)}


def cases():
    bits = tuple(float_bits(value) for value in (0, -0.0, 0.5, -0.5, 96, -96, 192, -192, 10000, 1e10, -1e10)) + (
        0x00000001, 0x80000001, 0x7F7FFFFF, 0xFF7FFFFF, 0x7F800000, 0xFF800000, 0x7FC00000, 0x7F800001)
    for value, control, count in product(bits, (0x37F, 0x27F, 0x7F, 0x77F, 0xB7F, 0xF7F), (0, 127, 128)):
        yield Case(requests=(("play", 0, value),), fpcw=control, effects=((0, count, (11,)),))
    for count in (-1, -12, -1409, 0, 127, 128, 129, 0x7FFFFFFF, 0x80000000):
        yield Case(effects=((0, count, ()),))
        yield Case(initial_counts=(count,))
    for priority in (-32768, -1, 0, 32767):
        yield Case(effect_priority=priority)
    for operation, index, filled in product(("play", "stop"), (0, 1, 11, 12, 46, 47, 0x40000000, 0xFFFFFFFF, 0x80000000), (0, 1, 11, 12)):
        yield Case(requests=((operation, index, float_bits(1)),), effects=tuple((i, 1, (7,)) for i in range(filled)))
    for operation in ("play", "stop"):
        yield Case(requests=((operation, 0, float_bits(1)),), manager=0)
        yield Case(requests=((operation, 0x1000000, float_bits(1)),))
    yield Case(requests=tuple(("play", 0, float_bits(i - 64)) for i in range(131)))
    yield Case(requests=tuple(("stop", i, 0) for i in range(14)))
    yield Case(effects=((0, 1, (11,)), (-1, 0, ()), (2, 1, (33,))), requests=(("play", 2, float_bits(192)),))
    yield Case(effects=((0, 1, (11,)), (-1, 0, ()), (2, 1, (33,))), requests=(("stop", 2, 0),))
    for requests in (
            (("play", 0, float_bits(192)), ("play", 0, float_bits(96)), ("play", 1, float_bits(-192))),
            (("play", 0, float_bits(192)), ("stop", 0, 0)),
            (("stop", 0, 0), ("play", 0, float_bits(192))),
            tuple(("play", i, float_bits((i - 6) * 16)) for i in range(12)),
            (("stop", 0, 0), ("stop", 1, 0)),
            (("play", 0, 0x7F800000),), (("play", 0, 0x7FC00000),)):
        for enabled, buffers in product((0, 1), ((BUFFER,), (0,))):
            yield Case(requests=requests, consume=True, effects_enabled=enabled, effect_buffers=buffers)


def independent_checks(image, compiled):
    queued = Execution(image, compiled).execute(Case())
    assert struct.unpack_from("<I", queued["manager"], 0x620)[0] == 0
    assert struct.unpack_from("<i", queued["manager"], 0x408)[0] == -37
    assert struct.unpack_from("<I", queued["manager"], 0x650)[0] == 1
    assert struct.unpack_from("<i", queued["manager"], 0x680)[0] == 1000
    consumed = Execution(image, compiled).execute(Case(requests=(
        ("play", 0, float_bits(192)), ("play", 0, float_bits(96)), ("play", 1, float_bits(-192))),
        consume=True, effects_enabled=1))
    assert [event[2] for event in consumed["events"] if event[0] == "pan"] == [750, (-1000) & 0xFFFFFFFF]
    assert struct.unpack_from("<II", consumed["manager"], 0x620) == (0xFFFFFFFF, 0xFFFFFFFF)
    assert struct.unpack_from("<II", consumed["manager"], 0x650) == (0, 0)
    stopped = Execution(image, compiled).execute(Case(requests=(("play", 0, float_bits(192)), ("stop", 0, 0)),
                                                    consume=True, effects_enabled=1))
    assert [event[0] for event in stopped["events"] if not event[0] == "queued"] == ["effect-stop"]
    bad_sequence = Execution(image, compiled).execute(Case(requests=(("stop", 0, 0), ("play", 0, float_bits(192))),
                                                         consume=True, effects_enabled=1))
    assert bad_sequence["faults"] == [("interrupt", 0)]
    alias = Execution(image, compiled).execute(Case(effects=((0, -12, ()),)))
    assert struct.unpack_from("<I", alias["manager"], 0x650)[0] == 1001


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--oracle", type=Path, default=ROOT / "matching2/build/oracle/th10.exe")
    options = parser.parse_args()
    config = load_manifest(ROOT / "matching2/msvc/regions.json")
    load_oracle(options.oracle, config)
    image = PEImage(options.oracle.read_bytes())
    with tempfile.TemporaryDirectory(prefix="th10-effect-queue-") as temporary:
        compiled = compile_candidates(Path(temporary))
        totals, faults = [0, 0], [0, 0]
        for number, case in enumerate(cases()):
            expected, actual = Execution(image).execute(case), Execution(image, compiled).execute(case)
            assert actual == expected, (number, case, difference(expected, actual))
            index = int(case.consume)
            totals[index] += 1
            faults[index] += bool(expected["faults"])
        independent_checks(image, compiled)
        print(f"PASS: {totals[0]} pan/stop producer comparisons ({faults[0]} faults), "
              f"{totals[1]} producer-to-dispatcher comparisons ({faults[1]} faults), independent accumulation/stop/alias checks; "
              f"{len(compiled[1].data)} Clang module bytes. Native MSVC bytes and floating exception-state equivalence remain unverified.")


if __name__ == "__main__":
    main()
