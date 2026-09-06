/* Raw Ghidra reference; not compilable reconstruction. Address: 0040B560 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_0040b560(int param_1)

{
  int iVar1;
  char cVar2;
  char *pcVar3;
  void *pvVar4;
  undefined4 *puVar5;
  char *pcVar6;
  byte *pbVar7;
  uint uVar8;
  char *pcVar9;
  char *pcVar10;
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_004657bb;
  local_c = ExceptionList;
  ExceptionList = &local_c;
  puVar5 = operator_new(0x24);
  if (puVar5 == (undefined4 *)0x0) {
    puVar5 = (undefined4 *)0x0;
  }
  else {
    puVar5[2] = 0;
    puVar5[3] = 0;
    puVar5[4] = 0;
    *puVar5 = 0;
    puVar5[1] = puVar5[1] & 0xfffffffe;
    puVar5[5] = puVar5;
    puVar5[6] = 0;
    puVar5[7] = 0;
  }
  puVar5[1] = puVar5[1] | 3;
  iVar1 = DAT_00491be4;
  puVar5[2] = &LAB_0040ba70;
  puVar5[3] = 0;
  puVar5[4] = 0;
  puVar5[8] = param_1;
  FUN_00449ae0(iVar1);
  *(undefined4 **)(param_1 + 8) = puVar5;
  puVar5 = operator_new(0x24);
  if (puVar5 == (undefined4 *)0x0) {
    puVar5 = (undefined4 *)0x0;
  }
  else {
    puVar5[2] = 0;
    puVar5[3] = 0;
    puVar5[4] = 0;
    *puVar5 = 0;
    puVar5[1] = puVar5[1] & 0xfffffffe;
    puVar5[5] = puVar5;
    puVar5[6] = 0;
    puVar5[7] = 0;
  }
  iVar1 = DAT_00491be4;
  puVar5[1] = puVar5[1] | 3;
  puVar5[2] = &LAB_0040ba80;
  puVar5[3] = 0;
  puVar5[4] = 0;
  puVar5[8] = param_1;
  FUN_00449b70(iVar1);
  pvVar4 = g_pGameThread;
  *(undefined4 **)(param_1 + 0xc) = puVar5;
  if (*(int *)((int)pvVar4 + 0x89a4) == 0) {
    puVar5 = (undefined4 *)FUN_00448d50(*(undefined2 **)((int)pvVar4 + 0x8994));
    *(undefined4 *)((int)pvVar4 + 0x89a4) = *puVar5;
  }
  iVar1 = DAT_00474c6c + DAT_00474c68 * 3;
  *(int *)(param_1 + 0x1c) = iVar1;
  if ((_DAT_00474c90 == 0) && (0 < DAT_00474c74)) {
    *(int *)(param_1 + 0x1c) = iVar1 + 6;
  }
  iVar1 = DAT_0047783c;
  if (*(char *)(*(int *)(param_1 + 0x1c) + 0x1d882 + DAT_0047783c) == '\0') {
    *(uint *)(param_1 + 0x20) = *(uint *)(param_1 + 0x20) | 1;
  }
  if (*(char *)(iVar1 + 0x1d88e) == '\0') {
    *(uint *)(param_1 + 0x20) = *(uint *)(param_1 + 0x20) | 2;
  }
  *(undefined1 *)(*(int *)(param_1 + 0x1c) + 0x1d882 + iVar1) = 1;
  if (5 < *(int *)(param_1 + 0x1c)) {
    *(undefined1 *)(iVar1 + 0x1d88e) = 1;
  }
  pcVar3 = (&PTR_s_e00_msg_00474440)[*(int *)(param_1 + 0x1c)];
  DAT_00497c38._0_1_ = 0;
  pcVar6 = pcVar3;
  do {
    cVar2 = *pcVar6;
    pcVar6 = pcVar6 + 1;
  } while (cVar2 != '\0');
  pcVar10 = (char *)0x497c37;
  do {
    pcVar9 = pcVar10 + 1;
    pcVar10 = pcVar10 + 1;
  } while (*pcVar9 != '\0');
  pcVar9 = pcVar3;
  for (uVar8 = (uint)((int)pcVar6 - (int)pcVar3) >> 2; uVar8 != 0; uVar8 = uVar8 - 1) {
    *(undefined4 *)pcVar10 = *(undefined4 *)pcVar9;
    pcVar9 = pcVar9 + 4;
    pcVar10 = pcVar10 + 4;
  }
  for (uVar8 = (int)pcVar6 - (int)pcVar3 & 3; uVar8 != 0; uVar8 = uVar8 - 1) {
    *pcVar10 = *pcVar9;
    pcVar9 = pcVar9 + 1;
    pcVar10 = pcVar10 + 1;
  }
  pbVar7 = FUN_0044b360((size_t *)0x0,0);
  *(byte **)(param_1 + 0x14) = pbVar7;
  if (pbVar7 == (byte *)0x0) {
    FUN_0044b810(&DAT_00474f70,&DAT_0046cb68);
    ExceptionList = local_c;
    return 0xffffffff;
  }
  puVar5 = operator_new(0xec);
  local_4 = 0;
  if (puVar5 == (undefined4 *)0x0) {
    puVar5 = (undefined4 *)0x0;
  }
  else {
    puVar5 = FUN_0040ba90(puVar5,*(int *)(*(int *)(param_1 + 0x14) + 4) + *(int *)(param_1 + 0x14));
  }
  *(undefined4 **)(param_1 + 0x18) = puVar5;
  ExceptionList = local_c;
  return 0;
}

