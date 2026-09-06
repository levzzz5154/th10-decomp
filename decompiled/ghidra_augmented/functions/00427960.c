/* Raw Ghidra reference; not compilable reconstruction. Address: 00427960 */

void FUN_00427960(void)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  undefined4 *puVar7;
  int unaff_ESI;
  ulonglong uVar8;
  
  iVar4 = DAT_00477834;
  iVar2 = *(int *)(DAT_00477834 + 0x4474);
  iVar5 = *(int *)(unaff_ESI + 0x88) * 0x40;
  iVar6 = *(int *)(iVar5 + 0x43ac + DAT_00477834);
  iVar5 = iVar5 + DAT_00477834;
  *(int *)(unaff_ESI + 0x34) = iVar6;
  iVar5 = *(int *)(iVar5 + 0x43b0);
  *(int *)(unaff_ESI + 0x38) = iVar5;
  if (iVar2 == 0) {
    iVar3 = *(int *)(iVar4 + 0x3d0);
    *(int *)(unaff_ESI + 0x44) = iVar6 - *(int *)(iVar4 + 0x3cc);
    *(int *)(unaff_ESI + 0x48) = iVar5 - iVar3;
  }
  else {
    iVar5 = *(int *)(unaff_ESI + 0x48);
    iVar6 = *(int *)(iVar4 + 0x3d0);
    piVar1 = (int *)(*(int *)(unaff_ESI + 0x88) * 0x40 + 0x43ac + iVar4);
    *piVar1 = *(int *)(iVar4 + 0x3cc) + *(int *)(unaff_ESI + 0x44);
    piVar1[1] = iVar6 + iVar5;
    iVar6 = *(int *)(unaff_ESI + 0x88) * 8;
    iVar5 = iVar6 + 1;
    if (iVar5 <= iVar6 + 7) {
      puVar7 = (undefined4 *)(iVar4 + 0x4370 + iVar5 * 8);
      do {
        uVar8 = FUN_00463b2c();
        puVar7[-1] = (int)uVar8;
        uVar8 = FUN_00463b2c();
        *puVar7 = (int)uVar8;
        iVar5 = iVar5 + 1;
        puVar7 = puVar7 + 2;
      } while (iVar5 <= *(int *)(unaff_ESI + 0x88) * 8 + 7);
    }
  }
  iVar5 = *(int *)(iVar4 + 0x3d0);
  *(int *)(unaff_ESI + 0x34) = *(int *)(unaff_ESI + 0x44) + *(int *)(iVar4 + 0x3cc);
  *(int *)(unaff_ESI + 0x38) = *(int *)(unaff_ESI + 0x48) + iVar5;
  *(int *)(unaff_ESI + 0x84) = iVar2;
  return;
}

