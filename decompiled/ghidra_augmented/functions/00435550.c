/* Raw Ghidra reference; not compilable reconstruction. Address: 00435550 */

undefined4 __thiscall FUN_00435550(void *this,LONG param_1,DWORD param_2)

{
  DWORD DVar1;
  
  if (*(HANDLE *)((int)this + 4) == (HANDLE)0xffffffff) {
    return 0xffffff00;
  }
  DVar1 = SetFilePointer(*(HANDLE *)((int)this + 4),param_1,(PLONG)0x0,param_2);
  return CONCAT31((int3)(DVar1 >> 8),1);
}

