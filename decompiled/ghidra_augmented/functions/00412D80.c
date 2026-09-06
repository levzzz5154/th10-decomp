/* Raw Ghidra reference; not compilable reconstruction. Address: 00412D80 */

void __fastcall FUN_00412d80(int param_1)

{
  undefined4 *in_EAX;
  
  *(undefined4 *)(param_1 + 0x10) = *in_EAX;
  *(undefined4 *)(param_1 + 0x14) = in_EAX[1];
  return;
}

