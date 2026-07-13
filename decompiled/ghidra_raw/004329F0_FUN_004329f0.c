/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x004329F0
 * Tracking name: FUN_004329f0
 * Ghidra name: FUN_004329f0
 * Tracked span: 704 bytes
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_004329f0(void)

{
  int iVar1;
  void *pvVar2;
  int iVar3;
  int unaff_EDI;
  uint local_20;
  int local_1c;
  
  pvVar2 = g_pGameThread;
  if (*(int *)(unaff_EDI + 0x20) == 2) {
    iVar3 = *(int *)(unaff_EDI + 0xfc);
    *(undefined4 *)((int)g_pGameThread + 0x8988) = 1;
    if (*(int *)(unaff_EDI + 0x1d4) == 0) {
      iVar3 = iVar3 * 0xf0;
      local_20 = 0xff;
      local_1c = 10;
      do {
        *(uint *)((int)pvVar2 + 0x8974) = (local_20 << 8 | local_20) << 8 | 0xff0000ff;
        iVar1 = *(int *)(unaff_EDI + 0x24) * 0x437c;
        if (*(int *)(iVar3 + iVar1 + 0x28 + DAT_0047783c) == 0) {
          FUN_00401630((int)pvVar2,"%2d  %s  %9ld%d  ----/--/-- --:--  Stage -  ---%%");
        }
        else {
          _localtime((time_t *)(iVar3 + iVar1 + 0x28 + DAT_0047783c));
          FUN_00401630((int)g_pGameThread,"%2d  %s  %9ld%d  %.4d/%.2d/%.2d %.2d:%.2d  %s  %2.1f%%");
        }
        local_20 = local_20 - 0x10;
        iVar3 = iVar3 + 0x18;
        local_1c = local_1c + -1;
        pvVar2 = g_pGameThread;
      } while (local_1c != 0);
    }
    *(undefined4 *)((int)pvVar2 + 0x8974) = 0xffffffff;
    FUN_00401630((int)pvVar2,"    %5d");
    FUN_00401630((int)g_pGameThread,"%3d:%.2d:%.2d");
    FUN_00401630((int)g_pGameThread,"    %5d");
    pvVar2 = g_pGameThread;
    *(undefined4 *)((int)g_pGameThread + 0x8974) = 0xffffffff;
    *(undefined4 *)((int)pvVar2 + 0x8988) = 0;
  }
  return 1;
}

