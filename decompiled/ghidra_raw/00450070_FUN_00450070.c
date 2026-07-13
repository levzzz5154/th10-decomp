/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x00450070
 * Tracking name: FUN_00450070
 * Ghidra name: FUN_00450070
 * Tracked span: 96 bytes
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int __fastcall FUN_00450070(int param_1)

{
  int in_EAX;
  int iVar1;
  ulonglong uVar2;
  
  if ((1 << ((byte)param_1 & 0x1f) & (uint)*(ushort *)(*(int *)(in_EAX + 4) + 8)) == 0) {
    return 0;
  }
  if (_DAT_00470b04 <= *(float *)(*(int *)(in_EAX + 4) + 0x10 + param_1 * 4)) {
    uVar2 = FUN_00463b2c();
    return *(int *)(in_EAX + 0x100c) + (int)uVar2 + in_EAX + 8;
  }
  iVar1 = **(int **)(in_EAX + 0x1014);
  uVar2 = FUN_00463b2c();
  iVar1 = (**(code **)(iVar1 + 0x10))((int)uVar2);
  return iVar1;
}

