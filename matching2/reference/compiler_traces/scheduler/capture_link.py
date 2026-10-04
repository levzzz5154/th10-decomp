# usage: capture_link.py cmds.json --source X --project P --output O
# Run probe.py while recording every tool command line to a JSON file.
import sys, json, runpy
sys.path.insert(0, '/home/levzzz/Games/th10Decomp')
out = sys.argv[1]; sys.argv = ['probe.py', *sys.argv[2:]]
import matching2.tools.matching.ltcg_cluster as lc
orig = lc._run_logged
cmds = []
def rec(command, env, cwd, log, timeout):
    cmds.append([str(c) for c in command]); json.dump(cmds, open(out, 'w'), indent=1)
    return orig(command, env, cwd, log, timeout)
lc._run_logged = rec
runpy.run_path('/home/levzzz/Games/th10Decomp/matching2/tools/matching/probe.py', run_name='__main__')
