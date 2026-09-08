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
# anchors. The probe can also navigate into a stage: a longer Z sequence
# confirms Game Start -> difficulty -> character and reaches StageContext_Enter
# (0x00417870) plus the stage script load (0x00403850).
#
# Usage:
#   retail_bounded_probe.sh OUTPUT.log [INPUT_KEYS]
#
#   OUTPUT.log    destination for the captured gdb/JSONL event stream
#   INPUT_KEYS    optional key list (default from $KEYS)
#
# Environment:
#   PROBE_SECONDS  capture window after the input delivery (default 30)
#   KEY_DELAY      seconds between input keys (default 0.5)
#   KEY_HOLD       seconds each key stays down (default 0.08)
#   DIAG           set to 1 to stop on SIGSEGV and dump the fault site
#                  (backtrace, registers, stack, dispatch tables) instead
#                  of passing it through
#   NO_TICK        set to 1 to omit the 0x0044E1A0 tick anchor entirely
#                  (control runs that isolate the interpreter breakpoint)
#   TICK_MODE      hbreak (default) or break: how the tick anchor is set;
#                  count: hardware breakpoint that only counts stops, no
#                  reads or per-tick output (isolation control)
#
# Requires: gamescope, winedbg, wine, python3 + python-xlib, and the retail
# game directory ($TH10_GAME_DIR or "$HOME/Games/TH10 - Mountain of Faith").
#
# The probe installs breakpoints on the frame loop, the ECL core tick, the
# stage script load, and StageContext_Enter anchors and appends one JSON line
# per event. The ECL command reads the VM state through the fastcall entry
# register (EAX = the VM, EclCoreVm layout: ip at +4, scratch_top at +0x1008,
# async_id at +0x1010, rank_mask at +0x101C) inside a pointer-range guard.
# The tick handler only ever assigns convenience variables with names that
# cannot collide with registers ($vmp/$instrp/$pclo); gdb treats $pc, $eip
# and the segment registers as the inferior's registers, and assigning them
# rewrites the resume context (this bug once made every tick stop resume the
# game at ip & 0xFFFF, which crashed it within a few frames). The ANM tick
# anchor (0x0043EE30) is omitted: stepping over it in the render thread
# destabilizes the session, while the frame/ECL pair is stable. The captured
# event stream uses the reconstruction's JSONL vocabulary (frame_begin /
# ecl_vm_tick / stage_load / stage_enter). Gamescope is capped at 60 Hz
# (-r 60) so the game advances at its designed frame rate instead of running
# uncapped under the GDB surrogate. The startup waits for the nested :1
# display to accept connections instead of a blind sleep, and cleanup resets
# the persistent wineserver so a crashed session cannot poison the next boot.

set -u

GAME_DIR="${TH10_GAME_DIR:-$HOME/Games/TH10 - Mountain of Faith}"
OUT="${1:?output path}"
KEYS="${2:-Return Enter Z Z Down Z}"

PROBE_GDB=$(mktemp /tmp/retail_probe.XXXX.gdb)
CTL=$(mktemp -u /tmp/retail_probe.XXXX.fifo)
mkfifo "$CTL"

cleanup() {
    wineserver -k >/dev/null 2>&1 || true
    pkill -9 -f "winedbg --gdb th10.exe" 2>/dev/null || true
    pkill -9 -f "gamescope .*wine th10.exe" 2>/dev/null || true
    pkill -9 -f "th10.exe" 2>/dev/null || true
    pkill -9 -f "sleep 600" 2>/dev/null || true
    rm -f "$PROBE_GDB" "$CTL"
}
trap cleanup EXIT

{
  if [ "${DIAG:-0}" = 1 ]; then
    # Diagnostic mode: stop on the fault so the catchpoint dumps the site.
    printf 'handle SIGSEGV stop print nopass\n'
  else
    # Normal mode: pass Wine-internal page faults through.
    printf 'handle SIGSEGV nostop noprint pass\n'
  fi
  cat <<'GDB'
set pagination off
set confirm off
set breakpoint always-inserted on
set $q = 0
# A real unhandled fault stops here and dumps eip, a short backtrace,
# registers, the stack words, and the interpreter dispatch tables before
# quitting.  NOTE: this catchpoint is breakpoint number 1, so every
# breakpoint block below binds with a bare `commands` (most recent
# breakpoint), never `commands 1`.
catch signal SIGSEGV
commands
  silent
  set $q = $q + 1
  printf "{\"type\":\"segv_caught\",\"seq\":%d,\"eip\":%u}\n", $q, $eip
  bt 20
  info registers
  x/12wx $esp
  x/32wx 0x44E205
  x/24wx 0x44FCB4
  quit
end
break *0x00439390
commands
  silent
  set $q = $q + 1
  set $gst = *(unsigned int*)0x4776E4
  set $gspv = *(unsigned int*)0x4776E8
  printf "{\"type\":\"frame_begin\",\"seq\":%d,\"gs\":%u,\"gs_prev\":%u}\n", $q, $gst, $gspv
  continue
end
GDB
  if [ "${NO_TICK:-0}" != 1 ]; then
    case "${TICK_MODE:-hbreak}" in
      break) printf 'break *0x0044E1A0\n' ;;
      *)     printf 'hbreak *0x0044E1A0\n' ;;
    esac
    if [ "${TICK_MODE:-hbreak}" = count ]; then
      cat <<'GDB'
