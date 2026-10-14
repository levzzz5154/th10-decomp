"""Drive an isolated th10 instance under rtrace.exe through a replay.

    drive.py start <exe> <trace.bin>     launch Xvfb (if needed) + game under the tracer
    drive.py keys <key>[*n] ...          tap keys (e.g. Down*3 z)
    drive.py hold <key> / release <key>
    drive.py shot <file.png>
    drive.py stop                        kill only the isolated prefix

Environment: RS_DISPLAY (default :91), RS_GAME (game directory under build/behavior, default game),
RS_PREFIX (Wine prefix under build/behavior, default wineprefix). Give parallel instances their own
display, game copy and prefix.
"""
import os
import subprocess
import sys
import time
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2] / 'build' / 'behavior'
GAME = ROOT / os.environ.get('RS_GAME', 'game')
TOOLS = ROOT / 'runtime-tools' / 'usr'
DISPLAY = os.environ.get('RS_DISPLAY', ':91')
WINE_ENV = {**os.environ, 'DISPLAY': DISPLAY, 'WINEPREFIX': str(ROOT / os.environ.get('RS_PREFIX', 'wineprefix')), 'WINEDEBUG': '-all',
            'LIBGL_ALWAYS_SOFTWARE': '1', 'GALLIUM_DRIVER': 'llvmpipe'}
X_ENV = {**os.environ, 'DISPLAY': DISPLAY, 'LD_LIBRARY_PATH': str(TOOLS / 'lib')}


def xdo(*args):
    subprocess.run([str(TOOLS / 'bin' / 'xdotool'), *args], env=X_ENV, check=True)


def focus():
    found = subprocess.run([str(TOOLS / 'bin' / 'xdotool'), 'search', '--onlyvisible', '--name', 'Mountain of Faith'],
                           env=X_ENV, capture_output=True, text=True).stdout.split()
    if found:
        xdo('windowfocus', found[0])


def tap(key, hold=0.12, gap=0.6):
    focus()
    xdo('keydown', key)
    time.sleep(hold)
    xdo('keyup', key)
    time.sleep(gap)


def ensure_xvfb():
    if subprocess.run(['pgrep', '-f', f'Xvfb {DISPLAY}'], stdout=subprocess.DEVNULL).returncode == 0:
        return
    subprocess.Popen([str(TOOLS / 'bin' / 'Xvfb'), DISPLAY, '-screen', '0', '800x600x24', '-ac', '-nolisten', 'tcp'],
                     stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL, start_new_session=True)
    time.sleep(1.5)


def start(exe, trace):
    ensure_xvfb()
    log = open(Path(trace).with_suffix('.log'), 'w')
    subprocess.Popen(['wine', 'rtrace.exe', exe, str(Path(trace).resolve())], cwd=GAME, env=WINE_ENV,
                     stdout=log, stderr=subprocess.STDOUT, start_new_session=True)
    for _ in range(300):
        if subprocess.run([str(TOOLS / 'bin' / 'xdotool'), 'search', '--onlyvisible', '--name', 'Mountain of Faith'],
                          env=X_ENV, capture_output=True).stdout.strip():
            break
        time.sleep(0.1)
    time.sleep(0.5)
    xdo('mousemove', '440', '307', 'click', '1')


def status(trace):
    try:
        text = Path(str(Path(trace).resolve()) + '.status').read_text()
    except OSError:
        return {}
    return {k: int(v, 16 if k in ('title', 'player') else 10) for k, v in (f.split('=') for f in text.split())}


def wait_title(trace, timeout=60):
    end = time.time() + timeout
    while time.time() < end:
        st = status(trace)
        if st.get('submode') == 2 and st.get('phase') == 2 and not st.get('player'):
            return st
        if st.get('submode') == 1 and st.get('phase') == 2:
            tap('z', gap=0.3)        # "Press any button"
        elif st.get('player') and not st.get('title'):
            tap('Escape', gap=0.5)   # an attract demo started: cancel it
        time.sleep(0.05)
    raise SystemExit(f'title not ready: {status(trace)}')


def title_select(trace, index):
    """Move the title cursor to index (fast taps, verified from memory) and confirm."""
    wait_title(trace)
    for _ in range(20):
        cursor = status(trace).get('cursor')
        if cursor == index:
            tap('z', gap=1.0)
            return
        tap('Down' if cursor < index else 'Up', hold=0.08, gap=0.15)
    raise SystemExit(f'cursor stuck: {status(trace)}')


def main(argv):
    cmd = argv[0]
    if cmd == 'start':
        start(argv[1], argv[2])
    elif cmd == 'keys':
        for spec in argv[1:]:
            key, _, count = spec.partition('*')
            for _ in range(int(count or 1)):
                tap(key)
    elif cmd == 'title':
        title_select(argv[1], int(argv[2]))
    elif cmd == 'status':
        print(status(argv[1]))
    elif cmd == 'hold':
        focus()
        xdo('keydown', argv[1])
    elif cmd == 'release':
        xdo('keyup', argv[1])
    elif cmd == 'shot':
        subprocess.run(['import', '-window', 'root', argv[1]], env=X_ENV, check=True)
    elif cmd == 'stop':
        subprocess.run(['wineserver', '-k'], env=WINE_ENV)   # only this instance's prefix
    else:
        raise SystemExit(__doc__)


if __name__ == '__main__':
    main(sys.argv[1:])
