"""Play one replay under rtrace.exe in the isolated Wine install and record a per-frame trace.

    run_replay.py <exe in build/behavior/game> <replay list index (1-based)> <stage row (0-based)> <trace.bin>

Writes <trace.bin>, <trace.bin>.meta.json (replay start hit, outcome) and <trace>.log (tracer stderr:
exceptions with stack return addresses). Holds Ctrl to fast-forward. Stops when the game returns to the
title, crashes, or stops advancing.
"""
import json
import sys
import time
from pathlib import Path

import drive


def main(argv):
    exe, replay, stage, trace = argv[0], int(argv[1]), int(argv[2]), str(Path(argv[3]).resolve())
    drive.main(['stop'])
    time.sleep(2)
    drive.start(exe, trace)
    drive.title_select(trace, 3)                  # Replay
    drive.main(['keys', f'Down*{replay - 1}', 'z'])
    if stage:
        drive.main(['keys', f'Down*{stage}'])
    start_hit = drive.status(trace)['hits']
    drive.tap('z', gap=0.5)
    drive.main(['hold', 'Control_L'])
    meta = {'exe': exe, 'replay': replay, 'stage': stage, 'start_hit': start_hit}
    log = Path(trace).with_suffix('.log')
    last, stalled, outcome = -1, 0, 'timeout'
    deadline = time.time() + 3 * 3600
    while time.time() < deadline:
        time.sleep(5)
        st = drive.status(trace)
        text = log.read_text(errors='replace') if log.exists() else ''
        if 'EXIT' in text:
            outcome = 'exited'
            break
        if 'EXCEPTION' in text and 'first=0' in text:
            outcome = 'crashed'
            break
        if st.get('title') and st.get('hits', 0) > start_hit + 60:
            outcome = 'returned-to-title'
            break
        stalled = stalled + 1 if st.get('hits') == last else 0
        last = st.get('hits')
        if stalled >= 24:                         # no gameplay frame for 2 minutes
            outcome = 'stalled'
            break
    drive.main(['shot', str(Path(trace).with_suffix('.png'))])
    drive.main(['release', 'Control_L'])
    meta.update(outcome=outcome, final_status=drive.status(trace))
    Path(trace + '.meta.json').write_text(json.dumps(meta, indent=1))
    drive.main(['stop'])
    print(json.dumps(meta))


if __name__ == '__main__':
    main(sys.argv[1:])
