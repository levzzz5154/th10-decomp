/* Raw Ghidra reference; not compilable reconstruction. Address: 004452F0 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

longlong FUN_004452f0(void)

{
  float fVar1;
  float fVar2;
  ushort uVar3;
  float *pfVar4;
  uint uVar5;
  float *extraout_EDX;
  int extraout_EDX_00;
  float *this;
  int unaff_EDI;
  float10 fVar6;
  float local_28;
  float local_24;
  int local_20;
  float local_18;
  float local_14;
  float local_10;
  float local_4;
  
  if (*(void **)(unaff_EDI + 0x358) != (void *)0x0) {
    _free(*(void **)(unaff_EDI + 0x358));
    *(undefined4 *)(unaff_EDI + 0x358) = 0;
  }
  pfVar4 = _malloc(0x4b0);
  *(float **)(unaff_EDI + 0x358) = pfVar4;
  *(code **)(unaff_EDI + 0x398) = FUN_00445620;
  *(code **)(unaff_EDI + 0x39c) = FUN_00445880;
  fVar6 = FUN_0044bb90(&DAT_004918b0);
  pfVar4[0x129] = (float)(fVar6 * (float10)_DAT_00470c7c);
  fVar6 = FUN_0044bb90(&DAT_004918b0);
  local_24 = -3.1415927;
  pfVar4[0x12a] = (float)(fVar6 * (float10)_DAT_00470c7c);
  local_18 = *(float *)(unaff_EDI + 0x340) + *(float *)(unaff_EDI + 0x334);
  local_14 = *(float *)(unaff_EDI + 0x344) + *(float *)(unaff_EDI + 0x338);
  local_10 = *(float *)(unaff_EDI + 0x348) + *(float *)(unaff_EDI + 0x33c);
  *pfVar4 = local_18;
  pfVar4[1] = local_14;
  pfVar4[3] = 1.0;
  pfVar4[2] = local_10;
  pfVar4[5] = 0.5;
  pfVar4[6] = 0.5;
  fVar6 = FUN_0044bb90(&DAT_004918b0);
  local_20 = 0x1f;
  local_28 = (float)(fVar6 * (float10)_DAT_00470c78);
  do {
    this = pfVar4 + 7;
    if (_DAT_00470b18 <= local_24) {
      local_24 = local_24 - _DAT_00470b14;
    }
    pfVar4[10] = 1.0;
    FUN_004458b0(&local_18,local_24,0.5);
    fVar1 = local_18 + _DAT_00470b0c;
    pfVar4[9] = 0.0;
    pfVar4[0xc] = fVar1;
    pfVar4[0xd] = local_14 + _DAT_00470b0c;
    uVar3 = ((ushort)_DAT_004918b0 ^ 0x9630) + 0x9aad;
    _DAT_004918b0 = CONCAT22(DAT_004918b0_2,(uVar3 >> 0xe) + uVar3 * 4);
    uVar5 = (_DAT_004918b0 ^ 0x9630) - 0x6553;
    uVar5 = (uVar5 >> 0xe & 3) + uVar5 * 4;
    DAT_004918b0 = (ushort)uVar5;
    uVar5 = uVar5 * 0x10000 | uVar5 & 0xffff;
    DAT_004918b4 = DAT_004918b4 + 2;
    fVar1 = (float)(int)uVar5;
    if ((int)uVar5 < 0) {
      fVar1 = fVar1 + _DAT_00470b98;
    }
    fVar1 = fVar1 * _DAT_00470bec;
    extraout_EDX[0x21] = local_28;
    *extraout_EDX = (fVar1 - _DAT_00470afc) * _DAT_00470bd0 + _DAT_00470c28;
    uVar3 = (DAT_004918b0 ^ 0x9630) + 0x9aad;
    _DAT_004918b0 = CONCAT22(DAT_004918b0_2,(uVar3 >> 0xe) + uVar3 * 4);
    uVar5 = (_DAT_004918b0 ^ 0x9630) - 0x6553;
    uVar5 = (uVar5 >> 0xe & 3) + uVar5 * 4;
    _DAT_004918b0 = CONCAT22(DAT_004918b0_2,(short)uVar5);
    uVar5 = uVar5 * 0x10000 | uVar5 & 0xffff;
    DAT_004918b4 = DAT_004918b4 + 2;
    fVar1 = (float)(int)uVar5;
    if ((int)uVar5 < 0) {
      fVar1 = fVar1 + _DAT_00470b98;
    }
    local_28 = (fVar1 * _DAT_00470bec - _DAT_00470afc) * _DAT_00470c74 + local_28;
    if (_DAT_00470c70 <= local_28) {
      if (_DAT_00470c78 < local_28) {
        local_28 = 0.06666667;
      }
    }
    else {
      local_28 = -0.06666667;
    }
    FUN_004458b0(this,local_24,*extraout_EDX);
    fVar1 = *(float *)(unaff_EDI + 0x338);
    fVar2 = *(float *)(unaff_EDI + 0x344);
    local_20 = local_20 + -1;
    local_4 = *(float *)(unaff_EDI + 0x348) + *(float *)(unaff_EDI + 0x33c);
    *this = *(float *)(unaff_EDI + 0x340) + *(float *)(unaff_EDI + 0x334) + *this;
    pfVar4[8] = fVar1 + fVar2 + pfVar4[8];
    pfVar4[9] = local_4 + pfVar4[9];
    local_24 = local_24 + _DAT_00470b6c;
    pfVar4 = this;
  } while (local_20 != 0);
  return (ulonglong)(extraout_EDX_00 + 4) << 0x20;
}

