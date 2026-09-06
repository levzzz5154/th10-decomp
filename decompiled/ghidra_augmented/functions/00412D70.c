/* Raw Ghidra reference; not compilable reconstruction. Address: 00412D70 */

void __fastcall FUN_00412d70(int param_1)

{
  undefined4 *in_EAX;
  
  *(undefined4 *)(param_1 + 8) = *in_EAX;
  *(undefined4 *)(param_1 + 0xc) = in_EAX[1];
  return;
}

