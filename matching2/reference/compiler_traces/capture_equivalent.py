# usage: capture_equivalent.py cmds.json <layout> [project]
# Run one equivalence measurement, keep its work directory and record every
# tool command so the c2 tracers can replay the model link: `cmds[-1]` is the
# link at the retail address (all paths in the commands are absolute).
import json, shutil, subprocess, sys
from pathlib import Path
sys.path.insert(0, '/home/levzzz/Games/th10Decomp')
from matching2.tools.common.project_paths import project_support
from matching2.tools.matching import equivalence
from matching2.tools.matching.variant import measure
out, layout = sys.argv[1], sys.argv[2]
project = Path(sys.argv[3] if len(sys.argv) > 3 else '/home/levzzz/Games/th10Decomp/matching2/msvc')
output = Path('/home/levzzz/Games/th10Decomp/matching2/build/msvc')
cmds = []
real_run = subprocess.run
def run(command, *a, **k):
    if command and command[0] == 'wine':
        cmds.append([str(c) for c in command])
    return real_run(command, *a, **k)
equivalence.subprocess.run = run
shutil.rmtree = lambda *a, **k: None  # keep the work directory
config = json.loads(project_support(project, 'regions.json').read_text())
row = measure(layout, project, output, config, (output / 'text.bin').read_bytes())
links = [c for c in cmds if c[1].endswith('link.exe')]
# The tracers replay cmds[-1]: put the link at the retail address last.
json.dump([c for c in cmds if c is not links[0]] + [links[0]], open(out, 'w'), indent=1)
print(row['diff_bytes'], 'differing bytes; commands in', out)
