/* Raw Ghidra reference; not compilable reconstruction. Address: 0042C360 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_0042c360(void)

{
  int iVar1;
  int unaff_EDI;
  
  AppendMarkedGameThreadRecord("Spt Test\n");
  iVar1 = *(int *)(unaff_EDI + 0x30);
  if (iVar1 == 1) {
    if (*(int *)(unaff_EDI + 0x38) == 0) {
      AppendMarkedGameThreadRecord("File not found.");
    }
    else {
      AppendMarkedGameThreadRecord("File %s");
    }
    if (*(int *)(unaff_EDI + 0x2d8) == 0) {
      AppendMarkedGameThreadRecord("Ecl not load");
    }
    else {
      AppendMarkedGameThreadRecord("Ecl %s");
    }
    AppendMarkedGameThreadRecord("Quit");
    AppendMarkedGameThreadRecord(">");
    *(undefined4 *)((int)g_pGameThread + 0x8974) = 0xffffffff;
  }
  else {
    if (iVar1 == 2) {
      *(undefined4 *)((int)g_pGameThread + 0x8974) = 0xffff4040;
      AppendMarkedGameThreadRecord("Loading %s");
      *(undefined4 *)((int)g_pGameThread + 0x8974) = 0xffffffff;
      return 1;
    }
    if (iVar1 == 3) {
      *(undefined4 *)((int)g_pGameThread + 0x8974) = 0xffa0a0a0;
      FUN_00463b2c();
      FUN_00463b2c();
      AppendMarkedGameThreadRecord("Pos %.3d %.3d");
      *(undefined4 *)((int)g_pGameThread + 0x8974) = 0xffffffff;
      return 1;
    }
  }
  return 1;
}

