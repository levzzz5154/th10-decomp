/* Raw Ghidra reference; not compilable reconstruction. Address: 00403C80 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_00403c80(int param_1)

{
  uint uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  undefined4 uVar8;
  undefined4 uVar9;
  undefined4 uVar10;
  float fVar11;
  undefined4 *puVar12;
  int iVar13;
  float *pfVar14;
  float *pfVar15;
  undefined4 *puVar16;
  float10 fVar17;
  ulonglong uVar18;
  undefined8 uVar19;
  float local_1c [7];
  
  if (**(int **)(param_1 + 0x4c) <= *(int *)(param_1 + 0x3c)) {
    do {
      iVar13 = *(int *)(param_1 + 0x4c);
      switch(*(undefined2 *)(iVar13 + 4)) {
      case 0:
        goto switchD_00403cb4_caseD_0;
      case 1:
        iVar13 = *(int *)(iVar13 + 0xc);
        if ((*(uint *)(param_1 + 0x48) & 1) == 0) {
          *(undefined4 *)(param_1 + 0x3c) = 0;
          *(undefined4 *)(param_1 + 0x38) = 0xfff0bdc1;
          *(undefined4 *)(param_1 + 0x40) = 0;
          *(undefined4 **)(param_1 + 0x44) = &DAT_00476f78;
          *(uint *)(param_1 + 0x48) = *(uint *)(param_1 + 0x48) | 1;
        }
        *(int *)(param_1 + 0x3c) = iVar13;
        *(int *)(param_1 + 0x38) = iVar13 + -1;
        *(float *)(param_1 + 0x40) = (float)iVar13;
        *(int *)(param_1 + 0x4c) = *(int *)(param_1 + 0x1c) + *(int *)(*(int *)(param_1 + 0x4c) + 8)
        ;
        goto LAB_0040425d;
      case 2:
        pfVar14 = (float *)(param_1 + 0x2a4c);
        pfVar15 = (float *)(param_1 + 0x2b3c);
        *pfVar15 = *pfVar14;
        *(undefined4 *)(param_1 + 0x2b40) = *(undefined4 *)(param_1 + 0x2a50);
        *(undefined4 *)(param_1 + 0x2b44) = *(undefined4 *)(param_1 + 0x2a54);
        *pfVar14 = *(float *)(iVar13 + 8);
        *(undefined4 *)(param_1 + 0x2a50) = *(undefined4 *)(iVar13 + 0xc);
        *(undefined4 *)(param_1 + 0x2a54) = *(undefined4 *)(iVar13 + 0x10);
        *pfVar15 = *pfVar14 - *pfVar15;
        *(float *)(param_1 + 0x2b40) = *(float *)(param_1 + 0x2a50) - *(float *)(param_1 + 0x2b40);
        *(float *)(param_1 + 0x2b44) = *(float *)(param_1 + 0x2a54) - *(float *)(param_1 + 0x2b44);
        break;
      case 3:
        uVar2 = *(undefined4 *)(iVar13 + 0x10);
        uVar3 = *(undefined4 *)(iVar13 + 0x14);
        uVar4 = *(undefined4 *)(iVar13 + 0x18);
        *(undefined4 *)(param_1 + 0xe0) = *(undefined4 *)(iVar13 + 8);
        *(undefined4 *)(param_1 + 0xe4) = *(undefined4 *)(iVar13 + 0xc);
        *(undefined4 *)(param_1 + 0x9c) = *(undefined4 *)(param_1 + 0x2a4c);
        *(undefined4 *)(param_1 + 0xa0) = *(undefined4 *)(param_1 + 0x2a50);
        *(undefined4 *)(param_1 + 0xa4) = *(undefined4 *)(param_1 + 0x2a54);
        *(undefined4 *)(param_1 + 0xa8) = uVar2;
        *(undefined4 *)(param_1 + 0xac) = uVar3;
        *(undefined4 *)(param_1 + 0xb0) = uVar4;
        goto LAB_00404086;
      case 4:
        *(undefined4 *)(param_1 + 0x2a58) = *(undefined4 *)(iVar13 + 8);
        *(undefined4 *)(param_1 + 0x2a5c) = *(undefined4 *)(iVar13 + 0xc);
        *(undefined4 *)(param_1 + 0x2a60) = *(undefined4 *)(iVar13 + 0x10);
        break;
      case 5:
        uVar2 = *(undefined4 *)(iVar13 + 0x10);
        uVar3 = *(undefined4 *)(iVar13 + 0x14);
        uVar4 = *(undefined4 *)(iVar13 + 0x18);
        *(undefined4 *)(param_1 + 0x94) = *(undefined4 *)(iVar13 + 8);
        *(undefined4 *)(param_1 + 0x98) = *(undefined4 *)(iVar13 + 0xc);
        *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(param_1 + 0x2a58);
        *(undefined4 *)(param_1 + 0x54) = *(undefined4 *)(param_1 + 0x2a5c);
        *(undefined4 *)(param_1 + 0x58) = *(undefined4 *)(param_1 + 0x2a60);
        *(undefined4 *)(param_1 + 0x5c) = uVar2;
        *(undefined4 *)(param_1 + 0x60) = uVar3;
        *(undefined4 *)(param_1 + 100) = uVar4;
        goto LAB_00404182;
      case 6:
        *(undefined4 *)(param_1 + 0x2a64) = *(undefined4 *)(iVar13 + 8);
        *(undefined4 *)(param_1 + 0x2a68) = *(undefined4 *)(iVar13 + 0xc);
        *(undefined4 *)(param_1 + 0x2a6c) = *(undefined4 *)(iVar13 + 0x10);
        break;
      case 7:
        *(undefined4 *)(param_1 + 0x2a94) = *(undefined4 *)(iVar13 + 8);
        break;
      case 8:
        uVar1 = *(uint *)(iVar13 + 8);
        *(uint *)(param_1 + 0x2b60) = uVar1;
        *(float *)(param_1 + 0x2b50) = (float)(uVar1 & 0xff);
        *(float *)(param_1 + 0x2b54) = (float)*(byte *)(param_1 + 0x2b61);
        *(float *)(param_1 + 0x2b58) = (float)*(byte *)(param_1 + 0x2b62);
        *(float *)(param_1 + 0x2b5c) = (float)*(byte *)(param_1 + 0x2b63);
        *(undefined4 *)(param_1 + 0x2b48) = *(undefined4 *)(iVar13 + 0xc);
        *(undefined4 *)(param_1 + 0x2b4c) = *(undefined4 *)(iVar13 + 0x10);
        break;
      case 9:
        FUN_00405040(*(undefined4 *)(iVar13 + 0x14),*(undefined4 *)(iVar13 + 0x18),
                     (float)*(byte *)(iVar13 + 0x10),(float)*(byte *)(iVar13 + 0x11),
                     (float)*(byte *)(iVar13 + 0x12),(float)*(byte *)(iVar13 + 0x13));
        *(undefined4 *)(param_1 + 0x16c) = *(undefined4 *)(iVar13 + 8);
        uVar2 = *(undefined4 *)(iVar13 + 0xc);
        puVar12 = (undefined4 *)(param_1 + 0x2b48);
        puVar16 = (undefined4 *)(param_1 + 0xe8);
        for (iVar13 = 7; iVar13 != 0; iVar13 = iVar13 + -1) {
          *puVar16 = *puVar12;
          puVar12 = puVar12 + 1;
          puVar16 = puVar16 + 1;
        }
        pfVar14 = local_1c;
        pfVar15 = (float *)(param_1 + 0x104);
        for (iVar13 = 7; iVar13 != 0; iVar13 = iVar13 + -1) {
          *pfVar15 = *pfVar14;
          pfVar14 = pfVar14 + 1;
          pfVar15 = pfVar15 + 1;
        }
        *(undefined4 *)(param_1 + 0x170) = uVar2;
        if ((*(uint *)(param_1 + 0x168) & 1) == 0) {
          *(undefined4 *)(param_1 + 0x15c) = 0;
          *(undefined4 *)(param_1 + 0x158) = 0xfff0bdc1;
          *(undefined4 *)(param_1 + 0x160) = 0;
          *(undefined4 **)(param_1 + 0x164) = &DAT_00476f78;
          *(uint *)(param_1 + 0x168) = *(uint *)(param_1 + 0x168) | 1;
        }
        *(undefined4 *)(param_1 + 0x15c) = 0;
        *(undefined4 *)(param_1 + 0x160) = 0;
        *(undefined4 *)(param_1 + 0x158) = 0xffffffff;
        break;
      case 10:
        uVar2 = *(undefined4 *)(iVar13 + 0x10);
        uVar3 = *(undefined4 *)(iVar13 + 0x14);
        uVar4 = *(undefined4 *)(iVar13 + 0x18);
        uVar5 = *(undefined4 *)(iVar13 + 0x1c);
        uVar6 = *(undefined4 *)(iVar13 + 0x20);
        uVar7 = *(undefined4 *)(iVar13 + 0x24);
        uVar8 = *(undefined4 *)(iVar13 + 0x28);
        uVar9 = *(undefined4 *)(iVar13 + 0x2c);
        uVar10 = *(undefined4 *)(iVar13 + 0x30);
        *(undefined4 *)(param_1 + 0xe0) = *(undefined4 *)(iVar13 + 8);
        *(undefined4 *)(param_1 + 0x9c) = *(undefined4 *)(param_1 + 0x2a4c);
        *(undefined4 *)(param_1 + 0xa0) = *(undefined4 *)(param_1 + 0x2a50);
        *(undefined4 *)(param_1 + 0xa4) = *(undefined4 *)(param_1 + 0x2a54);
        *(undefined4 *)(param_1 + 0xb4) = uVar2;
        *(undefined4 *)(param_1 + 0xb8) = uVar3;
        *(undefined4 *)(param_1 + 0xbc) = uVar4;
        *(undefined4 *)(param_1 + 0xa8) = uVar5;
        *(undefined4 *)(param_1 + 0xac) = uVar6;
        *(undefined4 *)(param_1 + 0xb0) = uVar7;
        *(undefined4 *)(param_1 + 0xc0) = uVar8;
        *(undefined4 *)(param_1 + 0xc4) = uVar9;
        *(undefined4 *)(param_1 + 0xe4) = 8;
        *(undefined4 *)(param_1 + 200) = uVar10;
LAB_00404086:
        if ((*(uint *)(param_1 + 0xdc) & 1) == 0) {
          *(undefined4 *)(param_1 + 0xd0) = 0;
          *(undefined4 *)(param_1 + 0xcc) = 0xfff0bdc1;
          *(undefined4 *)(param_1 + 0xd4) = 0;
          *(undefined4 **)(param_1 + 0xd8) = &DAT_00476f78;
          *(uint *)(param_1 + 0xdc) = *(uint *)(param_1 + 0xdc) | 1;
        }
        *(undefined4 *)(param_1 + 0xd0) = 0;
        *(undefined4 *)(param_1 + 0xd4) = 0;
        *(undefined4 *)(param_1 + 0xcc) = 0xffffffff;
        break;
      case 0xb:
        uVar2 = *(undefined4 *)(iVar13 + 0x10);
        uVar3 = *(undefined4 *)(iVar13 + 0x14);
        uVar4 = *(undefined4 *)(iVar13 + 0x18);
        uVar5 = *(undefined4 *)(iVar13 + 0x1c);
        uVar6 = *(undefined4 *)(iVar13 + 0x20);
        uVar7 = *(undefined4 *)(iVar13 + 0x24);
        uVar8 = *(undefined4 *)(iVar13 + 0x28);
        uVar9 = *(undefined4 *)(iVar13 + 0x2c);
        uVar10 = *(undefined4 *)(iVar13 + 0x30);
        *(undefined4 *)(param_1 + 0x94) = *(undefined4 *)(iVar13 + 8);
        *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(param_1 + 0x2a58);
        *(undefined4 *)(param_1 + 0x54) = *(undefined4 *)(param_1 + 0x2a5c);
        *(undefined4 *)(param_1 + 0x58) = *(undefined4 *)(param_1 + 0x2a60);
        *(undefined4 *)(param_1 + 0x68) = uVar2;
        *(undefined4 *)(param_1 + 0x6c) = uVar3;
        *(undefined4 *)(param_1 + 0x70) = uVar4;
        *(undefined4 *)(param_1 + 0x5c) = uVar5;
        *(undefined4 *)(param_1 + 0x60) = uVar6;
        *(undefined4 *)(param_1 + 100) = uVar7;
        *(undefined4 *)(param_1 + 0x74) = uVar8;
        *(undefined4 *)(param_1 + 0x78) = uVar9;
        *(undefined4 *)(param_1 + 0x98) = 8;
        *(undefined4 *)(param_1 + 0x7c) = uVar10;
LAB_00404182:
        if ((*(uint *)(param_1 + 0x90) & 1) == 0) {
          *(undefined4 *)(param_1 + 0x84) = 0;
          *(undefined4 *)(param_1 + 0x80) = 0xfff0bdc1;
          *(undefined4 *)(param_1 + 0x88) = 0;
          *(undefined4 **)(param_1 + 0x8c) = &DAT_00476f78;
          *(uint *)(param_1 + 0x90) = *(uint *)(param_1 + 0x90) | 1;
        }
        *(undefined4 *)(param_1 + 0x84) = 0;
        *(undefined4 *)(param_1 + 0x88) = 0;
        *(undefined4 *)(param_1 + 0x80) = 0xffffffff;
        break;
      case 0xc:
        *(undefined1 *)(param_1 + 0x20) = *(undefined1 *)(iVar13 + 8);
        if ((*(uint *)(param_1 + 0x34) & 1) == 0) {
          *(undefined4 *)(param_1 + 0x28) = 0;
          *(undefined4 *)(param_1 + 0x24) = 0xfff0bdc1;
          *(undefined4 *)(param_1 + 0x2c) = 0;
          *(undefined4 **)(param_1 + 0x30) = &DAT_00476f78;
          *(uint *)(param_1 + 0x34) = *(uint *)(param_1 + 0x34) | 1;
        }
        *(undefined4 *)(param_1 + 0x28) = 0;
        *(undefined4 *)(param_1 + 0x2c) = 0;
        *(undefined4 *)(param_1 + 0x24) = 0xffffffff;
        break;
      case 0xd:
        DAT_004923a8 = *(undefined4 *)(iVar13 + 8);
        break;
      case 0xe:
        if (*(int *)(iVar13 + 0xc) < 0) {
          iVar13 = *(int *)(iVar13 + 8) * 0x3ac;
          *(uint *)(iVar13 + param_1 + 0x4dc) = *(uint *)(iVar13 + 0x4dc + param_1) & 0xfffffffe;
        }
        else {
          FUN_00404f30((void *)(*(int *)(iVar13 + 8) * 0x3ac),*(undefined2 **)(param_1 + 0x178));
        }
      }
      *(int *)(param_1 + 0x4c) =
           (int)*(short *)(*(int *)(param_1 + 0x4c) + 6) + *(int *)(param_1 + 0x4c);
LAB_0040425d:
    } while (**(int **)(param_1 + 0x4c) <= *(int *)(param_1 + 0x3c));
  }
  pfVar14 = *(float **)(param_1 + 0x44);
  *(int *)(param_1 + 0x38) = *(int *)(param_1 + 0x3c);
  if ((*pfVar14 <= _DAT_00470b68) || (_DAT_00470b64 <= *pfVar14)) {
    *(float *)(param_1 + 0x40) = *pfVar14 + *(float *)(param_1 + 0x40);
    uVar18 = FUN_00463b2c();
    *(int *)(param_1 + 0x3c) = (int)uVar18;
  }
  else {
    fVar11 = *(float *)(param_1 + 0x40) + _DAT_00470afc;
    *(int *)(param_1 + 0x3c) = *(int *)(param_1 + 0x3c) + 1;
    *(float *)(param_1 + 0x40) = fVar11;
  }
switchD_00403cb4_caseD_0:
  if (*(int *)(param_1 + 0x94) != 0) {
    puVar12 = (undefined4 *)FUN_00404610();
    *(undefined4 *)(param_1 + 0x2a58) = *puVar12;
    *(undefined4 *)(param_1 + 0x2a5c) = puVar12[1];
    *(undefined4 *)(param_1 + 0x2a60) = puVar12[2];
  }
  if (*(int *)(param_1 + 0xe0) != 0) {
    puVar12 = (undefined4 *)FUN_00404610();
    *(undefined4 *)(param_1 + 0x2a4c) = *puVar12;
    *(undefined4 *)(param_1 + 0x2a50) = puVar12[1];
    *(undefined4 *)(param_1 + 0x2a54) = puVar12[2];
  }
  if (*(int *)(param_1 + 0x16c) != 0) {
    uVar19 = FUN_004049a0(local_1c);
    puVar12 = (undefined4 *)uVar19;
    puVar16 = (undefined4 *)(param_1 + 0x2b48);
    for (iVar13 = 7; iVar13 != 0; iVar13 = iVar13 + -1) {
      *puVar16 = *puVar12;
      puVar12 = puVar12 + 1;
      puVar16 = puVar16 + 1;
    }
  }
  if ((*(char *)(param_1 + 0x20) != '\0') && (*(char *)(param_1 + 0x20) == '\x01')) {
    fVar17 = (float10)fsin((float10)*(float *)(param_1 + 0x2c) * (float10)_DAT_00470cb0 -
                           (float10)_DAT_00470b18);
    *(float *)(param_1 + 0x2a88) = (float)(fVar17 * (float10)_DAT_00470cac);
    FUN_00404ed0();
    if (0x1ff < *(int *)(param_1 + 0x28)) {
      FUN_00405410(0);
    }
  }
  return 0;
}

