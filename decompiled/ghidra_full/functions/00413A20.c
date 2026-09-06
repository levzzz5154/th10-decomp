/* Raw Ghidra reference; not compilable reconstruction. Address: 00413A20 */

undefined4 FUN_00413a20(int param_1)

{
  char cVar1;
  char *pcVar2;
  undefined4 uVar3;
  int *piVar4;
  char *pcVar5;
  byte *pbVar6;
  uint uVar7;
  char *pcVar8;
  char *pcVar9;
  
  piVar4 = FUN_00447280(0x1c,(int)g_pGameStateManager,*(char **)(DAT_00477848 + 0x20));
  *(int **)(param_1 + 0x9e80) = piVar4;
  if (piVar4 != (int *)0x0) {
    if (DAT_00491be8 == 0) {
      pcVar2 = *(char **)(DAT_00477848 + 0x18 + DAT_00474c68 * 4);
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
      pbVar6 = FUN_0044b360((size_t *)0x0,0);
      *(byte **)(param_1 + 0x9ebc) = pbVar6;
      if (pbVar6 == (byte *)0x0) goto LAB_00413b27;
    }
    else {
      *(int *)(param_1 + 0x9ebc) = DAT_00491be8;
      DAT_00491be8 = 0;
    }
    if ((*(uint *)(param_1 + 0x9e70) & 1) == 0) {
      *(undefined4 *)(param_1 + 0x9e64) = 0;
      *(undefined4 *)(param_1 + 0x9e60) = 0xfff0bdc1;
      *(undefined4 *)(param_1 + 0x9e68) = 0;
      *(undefined4 **)(param_1 + 0x9e6c) = &DAT_00476f78;
      *(uint *)(param_1 + 0x9e70) = *(uint *)(param_1 + 0x9e70) | 1;
    }
    *(undefined4 *)(param_1 + 0x9e64) = 0;
    *(undefined4 *)(param_1 + 0x9e68) = 0;
    *(undefined4 *)(param_1 + 0x9e60) = 0xffffffff;
    uVar3 = DAT_00474c44;
    *(undefined4 *)(param_1 + 0x9ec0) = 0xffffffff;
    *(undefined4 *)(param_1 + 0x9ec4) = 0xffffffff;
    *(undefined4 *)(param_1 + 0x9e78) = uVar3;
    return 0;
  }
LAB_00413b27:
  FUN_0044b810(&DAT_00474f70,&DAT_0046cb68);
  return 0xffffffff;
}

