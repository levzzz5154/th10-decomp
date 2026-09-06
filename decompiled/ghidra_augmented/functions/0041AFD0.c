/* Raw Ghidra reference; not compilable reconstruction. Address: 0041AFD0 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_0041afd0(int param_1)

{
  void *this;
  float *pfVar1;
  float fVar2;
  bool bVar3;
  bool bVar4;
  undefined3 extraout_var;
  undefined3 extraout_var_00;
  int iVar5;
  void *extraout_ECX;
  void *extraout_ECX_00;
  int iVar6;
  void *pvVar7;
  int extraout_EDX;
  float *extraout_EDX_00;
  float *pfVar8;
  float10 fVar9;
  float10 fVar10;
  ulonglong uVar11;
  float fVar12;
  uint local_58;
  float local_50;
  int local_4c;
  
  local_58 = param_1 + 0x14;
  bVar3 = false;
  *(undefined4 *)(param_1 + 0x21cebc) = 0;
  *(undefined4 *)(param_1 + 0x21ceb4) = 0;
  pfVar8 = (float *)(param_1 + 0x3c4);
  local_4c = 0x896;
  do {
    iVar5 = DAT_00477834;
    pvVar7 = (void *)0x0;
    fVar12 = pfVar8[0xb];
    if (fVar12 == 0.0) goto LAB_0041b85a;
    if (fVar12 == 7.00649e-45) {
      pfVar1 = pfVar8 + 0xf;
      *pfVar1 = (float)((int)*pfVar1 + -1);
      pvVar7 = DAT_004776f0;
      if ((int)*pfVar1 < 0) {
        pfVar8[0xb] = 2.8026e-45;
        FUN_00404f30(pvVar7,*(undefined2 **)((int)pvVar7 + 0x3e0b50));
      }
      goto LAB_0041b85a;
    }
    if (fVar12 == 1.4013e-45) {
      if ((((*(int *)(DAT_00477834 + 0x458) != 2) && (*(int *)(DAT_00477834 + 0x458) != 4)) &&
          (*(float *)(DAT_00477834 + 0x3c4) < _DAT_00470bf4)) ||
         (*(int *)(DAT_004776ec + 0x28) != 0)) {
        pfVar8[0xe] = *(float *)(*(int *)(DAT_00477834 + 0x45c) + 8);
        pfVar8[0xb] = 4.2039e-45;
        goto LAB_0041b1e7;
      }
      fVar12 = DAT_00476f78 * pfVar8[3];
      fVar2 = DAT_00476f78 * pfVar8[4];
      pfVar8[-1] = DAT_00476f78 * pfVar8[2] + pfVar8[-1];
      *pfVar8 = fVar12 + *pfVar8;
      pfVar8[1] = fVar2 + pfVar8[1];
      fVar12 = DAT_00476f78 * _DAT_00470cdc + pfVar8[3];
      pfVar8[3] = fVar12;
      if (_DAT_00470b04 <= fVar12) {
        pfVar8[2] = 0.0;
      }
      if (_DAT_00470b08 < pfVar8[3]) {
        pfVar8[3] = 2.0;
      }
      if (*pfVar8 <= _DAT_00470be0) goto LAB_0041b347;
      pfVar8[0xb] = 0.0;
      goto LAB_0041b85a;
    }
    if (fVar12 == 2.8026e-45) {
      fVar12 = DAT_00476f78 * pfVar8[3];
      fVar2 = DAT_00476f78 * pfVar8[4];
      pfVar8[-1] = DAT_00476f78 * pfVar8[2] + pfVar8[-1];
      *pfVar8 = fVar12 + *pfVar8;
      pfVar8[1] = fVar2 + pfVar8[1];
      fVar12 = DAT_00476f78 * _DAT_00470cdc + pfVar8[3];
      pfVar8[3] = fVar12;
      if (fVar12 < _DAT_00470b04) {
        iVar5 = DAT_00477834;
        if (*pfVar8 <= _DAT_00470be0) goto LAB_0041b347;
        pfVar8[0xb] = 0.0;
        FUN_00405b60(-4);
        goto LAB_0041b85a;
      }
      pfVar8[0xe] = *(float *)(*(int *)(DAT_00477834 + 0x45c) + 8);
      pfVar8[0xb] = 4.2039e-45;
      iVar5 = DAT_00477834;
LAB_0041b1e7:
      fVar9 = (float10)*(float *)(iVar5 + 0x3c0) - (float10)pfVar8[-1];
      fVar10 = (float10)*(float *)(iVar5 + 0x3c4) - (float10)*pfVar8;
      if ((fVar10 == (float10)_DAT_00470b04) && (fVar9 == (float10)_DAT_00470b04)) {
        local_50 = 1.5707964;
      }
      else {
        fVar9 = (float10)fpatan(fVar10,fVar9);
        local_50 = (float)fVar9;
      }
      FUN_0041beb0(pfVar8 + 2,local_50,pfVar8[0xe]);
      fVar12 = DAT_00476f78 * pfVar8[3];
      fVar2 = DAT_00476f78 * pfVar8[4];
      pfVar8[-1] = DAT_00476f78 * pfVar8[2] + pfVar8[-1];
      *pfVar8 = fVar12 + *pfVar8;
      pfVar8[1] = fVar2 + pfVar8[1];
      if (pfVar8[0xe] < _DAT_00470cd8) {
        pfVar8[0xe] = pfVar8[0xe] + _DAT_00470c38;
      }
      iVar6 = *(int *)(extraout_EDX + 0x458);
      pvVar7 = extraout_ECX;
      iVar5 = extraout_EDX;
LAB_0041b32a:
      if (iVar6 == 4) {
        pfVar8[0xb] = 1.4013e-45;
        pfVar8[2] = 0.0;
        pfVar8[3] = 0.0;
      }
    }
    else {
      if (fVar12 == 4.2039e-45) goto LAB_0041b1e7;
      if (fVar12 == 5.60519e-45) {
        fVar12 = pfVar8[0xe];
        fVar9 = FUN_00426660(DAT_00477834);
        FUN_0041beb0(pfVar8 + 2,(float)fVar9,fVar12);
        fVar12 = DAT_00476f78 * pfVar8[3];
        fVar2 = DAT_00476f78 * pfVar8[4];
        *extraout_EDX_00 = DAT_00476f78 * pfVar8[2] + *extraout_EDX_00;
        *pfVar8 = fVar12 + *pfVar8;
        pfVar8[1] = fVar2 + pfVar8[1];
        if (pfVar8[0xe] < _DAT_00470cd8) {
          pfVar8[0xe] = pfVar8[0xe] + _DAT_00470c38;
        }
        iVar6 = *(int *)(iVar5 + 0x458);
        pvVar7 = extraout_ECX_00;
        iVar5 = DAT_00477834;
        goto LAB_0041b32a;
      }
    }
LAB_0041b347:
    if (*(int *)(iVar5 + 0x458) == 2) {
LAB_0041b7fd:
      FUN_0043ee30(pvVar7,local_58,local_58);
      pfVar1 = (float *)pfVar8[9];
      pfVar8[6] = pfVar8[7];
      if ((*pfVar1 <= _DAT_00470b68) || (_DAT_00470b64 <= *pfVar1)) {
        pfVar8[8] = pfVar8[8] + *pfVar1;
        uVar11 = FUN_00463b2c();
        pfVar8[7] = (float)uVar11;
      }
      else {
        fVar12 = pfVar8[8] + _DAT_00470afc;
        pfVar8[7] = (float)((int)pfVar8[7] + 1);
        pfVar8[8] = fVar12;
      }
      *(int *)(param_1 + 0x21ceb4) = *(int *)(param_1 + 0x21ceb4) + 1;
      goto LAB_0041b85a;
    }
    fVar12 = pfVar8[-1];
    this = (void *)*pfVar8;
    if (((fVar12 < *(float *)(iVar5 + 0x4324)) || ((float)this < *(float *)(iVar5 + 0x4328))) ||
       ((*(float *)(iVar5 + 0x4330) < fVar12 || (*(float *)(iVar5 + 0x4334) < (float)this)))) {
      pvVar7 = this;
      if (((pfVar8[0xb] != 5.60519e-45) && (pfVar8[0xb] != 4.2039e-45)) &&
         (((pvVar7 = (void *)(_DAT_00474e5c & 4), pvVar7 != (void *)0x0 &&
           ((((*(float *)(iVar5 + 0x433c) <= fVar12 && (*(float *)(iVar5 + 0x4340) <= (float)this))
             && (fVar12 <= *(float *)(iVar5 + 0x4348))) &&
            ((float)this <= *(float *)(iVar5 + 0x434c))))) ||
          ((((short)pvVar7 == 0 && (*(float *)(iVar5 + 0x4354) <= fVar12)) &&
           ((*(float *)(iVar5 + 0x4358) <= (float)this &&
            ((fVar12 <= *(float *)(iVar5 + 0x4360) && ((float)this <= *(float *)(iVar5 + 0x4364)))))
           )))))) {
        pvVar7 = *(void **)(iVar5 + 0x45c);
        fVar12 = *(float *)((int)pvVar7 + 8);
        pfVar8[0xb] = 5.60519e-45;
        pfVar8[0xe] = fVar12 * _DAT_00470cc4;
      }
      goto LAB_0041b7fd;
    }
    switch(pfVar8[0xc]) {
    case 1.4013e-45:
    case 1.4013e-44:
      bVar4 = FUN_00418930(this,1);
      iVar5 = (int)DAT_00474c48 / 0x14;
      FUN_004054b0(iVar5,iVar5,(((int)DAT_00474c48 % 0x14) * 100) / 0x14);
      if (CONCAT31(extraout_var,bVar4) == 0) {
        FUN_0042b9c0(0xffff4040);
        FUN_00412ff0(0x3c);
      }
      else {
        FUN_00426f70(DAT_00477834);
        FUN_0042b9c0(0xffffff40);
        FUN_0043dd10();
        if (99 < DAT_00474c48) {
          bVar3 = true;
        }
        FUN_00405b60(0xc);
        FUN_00412ff0(0x3c);
      }
      break;
    case 2.8026e-45:
      if (*(float *)(iVar5 + 0x3c4) < _DAT_00470cd4) {
        iVar5 = DAT_00474c4c * 10 - (DAT_00474c4c * 10) % 10;
        goto LAB_0041b542;
      }
      uVar11 = FUN_00463b2c();
      iVar5 = (DAT_00474c4c * 10) / 2 - (int)uVar11;
      iVar5 = iVar5 - iVar5 % 10;
      FUN_0042b9c0(0xffffffff);
      iVar6 = 1;
      goto LAB_0041b559;
    case 4.2039e-45:
      iVar5 = 5000;
      switch(DAT_00474c74) {
      case 0:
      case 1:
        iVar5 = 5000;
        break;
      case 2:
        iVar5 = 8000;
        break;
      case 3:
      case 4:
        iVar5 = 10000;
      }
      FUN_0042b9c0(0xff00ff00);
      FUN_0041be80(&DAT_00474c40,iVar5);
      FUN_00412ff0(0x78);
      break;
    case 5.60519e-45:
    case 1.54143e-44:
      bVar4 = FUN_00418930(this,0x14);
      iVar5 = (int)DAT_00474c48 / 0x14;
      FUN_004054b0(iVar5,iVar5,(((int)DAT_00474c48 % 0x14) * 100) / 0x14);
      if (CONCAT31(extraout_var_00,bVar4) == 0) {
        FUN_0042b9c0(0xffff4040);
      }
      else {
        FUN_00426f70(DAT_00477834);
        FUN_0043dd10();
        FUN_0042b9c0(0xffffff40);
        FUN_00405b60(0x18);
        if (99 < DAT_00474c48) {
          bVar3 = true;
          FUN_00412ff0(0x14);
          break;
        }
      }
      FUN_00412ff0(0x14);
      break;
    case 7.00649e-45:
      iVar5 = DAT_00474c4c * 10;
LAB_0041b542:
      FUN_0042b9c0(0xffffff00);
      iVar6 = 8;
LAB_0041b559:
      FUN_00405b60(iVar6);
      FUN_00409d90(&DAT_00474c40,iVar5);
      FUN_00412ff0(100);
      break;
    case 9.80909e-45:
      FUN_004188a0(1);
      FUN_00405b60(0x100);
      break;
    case 1.12104e-44:
      FUN_0041be80(&DAT_00474c40,10);
      FUN_00412ff0(3);
      FUN_00409d90(&DAT_00474c40,10);
      break;
    case 1.26117e-44:
      FUN_0042b9c0(0xff00ff00);
      FUN_0041be80(&DAT_00474c40,100);
      FUN_00412ff0(0x3c);
    }
    pfVar8[0xb] = 0.0;
    FUN_0043dd10();
LAB_0041b85a:
    local_58 = local_58 + 0x3f0;
    pfVar8 = pfVar8 + 0xfc;
    local_4c = local_4c + -1;
    if (local_4c == 0) {
      if (bVar3) {
        FUN_0041ba50();
      }
      return 1;
    }
  } while( true );
}

