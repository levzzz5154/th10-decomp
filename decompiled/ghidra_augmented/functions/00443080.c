/* Raw Ghidra reference; not compilable reconstruction. Address: 00443080 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00443080(void *param_1)

{
  float fVar1;
  float fVar2;
  uint uVar3;
  int unaff_ESI;
  float10 fVar4;
  float fVar5;
  
  fVar5 = *(float *)(unaff_ESI + 0x4c) * *(float *)(unaff_ESI + 0x3c);
  uVar3 = *(uint *)(unaff_ESI + 0x35c) >> 0x12 & 3;
  fVar1 = *(float *)(unaff_ESI + 0x50) * *(float *)(unaff_ESI + 0x40);
  fVar2 = fVar1 * _DAT_00470b0c;
  if (uVar3 == 0) {
    fVar4 = FUN_00452ff0((double)((*(float *)(unaff_ESI + 0x34c) + *(float *)(unaff_ESI + 0x340) +
                                  *(float *)(unaff_ESI + 0x334)) - fVar5 * _DAT_00470b0c),
                         SUB42(fVar5,0));
    DAT_004978f8 = (float)fVar4;
    DAT_004978dc = DAT_004978f8 + fVar5;
    DAT_004978c0 = DAT_004978f8;
    DAT_00497914 = DAT_004978dc;
  }
  else if (uVar3 == 1) {
    DAT_004978c0 = *(float *)(unaff_ESI + 0x334) + *(float *)(unaff_ESI + 0x340) +
                   *(float *)(unaff_ESI + 0x34c);
    DAT_004978dc = *(float *)(unaff_ESI + 0x334) + *(float *)(unaff_ESI + 0x340) + fVar5 +
                   *(float *)(unaff_ESI + 0x34c);
    DAT_004978f8 = DAT_004978c0;
    DAT_00497914 = DAT_004978dc;
  }
  else if (uVar3 == 2) {
    DAT_004978c0 = (*(float *)(unaff_ESI + 0x334) + *(float *)(unaff_ESI + 0x340) +
                   *(float *)(unaff_ESI + 0x34c)) - fVar5;
    DAT_004978dc = *(float *)(unaff_ESI + 0x334) + *(float *)(unaff_ESI + 0x340) +
                   *(float *)(unaff_ESI + 0x34c);
    DAT_004978f8 = DAT_004978c0;
    DAT_00497914 = DAT_004978dc;
  }
  uVar3 = *(uint *)(unaff_ESI + 0x35c) >> 0x14 & 3;
  if (uVar3 == 0) {
    fVar4 = FUN_00452ff0((double)((*(float *)(unaff_ESI + 0x350) + *(float *)(unaff_ESI + 0x344) +
                                  *(float *)(unaff_ESI + 0x338)) - fVar2),SUB42(fVar5,0));
    DAT_004978e0 = (float)fVar4;
    fVar5 = DAT_004978e0;
  }
  else {
    if (uVar3 != 1) {
      if (uVar3 == 2) {
        DAT_004978c4 = (*(float *)(unaff_ESI + 0x344) + *(float *)(unaff_ESI + 0x350) +
                       *(float *)(unaff_ESI + 0x338)) - fVar1;
        DAT_004978fc = *(float *)(unaff_ESI + 0x344) + *(float *)(unaff_ESI + 0x350) +
                       *(float *)(unaff_ESI + 0x338);
        DAT_004978e0 = DAT_004978c4;
        DAT_00497918 = DAT_004978fc;
      }
      goto LAB_00443246;
    }
    DAT_004978e0 = *(float *)(unaff_ESI + 0x344) + *(float *)(unaff_ESI + 0x350) +
                   *(float *)(unaff_ESI + 0x338);
    fVar5 = *(float *)(unaff_ESI + 0x344) + *(float *)(unaff_ESI + 0x350) +
            *(float *)(unaff_ESI + 0x338);
  }
  DAT_004978fc = fVar5 + fVar1;
  DAT_004978c4 = DAT_004978e0;
  DAT_00497918 = DAT_004978fc;
LAB_00443246:
  _DAT_004978c8 =
       *(float *)(unaff_ESI + 0x354) + *(float *)(unaff_ESI + 0x348) + *(float *)(unaff_ESI + 0x33c)
  ;
  _DAT_004978e4 = _DAT_004978c8;
  _DAT_00497900 = _DAT_004978c8;
  _DAT_0049791c = _DAT_004978c8;
  FUN_00442670(param_1,1);
  return;
}

