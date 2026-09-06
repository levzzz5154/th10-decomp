/* Raw Ghidra reference; not compilable reconstruction. Address: 00435250 */

void __fastcall FUN_00435250(undefined4 *param_1)

{
  if ((void *)*param_1 != (void *)0x0) {
    _free((void *)*param_1);
    *param_1 = 0;
  }
  return;
}

