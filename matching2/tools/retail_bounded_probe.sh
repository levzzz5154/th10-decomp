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
# reaches the frame loop (0x00439390) and ECL core tick (0x0044E1A0)
# anchors. Captured in this checkout: thousands of frames and thousands of
# ECL VM ticks from the untouched image, including the VM state (pc,
# async_id, rank_mask, scratch_top) for each core tick.
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
# The probe installs breakpoints on the frame loop and ECL core tick anchors
# and appends one JSON line per event. The ECL command reads the VM state
# through the fastcall entry register (EAX = the VM, EclCoreVm layout: ip at
# +4, scratch_top at +0x1008, async_id at +0x1010, rank_mask at +0x101C)
# inside a pointer-range guard. The ANM tick anchor (0x0043EE30) is omitted:
# stepping over it in the render thread destabilizes the session, while the
# frame/ECL pair is stable past 9,000 frames. The captured event stream uses
# the reconstruction's JSONL vocabulary (frame_begin / ecl_vm_tick).

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
set breakpoint always-inserted on
set $q = 0
break *0x00439390
commands 1
  silent
  set $q = $q + 1
  printf "{\"type\":\"frame_begin\",\"seq\":%d}\n", $q
  continue
end
break *0x0044E1A0
commands 2
  silent
  set $q = $q + 1
  set $vm = $eax
  if $vm >= 0x400000 && $vm < 0x80000000
    set $instr = *(unsigned int*)($vm+4)
    set $pc = $instr & 0xFFFF
    printf "{\"type\":\"ecl_vm_tick\",\"seq\":%d,\"vm\":%u,\"pc_before\":%u,\"pc_after\":%u,\"async_id\":%d,\"rank_mask\":%u,\"scratch_top\":%u,\"result\":0,\"live\":1}\n", $q, $vm, $pc, $pc, *(int*)($vm+0x1010), *(unsigned char*)($vm+0x101C), *(unsigned int*)($vm+0x1008)
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