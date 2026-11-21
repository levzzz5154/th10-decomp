"""Compiler wrappers preserve source ownership and invalidate cached outputs."""
from pathlib import Path
import tempfile
import unittest

from matching2.tools.common.project_paths import compilation_source
from matching2.tools.matching.progress import cpp_parity_issues
from matching2.tools.matching.unit_cache import UnitCache


class CompilationUnitTests(unittest.TestCase):
    def test_cpp_parity_checks_headers_separately_from_the_image_hash(self):
        with tempfile.TemporaryDirectory() as directory:
            project = Path(directory)
            header = project / 'helper.inl'
            header.write_text('// asm\\\n _emit\n/* __asm */ const char* name = R"tag(a " __asm " b)tag";\n')
            self.assertEqual(list(cpp_parity_issues(project, [], False)),
                             ['packaged executable SHA-256 differs from retail'])
            header.write_text(header.read_text() + '#define SNAP __as\\\nm { frndint }\n')
            regions = [{'kind': 'asm', 'address': '0x401000', 'source': 'exact.cpp'}]
            self.assertEqual(list(cpp_parity_issues(project, regions, True)), [
                '0x401000: exact link still uses exact.cpp',
                'helper.inl: inline assembly or instruction emitter'])

    def test_wrapper_must_be_an_existing_project_cpp(self):
        with tempfile.TemporaryDirectory() as directory:
            project = Path(directory)
            (project / 'body.cpp').write_text('void body() {}\n')
            for path in ('../outside.cpp', 'missing.cpp', 'body.h'):
                with self.subTest(path=path), self.assertRaisesRegex(ValueError, 'project C\\+\\+ source'):
                    compilation_source(project, 'body.cpp', {'compilation_units': {'body.cpp': path}})

    def test_wrapper_is_optional_and_does_not_change_source_attribution(self):
        with tempfile.TemporaryDirectory() as directory:
            project = Path(directory)
            body = project / 'body.cpp'; body.write_text('void body() {}\n')
            wrapper = project / 'unit.cpp'; wrapper.write_text('#include "body.cpp"\n')
            self.assertEqual(compilation_source(project, 'body.cpp', {}), body)
            self.assertEqual(compilation_source(project, 'body.cpp', {
                'compilation_units': {'body.cpp': 'unit.cpp'}}), wrapper)

    def test_wrapper_and_its_declarations_are_cache_dependencies(self):
        with tempfile.TemporaryDirectory() as directory:
            project = Path(directory)
            (project / 'body.cpp').write_text('void body() {}\n')
            wrapper = project / 'unit.cpp'; wrapper.write_text('#include "types.hpp"\n#include "body.cpp"\n')
            header = project / 'types.hpp'; header.write_text('struct View {};\n')
            config = {'compilation_units': {'body.cpp': 'unit.cpp'}}
            def key():
                cache = UnitCache.__new__(UnitCache)
                cache.project, cache.file_digests, cache.closures, cache.base = project, {}, {}, {}
                return cache.key('body.cpp', config, [], None)
            first = key()
            header.write_text('struct View { int field; };\n')
            self.assertNotEqual(first, key())
            second = key()
            wrapper.write_text(wrapper.read_text() + '// revised compile context\n')
            self.assertNotEqual(second, key())


if __name__ == '__main__':
    unittest.main()
