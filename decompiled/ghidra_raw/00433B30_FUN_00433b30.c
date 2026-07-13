/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x00433B30
 * Tracking name: FUN_00433b30
 * Ghidra name: FUN_00433b30
 * Tracked span: 960 bytes
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_00433b30(int param_1)

{
  undefined *puVar1;
  char cVar2;
  char *pcVar3;
  void *pvVar4;
  int *piVar5;
  int iVar6;
  
  pvVar4 = g_pGameThread;
  if (*(int *)(param_1 + 0x20) == 2) {
    *(undefined4 *)((int)g_pGameThread + 0x8988) = 1;
    iVar6 = 0;
    piVar5 = (int *)(param_1 + 0x59e4);
    do {
      *(uint *)((int)pvVar4 + 0x8974) =
           ((*(int *)(param_1 + 0x24) != iVar6) - 1 & 0x7f7e80) - 0x7f7f80;
      if (*piVar5 == 0) {
        FUN_00401630((int)pvVar4,"No.%.2d -------- --/--/-- --:-- ------- ------- --- ---%%");
      }
      else {
        _localtime((time_t *)(*(int *)(*piVar5 + 0x18) + 0xc));
        FUN_00401630((int)g_pGameThread,"No.%.2d %s %.2d/%.2d/%.2d %.2d:%.2d %s %s %s %2.1f%%");
      }
      iVar6 = iVar6 + 1;
      piVar5 = piVar5 + 1;
      pvVar4 = g_pGameThread;
    } while (iVar6 < 0x19);
  }
  else {
    if (*(int *)(param_1 + 0x20) != 3) {
      return 1;
    }
    _localtime((time_t *)(*(int *)(DAT_00477838 + 0x18) + 0xc));
    FUN_00401630((int)g_pGameThread,"No.%.2d %s %.2d/%.2d/%.2d %.2d:%.2d %s %s %s %2.1f%%");
    pvVar4 = g_pGameThread;
    if (9 < *(int *)(param_1 + 0x2b4)) {
      puVar1 = PTR_s_ABCDEFGHIJKLMNOPQRSTUVWXYZabcdef_004746d8 + 1;
      pcVar3 = PTR_s_ABCDEFGHIJKLMNOPQRSTUVWXYZabcdef_004746d8;
      do {
        cVar2 = *pcVar3;
        pcVar3 = pcVar3 + 1;
      } while (cVar2 != '\0');
      *(undefined4 *)((int)g_pGameThread + 0x8974) = 0xffffffff;
      FUN_00401630((int)pvVar4,"%s");
      pvVar4 = g_pGameThread;
      *(undefined4 *)((int)g_pGameThread + 0x8974) = 0xffffff00;
      FUN_00401630((int)pvVar4,"_");
      pvVar4 = g_pGameThread;
      *(undefined4 *)((int)g_pGameThread + 0x8974) = 0xffffffff;
      iVar6 = 0;
      if (0 < (int)pcVar3 - (int)puVar1) {
        do {
          *(uint *)((int)pvVar4 + 0x8974) =
               ((*(int *)(param_1 + 0x58f4) != iVar6) - 1 & 0x7f7e80) - 0x7f7f80;
          FUN_00401630((int)pvVar4,"%c");
          iVar6 = iVar6 + 1;
          pvVar4 = g_pGameThread;
        } while (iVar6 < (int)pcVar3 - (int)puVar1);
      }
      *(undefined4 *)((int)pvVar4 + 0x8974) = 0xffffffff;
    }
  }
  *(undefined4 *)((int)pvVar4 + 0x8974) = 0xffffffff;
  *(undefined4 *)((int)pvVar4 + 0x8988) = 0;
  return 1;
}

