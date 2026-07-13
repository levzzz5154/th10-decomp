/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x0040C9D0
 * Tracking name: FUN_0040c9d0
 * Ghidra name: FUN_0040c9d0
 * Tracked span: 640 bytes
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0040c9d0(float param_1)

{
  ushort uVar1;
  float fVar2;
  float fVar3;
  uint uVar4;
  int iVar5;
  float *unaff_ESI;
  int *piVar6;
  int *piVar7;
  float10 fVar8;
  int local_18;
  float local_c;
  float local_8;
  float local_4;
  
  fVar3 = param_1;
  fVar8 = FUN_0044bb90(&DAT_004918b0);
  piVar7 = (int *)((int)param_1 + 4);
  local_18 = 0;
  param_1 = (float)(fVar8 * (float10)_DAT_00470b18);
  piVar6 = piVar7;
  do {
    iVar5 = 0;
    if (0 < *piVar6) {
      do {
        FUN_00413270(&local_c,param_1,*(float *)((int)fVar3 + 0x34),*(float *)((int)fVar3 + 0x38));
        uVar1 = ((ushort)_DAT_004918b0 ^ 0x9630) + 0x9aad;
        _DAT_004918b0 = CONCAT22(DAT_004918b0_2,(uVar1 >> 0xe) + uVar1 * 4);
        uVar4 = (_DAT_004918b0 ^ 0x9630) - 0x6553;
        uVar4 = (uVar4 >> 0xe & 3) + uVar4 * 4;
        DAT_004918b0 = (ushort)uVar4;
        uVar4 = uVar4 * 0x10000 | uVar4 & 0xffff;
        DAT_004918b4 = DAT_004918b4 + 2;
        fVar2 = (float)(int)uVar4;
        if ((int)uVar4 < 0) {
          fVar2 = fVar2 + _DAT_00470b98;
        }
        local_4 = unaff_ESI[2];
        fVar2 = fVar2 * _DAT_00470d18 + _DAT_00470b0c;
        local_c = local_c * fVar2 + *unaff_ESI;
        local_8 = local_8 * fVar2 + unaff_ESI[1];
        FUN_0041bb00(&local_c,local_18 + 1,0xffffffff,-1.5707964,2.2);
        uVar1 = (DAT_004918b0 ^ 0x9630) + 0x9aad;
        _DAT_004918b0 = CONCAT22(DAT_004918b0_2,(uVar1 >> 0xe) + uVar1 * 4);
        uVar4 = (_DAT_004918b0 ^ 0x9630) - 0x6553;
        uVar4 = (uVar4 >> 0xe & 3) + uVar4 * 4;
        _DAT_004918b0 = CONCAT22(DAT_004918b0_2,(short)uVar4);
        uVar4 = uVar4 * 0x10000 | uVar4 & 0xffff;
        DAT_004918b4 = DAT_004918b4 + 2;
        fVar2 = (float)(int)uVar4;
        if ((int)uVar4 < 0) {
          fVar2 = fVar2 + _DAT_00470b98;
        }
        fVar8 = (float10)FUN_0044bc70((fVar2 * _DAT_00470bec - _DAT_00470afc) * _DAT_00470c48 +
                                      param_1 + _DAT_00470b94);
        param_1 = (float)fVar8;
        iVar5 = iVar5 + 1;
      } while (iVar5 < *piVar6);
    }
    local_18 = local_18 + 1;
    piVar6 = piVar6 + 1;
  } while (local_18 < 0xb);
  for (iVar5 = 0xc; iVar5 != 0; iVar5 = iVar5 + -1) {
    *piVar7 = 0;
    piVar7 = piVar7 + 1;
  }
  return;
}

