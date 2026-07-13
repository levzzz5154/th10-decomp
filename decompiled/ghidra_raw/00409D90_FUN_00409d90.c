/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x00409D90
 * Tracking name: FUN_00409d90
 * Ghidra name: FUN_00409d90
 * Tracked span: 144 bytes
 */


void __thiscall FUN_00409d90(void *this,int param_1)

{
  int iVar1;
  
  iVar1 = *(int *)((int)this + 4) + param_1 / 10;
  *(int *)((int)this + 4) = iVar1;
  if (999999999 < iVar1) {
    *(undefined4 *)((int)this + 4) = 999999999;
  }
  return;
}

