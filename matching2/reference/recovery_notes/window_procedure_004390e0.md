# Window procedure recovery: `0x004390E0`

## Source-level conversion

`src/platform/fun_004390e0_004390e0.cpp` now contains an ordinary C++ Win32
window procedure. Its source signature is `LRESULT CALLBACK` with the four
standard window-procedure arguments. No inline assembly is used.

Ghidra's entry listing confirms that the function reads four stack arguments
and returns with `ret 0x10`. The caller at `0x00439730` stores the function
address in the `WNDCLASSA` procedure field (`0x00439783` data reference); there
are no direct callers. Ghidra's auto-prototype adds an ECX `this` argument, but
the retail instructions do not read ECX as a window-procedure input. In the
MIDI completion branch, retail instead sets EDX from `0x00491FE8` and has ESI
hold the fourth stack argument before its private call to `0x0043AEB0`.

## Recovered behavior

* `WM_CLOSE` sets bit `0x80` in `0x00491FF4` and returns 1.
* `WM_ERASEBKGND` returns 1.
* `WM_SETCURSOR` hides the cursor when `0x00491D65` and `0x00492500` are both
  zero; otherwise it loads the arrow cursor and shows it.
* `WM_ACTIVATEAPP` stores `wParam` in `0x004924FC`, stores `wParam == 0` in
  `0x00492500`, and calls `DefWindowProcA`.
* `WM_LBUTTONDOWN` calls `SetForegroundWindow` before `DefWindowProcA`.
* Message `0x3C9` (MIDI output completion) searches the manager's 32 header
  slots at `+0x14`. On a match it clears the slot, calls the
  `midiOutUnprepareHeader` import at `0x00466284` with size `0x40`, frees and
  clears `MIDIHDR::lpData` if present, then frees the header. This is the
  side-effect body of the private `0x0043AEB0` helper, expressed inline so the
  converted callback does not rely on that helper's EDX/ESI ABI.
* All other messages go to `DefWindowProcA`.

The import slots, global fields, and helper behavior above are supported by
Ghidra's decompilation and instruction listing for `0x004390E0` and
`0x0043AEB0`.

## Model status

The active manifest now marks `0x004390E0` as semantic and retains the former
assembly row in `previous_record`. The entry binds to the C-linkage
`WindowProcedure_004390e0` symbol with the Win32 stdcall callback ABI; the old
`_asm_FUN_004390e0_004390e0` address alias remains available to the registration
path. Ghidra's signature is corrected to the four stack arguments rather than
a spurious ECX `this` parameter. Exact compiler output remains unverified. No
build, probe, or test was run.
