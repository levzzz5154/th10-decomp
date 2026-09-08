"""Shared helpers retain process failures and authenticated asset boundaries."""

import sys
from pathlib import Path

if __package__ in (None, ""):
    sys.path.insert(0, str(Path(__file__).resolve().parents[2]))
import hashlib
import json
import subprocess
import tempfile
import unittest
from unittest.mock import patch

from matching2.tools.common.process import run
from matching2.tools.common.wine import compiler_environment, toolchain_hashes, winpath
from matching2.tools.matching.pack_asm_pe import PackError, _read_asset

ROOT = Path(__file__).resolve().parents[2]


class CommonToolsTest(unittest.TestCase):
    def test_logged_process_preserves_environment_output_and_failure(self):
        with tempfile.TemporaryDirectory() as temporary:
            directory = Path(temporary)
            log = directory / "command.log"
            result = run([sys.executable, "-c", "import os; print(os.environ['TH10_TEST_VALUE'])"],
                         log, directory, env={"TH10_TEST_VALUE": "retained"})
            self.assertEqual(result.returncode, 0)
            self.assertEqual(log.read_text(), "retained\n")
            with self.assertRaises(RuntimeError):
                run([sys.executable, "-c", "import sys; print('failure', file=sys.stderr); sys.exit(7)"],
                    log, directory)
            self.assertEqual(log.read_text(), "failure\n")

    def test_logged_process_forwards_timeout(self):
        with tempfile.TemporaryDirectory() as temporary:
            directory = Path(temporary)
            with patch("matching2.tools.common.process.subprocess.run",
                       side_effect=subprocess.TimeoutExpired("compiler", 17)) as command:
                with self.assertRaises(subprocess.TimeoutExpired):
                    run(["compiler"], directory / "log", directory, timeout=17)
                self.assertEqual(command.call_args.kwargs["timeout"], 17)

    def test_wine_path_is_one_argument_and_quiets_wine(self):
        with patch("matching2.tools.common.wine.subprocess.check_output", return_value="Z:\\some path\n") as command:
            self.assertEqual(winpath(Path("/some path")), "Z:\\some path")
            self.assertEqual(command.call_args.args[0], ["winepath", "-w", "/some path"])
            self.assertEqual(command.call_args.kwargs["env"]["WINEDEBUG"], "-all")

    def test_both_layouts_resolve_the_same_five_authenticated_assets(self):
        asset_sets = []
        for name in ("asm", "msvc"):
            layout_path = ROOT / "matching2" / name / "pe_layout.json"
            layout = json.loads(layout_path.read_text())
            specs = [layout["dos_prefix"]["header"], layout["dos_prefix"]["rich_metadata"]]
            specs += [{"path": section["source"], "size": section["raw_size"], "sha256": section["sha256"]}
                      for section in layout["sections"] if section["name"] != ".text"]
            paths = set()
            for spec in specs:
                data = _read_asset(layout_path, spec["path"], spec["size"], spec["sha256"])
                self.assertEqual(hashlib.sha256(data).hexdigest(), spec["sha256"])
                paths.add((layout_path.parent / spec["path"]).resolve())
            self.assertEqual(len(paths), 5)
            self.assertTrue(all(path.parent == ROOT / "matching2/reference/data" for path in paths))
            asset_sets.append(paths)
        self.assertEqual(*asset_sets)

    def test_compiler_environment_and_binary_identities(self):
        with patch("matching2.tools.common.wine.winpath", side_effect=lambda path: "win:" + str(path)):
            environment = compiler_environment(Path("/toolkit"), include_library=True)
            self.assertEqual(environment["INCLUDE"], "win:/toolkit/include")
            self.assertEqual(environment["LIB"], "win:/toolkit/lib")
            self.assertEqual(environment["WINEDEBUG"], "-all")
        with tempfile.TemporaryDirectory() as temporary:
            toolkit = Path(temporary)
            (toolkit / "bin").mkdir()
            (toolkit / "bin/cl.exe").write_bytes(b"compiler fixture")
            self.assertEqual(toolchain_hashes(toolkit, ["cl.exe"]),
                             {"cl.exe": hashlib.sha256(b"compiler fixture").hexdigest()})

    def test_corrupt_shared_asset_is_rejected(self):
        with tempfile.TemporaryDirectory() as temporary:
            directory = Path(temporary)
            (directory / "asset.bin").write_bytes(b"wrong")
            with self.assertRaisesRegex(PackError, "hash mismatch"):
                _read_asset(directory / "layout.json", "asset.bin", 5, hashlib.sha256(b"right").hexdigest())


if __name__ == "__main__":
    unittest.main()
