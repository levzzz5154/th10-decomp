/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x00422660
 * Tracking name: FUN_00422660
 * Ghidra name: FUN_00422660
 * Tracked span: 1072 bytes
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_00422660(int *param_1)

{
  int iVar1;
  void *pvVar2;
  int iVar3;
  int *piVar4;
  int iVar5;
  
  piVar4 = param_1;
  pvVar2 = g_pGameThread;
  *(undefined4 *)((int)g_pGameThread + 0x8988) = 1;
  switch(param_1[1]) {
  case 10:
  case 0x11:
    param_1 = param_1 + 0x7b;
    iVar5 = 0;
    do {
      *(uint *)((int)pvVar2 + 0x8974) = ((piVar4[9] != iVar5) - 1 & 0x7f7e80) - 0x7f7f80;
      if (*param_1 == 0) {
        FUN_00401630((int)pvVar2,"No.%.2d -------- --/--/-- ------- - St-");
      }
      else {
        _localtime((time_t *)(*(int *)(*param_1 + 0x18) + 0xc));
        FUN_00401630((int)g_pGameThread,"No.%.2d %s %.2d/%.2d/%.2d %s %s %s");
      }
      iVar5 = iVar5 + 1;
      param_1 = param_1 + 1;
      pvVar2 = g_pGameThread;
    } while (iVar5 < 0x19);
    break;
  case 0xb:
  case 0x12:
    FUN_004224c0((int)param_1);
    _localtime((time_t *)(*(int *)(DAT_00477838 + 0x18) + 0xc));
    FUN_00401630((int)g_pGameThread,"No.%.2d          %.2d/%.2d/%.2d %s %s %s");
    pvVar2 = g_pGameThread;
    goto switchD_00422691_caseD_d;
  case 0xc:
  case 0x13:
    piVar4 = (int *)param_1[9];
    FUN_00401630((int)pvVar2,"            Score Ranking!!");
    if (param_1[0x7a] == 0) {
      FUN_004224c0((int)param_1);
      param_1 = piVar4;
    }
    else {
      param_1 = (int *)0xffffffff;
    }
    piVar4 = (int *)0x0;
    do {
      iVar5 = DAT_0047783c;
      pvVar2 = g_pGameThread;
      *(uint *)((int)g_pGameThread + 0x8974) = ((piVar4 != param_1) - 1 & 0x7f7e80) - 0x7f7f80;
      iVar1 = (DAT_00474c6c + DAT_00474c68 * 3) * 0x437c;
      iVar3 = ((int)piVar4 + DAT_00474c74 * 10) * 0x18;
      if (*(int *)(iVar3 + iVar1 + 0x28 + iVar5) == 0) {
        FUN_00401630((int)pvVar2,"%2d %s %.9ld%d --/--/-- Stage -");
      }
      else {
        _localtime((time_t *)(iVar3 + iVar1 + 0x28 + iVar5));
        FUN_00401630((int)g_pGameThread,"%2d %s %.9ld%d %.2d/%.2d/%.2d %s");
      }
      piVar4 = (int *)((int)piVar4 + 1);
    } while ((int)piVar4 < 10);
    break;
  default:
    goto switchD_00422691_caseD_d;
  }
  pvVar2 = g_pGameThread;
  *(undefined4 *)((int)g_pGameThread + 0x8974) = 0xffffffff;
switchD_00422691_caseD_d:
  *(undefined4 *)((int)pvVar2 + 0x8988) = 0;
  return 1;
}

