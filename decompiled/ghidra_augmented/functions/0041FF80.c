/* Raw Ghidra reference; not compilable reconstruction. Address: 0041FF80 */

int __fastcall FUN_0041ff80(int param_1)

{
  int iVar1;
  void *this;
  
  if ((*(char *)(param_1 + 0x3cc) < '\0') && (*(int *)(param_1 + 0x63c) == 0)) {
    DAT_00491fb8 = 3;
  }
  FUN_00421e00();
  FUN_0044a5f0(0);
  iVar1 = FUN_00447700(this,(int)g_pGameStateManager);
  if (iVar1 == 0) {
    if (*(int *)(param_1 + 0x648) == 0) {
      iVar1 = FUN_004218d0();
      return iVar1;
    }
    return ((*(int *)(param_1 + 0x648) != 2) - 1 & 3) + 1;
  }
  return 4;
}

