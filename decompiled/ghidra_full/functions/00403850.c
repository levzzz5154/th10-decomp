/* Raw Ghidra reference; not compilable reconstruction. Address: 00403850 */

undefined4 FUN_00403850(char *param_1)

{
  char cVar1;
  short *psVar2;
  char *pcVar3;
  byte *pbVar4;
  undefined4 *puVar5;
  int *piVar6;
  void *pvVar7;
  uint uVar8;
  uint uVar9;
  int iVar10;
  int unaff_EBX;
  char *pcVar11;
  undefined4 *puVar12;
  char *pcVar13;
  
  if (*(int *)(unaff_EBX + 0x2a44) == 0) {
    DAT_00497c38._0_1_ = 0;
    pcVar3 = param_1;
    do {
      cVar1 = *pcVar3;
      pcVar3 = pcVar3 + 1;
    } while (cVar1 != '\0');
    pcVar13 = (char *)0x497c37;
    do {
      pcVar11 = pcVar13 + 1;
      pcVar13 = pcVar13 + 1;
    } while (*pcVar11 != '\0');
    pcVar11 = param_1;
    for (uVar8 = (uint)((int)pcVar3 - (int)param_1) >> 2; uVar8 != 0; uVar8 = uVar8 - 1) {
      *(undefined4 *)pcVar13 = *(undefined4 *)pcVar11;
      pcVar11 = pcVar11 + 4;
      pcVar13 = pcVar13 + 4;
    }
    for (uVar8 = (int)pcVar3 - (int)param_1 & 3; uVar8 != 0; uVar8 = uVar8 - 1) {
      *pcVar13 = *pcVar11;
      pcVar11 = pcVar11 + 1;
      pcVar13 = pcVar13 + 1;
    }
    pbVar4 = FUN_0044b360((size_t *)(unaff_EBX + 0x2a48),0);
    *(byte **)(unaff_EBX + 0x2a44) = pbVar4;
    if (pbVar4 == (byte *)0x0) {
      return 0xffffffff;
    }
  }
  puVar5 = _malloc(*(size_t *)(unaff_EBX + 0x2a48));
  uVar8 = *(uint *)(unaff_EBX + 0x2a48);
  *(undefined4 **)(unaff_EBX + 0x10) = puVar5;
  puVar12 = *(undefined4 **)(unaff_EBX + 0x2a44);
  for (uVar9 = uVar8 >> 2; pvVar7 = g_pGameStateManager, uVar9 != 0; uVar9 = uVar9 - 1) {
    *puVar5 = *puVar12;
    puVar12 = puVar12 + 1;
    puVar5 = puVar5 + 1;
  }
  for (uVar8 = uVar8 & 3; uVar8 != 0; uVar8 = uVar8 - 1) {
    *(undefined1 *)puVar5 = *(undefined1 *)puVar12;
    puVar12 = (undefined4 *)((int)puVar12 + 1);
    puVar5 = (undefined4 *)((int)puVar5 + 1);
  }
  piVar6 = FUN_00447280((*(uint *)(unaff_EBX + 0x2a30) & 1) + 4,(int)pvVar7,
                        (char *)(*(int *)(unaff_EBX + 0x10) + 0x10));
  *(int **)(unaff_EBX + 0x178) = piVar6;
  if (piVar6 == (int *)0x0) {
    FUN_0044b810(&DAT_00474f70,&DAT_0046cbc0);
    return 0xffffffff;
  }
  psVar2 = *(short **)(unaff_EBX + 0x10);
  *(short **)(unaff_EBX + 0x14) = psVar2 + 0x48;
  *(int *)(unaff_EBX + 0x18) = *(int *)(psVar2 + 2) + (int)psVar2;
  *(int *)(unaff_EBX + 0x1c) = *(int *)(psVar2 + 4) + (int)psVar2;
  iVar10 = 0;
  if (0 < *psVar2) {
    do {
      *(int *)(*(int *)(unaff_EBX + 0x14) + iVar10 * 4) =
           *(int *)(*(int *)(unaff_EBX + 0x14) + iVar10 * 4) + *(int *)(unaff_EBX + 0x10);
      iVar10 = iVar10 + 1;
    } while (iVar10 < **(short **)(unaff_EBX + 0x10));
  }
  pvVar7 = _malloc(*(short *)(*(int *)(unaff_EBX + 0x10) + 2) * 0x3ac);
  *(void **)(unaff_EBX + 0x17c) = pvVar7;
  return 0;
}

