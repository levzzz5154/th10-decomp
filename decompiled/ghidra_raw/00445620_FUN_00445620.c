/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x00445620
 * Tracking name: FUN_00445620
 * Ghidra name: FUN_00445620
 * Tracked span: 656 bytes
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 __fastcall FUN_00445620(int param_1)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float *pfVar5;
  float *pfVar6;
  int iVar7;
  int iVar8;
  int extraout_EDX;
  float *pfVar9;
  float *this;
  float local_18;
  
  pfVar9 = *(float **)(param_1 + 0x358);
  fVar1 = *(float *)(param_1 + 0x344);
  fVar2 = *(float *)(param_1 + 0x338);
  local_18 = -3.1415927;
  fVar3 = *(float *)(param_1 + 0x348);
  fVar4 = *(float *)(param_1 + 0x33c);
  *pfVar9 = *(float *)(param_1 + 0x340) + *(float *)(param_1 + 0x334);
  pfVar9[1] = fVar1 + fVar2;
  pfVar9[2] = fVar3 + fVar4;
  fVar1 = pfVar9[5];
  pfVar9[5] = pfVar9[0x129] + fVar1;
  if (pfVar9[0x129] + fVar1 < _DAT_00470b04) {
    iVar7 = 0xb;
    pfVar5 = pfVar9 + 0xc;
    do {
      iVar7 = iVar7 + -1;
      pfVar5[-7] = pfVar5[-7] + _DAT_00470afc;
      *pfVar5 = *pfVar5 + _DAT_00470afc;
      pfVar5[7] = pfVar5[7] + _DAT_00470afc;
      pfVar5 = pfVar5 + 0x15;
    } while (iVar7 != 0);
  }
  fVar1 = pfVar9[6];
  pfVar9[6] = pfVar9[0x129] + fVar1;
  if (pfVar9[0x129] + fVar1 < _DAT_00470b04) {
    iVar7 = 0xb;
    pfVar5 = pfVar9 + 0xd;
    do {
      iVar7 = iVar7 + -1;
      pfVar5[-7] = pfVar5[-7] + _DAT_00470afc;
      *pfVar5 = *pfVar5 + _DAT_00470afc;
      pfVar5[7] = pfVar5[7] + _DAT_00470afc;
      pfVar5 = pfVar5 + 0x15;
    } while (iVar7 != 0);
  }
  pfVar9[4] = *(float *)(param_1 + 0x2fc);
  pfVar5 = pfVar9 + 0xe8;
  iVar7 = 0x1f;
  this = pfVar9 + 7;
  do {
    fVar1 = pfVar9[0x129];
    fVar2 = this[5];
    this[5] = fVar1 + fVar2;
    if (fVar1 + fVar2 < _DAT_00470b04) {
      iVar8 = 0xb;
      pfVar6 = pfVar9 + 0xc;
      do {
        iVar8 = iVar8 + -1;
        pfVar6[-7] = pfVar6[-7] + _DAT_00470afc;
        *pfVar6 = *pfVar6 + _DAT_00470afc;
        pfVar6[7] = pfVar6[7] + _DAT_00470afc;
        pfVar6 = pfVar6 + 0x15;
      } while (iVar8 != 0);
    }
    fVar1 = this[6];
    fVar2 = pfVar9[0x129];
    this[6] = fVar1 + fVar2;
    if (fVar1 + fVar2 < _DAT_00470b04) {
      iVar8 = 0xb;
      pfVar6 = pfVar9 + 0xd;
      do {
        iVar8 = iVar8 + -1;
        pfVar6[-7] = pfVar6[-7] + _DAT_00470afc;
        *pfVar6 = *pfVar6 + _DAT_00470afc;
        pfVar6[7] = pfVar6[7] + _DAT_00470afc;
        pfVar6 = pfVar6 + 0x15;
      } while (iVar8 != 0);
    }
    this[4] = *(float *)(param_1 + 0x2fc);
    *(undefined1 *)((int)this + 0x13) = 0;
    fVar1 = *pfVar5;
    *pfVar5 = pfVar5[0x21] + fVar1;
    FUN_004458b0(this,local_18,pfVar5[0x21] + fVar1);
    pfVar6 = this + 7;
    fVar1 = *(float *)(extraout_EDX + 0x338);
    pfVar5 = pfVar5 + 1;
    iVar7 = iVar7 + -1;
    fVar2 = *(float *)(extraout_EDX + 0x344);
    fVar3 = *(float *)(extraout_EDX + 0x348);
    fVar4 = *(float *)(extraout_EDX + 0x33c);
    *this = *(float *)(extraout_EDX + 0x340) + *(float *)(extraout_EDX + 0x334) + *this;
    this[1] = fVar1 + fVar2 + this[1];
    this[2] = fVar3 + fVar4 + this[2];
    local_18 = local_18 + _DAT_00470b6c;
    param_1 = extraout_EDX;
    this = pfVar6;
  } while (iVar7 != 0);
  pfVar9 = pfVar9 + 7;
  for (iVar7 = 7; iVar7 != 0; iVar7 = iVar7 + -1) {
    *pfVar6 = *pfVar9;
    pfVar9 = pfVar9 + 1;
    pfVar6 = pfVar6 + 1;
  }
  return 0;
}

