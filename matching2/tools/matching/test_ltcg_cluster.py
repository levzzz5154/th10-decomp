"""Focused manifest tests for native-LTCG cluster ownership."""

import json
from pathlib import Path
import tempfile
import unittest

from matching2.tools.matching.ltcg_cluster import load_cluster


class ClusterSourceOwnershipTests(unittest.TestCase):
    def _write_manifest(self, project, *, multi_source):
        (project / "src").mkdir()
        (project / "layout" / "ltcg").mkdir(parents=True)
        (project / "src" / "primary.cpp").write_text("// primary\n")
        (project / "src" / "secondary.cpp").write_text("// secondary\n")
        (project / "layout" / "ltcg" / "context.cpp").write_text("// context\n")
        functions = [{
            "name": "Primary",
            "symbol": "?Primary@@YAHXZ",
            "section": ".text$01primary",
            "address": "0x00401000",
            "size": 1,
            "actual_abi": "plain RET",
        }]
        regions = [{
            "name": "semantic_primary",
            "source": "src/primary.cpp",
            "symbol": "?Primary@@YAHXZ",
            "address": "0x00401000",
            "size": 1,
            "kind": "semantic",
            "owner": "0x00401000",
        }]
        if multi_source:
            functions.append({
                "name": "Secondary",
                "symbol": "?Secondary@@YAHXZ",
                "section": ".text$05secondary",
                "address": "0x00401010",
                "size": 1,
                "actual_abi": "plain RET",
                "source": "src/secondary.cpp",
            })
            functions[0]["source"] = "src/primary.cpp"
            regions.append({
                "name": "semantic_secondary",
                "source": "src/secondary.cpp",
                "symbol": "?Secondary@@YAHXZ",
                "address": "0x00401010",
                "size": 1,
                "kind": "semantic",
                "owner": "0x00401010",
            })
        manifest = {
            "schema_version": 1,
            "name": "source_ownership_test",
            "source": "src/primary.cpp",
            "driver": "layout/ltcg/context.cpp",
            "headers": [],
            "image_base": "0x00400000",
            "description": "test cluster",
            "functions": functions,
            "context": {
                "symbol": "?Context@@YAHXZ",
                "section": ".text$03context",
                "address": "0x00401020",
                "size": 1,
                "description": "test context",
            },
            "gaps": [
                {"section": ".text$00layout", "address": "0x00400000", "size": 4096},
                {"section": ".text$02layout", "address": "0x00401001", "size": 15},
                {"section": ".text$04layout", "address": "0x00401011", "size": 15},
            ],
            "constants": [],
            "absolute_symbols": [],
        }
        if multi_source:
            manifest["additional_sources"] = ["src/secondary.cpp"]
        (project / "layout" / "ltcg" / "source_ownership_test.json").write_text(
            json.dumps(manifest)
        )
        return regions

    def test_multi_source_functions_are_owned_by_declared_sources(self):
        with tempfile.TemporaryDirectory() as directory:
            project = Path(directory)
            regions = self._write_manifest(project, multi_source=True)
            loaded = load_cluster(project, "layout/ltcg/source_ownership_test.json", regions)

        self.assertEqual(
            loaded["source_names"], ["src/primary.cpp", "src/secondary.cpp"]
        )
        self.assertEqual(
            [function["_source"] for function in loaded["functions"]],
            ["src/primary.cpp", "src/secondary.cpp"],
        )
        self.assertEqual(
            {region["source"] for region in loaded["regions"]},
            {"src/primary.cpp", "src/secondary.cpp"},
        )

    def test_legacy_manifest_defaults_function_source_to_primary(self):
        with tempfile.TemporaryDirectory() as directory:
            project = Path(directory)
            regions = self._write_manifest(project, multi_source=False)
            loaded = load_cluster(project, "layout/ltcg/source_ownership_test.json", regions)

        self.assertEqual(loaded["source_names"], ["src/primary.cpp"])
        self.assertEqual(loaded["functions"][0]["_source"], "src/primary.cpp")


if __name__ == "__main__":
    unittest.main()
