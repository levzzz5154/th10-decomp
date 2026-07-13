/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x00404ED0
 * Tracking name: FUN_00404ed0
 * Ghidra name: FUN_00404ed0
 * Tracked span: 96 bytes
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00404ed0(void)

{
  float *pfVar1;
  float fVar2;
  int *unaff_ESI;
  ulonglong uVar3;
  
  pfVar1 = (float *)unaff_ESI[3];
  *unaff_ESI = unaff_ESI[1];
  if ((_DAT_00470b68 < *pfVar1) && (*pfVar1 < _DAT_00470b64)) {
    fVar2 = (float)unaff_ESI[2] + _DAT_00470afc;
    unaff_ESI[1] = unaff_ESI[1] + 1;
    unaff_ESI[2] = (int)fVar2;
    return;
  }
  unaff_ESI[2] = (int)(*pfVar1 + (float)unaff_ESI[2]);
  uVar3 = FUN_00463b2c();
  unaff_ESI[1] = (int)uVar3;
  return;
}

