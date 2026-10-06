"""Audit actual C1 include dependencies without replacing any compiled object."""
from pathlib import Path
from concurrent.futures import ThreadPoolExecutor
import json,subprocess,sys,re
sys.path.insert(0,str(Path.cwd()))
from matching2.tools.common.wine import DEFAULT_TOOLKIT,compiler_environment,winpath
from matching2.tools.matching.ltcg_cluster import _verify_includes
root=Path(__file__).resolve().parent
work=Path('matching2/build/experiments/laser_circle_cut_native_2026_10_06')/(sys.argv[1] if len(sys.argv)>1 else 'cutter_family_maintained')
commands=[x for x in json.loads((work/'commands.json').read_text()) if len(x)>1 and str(x[1]).endswith('/cl.exe')]
assert len(commands)==len(json.loads((root/'layout.json').read_text())['sources'])
# /EP runs the same preprocessor/includes, without producing a replacement OBJ.
commands=[[x for x in command if x!='/c' and not x.startswith('/Fo')][:-1]+['/EP','/showIncludes',command[-1]] for command in commands]
env=compiler_environment(DEFAULT_TOOLKIT)
def probe(command):
 result=subprocess.run(command,capture_output=True,text=True,env=env,timeout=180);assert result.returncode==0,result.stderr+result.stdout[-1000:]
 return result.stdout+result.stderr
with ThreadPoolExecutor(max_workers=2) as pool:logs=list(pool.map(probe,commands))
reported=[]
roots=[(winpath(Path.cwd()),Path.cwd()),(winpath(DEFAULT_TOOLKIT),DEFAULT_TOOLKIT)]
for log in logs:
 for line in log.splitlines():
  match=re.match(r'^Note: including file:\s*(.+?)\s*$',line)
  if match:
   windows=match.group(1)
   prefix,base=next((prefix,base) for prefix,base in roots if windows.lower().startswith(prefix.lower()+'\\'))
   path=(base/windows[len(prefix)+1:].replace('\\','/')).resolve()
   assert path.is_file(),path
   reported.append(path)
sources=[root/x for x in json.loads((root/'layout.json').read_text())['sources']]
headers=sorted({x for x in reported if not x.is_relative_to(DEFAULT_TOOLKIT) and x not in sources})
spec={'project':Path.cwd(),'source_paths':sources,'included_source_paths':[],'header_paths':headers}
includes=_verify_includes('\n'.join(logs),spec,DEFAULT_TOOLKIT,direct_sources=spec['source_paths'])
report={'method':'MSVC /EP /showIncludes on actual compiler command lines; no object or PE replaced','commands':commands,'translation_units':len(commands),'compiler_includes':includes}
(work/'include_probe.json').write_text(json.dumps(report,indent=2)+'\n');print('audited',len(includes),'inclusion records across',len(commands),'translation units')
