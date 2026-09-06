/* Raw Ghidra reference; not compilable reconstruction. Address: 0044FDB0 */

ulonglong __fastcall ResolveEclIntOperand(undefined4 param_1,int param_2,int param_3)

{
  int iVar1;
  ulonglong uVar2;
  
  iVar1 = *(int *)(param_2 + 4);
  if ((1 << ((byte)param_3 & 0x1f) & (uint)*(ushort *)(iVar1 + 8)) == 0) {
    param_3 = *(int *)(iVar1 + 0x10 + param_3 * 4);
  }
  else {
    iVar1 = *(int *)(iVar1 + 0x10 + param_3 * 4);
    if (-1 < iVar1) {
      return CONCAT44(param_2,*(undefined4 *)(*(int *)(param_2 + 0x100c) + iVar1 + 8 + param_2));
    }
    if (iVar1 != -1) {
      uVar2 = (**(code **)(**(int **)(param_2 + 0x1014) + 4))(iVar1);
      return uVar2;
    }
    iVar1 = *(int *)(param_2 + 0x1008);
    if (-1 < iVar1 + -4) {
      *(int *)(param_2 + 0x1008) = iVar1 + -4;
      param_3 = *(int *)(iVar1 + 4 + param_2);
      *(int *)(param_2 + 0x1008) = iVar1 + -8;
      if (*(char *)(iVar1 + param_2) == 'f') {
        uVar2 = FUN_00463b2c();
        return uVar2;
      }
    }
  }
  return CONCAT44(param_2,param_3);
}

