/* Raw Ghidra reference; not compilable reconstruction. Address: 0040ACE0 */

undefined4 __fastcall FUN_0040ace0(int param_1)

{
  ushort in_AX;
  
  if (((*(ushort *)(param_1 + 6) & in_AX) == 0) && ((*(ushort *)(param_1 + 4) & in_AX) == 0)) {
    return 0;
  }
  return 1;
}

