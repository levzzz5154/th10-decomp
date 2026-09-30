#!/usr/bin/env python3
"""Execute the factory's table-selected cleanup actions at selected throw sites.

Reads actual retail/Clang frame records and FuncInfo tables. This tests unwind
obligations and action code, not Windows dispatch or runtime handler compatibility.
"""
import argparse
from pathlib import Path
import tempfile

from unicorn.x86_const import UC_X86_REG_EBP, UC_X86_REG_ESP, UC_X86_REG_EIP
from sound_stream_create_memory_differential import (
    Case, Execution, compile_candidates, FACTORY_SYMBOL, ALLOCATE, FREE, CREATE, QUERY, SET_NOTICES,
    ROOT, STOP, STATE, PEImage, load_manifest, load_oracle, difference)
from sound_stream_initialize_differential import RELEASE_NOTIFY, POSITION
from lzss_compressor_differential import STACK
from x86_seh import TEB, INITIAL_EXCEPTION_LIST, exception_list


class Injected(Exception):
    pass


class UnwindExecution(Execution):
    def __init__(self, image, compiled, phase, index, allow_state_gap=False):
        super().__init__(image, compiled)
        self.phase, self.index = phase, index
        self.injected = self.unwinding = False
        self.allow_state_gap = allow_state_gap

    def hook(self, machine, address, size, context):
        if not self.unwinding:
            labels = {ALLOCATE: ("allocate", self.allocate_calls + 1), CREATE: ("create", 1),
                      QUERY: ("query", 1), SET_NOTICES: ("set-notices", 1), RELEASE_NOTIFY: ("release-notify", 1),
                      FREE: ("free", len(self.freed) + 1), POSITION: ("position", 1)}
            labels.update((entry, ("construct", 1)) for entry in self.construct_entries)
            labels.update((entry, ("fill", 1)) for entry in self.fill_entries)
            if labels.get(address) == (self.phase, self.index):
                self.event("injected", self.phase, self.index)
                self.injected = True
                raise Injected()
        super().hook(machine, address, size, context)

    def execute_unwind(self, case):
        try:
            super().execute(case)
        except Injected:
            pass
        else:
            assert self.phase == "null-publication" and self.faults
            assert self.faults[0][1] == 0x34
            self.injected = True
        assert self.injected
        uc = self.uc
        frame = exception_list(uc)
        previous, handler, state = self.read_words(frame, 3)
        assert previous == INITIAL_EXCEPTION_LIST
        module = self.factories[int(case.integrated)] if self.factories else None
        expected_handler = module.symbols["___ehhandler$" + self.factory_symbol] if module else self.retail_handler
        assert handler == expected_handler
        assert bytes(uc.mem_read(handler, 1)) == b"\xB8"
        assert bytes(uc.mem_read(handler + 5, 1)) == b"\xE9"
        info, = self.read_words(handler + 1)
        magic, count, unwind_map, try_count, try_map = self.read_words(info, 5)
        assert magic == (0x19930522 if module else 0x19930520)
        assert count == 1 and try_count == try_map == 0
        active = self.phase in ("construct", "fill", "position", "null-publication") or (self.phase == "allocate" and self.index == 4)
        if self.allow_state_gap and state != (0 if active else 0xFFFFFFFF):
            return {"state_gap": (state, 0 if active else 0xFFFFFFFF)}
        assert state == (0 if active else 0xFFFFFFFF), (self.phase, self.index, hex(state))
        prior_frees = list(self.freed)
        self.unwinding = True
        if active:
            prior, action = self.read_words(unwind_map, 2)
            assert prior == 0xFFFFFFFF and action
            self.words(frame + 8, prior)
            sp = STACK + 0x3000
            self.words(sp, STOP)
            uc.reg_write(UC_X86_REG_ESP, sp)
            uc.reg_write(UC_X86_REG_EBP, frame + 12)
            uc.emu_start(action, STOP, count=100000)
            assert uc.reg_read(UC_X86_REG_EIP) == STOP
            assert uc.reg_read(UC_X86_REG_ESP) == sp + 4
            assert exception_list(uc) == frame
            # The action frees only allocation three (the raw 0x78 stream),
            # even when that allocation is NULL. The cursor/buffer stay owned.
            assert self.freed == prior_frees + [self.allocated[2][0]]
        else:
            assert self.freed == prior_frees
        self.words(TEB, previous)  # removal is modeled dispatcher work
        assert exception_list(uc) == INITIAL_EXCEPTION_LIST
        return {"events": self.events, "faults": self.faults,
                "memory": tuple(bytes(uc.mem_read(address, 0x10000)) for address in (STATE, 0x2600000, 0x2100000)),
                "allocated": self.allocated, "freed": self.freed, "state": state}


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--oracle", type=Path, default=ROOT / "matching2/build/oracle/th10.exe")
    options = parser.parse_args()
    config = load_manifest(ROOT / "matching2/msvc/regions.json")
    load_oracle(options.oracle, config)
    image = PEImage(options.oracle.read_bytes())
    with tempfile.TemporaryDirectory(prefix="th10-create-memory-unwind-") as temporary:
        compiled = compile_candidates(Path(temporary))
        comparisons = 0
        phases = (("allocate", 1), ("allocate", 2), ("allocate", 3), ("create", 1), ("query", 1),
                  ("set-notices", 1), ("release-notify", 1), ("free", 1), ("construct", 1))
        for integrated in (False, True):
            selected = phases + ((("allocate", 4), ("fill", 1), ("position", 1)) if integrated else ())
            for count in (0, 1, 16):
                for phase, index in selected:
                    case = Case(integrated=integrated, segment_count=count)
                    expected = UnwindExecution(image, None, phase, index).execute_unwind(case)
                    actual = UnwindExecution(image, compiled, phase, index).execute_unwind(case)
                    assert actual == expected, (case, phase, index, difference(expected, actual))
                    comparisons += 1
            case = Case(integrated=integrated, fail_allocate=3)
            expected = UnwindExecution(image, None, "null-publication", 1).execute_unwind(case)
            actual = UnwindExecution(image, compiled, "null-publication", 1).execute_unwind(case)
            assert actual == expected, difference(expected, actual)
            comparisons += 1
        synchronous = compile_candidates(Path(temporary), asynchronous=False)
        diagnostic = UnwindExecution(image, synchronous, "null-publication", 1, allow_state_gap=True).execute_unwind(Case(fail_allocate=3))
        assert diagnostic == {"state_gap": (0xFFFFFFFF, 0)}
        print(f"PASS: {comparisons} factory registered-state/unwind-action comparisons, including null allocation cleanup. "
              "Synchronous Clang post-constructor state gap reproduced separately. "
              "Actual table-selected actions execute; Windows exception dispatch and native MSVC matching remain unverified.")


if __name__ == "__main__":
    main()
