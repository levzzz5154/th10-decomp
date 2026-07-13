/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x0044BF40
 * Tracking name: FUN_0044bf40
 * Ghidra name: FUN_0044bf40
 * Tracked span: 448 bytes
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0044bf40(float param_1)

{
  float *pfVar1;
  undefined4 *unaff_ESI;
  ulonglong uVar2;
  
  pfVar1 = (float *)unaff_ESI[3];
  *unaff_ESI = unaff_ESI[1];
  if ((_DAT_00470b68 < *pfVar1) && (*pfVar1 < _DAT_00470b64)) {
    unaff_ESI[2] = param_1 + (float)unaff_ESI[2];
    uVar2 = FUN_00463b2c();
    unaff_ESI[1] = (int)uVar2;
    return;
  }
  unaff_ESI[2] = param_1 * *pfVar1 + (float)unaff_ESI[2];
  uVar2 = FUN_00463b2c();
  unaff_ESI[1] = (int)uVar2;
  return;
}

