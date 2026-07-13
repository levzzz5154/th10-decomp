/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x00431BA0
 * Tracking name: FUN_00431ba0
 * Ghidra name: FUN_00431ba0
 * Tracked span: 832 bytes
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_00431ba0(int *param_1)

{
  int *piVar1;
  void *pvVar2;
  int iVar3;
  
  piVar1 = param_1;
  pvVar2 = g_pGameThread;
  if (param_1[8] == 2) {
    param_1 = param_1 + 0x1679;
    *(undefined4 *)((int)g_pGameThread + 0x8988) = 1;
    iVar3 = 0;
    do {
      *(uint *)((int)pvVar2 + 0x8974) = ((piVar1[9] != iVar3) - 1 & 0x7f7e80) - 0x7f7f80;
      if (*param_1 == 0) {
        FUN_00401630((int)pvVar2,"No.%.2d -------- --/--/-- --:-- ------- ------- --- ---%%");
      }
      else {
        _localtime((time_t *)(*(int *)(*param_1 + 0x18) + 0xc));
        FUN_00401630((int)g_pGameThread,"No.%.2d %s %.2d/%.2d/%.2d %.2d:%.2d %s %s %s %2.1f%%");
      }
      iVar3 = iVar3 + 1;
      param_1 = param_1 + 1;
      pvVar2 = g_pGameThread;
    } while (iVar3 < 0x19);
  }
  else {
    if (param_1[8] != 4) {
      return 1;
    }
    iVar3 = *(int *)(param_1[param_1[0x1677] + 0x1679] + 0x18);
    *(undefined4 *)((int)g_pGameThread + 0x8988) = 1;
    _localtime((time_t *)(iVar3 + 0xc));
    FUN_00401630((int)g_pGameThread,"No.%.2d %s %.2d/%.2d/%.2d %.2d:%.2d %s %s %s %2.1f%%");
    if (9 < param_1[0xad]) {
      iVar3 = 1;
      param_1 = (int *)0x24;
      do {
        pvVar2 = g_pGameThread;
        *(uint *)((int)g_pGameThread + 0x8974) =
             ((piVar1[9] != iVar3 + -1) - 1 & 0x7f7e80) - 0x7f7f80;
        if (*(int *)((int)param_1 + piVar1[piVar1[0x1677] + 0x1679] + 0xb0) == 0) {
          FUN_00401630((int)pvVar2,"%s  ---------");
        }
        else {
          FUN_00401630((int)pvVar2,"%s  %.8d%d");
        }
        iVar3 = iVar3 + 1;
        param_1 = param_1 + 9;
      } while (iVar3 < 8);
    }
  }
  pvVar2 = g_pGameThread;
  *(undefined4 *)((int)g_pGameThread + 0x8974) = 0xffffffff;
  *(undefined4 *)((int)pvVar2 + 0x8988) = 0;
  return 1;
}

