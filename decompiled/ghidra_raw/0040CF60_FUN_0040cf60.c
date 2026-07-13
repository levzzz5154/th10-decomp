/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x0040CF60
 * Tracking name: FUN_0040cf60
 * Ghidra name: FUN_0040cf60
 * Tracked span: 48 bytes
 */


void __fastcall FUN_0040cf60(int param_1)

{
  undefined4 *in_EAX;
  
  *(undefined4 *)(param_1 + 0x430) = *in_EAX;
  *(undefined4 *)(param_1 + 0x434) = in_EAX[1];
  *(undefined4 *)(param_1 + 0x438) = in_EAX[2];
  return;
}

