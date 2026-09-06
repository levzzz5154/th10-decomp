/* Raw Ghidra reference; not compilable reconstruction. Address: 00441950 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

ulonglong __fastcall FUN_00441950(undefined4 param_1,int param_2)

{
  float *pfVar1;
  int iVar2;
  float fVar3;
  int *unaff_ESI;
  ulonglong uVar4;
  int local_8;
  
  local_8 = unaff_ESI[9];
  if (0 < local_8) {
    pfVar1 = (float *)unaff_ESI[7];
    unaff_ESI[4] = unaff_ESI[5];
    if ((*pfVar1 <= _DAT_00470b68) || (_DAT_00470b64 <= *pfVar1)) {
      unaff_ESI[6] = (int)(*pfVar1 + (float)unaff_ESI[6]);
      uVar4 = FUN_00463b2c();
      param_2 = (int)(uVar4 >> 0x20);
      unaff_ESI[5] = (int)uVar4;
    }
    else {
      param_2 = unaff_ESI[5] + 1;
      fVar3 = (float)unaff_ESI[6] + _DAT_00470afc;
      unaff_ESI[5] = param_2;
      unaff_ESI[6] = (int)fVar3;
    }
    local_8 = unaff_ESI[9];
    if (local_8 <= unaff_ESI[5]) {
      if ((unaff_ESI[8] & 1U) == 0) {
        unaff_ESI[5] = 0;
        unaff_ESI[4] = -999999;
        unaff_ESI[6] = 0;
        unaff_ESI[7] = (int)&DAT_00476f78;
        unaff_ESI[8] = unaff_ESI[8] | 1;
      }
      unaff_ESI[5] = local_8;
      unaff_ESI[4] = local_8 + -1;
      unaff_ESI[6] = (int)(float)local_8;
      unaff_ESI[9] = 0;
      if (unaff_ESI[10] != 7) {
        return CONCAT44(param_2,unaff_ESI[1]);
      }
      goto LAB_00441a15;
    }
  }
  iVar2 = unaff_ESI[10];
  if (iVar2 != 7) {
    if (iVar2 == 0x11) {
      *unaff_ESI = *unaff_ESI + unaff_ESI[3];
      unaff_ESI[3] = unaff_ESI[1] + unaff_ESI[3];
      return CONCAT44(param_2,*unaff_ESI);
    }
    if (iVar2 == 8) {
      uVar4 = FUN_00463b2c();
      return uVar4;
    }
    FUN_0044c350((float)unaff_ESI[6],(float)local_8);
    uVar4 = FUN_00463b2c();
    return uVar4;
  }
  *unaff_ESI = *unaff_ESI + unaff_ESI[1];
LAB_00441a15:
  return CONCAT44(param_2,*unaff_ESI);
}

