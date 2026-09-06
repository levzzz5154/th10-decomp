/* Raw Ghidra reference; not compilable reconstruction. Address: 00412A10 */

int __fastcall FUN_00412a10(int param_1)

{
  int iVar1;
  int in_EAX;
  int iVar2;
  
  iVar2 = *(int *)(*(int *)(in_EAX + 0x14d8) + 4);
  if ((1 << ((byte)param_1 & 0x1f) & (uint)*(ushort *)(*(int *)(iVar2 + 4) + 8)) == 0) {
    return 0;
  }
  iVar1 = *(int *)(*(int *)(iVar2 + 4) + 0x10 + param_1 * 4);
  if (-1 < iVar1) {
    return *(int *)(iVar2 + 0x100c) + iVar1 + iVar2 + 8;
  }
  iVar2 = (**(code **)(**(int **)(iVar2 + 0x1014) + 8))(iVar1);
  return iVar2;
}

