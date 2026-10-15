"""Compiler wrappers preserve source ownership and invalidate cached outputs."""
from pathlib import Path
import tempfile
import unittest
from matching2.tools.matching.build_msvc import UnitCache, compilation_source


class CompilationUnitTests(unittest.TestCase):
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
                return cache.key('body.cpp', config, [], None, None)
            first = key()
            header.write_text('struct View { int field; };\n')
            self.assertNotEqual(first, key())
            second = key()
            wrapper.write_text(wrapper.read_text() + '// revised compile context\n')
            self.assertNotEqual(second, key())


if __name__ == '__main__':
    unittest.main()
