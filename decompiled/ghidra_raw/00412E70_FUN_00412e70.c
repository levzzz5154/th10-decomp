/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x00412E70
 * Tracking name: FUN_00412e70
 * Ghidra name: FUN_00412e70
 * Tracked span: 96 bytes
 */


void __thiscall FUN_00412e70(void *this,int param_1)

{
  int iVar1;
  
  iVar1 = (int)((ulonglong)((longlong)param_1 * -0x66666667) >> 0x20);
  iVar1 = *(int *)((int)this + 0xc) + ((iVar1 >> 2) - (iVar1 >> 0x1f));
  *(int *)((int)this + 0xc) = iVar1;
  if (iVar1 < 5000) {
    *(undefined4 *)((int)this + 0xc) = 5000;
  }
  return;
}

