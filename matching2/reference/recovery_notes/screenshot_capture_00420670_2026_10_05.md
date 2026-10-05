# 0x00420670 screenshot capture (recovered 2026-10-05)

`src/app/screenshot_capture_00420670.cpp` compiles to the retail 504 bytes in
the `screenshot_capture_00420670` cluster. `make` and `make EXACT=1` pass.

* `GameApp_00420670::CaptureScreenshot(const char* name)`: application object
  in ESI, name in EAX. The thread handle is read through `this` (+0x50C) and
  written through the global object (0x00492134).
* Row loop: `row` declared before `offset`, `do { ...; --row; offset += 0x780; }
  while (row > -1)` gives `dec ebp / add edx / cmp ebp,-1 / jg`. A `for` with
  `row >= 0` ends in `jns` and swaps the two registers.
* The two "out of memory" blocks are identical and are merged late
  (FgDoCommonTailMerge, traced with `flowgraph/trace_lateflow_cl.py`). Both
  copies exist at layout time, each after its own test; the merge keeps one.
  With `break` in both the second copy survives; retail keeps the first. A
  `goto done` (label after the switch) in the second block, or in both,
  makes the first one survive.
* `ScreenshotWriter_00420540` is only used as a pointer, so its cluster symbol
  is kind `data` (absolute), not `relative_code`.