commands
  silent
  set $q = $q + 1
  continue
end
GDB
    else
      cat <<'GDB'
commands
  silent
  set $q = $q + 1
  set $vmp = $eax
  if $vmp >= 0x400000 && $vmp < 0x80000000
    set $instrp = *(unsigned int*)($vmp+4)
    set $pclo = $instrp & 0xFFFF
    set $clkp = *(unsigned int*)($vmp)
    set $dltp = *(unsigned int*)($esp)
    printf "{\"type\":\"ecl_vm_tick\",\"seq\":%d,\"vm\":%u,\"ip\":%u,\"pc_before\":%u,\"pc_after\":%u,\"clock\":%u,\"delta\":%u,\"async_id\":%d,\"rank_mask\":%u,\"scratch_top\":%u,\"result\":0,\"live\":1}\n", $q, $vmp, $instrp, $pclo, $pclo, $clkp, $dltp, *(int*)($vmp+0x1010), *(unsigned char*)($vmp+0x101C), *(unsigned int*)($vmp+0x1008)
  else
    printf "{\"type\":\"ecl_guard_fail\",\"seq\":%d,\"vm\":%u}\n", $q, $vmp
  end
  continue
end
GDB
    fi
  fi
  cat <<'GDB'
break *0x00403850
commands
  silent
  set $q = $q + 1
  printf "{\"type\":\"stage_load\",\"seq\":%d}\n", $q
  continue
end
break *0x00450220
commands
  silent
  set $q = $q + 1
  set $arg0v = *(unsigned int*)($esp+4)
  set $arg1v = *(unsigned int*)($esp+8)
  set $arg2v = *(unsigned int*)($esp+12)
  printf "{\"type\":\"script_register\",\"seq\":%d,\"script\":%u,\"ecx\":%u,\"edx\":%u,\"arg0\":%u,\"arg1\":%u,\"arg2\":%u}\n", $q, $arg0v, $ecx, $edx, $arg0v, $arg1v, $arg2v
  continue
end
break *0x00417870
commands
  silent
  set $q = $q + 1
  printf "{\"type\":\"stage_enter\",\"seq\":%d}\n", $q
  continue
end
continue
GDB
} > "$PROBE_GDB"

# Keep the FIFO open so gdb never sees EOF and detaches.
(exec 3>"$CTL"; sleep 600) &

# A stale wineserver (left by a crashed session) makes the next boot fail
# with a BadWindow X error; reset it before launching.
wineserver -k >/dev/null 2>&1 || true
sleep 1

cd "$GAME_DIR" || exit 1
# -r 60 caps the gamescope refresh so the game advances at its designed
# frame rate instead of running uncapped under the GDB surrogate.
WINEDEBUG=-all gamescope -r 60 -W 640 -H 480 -w 640 -h 480 -- \
    winedbg --gdb th10.exe <"$CTL" > "$OUT" 2>&1 &

# Wait for the nested :1 display to accept connections (gamescope needs a
# moment to bring up its X server), then feed the probe script.
python3 - <<'PY'
import time
from Xlib import display
for _ in range(90):
    try:
        display.Display(":1")
        break
    except Exception:
        time.sleep(1)
PY
sleep 3
cat "$PROBE_GDB" > "$CTL"
# Wait until the frame loop has actually been reached (first frame_begin in
# the capture) so the input lands on a live title screen, not mid-boot.
for _ in $(seq 1 90); do
    grep -q '"type":"frame_begin"' "$OUT" 2>/dev/null && break
    sleep 1
done

# Deliver the input keys to break the startup wait on the nested :1 display.
DISPLAY=:1 KEY_DELAY="${KEY_DELAY:-0.5}" KEY_HOLD="${KEY_HOLD:-0.08}" \
    python3 - "$KEYS" <<'PY'
import os, sys, time
from Xlib import display, X, XK
from Xlib.ext import xtest

keys = sys.argv[1].split()
delay = float(os.environ.get("KEY_DELAY", "0.5"))
hold = float(os.environ.get("KEY_HOLD", "0.08"))
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
    xtest.fake_input(d, X.KeyPress, kc); d.sync(); time.sleep(hold)
    xtest.fake_input(d, X.KeyRelease, kc); d.sync()
    time.sleep(delay)
d.close()
PY

# Bounded capture window (seconds).
sleep "${PROBE_SECONDS:-30}"
