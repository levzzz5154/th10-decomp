/* Raw Ghidra reference; not compilable reconstruction. Address: 00426CF0 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00426cf0(int param_1)

{
  uint *puVar1;
  int iVar2;
  int iVar3;
  void *pvVar4;
  undefined4 *puVar5;
  undefined4 extraout_ECX;
  undefined4 extraout_ECX_00;
  undefined4 extraout_ECX_01;
  undefined4 extraout_ECX_02;
  bool bVar6;
  int local_10;
  
  iVar2 = param_1;
  *(undefined4 *)(param_1 + 0x458) = 4;
  puVar5 = FUN_00449950();
  puVar5[8] = 0;
  puVar5[0xd7] = puVar5[0xd7] | 0x40000000;
  FUN_00449870(puVar5,0x162);
  pvVar4 = g_pGameStateManager;
  FUN_004489d0(extraout_ECX,(int)g_pGameStateManager);
  FUN_004492f0(extraout_ECX_00,(int)pvVar4,param_1);
  param_1 = 0x20;
  do {
    puVar5 = FUN_00449950();
    puVar5[8] = 0;
    puVar5[0xd7] = puVar5[0xd7] | 0x40000000;
    FUN_00449870(puVar5,0x163);
    pvVar4 = g_pGameStateManager;
    FUN_004489d0(extraout_ECX_01,(int)g_pGameStateManager);
    FUN_004492f0(extraout_ECX_02,(int)pvVar4,local_10);
    param_1 = param_1 + -1;
  } while (param_1 != 0);
  if ((*(uint *)(iVar2 + 0x484) & 1) == 0) {
    *(undefined4 *)(iVar2 + 0x478) = 0;
    *(undefined4 *)(iVar2 + 0x474) = 0xfff0bdc1;
    *(undefined4 *)(iVar2 + 0x47c) = 0;
    *(undefined4 **)(iVar2 + 0x480) = &DAT_00476f78;
    *(uint *)(iVar2 + 0x484) = *(uint *)(iVar2 + 0x484) | 1;
  }
  iVar3 = DAT_00477810;
  bVar6 = DAT_00477810 != 0;
  *(undefined4 *)(iVar2 + 0x478) = 0;
  *(undefined4 *)(iVar2 + 0x47c) = 0;
  *(undefined4 *)(iVar2 + 0x474) = 0xffffffff;
  if ((bVar6) && ((*(uint *)(iVar3 + 0x58) & 0x200) == 0)) {
    FUN_0043dc90(&DAT_00492590,0);
  }
  if ((*(uint *)(iVar2 + 0x431c) & 1) == 0) {
    *(undefined4 *)(iVar2 + 0x4310) = 0;
    *(undefined4 *)(iVar2 + 0x430c) = 0xfff0bdc1;
    *(undefined4 *)(iVar2 + 0x4314) = 0;
    *(undefined4 **)(iVar2 + 0x4318) = &DAT_00476f78;
    *(uint *)(iVar2 + 0x431c) = *(uint *)(iVar2 + 0x431c) | 1;
  }
  *(undefined4 *)(iVar2 + 0x4310) = 6;
  *(undefined4 *)(iVar2 + 0x4314) = 0x40c00000;
  *(undefined4 *)(iVar2 + 0x430c) = 5;
  FUN_0043e710(*(undefined2 **)(iVar2 + 0x10));
  iVar2 = DAT_004776f4;
  if (0x3b < *(int *)(DAT_004776f4 + 0x3738)) {
    puVar1 = (uint *)(DAT_004776f4 + 0x378c);
    *(undefined4 *)(DAT_004776f4 + 0x3790) = 0;
    *(uint *)(iVar2 + 0x378c) = *puVar1 & 0xfffffffd;
    *(uint *)(iVar2 + 0xad4) = *(uint *)(iVar2 + 0xad4) & 0xfffffffd;
    *(uint *)(iVar2 + 0xe80) = *(uint *)(iVar2 + 0xe80) & 0xfffffffd;
    *(uint *)(iVar2 + 0x15d8) = *(uint *)(iVar2 + 0x15d8) & 0xfffffffd;
    *(uint *)(iVar2 + 0x1984) = *(uint *)(iVar2 + 0x1984) & 0xfffffffd;
    *(uint *)(iVar2 + 0x1d30) = *(uint *)(iVar2 + 0x1d30) & 0xfffffffd;
    *(uint *)(iVar2 + 0x20dc) = *(uint *)(iVar2 + 0x20dc) & 0xfffffffd;
    *(uint *)(iVar2 + 0x2488) = *(uint *)(iVar2 + 0x2488) & 0xfffffffd;
  }
  return;
}

