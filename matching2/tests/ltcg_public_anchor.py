#!/usr/bin/env python3
"""Exercise the real result-overlay graph's public helper root and byte gate.

Builds a fresh positive native graph, checks its complete overlay and public
initializer against retail, then removes the helper root in an isolated copy.
The changed native ABI must fail the complete-contribution gate. Also checks
that an otherwise valid native helper cannot come from an undeclared input.
Oracle bytes are read only after the positive compilation has finished.
"""
import argparse
import json
import shutil
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[2]))

from matching2.tools.common.wine import DEFAULT_TOOLKIT
from matching2.tools.matching.ltcg_cluster import (
    LTCGClusterError, build_cluster, load_cluster, validate_native_output,
)
from matching2.tools.matching.ltcg_semantic import PEImage, parse_map
from matching2.tools.matching.probe import DEFAULT_PROJECT, default_oracle

LAYOUT = 'layout/ltcg/result_overlay_004172e0.json'


def rejected(action, message):
    try:
        action()
    except LTCGClusterError as error:
        if message not in str(error):
            raise
        return str(error)
    raise AssertionError('invalid control was accepted: ' + message)


from matching2.tools.common.project_paths import project_support
def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--project', type=Path, default=DEFAULT_PROJECT)
    parser.add_argument('--toolkit', type=Path, default=DEFAULT_TOOLKIT)
    parser.add_argument('--oracle', type=Path, default=default_oracle())
    parser.add_argument('--output', type=Path,
                        default=DEFAULT_PROJECT.parent / 'build/tests/ltcg_public_anchor')
    args = parser.parse_args()
    project, output = args.project.resolve(), args.output.resolve()
    output.mkdir(parents=True, exist_ok=True)
    config = json.loads((project_support(project, 'regions.json')).read_text())
    spec = load_cluster(project, LAYOUT, config['regions'])
    positive = build_cluster(spec, args.toolkit.resolve(), output / 'positive', config['flags'])['native_build']
    native = PEImage.from_path(Path(positive['native_executable']))
    retail = PEImage.from_path(args.oracle.resolve())
    selected = spec['functions'][0]
    root = spec['anchor_roots'][0]
    initializer = next(item for item in spec['anchors'] if item['symbol'] == root)
    for item in (selected, initializer):
        assert native.read(item['address'], item['size'])[0] == retail.read(item['address'], item['size'])[0]

    origins = {Path(item['object']).name for item in positive['compile_commands']}
    map_path = Path(positive['native_map'])
    root_origin = next(item.origin for item in parse_map(map_path.read_text()).symbols
                       if item.name == root)
    bad_origin = rejected(
        lambda: validate_native_output(spec, Path(positive['native_executable']),
                                       map_path, origins - {root_origin}),
        'rooted ABI anchor is not from a compiled input',
    )

    # Control manifests and input hashes belong to this copy. Production files
    # are never modified while the compiler or another build may be using them.
    control = output / 'control_project'
    shutil.copytree(project, control, dirs_exist_ok=True)
    path = control / LAYOUT
    raw = json.loads(path.read_text())
    errors = {}
    for label, roots, message in (
        ('unknown', ['_UndeclaredHelper'], 'declared complete non-generated function'),
        ('duplicate', [root, root], 'anchor roots must be distinct'),
    ):
        path.write_text(json.dumps(dict(raw, anchor_roots=roots), indent=2) + '\n')
        errors[label] = rejected(lambda: load_cluster(control, LAYOUT, config['regions']), message)
    path.write_text(json.dumps(dict(raw, anchor_roots=[]), indent=2) + '\n')
    unrooted = load_cluster(control, LAYOUT, config['regions'])
    errors['unrooted_native_abi'] = rejected(
        lambda: build_cluster(unrooted, args.toolkit.resolve(), output / 'unrooted', config['flags']),
        'entire declared compiler contribution',
    )
    result = {'selected_bytes_exact': selected['size'],
              'public_helper_bytes_exact': initializer['size'],
              'unexpected_root_origin_rejected': bad_origin,
              'rejected_controls': errors, 'native_report': positive}
    (output / 'controls.json').write_text(json.dumps(result, indent=2) + '\n')
    print(f"Overlay {selected['size']} bytes and public helper {initializer['size']} bytes: EXACT")
    print('Unrooted ABI, undeclared origin, unknown root and duplicate root: rejected')
    return 0


if __name__ == '__main__':
    raise SystemExit(main())
