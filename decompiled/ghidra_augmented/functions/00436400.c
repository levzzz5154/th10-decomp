/* Raw Ghidra reference; not compilable reconstruction. Address: 00436400 */

undefined4 __thiscall FUN_00436400(void *this,uint *param_1)

{
  int iVar1;
  byte *pbVar2;
  DWORD DVar3;
  
  pbVar2 = FUN_00435800(param_1,(byte *)0x0);
  *(byte **)((int)this + 0xc) = pbVar2;
  DVar3 = FUN_004358e0(param_1);
  *(DWORD *)((int)this + 4) = DVar3;
  iVar1 = *(int *)((int)this + 0xc);
  *(int *)((int)this + 8) = iVar1;
  return CONCAT31((int3)((uint)iVar1 >> 8),iVar1 != 0);
}

