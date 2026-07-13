/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x0042C360
 * Tracking name: FUN_0042c360
 * Ghidra name: FUN_0042c360
 * Tracked span: 608 bytes
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_0042c360(void)

{
  int iVar1;
  int unaff_EDI;
  
  FUN_00401690("Spt Test\n");
  iVar1 = *(int *)(unaff_EDI + 0x30);
  if (iVar1 == 1) {
    if (*(int *)(unaff_EDI + 0x38) == 0) {
      FUN_00401690("File not found.");
    }
    else {
      FUN_00401690("File %s");
    }
    if (*(int *)(unaff_EDI + 0x2d8) == 0) {
      FUN_00401690("Ecl not load");
    }
    else {
      FUN_00401690("Ecl %s");
    }
    FUN_00401690("Quit");
    FUN_00401690(">");
    *(undefined4 *)((int)g_pGameThread + 0x8974) = 0xffffffff;
  }
  else {
    if (iVar1 == 2) {
      *(undefined4 *)((int)g_pGameThread + 0x8974) = 0xffff4040;
      FUN_00401690("Loading %s");
      *(undefined4 *)((int)g_pGameThread + 0x8974) = 0xffffffff;
      return 1;
    }
    if (iVar1 == 3) {
      *(undefined4 *)((int)g_pGameThread + 0x8974) = 0xffa0a0a0;
      FUN_00463b2c();
      FUN_00463b2c();
      FUN_00401690("Pos %.3d %.3d");
      *(undefined4 *)((int)g_pGameThread + 0x8974) = 0xffffffff;
      return 1;
    }
  }
  return 1;
}

