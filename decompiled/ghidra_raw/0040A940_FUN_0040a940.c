/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x0040A940
 * Tracking name: FUN_0040a940
 * Ghidra name: FUN_0040a940
 * Tracked span: 736 bytes
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_0040a940(void)

{
  void *pvVar1;
  int unaff_EDI;
  char *pcVar2;
  
  FUN_00401690("SprtView\n");
  switch(*(undefined4 *)(unaff_EDI + 0x30)) {
  case 1:
    if (*(int *)(unaff_EDI + 0x38) == 0) {
      FUN_00401690("File not found.");
    }
    else {
      FUN_00401690("File %s");
    }
    if (DAT_00477704 == 0) {
      pcVar2 = "Ecl %d";
    }
    else {
      pcVar2 = "Ecl %s";
    }
    FUN_00401690(pcVar2);
    FUN_00401690("Quit");
    FUN_00401690(">");
    break;
  case 2:
    *(undefined4 *)((int)g_pGameThread + 0x8974) = 0xffff4040;
    FUN_00401690("Loading %s");
    *(undefined4 *)((int)g_pGameThread + 0x8974) = 0xffffffff;
    return 1;
  case 3:
    *(undefined4 *)((int)g_pGameThread + 0x8974) = 0xffa0a0a0;
    FUN_00463b2c();
    FUN_00463b2c();
    FUN_00401690("Pos %.3d %.3d");
    break;
  case 4:
    FUN_00401690("Enemy %d");
    return 1;
  default:
    goto switchD_0040a981_default;
  }
  *(undefined4 *)((int)g_pGameThread + 0x8974) = 0xffffffff;
  if ((*(byte *)(unaff_EDI + 0x684) & 2) != 0) {
    *(undefined4 *)(unaff_EDI + 0x5fc) = 0x43a00000;
    *(undefined4 *)(unaff_EDI + 0x600) = 0x43700000;
    pvVar1 = g_pGameStateManager;
    *(undefined4 *)(unaff_EDI + 0x604) = 0;
    FUN_00443080(pvVar1);
  }
switchD_0040a981_default:
  return 1;
}

