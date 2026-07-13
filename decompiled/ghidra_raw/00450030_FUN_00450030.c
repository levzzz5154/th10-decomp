/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x00450030
 * Tracking name: FUN_00450030
 * Ghidra name: FUN_00450030
 * Tracked span: 64 bytes
 */


int __fastcall FUN_00450030(int param_1)

{
  int iVar1;
  int unaff_ESI;
  
  if ((1 << ((byte)param_1 & 0x1f) & (uint)*(ushort *)(*(int *)(unaff_ESI + 4) + 8)) == 0) {
    return 0;
  }
  iVar1 = *(int *)(*(int *)(unaff_ESI + 4) + 0x10 + param_1 * 4);
  if (-1 < iVar1) {
    return *(int *)(unaff_ESI + 0x100c) + iVar1 + unaff_ESI + 8;
  }
  iVar1 = (**(code **)(**(int **)(unaff_ESI + 0x1014) + 8))(iVar1);
  return iVar1;
}

