/* Raw Ghidra reference; not compilable reconstruction. Address: 00428630 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int __thiscall FUN_00428630(void *this,int param_1,float *param_2,float *param_3)

{
  int *piVar1;
  float fVar2;
  float fVar3;
  char cVar4;
  undefined4 uVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  float fVar10;
  int iVar11;
  int iVar12;
  int iVar13;
  undefined4 *puVar14;
  int extraout_ECX;
  int extraout_ECX_00;
  undefined4 extraout_ECX_01;
  undefined4 extraout_ECX_02;
  int *piVar15;
  float *pfVar16;
  undefined4 *puVar17;
  int iVar18;
  ushort uVar19;
  float10 fVar20;
  float10 fVar21;
  void *local_40;
  int local_3c;
  
  iVar18 = param_1;
  piVar15 = (int *)(param_1 + 0x478);
  piVar1 = (int *)(param_1 + 0x474);
  param_1 = 0;
  if (*piVar15 == *piVar1) {
    return 0;
  }
  local_40 = (void *)(iVar18 + 0x49c);
  fVar6 = *param_2 - *param_3 * _DAT_00470b0c;
  fVar8 = param_2[1] - param_3[1] * _DAT_00470b0c;
  fVar7 = *param_3 * _DAT_00470b0c + *param_2;
  fVar9 = param_3[1] * _DAT_00470b0c + param_2[1];
  if (this != (void *)0x0) {
    *(undefined4 *)this = 0;
  }
  puVar17 = (undefined4 *)(iVar18 + 0x4e0);
  local_3c = 0x80;
  do {
    if ((puVar17[-1] != 0) && (puVar17[-1] != 2)) {
      iVar13 = puVar17[5];
      fVar2 = *(float *)(iVar13 + 0xc) * _DAT_00470b0c;
      fVar3 = *(float *)(iVar13 + 0x10) * _DAT_00470b0c;
      fVar10 = (float)puVar17[-0xb] - fVar3;
      if ((fVar10 <= fVar9) &&
         ((((float)puVar17[-0xc] - fVar2 <= fVar7 && (fVar8 <= fVar3 + (float)puVar17[-0xb])) &&
          (fVar6 <= fVar2 + (float)puVar17[-0xc])))) {
        if (*(char *)(iVar13 + 0x1d) == '\x03') {
LAB_00428763:
          if (_DAT_00470b04 <= fVar9) {
LAB_00428778:
            if ((*(code **)(iVar13 + 0x30) == (code *)0x0) ||
               (iVar11 = (**(code **)(iVar13 + 0x30))(param_2), iVar13 = extraout_ECX, iVar11 == 0))
            {
              if (puVar17[4] == 0) {
                FUN_0040c480(iVar13);
                puVar17[4] = 1;
              }
              iVar13 = puVar17[5];
              puVar17[3] = 1;
              cVar4 = *(char *)(iVar13 + 0x1d);
              if ((cVar4 != '\x03') ||
                 (iVar12 = FUN_00427c70(local_40,4), iVar11 = extraout_ECX_00, iVar12 != 0)) {
                iVar11 = (int)*(short *)(iVar13 + 2);
                param_1 = param_1 + iVar11;
              }
              if (cVar4 != '\x03') {
                iVar13 = FUN_00449450(iVar11);
                uVar5 = *(undefined4 *)(iVar13 + 0x2c);
                FUN_00449630(extraout_ECX_01);
                puVar14 = (undefined4 *)
                          FUN_00448d00(*(undefined4 *)(iVar18 + 0x10),
                                       *(short *)(puVar17[5] + 0x20) + 5,0xf);
                *puVar17 = *puVar14;
                iVar13 = FUN_00449450(extraout_ECX_02);
                *(undefined4 *)(iVar13 + 0x2c) = uVar5;
                *(uint *)(iVar13 + 0x35c) = *(uint *)(iVar13 + 0x35c) | 4;
                fVar2 = (float)puVar17[-6] * _DAT_00470b90;
                puVar17[-10] = 0x3dcccccd;
                puVar17[-1] = 2;
                puVar17[-6] = fVar2;
              }
              if (*(char *)(puVar17[5] + 0x1d) == '\x02') {
                iVar13 = (int)*(short *)(puVar17[5] + 2);
                FUN_00427b50(iVar13,iVar18,puVar17 + -0xc,0x42000000,0x3fb33333,0xd,iVar13 / 3);
              }
            }
          }
        }
        else if (_DAT_00470b04 <= fVar10) {
          if (*(char *)(iVar13 + 0x1d) == '\x03') goto LAB_00428763;
          goto LAB_00428778;
        }
      }
    }
    local_40 = (void *)((int)local_40 + 0x5c);
    puVar17 = puVar17 + 0x17;
    local_3c = local_3c + -1;
  } while (local_3c != 0);
  iVar13 = TestPlayerHit(DAT_004776ec);
  param_1 = param_1 + iVar13;
  pfVar16 = (float *)(iVar18 + 0x350c);
  piVar15 = (int *)(iVar18 + 0x3554);
  iVar18 = 0x20;
  do {
    if (((piVar15[8] & 1U) == 0) || ((*piVar15 != piVar15[-1] && (*piVar15 % piVar15[7] == 0))))
    goto LAB_00428a60;
    if ((piVar15[8] & 2U) == 0) {
      if ((float)piVar15[-0x10] == _DAT_00470b04) {
        if ((((float)piVar15[-0xc] - (float)piVar15[-0xe] * _DAT_00470b0c <= fVar7) &&
            (fVar6 <= (float)piVar15[-0xe] * _DAT_00470b0c + (float)piVar15[-0xc])) &&
           (((float)piVar15[-0xb] - (float)piVar15[-0xd] * _DAT_00470b0c <= fVar9 &&
            (fVar8 <= (float)piVar15[-0xd] * _DAT_00470b0c + (float)piVar15[-0xb]))))
        goto LAB_00428a37;
      }
      else {
        fVar20 = (float10)fsin(-(float10)(float)piVar15[-0x10]);
        fVar21 = (float10)fcos(-(float10)(float)piVar15[-0x10]);
        fVar2 = (float)(fVar21 * ((float10)*param_2 - (float10)(float)piVar15[-0xc]) -
                       (float10)(float)fVar20 *
                       ((float10)param_2[1] - (float10)(float)piVar15[-0xb]));
        fVar3 = (float)(fVar21 * ((float10)param_2[1] - (float10)(float)piVar15[-0xb]) +
                       (float10)(float)fVar20 * ((float10)*param_2 - (float10)(float)piVar15[-0xc]))
        ;
        if ((((float)piVar15[-0xe] * _DAT_00470b78 <= *param_3 * _DAT_00470b0c + fVar2) &&
            (fVar2 - *param_3 * _DAT_00470b0c <= (float)piVar15[-0xe] * _DAT_00470b0c)) &&
           ((float)piVar15[-0xd] * _DAT_00470b78 <= param_3[1] * _DAT_00470b0c + fVar3)) {
          fVar3 = fVar3 - param_3[1] * _DAT_00470b0c;
          uVar19 = (ushort)(fVar3 < (float)piVar15[-0xd] * _DAT_00470b0c) << 8 |
                   (ushort)(fVar3 == (float)piVar15[-0xd] * _DAT_00470b0c) << 0xe;
          goto LAB_00428a2e;
        }
      }
    }
    else {
      fVar2 = *pfVar16 * *pfVar16;
      fVar3 = ((float)piVar15[-0xb] - param_2[1]) * ((float)piVar15[-0xb] - param_2[1]) +
              ((float)piVar15[-0xc] - *param_2) * ((float)piVar15[-0xc] - *param_2);
      uVar19 = (ushort)(fVar3 < fVar2) << 8 | (ushort)(fVar3 == fVar2) << 0xe;
LAB_00428a2e:
      if (uVar19 != 0) {
LAB_00428a37:
        param_1 = param_1 + piVar15[4];
        iVar13 = piVar15[5] + piVar15[4];
        piVar15[5] = iVar13;
        if (piVar15[6] <= iVar13) {
          piVar15[4] = 0;
        }
      }
    }
LAB_00428a60:
    pfVar16 = pfVar16 + 0x1b;
    piVar15 = piVar15 + 0x1b;
    iVar18 = iVar18 + -1;
    if (iVar18 == 0) {
      if ((param_1 != 0) &&
         (DAT_00474c44 = DAT_00474c44 + (param_1 / 10 + 10) / 10, 999999999 < DAT_00474c44)) {
        DAT_00474c44 = 999999999;
      }
      return param_1;
    }
  } while( true );
}

