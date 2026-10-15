#!/usr/bin/env python3
"""Check file-factory registered cleanup states and execute their actual actions."""
import argparse
from pathlib import Path
import tempfile

from sound_stream_create_memory_unwind import UnwindExecution as MemoryUnwindExecution, Injected
from sound_stream_create_file_differential import (
    Case, Execution, compile_candidates, CREATE_FILE, CLOSE_FILE,
    ROOT, PEImage, load_manifest, load_oracle, difference)
from music_cursor_differential import SEEK


class UnwindExecution(MemoryUnwindExecution, Execution):
    def hook(self, machine, address, size, context):
        if not self.unwinding:
            labels = {CREATE_FILE: "create-file", CLOSE_FILE: "close-file", SEEK: "seek"}
            labels.update((entry, "cursor-open") for entry in self.open_entries)
            if labels.get(address) == self.phase:
                self.event("injected", self.phase, self.index)
                self.injected = True
                raise Injected()
        super().hook(machine, address, size, context)


import sys as _project_sys
from pathlib import Path as _ProjectPath
_project_sys.path.insert(0, str(_ProjectPath(__file__).resolve().parents[2]))
from matching2.tools.common.project_paths import project_support
def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--oracle", type=Path, default=ROOT / "matching2/build/oracle/th10.exe")
    options = parser.parse_args()
    config = load_manifest(project_support((ROOT) / 'matching2/msvc', 'regions.json'))
    load_oracle(options.oracle, config)
    image = PEImage(options.oracle.read_bytes())
    with tempfile.TemporaryDirectory(prefix="th10-create-file-unwind-") as temporary:
        compiled = compile_candidates(Path(temporary))
        comparisons = 0
        phases = (("allocate", 1), ("allocate", 2), ("allocate", 3), ("cursor-open", 1),
                  ("create", 1), ("query", 1), ("set-notices", 1), ("release-notify", 1), ("free", 1), ("construct", 1))
        for integrated in (False, True):
            selected = phases + ((("create-file", 1), ("seek", 1), ("allocate", 4), ("fill", 1), ("position", 1)) if integrated else ())
            for count in (0, 1, 16):
                for phase, index in selected:
                    case = Case(integrated=integrated, segment_count=count)
                    expected = UnwindExecution(image, None, phase, index).execute_unwind(case)
                    actual = UnwindExecution(image, compiled, phase, index).execute_unwind(case)
                    assert actual == expected, (case, phase, difference(expected, actual))
                    comparisons += 1
            for phase, case in (("null-publication", Case(integrated=integrated, fail_allocate=3)),
                                ("close-file", Case(integrated=integrated, open_result=1, filename=0)),
                                ("free", Case(integrated=integrated, open_result=1, filename=0))):
                expected = UnwindExecution(image, None, phase, 1).execute_unwind(case)
                actual = UnwindExecution(image, compiled, phase, 1).execute_unwind(case)
                assert actual == expected, (case, phase, difference(expected, actual))
                comparisons += 1
        synchronous = compile_candidates(Path(temporary), asynchronous=False)
        diagnostic = UnwindExecution(image, synchronous, "null-publication", 1, allow_state_gap=True).execute_unwind(Case(fail_allocate=3))
        assert diagnostic == {"state_gap": (0xFFFFFFFF, 0)}
        print(f"PASS: {comparisons} file-factory registered-state/unwind-action comparisons. "
              "Synchronous Clang post-constructor state gap reproduced separately; "
              "Windows exception dispatch and native MSVC bytes remain unverified.")


if __name__ == "__main__":
    main()
