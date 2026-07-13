/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x00433230
 * Tracking name: FUN_00433230
 * Ghidra name: FUN_00433230
 * Tracked span: 832 bytes
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_00433230(int param_1)

{
  undefined *puVar1;
  char cVar2;
  int iVar3;
  char *pcVar4;
  void *pvVar5;
  uint uVar6;
  int iVar7;
  int iVar8;
  
  pvVar5 = g_pGameThread;
  if (*(int *)(param_1 + 0x20) == 2) {
    iVar7 = 0;
    iVar8 = DAT_00474c74 * 0xf0;
    *(undefined4 *)((int)g_pGameThread + 0x8988) = 1;
    uVar6 = 0xff;
    do {
      if (*(int *)(param_1 + 0x58ec) == 0) {
        *(uint *)((int)pvVar5 + 0x8974) = ((*(int *)(param_1 + 0x24) == iVar7) - 1 & 0xff404041) - 1
        ;
      }
      else {
        *(uint *)((int)pvVar5 + 0x8974) = (uVar6 << 8 | uVar6) << 8 | 0xff0000ff;
      }
      iVar3 = (DAT_00474c6c + DAT_00474c68 * 3) * 0x437c;
      if (*(int *)(iVar8 + iVar3 + DAT_0047783c + 0x28) == 0) {
        FUN_00401630((int)pvVar5,"%2d  %s  %9ld%d  ----/--/-- --:--  Stage -  ---%%");
      }
      else {
        _localtime((time_t *)(iVar8 + iVar3 + 0x28 + DAT_0047783c));
        FUN_00401630((int)g_pGameThread,"%2d  %s  %9ld%d  %.4d/%.2d/%.2d %.2d:%.2d  %s  %2.1f%%");
      }
      pvVar5 = g_pGameThread;
      iVar7 = iVar7 + 1;
      uVar6 = uVar6 - 0x10;
      iVar8 = iVar8 + 0x18;
    } while (0x5f < (int)uVar6);
    if (*(int *)(param_1 + 0x58ec) == 0) {
      puVar1 = PTR_s_ABCDEFGHIJKLMNOPQRSTUVWXYZabcdef_004746d8 + 1;
      pcVar4 = PTR_s_ABCDEFGHIJKLMNOPQRSTUVWXYZabcdef_004746d8;
      do {
        cVar2 = *pcVar4;
        pcVar4 = pcVar4 + 1;
      } while (cVar2 != '\0');
      *(undefined4 *)((int)g_pGameThread + 0x8974) = 0xffffffff;
      FUN_00401630((int)pvVar5,"%s");
      pvVar5 = g_pGameThread;
      *(undefined4 *)((int)g_pGameThread + 0x8974) = 0xffffff00;
      FUN_00401630((int)pvVar5,"_");
      pvVar5 = g_pGameThread;
      *(undefined4 *)((int)g_pGameThread + 0x8974) = 0xffffffff;
      iVar7 = 0;
      if (0 < (int)pcVar4 - (int)puVar1) {
        do {
          *(uint *)((int)pvVar5 + 0x8974) =
               ((*(int *)(param_1 + 0x58f4) != iVar7) - 1 & 0x7f7e80) - 0x7f7f80;
          FUN_00401630((int)pvVar5,"%c");
          iVar7 = iVar7 + 1;
          pvVar5 = g_pGameThread;
        } while (iVar7 < (int)pcVar4 - (int)puVar1);
      }
      *(undefined4 *)((int)pvVar5 + 0x8974) = 0xffffffff;
    }
  }
  return 1;
}

