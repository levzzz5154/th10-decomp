/* Raw Ghidra reference; not compilable reconstruction. Address: 0040C3C0 */

undefined4 FUN_0040c3c0(void)

{
  char cVar1;
  char *pcVar2;
  int iVar3;
  void *pvVar4;
  char *pcVar5;
  int *piVar6;
  uint uVar7;
  int unaff_EBX;
  char *pcVar8;
  char *pcVar9;
  
  pvVar4 = g_pGameStateManager;
  pcVar2 = *(char **)(unaff_EBX + 0x70);
  DAT_00497c38._0_1_ = 0;
  pcVar5 = pcVar2;
  do {
    cVar1 = *pcVar5;
    pcVar5 = pcVar5 + 1;
  } while (cVar1 != '\0');
  pcVar9 = (char *)0x497c37;
  do {
    pcVar8 = pcVar9 + 1;
    pcVar9 = pcVar9 + 1;
  } while (*pcVar8 != '\0');
  pcVar8 = pcVar2;
  for (uVar7 = (uint)((int)pcVar5 - (int)pcVar2) >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
    *(undefined4 *)pcVar9 = *(undefined4 *)pcVar8;
    pcVar8 = pcVar8 + 4;
    pcVar9 = pcVar9 + 4;
  }
  for (uVar7 = (int)pcVar5 - (int)pcVar2 & 3; uVar7 != 0; uVar7 = uVar7 - 1) {
    *pcVar9 = *pcVar8;
    pcVar8 = pcVar8 + 1;
    pcVar9 = pcVar9 + 1;
  }
  piVar6 = FUN_00447280(*(int *)(*(int *)(unaff_EBX + 0x54) + 4) + 0x1d,(int)pvVar4,
                        (char *)&DAT_00497c38);
  pvVar4 = g_pGameThread;
  iVar3 = *(int *)(unaff_EBX + 0x54);
  *(int **)(unaff_EBX + 0x80 + *(int *)(iVar3 + 4) * 4) = piVar6;
  *(uint *)(unaff_EBX + 0x74) = *(uint *)(unaff_EBX + 0x74) & 0xfffffffb;
  FUN_00409e50(iVar3);
  *(undefined4 *)((int)pvVar4 + 0x89a4) = 0;
  return 0;
}

