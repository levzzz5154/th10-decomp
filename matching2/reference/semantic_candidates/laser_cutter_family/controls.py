"""Reproduce the recorded bounded controls from current maintained sources.
Run from the repository root, selecting one group to avoid rerunning all builds.
"""
from pathlib import Path
import argparse,json,shutil,subprocess,sys
p=argparse.ArgumentParser();p.add_argument('group',choices=['entry','origin','record','memory','flags','visible','revision']);a=p.parse_args()
root=Path(__file__).resolve().parent
work=Path('matching2/build/experiments/laser_circle_cut_native_2026_10_06');work.mkdir(parents=True,exist_ok=True)
base=Path('matching2/reference/semantic_candidates/laser_rectangle_trim_0041d880')
if a.group in ['entry','origin','record','memory']:
 shutil.copytree(base,work/'rectangle_trim_entry_candidate',dirs_exist_ok=True)
 script='rectangle_trim_'+a.group+'_controls.py'
elif a.group=='flags':
 target=work/'rectangle_trim_flag_candidate';shutil.copytree(base,target,dirs_exist_ok=True)
 shutil.copy2(root/'evidence/recipes/flag_measure.py',target/'measure.py')
 script='rectangle_trim_flag_controls.py'
elif a.group=='visible':script='visible_creator_controls.py'
else:
 target=work/'rectangle_trim_3052_candidate';shutil.copytree(base,target,dirs_exist_ok=True)
 measure=target/'measure.py';s=measure.read_text();needle='from matching2.tools.common.wine import DEFAULT_TOOLKIT,winpath'
 s=s.replace(needle,needle+"\nDEFAULT_TOOLKIT=Path('/home/levzzz/.wine/drive_c/Program Files (x86)/Microsoft Visual C++ Toolkit 2003')")
 measure.write_text(s);subprocess.run([sys.executable,str(measure),'rectangle_trim_3052_current'],check=True);sys.exit(0)
shutil.copy2(root/'evidence/recipes'/script,work/script)
# Current reproduction uses a non-overlapping diagnostic base; historical
# control reports include an explicitly rejected default-base binding alias.
needle='from matching2.tools.matching.equivalence import MAP_SYMBOL,build_model,disassemble,relocate,normalize,find_differences'
injection=needle+'\nfrom matching2.tools.matching import equivalence as _equivalence\n_equivalence.IMAGE_BASE=0x100000'
if a.group=='visible':
 recipe=work/script;text=recipe.read_text()
 text=text.replace("base=(c/'laser.cpp').read_text();", "measure=c/'measure.py';measure.write_text(measure.read_text().replace("+repr(needle)+","+repr(injection)+"));\n base=(c/'laser.cpp').read_text();")
 recipe.write_text(text)
else:
 candidate=work/('rectangle_trim_flag_candidate' if a.group=='flags' else 'rectangle_trim_entry_candidate')
 measure=candidate/'measure.py';measure.write_text(measure.read_text().replace(needle,injection))
subprocess.run([sys.executable,str(work/script)],check=True)
