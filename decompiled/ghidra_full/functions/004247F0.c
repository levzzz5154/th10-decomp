/* Raw Ghidra reference; not compilable reconstruction. Address: 004247F0 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_004247f0(void)

{
  float fVar1;
  char *pcVar2;
  int *piVar3;
  int iVar4;
  undefined4 *puVar5;
  void *this;
  int iVar6;
  int unaff_EBX;
  ulonglong uVar7;
  
  pcVar2 = "pl00.anm";
  if (DAT_00474c68 != 0) {
    pcVar2 = "pl01.anm";
  }
  piVar3 = FUN_00447280(8,(int)g_pGameStateManager,pcVar2);
  *(int **)(unaff_EBX + 0x10) = piVar3;
  if (piVar3 == (int *)0x0) {
    FUN_0044b810(&DAT_00474f70,&DAT_0046e3ec);
    return 0xffffffff;
  }
  if (DAT_00491bf0 == 0) {
    iVar6 = FUN_00426520();
    if (iVar6 != 0) {
      FUN_0044b810(&DAT_00474f70,&DAT_0046e3ec);
      return 0xffffffff;
    }
  }
  else {
    *(int *)(unaff_EBX + 0x45c) = DAT_00491bf0;
    DAT_00491bf0 = 0;
  }
  iVar4 = FUN_00449ed0(&LAB_00426500);
  iVar6 = DAT_00491be4;
  *(int *)(iVar4 + 0x20) = unaff_EBX;
  *(uint *)(iVar4 + 4) = *(uint *)(iVar4 + 4) & 0xfffffffd;
  FUN_00449ae0(iVar6);
  *(int *)(unaff_EBX + 8) = iVar4;
  iVar4 = FUN_00449ed0(&LAB_00426510);
  iVar6 = DAT_00491be4;
  *(uint *)(iVar4 + 4) = *(uint *)(iVar4 + 4) & 0xfffffffd;
  *(int *)(iVar4 + 0x20) = unaff_EBX;
  FUN_00449b70(iVar6);
  *(int *)(unaff_EBX + 0xc) = iVar4;
  FUN_00404f30(this,*(undefined2 **)(unaff_EBX + 0x10));
  *(undefined4 *)(unaff_EBX + 0x3c0) = 0;
  *(undefined4 *)(unaff_EBX + 0x3c4) = 0x43c80000;
  *(undefined4 *)(unaff_EBX + 0x3cc) = 0;
  *(undefined4 *)(unaff_EBX + 0x3d0) = 40000;
  uVar7 = FUN_00463b2c();
  *(int *)(unaff_EBX + 0x3d4) = (int)uVar7;
  uVar7 = FUN_00463b2c();
  *(int *)(unaff_EBX + 0x3d8) = (int)uVar7;
  uVar7 = FUN_00463b2c();
  *(int *)(unaff_EBX + 0x3dc) = (int)uVar7;
  uVar7 = FUN_00463b2c();
  *(int *)(unaff_EBX + 0x3e0) = (int)uVar7;
  puVar5 = (undefined4 *)(unaff_EBX + 0x436c);
  iVar6 = 0x21;
  do {
    *puVar5 = *(undefined4 *)(unaff_EBX + 0x3cc);
    puVar5[1] = *(undefined4 *)(unaff_EBX + 0x3d0);
    puVar5 = puVar5 + 2;
    iVar6 = iVar6 + -1;
  } while (iVar6 != 0);
  if ((*(uint *)(unaff_EBX + 0x470) & 1) == 0) {
    *(undefined4 *)(unaff_EBX + 0x464) = 0;
    *(undefined4 *)(unaff_EBX + 0x460) = 0xfff0bdc1;
    *(undefined4 *)(unaff_EBX + 0x468) = 0;
    *(undefined4 **)(unaff_EBX + 0x46c) = &DAT_00476f78;
    *(uint *)(unaff_EBX + 0x470) = *(uint *)(unaff_EBX + 0x470) | 1;
  }
  *(undefined4 *)(unaff_EBX + 0x468) = 0xbf800000;
  *(undefined4 *)(unaff_EBX + 0x460) = 0xfffffffe;
  *(undefined4 *)(unaff_EBX + 0x464) = 0xffffffff;
  *(undefined4 *)(*(int *)(unaff_EBX + 0x45c) + 4) =
       *(undefined4 *)(&DAT_00476fb8 + DAT_00474c68 * 4);
  *(undefined4 *)(*(int *)(unaff_EBX + 0x45c) + 0xc) =
       *(undefined4 *)(&DAT_00476fb0 + DAT_00474c68 * 4);
  *(undefined4 *)(*(int *)(unaff_EBX + 0x45c) + 8) =
       *(undefined4 *)(&DAT_00476fa0 + DAT_00474c68 * 4);
  fVar1 = *(float *)(*(int *)(unaff_EBX + 0x45c) + 4) * _DAT_00470b0c;
  *(undefined4 *)(unaff_EBX + 0x424) = 0x40a00000;
  *(float *)(unaff_EBX + 0x420) = fVar1;
  *(float *)(unaff_EBX + 0x41c) = fVar1;
  fVar1 = *(float *)(&DAT_00476fb0 + DAT_00474c68 * 4);
  *(undefined4 *)(unaff_EBX + 0x430) = 0x40a00000;
  fVar1 = fVar1 * _DAT_00470b0c;
  *(float *)(unaff_EBX + 0x42c) = fVar1;
  *(float *)(unaff_EBX + 0x428) = fVar1;
  fVar1 = *(float *)(&DAT_00476fa8 + DAT_00474c68 * 4);
  *(undefined4 *)(unaff_EBX + 0x43c) = 0x40a00000;
  fVar1 = fVar1 * _DAT_00470b0c;
  *(float *)(unaff_EBX + 0x438) = fVar1;
  *(float *)(unaff_EBX + 0x434) = fVar1;
  *(float *)(unaff_EBX + 0x404) = *(float *)(unaff_EBX + 0x3c0) - *(float *)(unaff_EBX + 0x41c);
  *(float *)(unaff_EBX + 0x408) = *(float *)(unaff_EBX + 0x3c4) - *(float *)(unaff_EBX + 0x420);
  *(float *)(unaff_EBX + 0x40c) = *(float *)(unaff_EBX + 0x3c8) - *(float *)(unaff_EBX + 0x424);
  *(float *)(unaff_EBX + 0x410) = *(float *)(unaff_EBX + 0x41c) + *(float *)(unaff_EBX + 0x3c0);
  *(float *)(unaff_EBX + 0x414) = *(float *)(unaff_EBX + 0x420) + *(float *)(unaff_EBX + 0x3c4);
  *(float *)(unaff_EBX + 0x418) = *(float *)(unaff_EBX + 0x424) + *(float *)(unaff_EBX + 0x3c8);
  *(float *)(unaff_EBX + 0x4324) = *(float *)(unaff_EBX + 0x3c0) - *(float *)(unaff_EBX + 0x428);
  *(float *)(unaff_EBX + 0x4328) = *(float *)(unaff_EBX + 0x3c4) - *(float *)(unaff_EBX + 0x42c);
  *(float *)(unaff_EBX + 0x432c) = *(float *)(unaff_EBX + 0x3c8) - *(float *)(unaff_EBX + 0x430);
  *(float *)(unaff_EBX + 0x4330) = *(float *)(unaff_EBX + 0x428) + *(float *)(unaff_EBX + 0x3c0);
  *(float *)(unaff_EBX + 0x4334) = *(float *)(unaff_EBX + 0x42c) + *(float *)(unaff_EBX + 0x3c4);
  *(float *)(unaff_EBX + 0x4338) = *(float *)(unaff_EBX + 0x430) + *(float *)(unaff_EBX + 0x3c8);
  *(float *)(unaff_EBX + 0x433c) = *(float *)(unaff_EBX + 0x3c0) - *(float *)(unaff_EBX + 0x434);
  *(float *)(unaff_EBX + 0x4340) = *(float *)(unaff_EBX + 0x3c4) - *(float *)(unaff_EBX + 0x438);
  *(float *)(unaff_EBX + 0x4344) = *(float *)(unaff_EBX + 0x3c8) - *(float *)(unaff_EBX + 0x43c);
  *(float *)(unaff_EBX + 0x4348) = *(float *)(unaff_EBX + 0x434) + *(float *)(unaff_EBX + 0x3c0);
  *(float *)(unaff_EBX + 0x434c) = *(float *)(unaff_EBX + 0x438) + *(float *)(unaff_EBX + 0x3c4);
  *(float *)(unaff_EBX + 0x4350) = *(float *)(unaff_EBX + 0x43c) + *(float *)(unaff_EBX + 0x3c8);
  *(float *)(unaff_EBX + 0x4354) = *(float *)(unaff_EBX + 0x3c0) - *(float *)(unaff_EBX + 0x434);
  *(float *)(unaff_EBX + 0x4358) = *(float *)(unaff_EBX + 0x3c4) - *(float *)(unaff_EBX + 0x438);
  *(float *)(unaff_EBX + 0x435c) = *(float *)(unaff_EBX + 0x3c8) - *(float *)(unaff_EBX + 0x43c);
  *(float *)(unaff_EBX + 0x4360) = *(float *)(unaff_EBX + 0x434) + *(float *)(unaff_EBX + 0x3c0);
  *(float *)(unaff_EBX + 0x4364) = *(float *)(unaff_EBX + 0x438) + *(float *)(unaff_EBX + 0x3c4);
  *(float *)(unaff_EBX + 0x4368) = *(float *)(unaff_EBX + 0x43c) + *(float *)(unaff_EBX + 0x3c8);
  if ((*(uint *)(unaff_EBX + 0x484) & 1) == 0) {
    *(undefined4 *)(unaff_EBX + 0x478) = 0;
    *(undefined4 *)(unaff_EBX + 0x474) = 0xfff0bdc1;
    *(undefined4 *)(unaff_EBX + 0x47c) = 0;
    *(undefined4 **)(unaff_EBX + 0x480) = &DAT_00476f78;
    *(uint *)(unaff_EBX + 0x484) = *(uint *)(unaff_EBX + 0x484) | 1;
  }
  *(undefined4 *)(unaff_EBX + 0x478) = 0;
  *(undefined4 *)(unaff_EBX + 0x47c) = 0;
  *(undefined4 *)(unaff_EBX + 0x474) = 0xffffffff;
  if ((*(uint *)(unaff_EBX + 0x431c) & 1) == 0) {
    *(undefined4 *)(unaff_EBX + 0x4310) = 0;
    *(undefined4 *)(unaff_EBX + 0x430c) = 0xfff0bdc1;
    *(undefined4 *)(unaff_EBX + 0x4314) = 0;
    *(undefined4 **)(unaff_EBX + 0x4318) = &DAT_00476f78;
    *(uint *)(unaff_EBX + 0x431c) = *(uint *)(unaff_EBX + 0x431c) | 1;
  }
  *(undefined4 *)(unaff_EBX + 0x4310) = 0x78;
  *(undefined4 *)(unaff_EBX + 0x4314) = 0x42f00000;
  *(undefined4 *)(unaff_EBX + 0x430c) = 0x77;
  *(undefined4 *)(unaff_EBX + 0x4308) = 0x1e;
  FUN_00426f70(unaff_EBX);
  return 0;
}

