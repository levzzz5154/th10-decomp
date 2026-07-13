/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x00435250
 * Tracking name: FUN_00435250
 * Ghidra name: FUN_00435250
 * Tracked span: 208 bytes
 */


void __fastcall FUN_00435250(undefined4 *param_1)

{
  if ((void *)*param_1 != (void *)0x0) {
    _free((void *)*param_1);
    *param_1 = 0;
  }
  return;
}

