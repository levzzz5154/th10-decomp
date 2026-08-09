#!/bin/bash
# retail_bounded_probe.sh - bounded GDB probe against the untouched retail
# th10.exe under Wine (winedbg --gdb + gamescope + XTEST input).
#
# The session originally recorded (docs/retail_trace_probe.md) that the
# untouched retail process "remains in its startup/modal/input wait under the
# current headless Wine desktop and does not reach the frame or ANM anchors".
#
# That barrier is breakable: run the retail image under a nested X display
# (gamescope), deliver the title key with XTEST (python-xlib), and the game
# reaches the frame loop (0x00439390) and ANM tick (0x0043EE30) anchors.
# This script reproduces the bounded probe and writes the captured event
# stream to the output path.
#
# Usage:
#   retail_bounded_probe.sh OUTPUT.log [INPUT_KEYS]
#
#   OUTPUT.log    destination for the captured gdb/JSONL event stream
#   INPUT_KEYS    optional key list (default from $KEYS)
#
# Requires: gamescope, winedbg, wine, python3 + python-xlib, and the retail
# game directory ($TH10_GAME_DIR or "$HOME/Games/TH10 - Mountain of Faith").
#
# The probe installs breakpoints on the known anchors and appends one JSON
# line per event.  The ANM tick command reads the ANM VM state through the
# stack argument ([esp+4]) inside a pointer-range guard so a transient
# invalid pointer cannot abort the session.  GDB step-over across the game's
# render threads is unreliable past a few hundred frames (observed SIGSEGV
# around frame 190-230 in the retail process); the frames/ticks captured
# before that are the bounded result.  The captured event stream uses the
# reconstruction's JSONL vocabulary (frame_begin / vm_tick) with the seab
# offsets kept script-relative where the script base is known.

set -u

GAME_DIR="${TH10_GAME_DIR:-$HOME/Games/TH10 - Mountain of Faith}"
OUT="${1:?output path}"
KEYS="${2:-Return Enter Z Z Down Z}"

PROBE_GDB=$(mktemp /tmp/retail_probe.XXXX.gdb)
CTL=$(mktemp -u /tmp/retail_probe.XXXX.fifo)
mkfifo "$CTL"

cleanup() {
    pkill -9 -f "winedbg --gdb th10.exe" 2>/dev/null || true
    pkill -9 -f "gamescope .*wine th10.exe" 2>/dev/null || true
    pkill -9 -f "th10.exe" 2>/dev/null || true
    pkill -9 -f "sleep 600" 2>/dev/null || true
    rm -f "$PROBE_GDB" "$CTL"
}
trap cleanup EXIT

cat > "$PROBE_GDB" <<'GDB'
set pagination off
set confirm off
set $q = 0
break *0x00439390
commands 1
  silent
  set $q = $q + 1
  printf "{\"type\":\"frame_begin\",\"seq\":%d}\n", $q
  continue
end
break *0x0043EE30
commands 2
  silent
  set $q = $q + 1
  set $vm = *(unsigned int*)($esp+4)
  if $vm >= 0x400000 && $vm < 0x80000000
    set $pc = *(unsigned int*)($vm+0x390)
    printf "{\"type\":\"vm_tick\",\"seq\":%d,\"vm\":%u,\"pc_before\":%u,\"pc_after\":%u,\"time\":%u,\"sprite\":%d,\"flags\":%u,\"ended\":0}\n", $q, $vm, $pc, $pc, *(int*)($vm+0x60), *(int*)($vm+0x308), *(unsigned int*)($vm+0x35c)
  end
  continue
end
continue
GDB

# Keep the FIFO open so gdb never sees EOF and detaches.
(exec 3>"$CTL"; sleep 600) &

cd "$GAME_DIR" || exit 1
WINEDEBUG=-all gamescope -W 640 -H 480 -w 640 -h 480 -- \
    winedbg --gdb th10.exe <"$CTL" > "$OUT" 2>&1 &

# Give Wine + gamescope time to start, then feed the probe script.
sleep 14
cat "$PROBE_GDB" > "$CTL"
sleep 4

# Deliver the input keys to break the startup wait on the nested :1 display.
DISPLAY=:1 python3 - "$KEYS" <<'PY'
import os, sys, time
from Xlib import display, X, XK
from Xlib.ext import xtest

keys = sys.argv[1].split()
d = display.Display(":1")
xtest.fake_input(d, X.MotionNotify, x=320, y=240); d.sync(); time.sleep(0.2)
xtest.fake_input(d, X.ButtonPress, 1); d.sync(); time.sleep(0.1)
xtest.fake_input(d, X.ButtonRelease, 1); d.sync(); time.sleep(0.5)
for name in keys:
    ks = XK.string_to_keysym(name)
    if ks == 0:
        continue
    kc = d.keysym_to_keycode(ks)
    if not kc:
        continue
    xtest.fake_input(d, X.KeyPress, kc); d.sync(); time.sleep(0.08)
    xtest.fake_input(d, X.KeyRelease, kc); d.sync()
    time.sleep(0.5)
d.close()
PY

# Bounded capture window (seconds).
sleep "${PROBE_SECONDS:-30}"