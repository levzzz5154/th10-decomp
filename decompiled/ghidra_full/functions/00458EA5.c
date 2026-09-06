/* Raw Ghidra reference; not compilable reconstruction. Address: 00458EA5 */

/* WARNING: This is an inlined function */

void __fastcall __security_check_cookie(uintptr_t _StackCookie)

{
  if (_StackCookie == DAT_00473660) {
    return;
  }
  report_failure();
  return;
}

