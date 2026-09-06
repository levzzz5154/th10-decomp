/* Raw Ghidra reference; not compilable reconstruction. Address: 004363C0 */

void __fastcall FUN_004363c0(undefined4 *param_1)

{
  *param_1 = &PTR_LAB_0046f308;
  if ((void *)param_1[3] != (void *)0x0) {
    _free((void *)param_1[3]);
    param_1[3] = 0;
  }
  param_1[3] = 0;
  param_1[1] = 0;
  param_1[2] = 0;
  *param_1 = &PTR_LAB_0046f210;
  return;
}

