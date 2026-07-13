/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x0041BE80
 * Tracking name: FUN_0041be80
 * Ghidra name: FUN_0041be80
 * Tracked span: 48 bytes
 */


void __thiscall FUN_0041be80(void *this,int param_1)

{
  int iVar1;
  
  iVar1 = *(int *)((int)this + 0xc) + param_1 / 10;
  *(int *)((int)this + 0xc) = iVar1;
  if (99999 < iVar1) {
    *(undefined4 *)((int)this + 0xc) = 99999;
  }
  return;
}

