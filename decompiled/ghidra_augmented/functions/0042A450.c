/* Raw Ghidra reference; not compilable reconstruction. Address: 0042A450 */

void FUN_0042a450(void)

{
  uint *puVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  int iVar6;
  int iVar7;
  int unaff_EBX;
  int iVar8;
  
  if (*(int *)(unaff_EBX + 8) != 0) {
    puVar1 = (uint *)(*(int *)(unaff_EBX + 8) + 4);
    *puVar1 = *puVar1 | 2;
  }
  if (*(int *)(unaff_EBX + 0x1cc) != 0) {
    puVar1 = (uint *)(*(int *)(unaff_EBX + 0x1cc) + 4);
    *puVar1 = *puVar1 | 2;
  }
  if (*(int *)(unaff_EBX + 0xc) != 0) {
    puVar1 = (uint *)(*(int *)(unaff_EBX + 0xc) + 4);
    *puVar1 = *puVar1 | 2;
  }
  iVar2 = DAT_00477834;
  if (*(int *)(unaff_EBX + 0x10) == 0) {
    iVar2 = *(int *)(unaff_EBX + 0x1c + DAT_00474c7c * 4);
    FUN_0042ab20(unaff_EBX);
    uVar3 = FUN_0042aa50(unaff_EBX);
    *(undefined4 *)(unaff_EBX + 0x9c) = uVar3;
    if (DAT_00491fc4 == 0) {
      *(undefined4 *)(iVar2 + 0xc) = DAT_00474c44;
      *(undefined2 *)(iVar2 + 0x10) = DAT_00474c48;
      *(undefined4 *)(iVar2 + 0x14) = DAT_00474c4c;
      *(undefined4 *)(iVar2 + 0x18) = DAT_00474c58;
      *(undefined4 *)(iVar2 + 0x1c) = DAT_00474c70;
      *(undefined4 *)(iVar2 + 0x20) = DAT_00474c98;
      *(undefined4 *)(iVar2 + 0x1b4) = DAT_00474c90;
    }
    iVar8 = DAT_00477834;
    *(undefined4 *)(iVar2 + 0x24) = *(undefined4 *)(DAT_00477834 + 0x3cc);
    *(undefined4 *)(iVar2 + 0x28) = *(undefined4 *)(iVar8 + 0x3d0);
    puVar5 = (undefined4 *)(iVar8 + 0x436c);
    puVar4 = (undefined4 *)(*(int *)(unaff_EBX + 0x1c + DAT_00474c7c * 4) + 0x2c);
    for (iVar6 = 0x42; iVar6 != 0; iVar6 = iVar6 + -1) {
      *puVar4 = *puVar5;
      puVar5 = puVar5 + 1;
      puVar4 = puVar4 + 1;
    }
    puVar5 = (undefined4 *)(iVar2 + 0x158);
    puVar4 = (undefined4 *)(iVar8 + 0x32e0);
    iVar6 = 4;
    do {
      puVar5[-9] = puVar4[-3];
      puVar5[-8] = puVar4[-2];
      puVar5[-1] = puVar4[-1];
      *puVar5 = *puVar4;
      puVar5[7] = puVar4[1];
      puVar5[8] = puVar4[2];
      puVar5[0xf] = puVar4[3];
      puVar5[0x10] = puVar4[4];
      puVar4 = puVar4 + 0x26;
      puVar5 = puVar5 + 2;
      iVar6 = iVar6 + -1;
    } while (iVar6 != 0);
    *(undefined4 *)(iVar2 + 0x1b8) = DAT_00474c9c;
    iVar2 = DAT_00474c7c;
    *(int *)(unaff_EBX + 0x1d0) = DAT_00474c7c;
    *(undefined4 *)(*(int *)(unaff_EBX + 0x1c + iVar2 * 4) + 0x1bc) =
         *(undefined4 *)(iVar8 + 0x4474);
  }
  else if (*(int *)(unaff_EBX + 0x10) == 1) {
    iVar8 = *(int *)(unaff_EBX + 0xb0 + DAT_00474c7c * 0x24);
    *(int *)(unaff_EBX + 0x1d0) = DAT_00474c7c;
    FUN_00428e10((undefined4 *)(iVar8 + 0x24));
    iVar6 = DAT_00477834;
    puVar5 = (undefined4 *)(iVar8 + 0x2c);
    puVar4 = (undefined4 *)(iVar2 + 0x436c);
    for (iVar7 = 0x42; iVar7 != 0; iVar7 = iVar7 + -1) {
      *puVar4 = *puVar5;
      puVar5 = puVar5 + 1;
      puVar4 = puVar4 + 1;
    }
    *(undefined4 *)(iVar6 + 0x4474) = *(undefined4 *)(iVar8 + 0x1bc);
    FUN_00426f70(iVar6);
    iVar2 = DAT_00477834;
    puVar5 = (undefined4 *)(iVar8 + 0x178);
    puVar4 = (undefined4 *)(DAT_00477834 + 0x32e0);
    iVar8 = 4;
    do {
      puVar4[-3] = puVar5[-0x11];
      puVar4[-2] = puVar5[-0x10];
      puVar4[-1] = puVar5[-9];
      *puVar4 = puVar5[-8];
      puVar4[1] = puVar5[-1];
      puVar4[2] = *puVar5;
      puVar4[3] = puVar5[7];
      puVar4[4] = puVar5[8];
      if (DAT_00474c6c + DAT_00474c68 * 3 == 5) {
        puVar4[3] = puVar5[-0x11];
        puVar4[4] = puVar5[-0x10];
      }
      puVar5 = puVar5 + 2;
      puVar4 = puVar4 + 0x26;
      iVar8 = iVar8 + -1;
    } while (iVar8 != 0);
    *(undefined4 *)(iVar2 + 0x332c) = 0;
    *(undefined4 *)(iVar2 + 0x33c4) = 0;
    *(undefined4 *)(iVar2 + 0x345c) = 0;
    *(undefined4 *)(iVar2 + 0x34f4) = 0;
    FUN_00424d90();
    *(undefined4 *)(unaff_EBX + 0x1c8) = 0;
    return;
  }
  *(undefined4 *)(unaff_EBX + 0x1c8) = 0;
  return;
}

