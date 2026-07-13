/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x00419650
 * Tracking name: FUN_00419650
 * Ghidra name: FUN_00419650
 * Tracked span: 592 bytes
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_00419650(void)

{
  float fVar1;
  float fVar2;
  int *piVar3;
  int unaff_EBX;
  float *pfVar4;
  int iVar5;
  float *pfVar6;
  float10 fVar7;
  float10 fVar8;
  float10 fVar9;
  float10 extraout_ST0;
  float10 extraout_ST1;
  float10 extraout_ST1_00;
  ulonglong uVar10;
  int local_4;
  
  if (*(int *)(unaff_EBX + 0xd8) != DAT_00474c84) {
    *(undefined4 *)(unaff_EBX + 0x14) = 0;
  }
  FUN_00419120(unaff_EBX,1);
  pfVar6 = (float *)(unaff_EBX + 0x17c);
  fVar7 = (float10)*(float *)(DAT_00477834 + 0x3c0) + (float10)_DAT_00470b4c;
  pfVar4 = (float *)(unaff_EBX + 0x108);
  local_4 = 10;
  fVar8 = (float10)*(float *)(DAT_00477834 + 0x3c4) + (float10)_DAT_00470b48;
LAB_004196b2:
  fVar1 = pfVar6[-0x28];
  if (fVar1 == 0.0) {
LAB_004196bc:
    iVar5 = 0;
  }
  else {
    for (piVar3 = *(int **)((int)g_pGameStateManager + 0x72dad4); piVar3 != (int *)0x0;
        piVar3 = (int *)piVar3[1]) {
      if (*(float *)*piVar3 == fVar1) goto LAB_004196f8;
    }
    piVar3 = *(int **)((int)g_pGameStateManager + 0x72dadc);
    if (piVar3 == (int *)0x0) goto LAB_004196bc;
    do {
      if (*(float *)*piVar3 == fVar1) goto LAB_004196f8;
      piVar3 = (int *)piVar3[1];
    } while (piVar3 != (int *)0x0);
    iVar5 = 0;
  }
  goto LAB_004196fe;
LAB_004196f8:
  iVar5 = *piVar3;
  if (iVar5 == 0) {
LAB_004196fe:
    pfVar6[-0x28] = 0.0;
    if (iVar5 == 0) goto LAB_00419858;
  }
  if (*(int *)(iVar5 + 300) == 0) {
    fVar9 = ABS(fVar7 - (float10)pfVar4[-1]);
    fVar1 = (float)ABS(fVar8 - (float10)*pfVar4);
    fVar2 = *pfVar6 * _DAT_00470b0c;
    if (((float10)fVar2 <= fVar9) ||
       (*(float *)(iVar5 + 0x50) * *(float *)(iVar5 + 0x40) * _DAT_00470b0c <= fVar1)) {
      if (((float10)(fVar2 + _DAT_00470bcc) <= fVar9) ||
         (*(float *)(iVar5 + 0x50) * *(float *)(iVar5 + 0x40) * _DAT_00470b0c <= fVar1)) {
        if (((float10)fVar2 <= fVar9) ||
           (*(float *)(iVar5 + 0x50) * *(float *)(iVar5 + 0x40) * _DAT_00470b0c + _DAT_00470bcc <=
            fVar1)) {
          *(undefined1 *)(iVar5 + 0x2ff) = *(undefined1 *)(iVar5 + 0x310);
        }
        else {
          uVar10 = FUN_00463b2c();
          *(char *)(iVar5 + 0x2ff) = (char)uVar10;
          fVar8 = extraout_ST0;
          fVar7 = extraout_ST1_00;
        }
      }
      else {
        fVar7 = fVar8;
        uVar10 = FUN_00463b2c();
        *(char *)(iVar5 + 0x2ff) = (char)uVar10;
        fVar8 = extraout_ST1;
      }
    }
    else {
      *(byte *)(iVar5 + 0x2ff) = *(byte *)(iVar5 + 0x310) >> 2;
    }
  }
LAB_00419858:
  pfVar6 = pfVar6 + 1;
  pfVar4 = pfVar4 + 3;
  local_4 = local_4 + -1;
  if (local_4 == 0) {
    *(int *)(unaff_EBX + 0x14) = *(int *)(unaff_EBX + 0x14) + 1;
    *(int *)(unaff_EBX + 0x10) = *(int *)(unaff_EBX + 0x10) + 1;
    return 1;
  }
  goto LAB_004196b2;
}

