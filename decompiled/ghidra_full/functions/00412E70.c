/* Raw Ghidra reference; not compilable reconstruction. Address: 00412E70 */

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

