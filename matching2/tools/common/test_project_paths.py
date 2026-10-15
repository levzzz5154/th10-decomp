"""Metadata locations remain usable for current and legacy scratch projects."""
from pathlib import Path
import tempfile
import unittest
from matching2.tools.common.project_paths import project_support


class ProjectSupportPaths(unittest.TestCase):
    def test_legacy_scratch_copy_keeps_its_original_paths(self):
        with tempfile.TemporaryDirectory() as directory:
            project = Path(directory)
            self.assertEqual(project_support(project, 'regions.json'), project / 'regions.json')
            self.assertEqual(project_support(project, 'layout/ltcg'), project / 'layout/ltcg')

    def test_current_project_keeps_metadata_and_contexts_private(self):
        with tempfile.TemporaryDirectory() as directory:
            project = Path(directory)
            (project / 'build_support').mkdir()
            self.assertEqual(project_support(project, 'regions.json'), project / 'build_support/regions.json')
            self.assertEqual(project_support(project, 'layout/ltcg'), project / 'build_support/layout/ltcg')
            self.assertEqual(project_support(project, 'equivalent/game'), project / 'build_support/contexts/equivalent/game')
