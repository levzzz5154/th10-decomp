/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x0044B010
 * Tracking name: FUN_0044b010
 * Ghidra name: FUN_0044b010
 * Tracked span: 112 bytes
 */


undefined4 __fastcall FUN_0044b010(undefined4 param_1,PBYTE param_2)

{
  int iVar1;
  PBYTE pBVar2;
  
  pBVar2 = param_2;
  for (iVar1 = 0x40; iVar1 != 0; iVar1 = iVar1 + -1) {
    pBVar2[0] = '\0';
    pBVar2[1] = '\0';
    pBVar2[2] = '\0';
    pBVar2[3] = '\0';
    pBVar2 = pBVar2 + 4;
  }
  if (DAT_004924fc != 0) {
    if ((DAT_00491ff4 & 0x200) != 0) {
      iVar1 = (**(code **)(*DAT_00491c38 + 0x24))(DAT_00491c38,0x100);
      if (iVar1 == -0x7ff8ffe2) {
        (**(code **)(*DAT_00491c38 + 0x1c))(DAT_00491c38);
        return 1;
      }
      if (iVar1 != 0) {
        (**(code **)(*DAT_00491c38 + 0x1c))(DAT_00491c38);
      }
      return 1;
    }
    GetKeyboardState(param_2);
  }
  return 0;
}

