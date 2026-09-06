/* Raw Ghidra reference; not compilable reconstruction. Address: 00412D90 */

void __fastcall FUN_00412d90(int param_1)

{
  undefined4 *in_EAX;
  
  *(undefined4 *)(param_1 + 0x18) = *in_EAX;
  *(undefined4 *)(param_1 + 0x1c) = in_EAX[1];
  return;
}

