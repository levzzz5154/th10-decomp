/* Raw Ghidra reference; not compilable reconstruction. Address: 00436680 */

void __fastcall FUN_00436680(undefined4 *param_1)

{
  *param_1 = &PTR_FUN_0046f308;
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

