/* Raw Ghidra reference; not compilable reconstruction. Address: 00427E20 */

void __fastcall FUN_00427e20(undefined4 *param_1,undefined4 *param_2)

{
  undefined4 uVar1;
  undefined4 *in_EAX;
  
  uVar1 = *param_2;
  *param_1 = uVar1;
  param_1[1] = param_2[1];
  *in_EAX = uVar1;
  in_EAX[1] = param_1[1];
  return;
}

