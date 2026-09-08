#!/bin/bash
# Isolation test: drive the untouched retail image into Stage 1 under
# gamescope WITHOUT the winedbg GDB surrogate, then report whether the
# process survives the post-entry window.
set -u
GAME_DIR="${TH10_GAME_DIR:-$HOME/Games/TH10 - Mountain of Faith}"
OUT="${1:-/tmp/nogdb_run.log}"

cd "$GAME_DIR" || exit 1
WINEDEBUG=-all gamescope -r 60 -W 640 -H 480 -w 640 -h 480 -- \
    wine th10.exe > "$OUT" 2>&1 &
sleep 16

DISPLAY=:1 python3 - <<'PY'
import time
from Xlib import display, X, XK
from Xlib.ext import xtest
d = display.Display(":1")
xtest.fake_input(d, X.MotionNotify, x=320, y=240); d.sync(); time.sleep(0.2)
xtest.fake_input(d, X.ButtonPress, 1); d.sync(); time.sleep(0.1)
xtest.fake_input(d, X.ButtonRelease, 1); d.sync(); time.sleep(0.5)
for name in ("Return", "Enter"):
    kc = d.keysym_to_keycode(XK.string_to_keysym(name))
    if kc:
        xtest.fake_input(d, X.KeyPress, kc); d.sync(); time.sleep(0.08)
        xtest.fake_input(d, X.KeyRelease, kc); d.sync(); time.sleep(0.5)
for _ in range(10):
    kc = d.keysym_to_keycode(XK.string_to_keysym("Z"))
    if kc:
        xtest.fake_input(d, X.KeyPress, kc); d.sync(); time.sleep(0.08)
        xtest.fake_input(d, X.KeyRelease, kc); d.sync(); time.sleep(1.4)
d.close()
PY

sleep 60
if pgrep -f "th10.exe" > /dev/null; then
    echo "ISOLATION: game process ALIVE after post-entry window"
    ALIVE=1
else
    echo "ISOLATION: game process DEAD"
    ALIVE=0
fi
echo "fault lines: $(grep -c 'Unhandled page fault' "$OUT")"
tail -4 "$OUT"
pkill -9 -f "th10.exe" 2>/dev/null || true
pkill -9 -f "gamescope .*wine" 2>/dev/null || true
exit $((1 - ALIVE))
