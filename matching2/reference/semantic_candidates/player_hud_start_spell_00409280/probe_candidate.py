#!/usr/bin/env python3
"""Replay the archived exact spell-card and registrar native byte gates."""
import argparse
import json
from pathlib import Path
import shutil
import subprocess
import sys


def main():
    here = Path(__file__).resolve().parent
    root = here.parents[3]
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--output', type=Path, default=root / 'matching2/build/experiments/player_hud_start_spell_candidate')
    args = parser.parse_args()
    output = args.output.resolve()
    project = output / 'project'
    if project.exists():
        parser.error(f'use a fresh output directory: {project}')
    shutil.copytree(root / 'matching2/msvc', project)
    shutil.copytree(here / 'overlay', project, dirs_exist_ok=True)
    manifest_path = project / 'regions.json'
    manifest = json.loads(manifest_path.read_text())
    source = 'src/game/player_hud_start_spell_00409280.cpp'
    regions = [item for item in manifest['regions'] if int(item['address'], 0) == 0x409280]
    if len(regions) != 1 or regions[0]['size'] != 2432:
        raise ValueError('expected the complete 2,432-byte retail region at 0x409280')
    regions[0].update(name='semantic_PlayerHud_StartSpell_00409280', source=source,
                      symbol='?StartSpell@PlayerHud_00408d60@@QAEXHPBDH@Z',
                      kind='semantic', owner='player_hud_start_spell_00409280')
    registrar_cluster = 'layout/ltcg/animation_register_primary_back_004489d0.json'
    if registrar_cluster in manifest['ltcg_clusters']:
        # The experiment combines the same registrar and caller in one scope.
        # Retain its complete byte gate without giving two clusters ownership
        # of the same dependency wrappers in this disposable project.
        manifest['ltcg_clusters'].remove(registrar_cluster)
    layout_path = project / 'layout/ltcg/player_hud_start_spell_00409280.json'
    layout = json.loads(layout_path.read_text())
    if any(item['name'] == 'register' for item in layout['anchors']):
        registrar = next(item for item in layout['anchors'] if item['name'] == 'register')
        registrar_source = 'src/render/animation_manager_register_primary_back_004489d0.cpp'
        layout['anchors'].remove(registrar)
        layout['functions'].append(dict(registrar, source=registrar_source,
                                         actual_abi='manager EDX, object EBX, output EAX; RET'))
        registrar_region = next(item for item in manifest['regions']
                                if int(item['address'], 0) == 0x4489D0)
        registrar_region.update(source=registrar_source, symbol=registrar['symbol'],
                                kind='semantic', owner='player_hud_start_spell_00409280')
        layout_path.write_text(json.dumps(layout, indent=2) + '\n')
    cluster = 'layout/ltcg/player_hud_start_spell_00409280.json'
    if cluster not in manifest['ltcg_clusters']:
        manifest['ltcg_clusters'].append(cluster)
    manifest_path.write_text(json.dumps(manifest, indent=2) + '\n')
    command = [sys.executable, str(root / 'matching2/tools/matching/probe.py'),
               '--source', source, '--project', str(project),
               '--output', str(output / 'probe'), '--show', '20']
    result = subprocess.run(command, stdout=subprocess.PIPE, stderr=subprocess.STDOUT, text=True)
    (output / 'probe.log').write_text(result.stdout)
    (output / 'command.json').write_text(json.dumps(command, indent=2) + '\n')
    print(result.stdout, end='')
    return result.returncode


if __name__ == '__main__':
    sys.exit(main())
