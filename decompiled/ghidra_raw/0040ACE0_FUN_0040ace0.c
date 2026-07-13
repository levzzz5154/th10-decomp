/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x0040ACE0
 * Tracking name: FUN_0040ace0
 * Ghidra name: FUN_0040ace0
 * Tracked span: 64 bytes
 */


undefined4 __fastcall FUN_0040ace0(int param_1)

{
  ushort in_AX;
  
  if (((*(ushort *)(param_1 + 6) & in_AX) == 0) && ((*(ushort *)(param_1 + 4) & in_AX) == 0)) {
    return 0;
  }
  return 1;
}

