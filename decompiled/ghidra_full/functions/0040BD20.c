/* Raw Ghidra reference; not compilable reconstruction. Address: 0040BD20 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 TickRecoveryState(void)

{
  float *pfVar1;
  float fVar2;
  int iVar3;
  undefined4 *unaff_ESI;
  ulonglong uVar4;
  
  iVar3 = FUN_0040bd80(unaff_ESI);
  if (iVar3 != 0) {
    return 1;
  }
  pfVar1 = (float *)unaff_ESI[4];
  unaff_ESI[1] = unaff_ESI[2];
  if ((_DAT_00470b68 < *pfVar1) && (*pfVar1 < _DAT_00470b64)) {
    fVar2 = (float)unaff_ESI[3] + _DAT_00470afc;
    unaff_ESI[2] = unaff_ESI[2] + 1;
    unaff_ESI[3] = fVar2;
    return 0;
  }
  unaff_ESI[3] = (float)unaff_ESI[3] + *pfVar1;
  uVar4 = FUN_00463b2c();
  unaff_ESI[2] = (int)uVar4;
  return 0;
}

