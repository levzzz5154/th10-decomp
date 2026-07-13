/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x0044FF00
 * Tracking name: FUN_0044ff00
 * Ghidra name: FUN_0044ff00
 * Tracked span: 128 bytes
 */


ulonglong __fastcall FUN_0044ff00(undefined4 param_1,int param_2,byte param_3,int param_4)

{
  int iVar1;
  ulonglong uVar2;
  undefined8 uVar3;
  
  if ((1 << (param_3 & 0x1f) & (uint)*(ushort *)(*(int *)(param_2 + 4) + 8)) != 0) {
    if (-1 < param_4) {
      iVar1 = *(int *)(param_2 + 0x100c) + param_2 + 8;
      return CONCAT44(iVar1,*(undefined4 *)(iVar1 + param_4));
    }
    if (param_4 == -1) {
      iVar1 = *(int *)(param_2 + 0x1008);
      if (-1 < iVar1 + -4) {
        *(int *)(param_2 + 0x1008) = iVar1 + -4;
        param_4 = *(int *)(iVar1 + 4 + param_2);
        *(int *)(param_2 + 0x1008) = iVar1 + -8;
        if (*(char *)(iVar1 + param_2) == 'f') {
          uVar2 = FUN_00463b2c();
          return uVar2;
        }
      }
    }
    else {
      uVar3 = (**(code **)(**(int **)(param_2 + 0x1014) + 4))(param_4);
      param_2 = (int)((ulonglong)uVar3 >> 0x20);
      param_4 = (int)uVar3;
    }
  }
  return CONCAT44(param_2,param_4);
}

