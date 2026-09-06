/* Raw Ghidra reference; not compilable reconstruction. Address: 00425730 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 __thiscall FUN_00425730(void *this,int param_1)

{
  int *piVar1;
  float *pfVar2;
  float fVar3;
  float fVar4;
  int iVar5;
  int iVar6;
  uint uVar7;
  undefined4 *puVar8;
  int *piVar9;
  void *extraout_ECX;
  void *extraout_ECX_00;
  void *extraout_ECX_01;
  void *extraout_ECX_02;
  void *extraout_ECX_03;
  void *extraout_ECX_04;
  void *extraout_ECX_05;
  void *extraout_ECX_06;
  void *extraout_ECX_07;
  void *extraout_ECX_08;
  void *extraout_ECX_09;
  void *extraout_ECX_10;
  float *pfVar10;
  int iVar11;
  void *this_00;
  float10 fVar12;
  ulonglong uVar13;
  
  iVar5 = param_1;
  iVar6 = DAT_004776ec;
  switch(*(undefined4 *)(param_1 + 0x458)) {
  case 0:
    iVar6 = 48000 - (*(int *)(param_1 + 0x478) * 8000) / 0x3c;
    *(int *)(param_1 + 0x3d0) = iVar6;
    iVar11 = 0x20;
    *(float *)(param_1 + 0x3c4) = (float)iVar6 * _DAT_00470b00;
    *(undefined4 *)(param_1 + 0x332c) = 1;
    *(undefined4 *)(param_1 + 0x33c4) = 1;
    *(undefined4 *)(param_1 + 0x345c) = 1;
    *(undefined4 *)(param_1 + 0x34f4) = 1;
    if (*(int *)(param_1 + 0x3500) * 8 < 0x20) {
      puVar8 = (undefined4 *)(param_1 + 0x446c);
      do {
        iVar6 = *(int *)(param_1 + 0x3500) * 0x40;
        *puVar8 = *(undefined4 *)(iVar6 + 0x436c + param_1);
        puVar8[1] = *(undefined4 *)(iVar6 + param_1 + 0x4370);
        iVar11 = iVar11 + -1;
        puVar8 = puVar8 + -2;
      } while (*(int *)(param_1 + 0x3500) * 8 < iVar11);
      if (0 < iVar11) goto LAB_00425804;
    }
    else {
LAB_00425804:
      puVar8 = (undefined4 *)(param_1 + 0x4370 + iVar11 * 8);
      do {
        puVar8[-1] = puVar8[-3];
        *puVar8 = puVar8[-2];
        puVar8 = puVar8 + -2;
        iVar11 = iVar11 + -1;
      } while (iVar11 != 0);
    }
    *(undefined4 *)(param_1 + 0x436c) = *(undefined4 *)(param_1 + 0x3cc);
    *(undefined4 *)(param_1 + 0x4370) = *(undefined4 *)(param_1 + 0x3d0);
    if (*(int *)(param_1 + 0x478) < 0x1e) {
      fVar3 = (float)*(int *)(param_1 + 0x478) * _DAT_00470d44 + _DAT_00470bc8;
      FUN_00408100(fVar3,0,1);
      FUN_00408100(fVar3 * _DAT_00470d40,0,0);
      FUN_0041c800();
      this = extraout_ECX;
    }
    else {
      iVar6 = DAT_004776f0 + 0x60;
      iVar11 = 2000;
      do {
        if (((*(short *)(iVar6 + 0x446) != 0) && (*(short *)(iVar6 + 0x446) != 3)) &&
           (*(int *)(iVar6 + 4) == 0)) {
          FUN_00408030();
        }
        iVar6 = iVar6 + 0x7f0;
        iVar11 = iVar11 + -1;
      } while (iVar11 != 0);
      this = (void *)0x0;
      piVar9 = *(int **)(DAT_0047781c + 0x18);
      if (*(int **)(DAT_0047781c + 0x18) != (int *)0x0) {
        do {
          piVar1 = (int *)piVar9[2];
          if (piVar9[3] != 1) {
            (**(code **)(*piVar9 + 0x14))(0);
          }
          piVar9 = piVar1;
        } while (piVar1 != (int *)0x0);
        this = (void *)0x0;
      }
    }
    if (0x3b < *(int *)(param_1 + 0x478)) {
      *(undefined4 *)(param_1 + 0x458) = 1;
      this = (void *)0x0;
      if ((*(uint *)(param_1 + 0x484) & 1) == 0) {
        *(undefined4 *)(param_1 + 0x478) = 0;
        *(undefined4 *)(param_1 + 0x474) = 0xfff0bdc1;
        *(undefined4 *)(param_1 + 0x47c) = 0;
        *(undefined4 **)(param_1 + 0x480) = &DAT_00476f78;
        *(uint *)(param_1 + 0x484) = *(uint *)(param_1 + 0x484) | 1;
      }
      *(undefined4 *)(param_1 + 0x478) = 0;
      *(undefined4 *)(param_1 + 0x47c) = 0;
      *(undefined4 *)(param_1 + 0x474) = 0xffffffff;
      goto switchD_0042574a_caseD_1;
    }
    break;
  case 1:
switchD_0042574a_caseD_1:
    iVar6 = DAT_004776ec;
    if (((DAT_0047770c != 0) && (this = *(void **)(DAT_0047770c + 0x9eb8), this == (void *)0x0)) &&
       ((DAT_004776ec != 0 &&
        (((*(int *)(DAT_004776ec + 0x28) == 0 &&
          (this = (void *)((int)DAT_00474c48 / 0x14), (short)this != 0)) &&
         (((byte)DAT_00474e5c & 2) != 0)))))) {
      FUN_00405410(0x10e);
      InitializePlayer(iVar6);
      DAT_00474c48 = DAT_00474c48 + -0x14;
      FUN_00426f70(param_1);
      iVar6 = (int)DAT_00474c48 / 0x14;
      FUN_004054b0(iVar6,iVar6,(((int)DAT_00474c48 % 0x14) * 100) / 0x14);
      FUN_00412e70(&DAT_00474c40,3000);
      this = extraout_ECX_00;
    }
    if (*(int *)(param_1 + 0x478) < 0x1e) {
      iVar6 = DAT_004776f0 + 0x60;
      iVar11 = 2000;
      do {
        if (((*(short *)(iVar6 + 0x446) != 0) && (*(short *)(iVar6 + 0x446) != 3)) &&
           (*(int *)(iVar6 + 4) == 0)) {
          FUN_00408030();
        }
        iVar6 = iVar6 + 0x7f0;
        iVar11 = iVar11 + -1;
      } while (iVar11 != 0);
      piVar9 = *(int **)(DAT_0047781c + 0x18);
      while (piVar1 = piVar9, this = (void *)0x0, piVar1 != (int *)0x0) {
        piVar9 = (int *)piVar1[2];
        if (piVar1[3] != 1) {
          (**(code **)(*piVar1 + 0x14))(0);
        }
      }
    }
    FUN_004250b0(this);
    this = extraout_ECX_01;
    break;
  case 2:
switchD_0042574a_caseD_2:
    if (*(int *)(param_1 + 0x478) == 3) {
      DAT_00474c48 = DAT_00474c48 + -0x40;
      if (DAT_00474c48 < 0) {
        DAT_00474c48 = 0;
      }
      iVar6 = (int)DAT_00474c48 / 0x14;
      FUN_004054b0(iVar6,iVar6,(((int)DAT_00474c48 % 0x14) * 100) / 0x14);
      fVar12 = FUN_00426610(param_1);
      param_1 = 0;
      do {
        if (((param_1 == 1) || (param_1 == 3)) || (iVar6 = 1, param_1 == 5)) {
          iVar6 = 4;
        }
        FUN_0041bb00((void *)(iVar5 + 0x3c0),iVar6,0xffffff,
                     ((float)param_1 * _DAT_00470d3c + (float)fVar12) - _DAT_00470d38,3.0);
        param_1 = param_1 + 1;
      } while (param_1 < 7);
      FUN_00426f70(iVar5);
      this = extraout_ECX_03;
    }
    if (0x1d < *(int *)(iVar5 + 0x478)) {
      if (DAT_00474c70 < 0) {
        if (*(int *)(DAT_00477838 + 0x10) == 1) {
          FUN_0040ac90(4);
          this = extraout_ECX_06;
        }
        else {
          FUN_004231d0((int)this);
          this = extraout_ECX_04;
        }
      }
      else {
        puVar8 = (undefined4 *)(iVar5 + 0x3c0);
        *(undefined4 *)(iVar5 + 0x458) = 0;
        DAT_00476f78 = 0x3f800000;
        FUN_00427b50(this,iVar5,puVar8,0x42000000,0x41800000,0x1e,0x96);
        *(undefined4 *)(iVar5 + 0x440) = *puVar8;
        *(undefined4 *)(iVar5 + 0x444) = *(undefined4 *)(iVar5 + 0x3c4);
        *(undefined4 *)(iVar5 + 0x448) = *(undefined4 *)(iVar5 + 0x3c8);
        *(undefined4 *)(iVar5 + 0x3cc) = 0;
        *(undefined4 *)(iVar5 + 0x3d0) = 48000;
        *puVar8 = 0;
        *(undefined4 *)(iVar5 + 0x3c4) = 0x43f00000;
        FUN_00405410(0x118);
        FUN_00405410(0);
        this = extraout_ECX_07;
      }
    }
    break;
  case 3:
    if ((*(int *)(param_1 + 0x478) != 4) && (*(int *)(param_1 + 0x478) == 0xf)) {
      iVar6 = DAT_004776f0 + 0x60;
      iVar11 = 2000;
      do {
        if ((*(short *)(iVar6 + 0x446) != 0) && (*(short *)(iVar6 + 0x446) != 3)) {
          FUN_00408030();
        }
        iVar6 = iVar6 + 0x7f0;
        iVar11 = iVar11 + -1;
      } while (iVar11 != 0);
      FUN_0041c850();
      this = extraout_ECX_08;
    }
    break;
  case 4:
    if (7 < *(int *)(param_1 + 0x478)) {
      FUN_004269d0(param_1);
      this = extraout_ECX_02;
      goto switchD_0042574a_caseD_2;
    }
    if ((((DAT_004776ec != 0) && (*(int *)(DAT_004776ec + 0x28) == 0)) &&
        (this = (void *)(int)DAT_00474c48,
        (short)(DAT_00474c48 / 0x14 + (DAT_00474c48 >> 0xf)) !=
        (short)((longlong)(int)this * 0x66666667 >> 0x3f))) && (((byte)DAT_00474e5c & 2) != 0)) {
      FUN_00405410(0x3c);
      FUN_00405410(200);
      InitializePlayer(iVar6);
      DAT_00474c48 = DAT_00474c48 + -0x14;
      FUN_00426f70(param_1);
      iVar6 = (int)DAT_00474c48 / 0x14;
      FUN_004054b0(iVar6,iVar6,(((int)DAT_00474c48 % 0x14) * 100) / 0x14);
      *(undefined4 *)(param_1 + 0x458) = 1;
      this = extraout_ECX_05;
    }
  }
  pfVar10 = (float *)(iVar5 + 0x350c);
  this_00 = (void *)(iVar5 + 0x3530);
  param_1 = 0x20;
  do {
    if ((*(byte *)((int)this_00 + 0x44) & 1) != 0) {
      if ((*(byte *)((int)this_00 + 0x1c) & 1) == 0) {
        FUN_0044c5d0(this_00,*(float *)((int)this_00 + 0x10),*(float *)((int)this_00 + 0xc));
        *(undefined4 *)((int)this_00 + 8) = 0;
      }
      else {
        *(float *)((int)this_00 + 0x14) =
             *(float *)((int)this_00 + 0x18) + *(float *)((int)this_00 + 0x14);
        fVar12 = (float10)NormalizeAngle(*(float *)((int)this_00 + 0xc) +
                                         *(float *)((int)this_00 + 0x10));
        *(float *)((int)this_00 + 0x10) = (float)fVar12;
      }
      FUN_0044c2a0();
      *pfVar10 = *(float *)((int)this_00 + -0x20) + *pfVar10;
      *(float *)((int)this_00 + -0x1c) =
           *(float *)((int)this_00 + -0x18) + *(float *)((int)this_00 + -0x1c);
      *(undefined4 *)((int)this_00 + 0x20) = *(undefined4 *)((int)this_00 + 0x24);
      pfVar2 = *(float **)((int)this_00 + 0x2c);
      if ((*pfVar2 <= _DAT_00470b68) || (_DAT_00470b64 <= *pfVar2)) {
        fVar3 = *(float *)((int)this_00 + 0x28) - *pfVar2 * _DAT_00470afc;
      }
      else {
        fVar3 = *(float *)((int)this_00 + 0x28) - _DAT_00470afc;
      }
      *(float *)((int)this_00 + 0x28) = fVar3;
      uVar13 = FUN_00463b2c();
      *(int *)((int)this_00 + 0x24) = (int)uVar13;
      this = extraout_ECX_09;
      if ((int)uVar13 < 1) {
        *(uint *)((int)this_00 + 0x44) = *(uint *)((int)this_00 + 0x44) & 0xfffffffe;
      }
    }
    pfVar10 = pfVar10 + 0x1b;
    this_00 = (void *)((int)this_00 + 0x6c);
    param_1 = param_1 + -1;
  } while (param_1 != 0);
  if (*(int *)(iVar5 + 0x4310) < 1) {
LAB_00425ee6:
    uVar7 = *(uint *)(iVar5 + 0x370) & 0xffff7fff;
  }
  else {
    pfVar10 = *(float **)(iVar5 + 0x4318);
    *(int *)(iVar5 + 0x430c) = *(int *)(iVar5 + 0x4310);
    if ((*pfVar10 <= _DAT_00470b68) || (_DAT_00470b64 <= *pfVar10)) {
      fVar3 = *(float *)(iVar5 + 0x4314) - *pfVar10 * _DAT_00470afc;
    }
    else {
      fVar3 = *(float *)(iVar5 + 0x4314) - _DAT_00470afc;
    }
    *(float *)(iVar5 + 0x4314) = fVar3;
    uVar13 = FUN_00463b2c();
    *(int *)(iVar5 + 0x4310) = (int)uVar13;
    this = extraout_ECX_10;
    if ((*(int *)(iVar5 + 0x478) == *(int *)(iVar5 + 0x474)) ||
       (this = (void *)0x3, *(int *)(iVar5 + 0x478) % 3 != 0)) goto LAB_00425ee6;
    *(undefined4 *)(iVar5 + 0x314) = 0xff0000ff;
    uVar7 = *(uint *)(iVar5 + 0x370) | 0x8000;
  }
  *(uint *)(iVar5 + 0x370) = uVar7;
  FUN_0043ee30(this,iVar5 + 0x14U,iVar5 + 0x14U);
  *(float *)(iVar5 + 0x404) = *(float *)(iVar5 + 0x3c0) - *(float *)(iVar5 + 0x41c);
  *(float *)(iVar5 + 0x408) = *(float *)(iVar5 + 0x3c4) - *(float *)(iVar5 + 0x420);
  *(float *)(iVar5 + 0x40c) = *(float *)(iVar5 + 0x3c8) - *(float *)(iVar5 + 0x424);
  *(float *)(iVar5 + 0x410) = *(float *)(iVar5 + 0x41c) + *(float *)(iVar5 + 0x3c0);
  *(float *)(iVar5 + 0x414) = *(float *)(iVar5 + 0x420) + *(float *)(iVar5 + 0x3c4);
  *(float *)(iVar5 + 0x418) = *(float *)(iVar5 + 0x424) + *(float *)(iVar5 + 0x3c8);
  fVar3 = *(float *)(iVar5 + 0x42c) * _DAT_00470b0c;
  fVar4 = *(float *)(iVar5 + 0x430) * _DAT_00470b0c;
  *(float *)(iVar5 + 0x4324) = *(float *)(iVar5 + 0x3c0) - *(float *)(iVar5 + 0x428) * _DAT_00470b0c
  ;
  *(float *)(iVar5 + 0x4328) = *(float *)(iVar5 + 0x3c4) - fVar3;
  *(float *)(iVar5 + 0x432c) = *(float *)(iVar5 + 0x3c8) - fVar4;
  fVar3 = *(float *)(iVar5 + 0x42c) * _DAT_00470b0c;
  fVar4 = *(float *)(iVar5 + 0x430) * _DAT_00470b0c;
  *(float *)(iVar5 + 0x4330) = *(float *)(iVar5 + 0x428) * _DAT_00470b0c + *(float *)(iVar5 + 0x3c0)
  ;
  *(float *)(iVar5 + 0x4334) = fVar3 + *(float *)(iVar5 + 0x3c4);
  *(float *)(iVar5 + 0x4338) = fVar4 + *(float *)(iVar5 + 0x3c8);
  *(float *)(iVar5 + 0x433c) = *(float *)(iVar5 + 0x3c0) - *(float *)(iVar5 + 0x434);
  *(float *)(iVar5 + 0x4340) = *(float *)(iVar5 + 0x3c4) - *(float *)(iVar5 + 0x438);
  *(float *)(iVar5 + 0x4344) = *(float *)(iVar5 + 0x3c8) - *(float *)(iVar5 + 0x43c);
  *(float *)(iVar5 + 0x4348) = *(float *)(iVar5 + 0x434) + *(float *)(iVar5 + 0x3c0);
  *(float *)(iVar5 + 0x434c) = *(float *)(iVar5 + 0x438) + *(float *)(iVar5 + 0x3c4);
  *(float *)(iVar5 + 0x4350) = *(float *)(iVar5 + 0x43c) + *(float *)(iVar5 + 0x3c8);
  *(float *)(iVar5 + 0x4354) = *(float *)(iVar5 + 0x3c0) - *(float *)(iVar5 + 0x428);
  *(float *)(iVar5 + 0x4358) = *(float *)(iVar5 + 0x3c4) - *(float *)(iVar5 + 0x42c);
  *(float *)(iVar5 + 0x435c) = *(float *)(iVar5 + 0x3c8) - *(float *)(iVar5 + 0x430);
  *(float *)(iVar5 + 0x4360) = *(float *)(iVar5 + 0x428) + *(float *)(iVar5 + 0x3c0);
  *(float *)(iVar5 + 0x4364) = *(float *)(iVar5 + 0x42c) + *(float *)(iVar5 + 0x3c4);
  *(float *)(iVar5 + 0x4368) = *(float *)(iVar5 + 0x430) + *(float *)(iVar5 + 0x3c8);
  pfVar10 = *(float **)(iVar5 + 0x480);
  *(int *)(iVar5 + 0x474) = *(int *)(iVar5 + 0x478);
  if ((*pfVar10 <= _DAT_00470b68) || (_DAT_00470b64 <= *pfVar10)) {
    *(float *)(iVar5 + 0x47c) = *pfVar10 + *(float *)(iVar5 + 0x47c);
    uVar13 = FUN_00463b2c();
    *(int *)(iVar5 + 0x478) = (int)uVar13;
  }
  else {
    fVar3 = *(float *)(iVar5 + 0x47c) + _DAT_00470afc;
    *(int *)(iVar5 + 0x478) = *(int *)(iVar5 + 0x478) + 1;
    *(float *)(iVar5 + 0x47c) = fVar3;
  }
  pfVar10 = *(float **)(iVar5 + 0x494);
  *(int *)(iVar5 + 0x488) = *(int *)(iVar5 + 0x48c);
  if ((*pfVar10 <= _DAT_00470b68) || (_DAT_00470b64 <= *pfVar10)) {
    *(float *)(iVar5 + 0x490) = *pfVar10 + *(float *)(iVar5 + 0x490);
    uVar13 = FUN_00463b2c();
    *(int *)(iVar5 + 0x48c) = (int)uVar13;
  }
  else {
    fVar3 = *(float *)(iVar5 + 0x490) + _DAT_00470afc;
    *(int *)(iVar5 + 0x48c) = *(int *)(iVar5 + 0x48c) + 1;
    *(float *)(iVar5 + 0x490) = fVar3;
  }
  if (*(int *)(DAT_0047770c + 0x9eb8) == 0) {
    if (((DAT_00477704 != 0) && (*(int *)(DAT_00477704 + 0x60) != 0)) &&
       (*(int *)(iVar5 + 0x478) % 0x3c == 0)) {
      DAT_00474c98 = DAT_00474c98 + 1;
      if (DAT_00474c98 < 0x401) {
        if (DAT_00474c98 < -0x400) {
          DAT_00474c98 = -0x400;
        }
      }
      else {
        DAT_00474c98 = 0x400;
      }
    }
    if (((*(int *)(DAT_0047770c + 0x9eb8) == 0) && (DAT_00477704 != 0)) &&
       (*(int *)(DAT_00477704 + 0x60) != 0)) {
      FUN_004281d0();
      goto LAB_0042632c;
    }
  }
  if ((*(uint *)(iVar5 + 0x470) & 1) == 0) {
    *(undefined4 *)(iVar5 + 0x464) = 0;
    *(undefined4 *)(iVar5 + 0x460) = 0xfff0bdc1;
    *(undefined4 *)(iVar5 + 0x468) = 0;
    *(undefined4 **)(iVar5 + 0x46c) = &DAT_00476f78;
    *(uint *)(iVar5 + 0x470) = *(uint *)(iVar5 + 0x470) | 1;
  }
  *(undefined4 *)(iVar5 + 0x464) = 0xffffffff;
  *(undefined4 *)(iVar5 + 0x468) = 0xbf800000;
  *(undefined4 *)(iVar5 + 0x460) = 0xfffffffe;
  *(undefined4 *)(iVar5 + 0x3504) = 0;
  *(undefined1 *)(iVar5 + 0x3508) = 0;
LAB_0042632c:
  FUN_00428280(iVar5);
  return 1;
}

