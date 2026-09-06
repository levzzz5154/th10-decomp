/* Raw Ghidra reference; not compilable reconstruction. Address: 004223F0 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 __fastcall FUN_004223f0(void *param_1)

{
  float *pfVar1;
  float fVar2;
  int iVar3;
  int unaff_ESI;
  ulonglong uVar4;
  
  switch(*(undefined4 *)(unaff_ESI + 4)) {
  case 0:
    if (((DAT_00474ca0 & 0x20) == 0) &&
       (((((DAT_00474e36 & 8) != 0 || (((byte)DAT_00491ff4 & 0x10) != 0)) &&
         (*(int *)(DAT_00477810 + 8) != 0)) &&
        (((*(byte *)(*(int *)(DAT_00477810 + 8) + 4) & 2) != 0 &&
         (0x1d < *(int *)(DAT_00477810 + 0x14))))))) {
      FUN_00422ab0(unaff_ESI);
    }
    break;
  case 1:
  case 2:
  case 3:
  case 4:
  case 5:
    FUN_00422c80(param_1,unaff_ESI);
    break;
  case 6:
  case 7:
  case 8:
  case 9:
  case 10:
  case 0xb:
  case 0xc:
  case 0xd:
    FUN_004236f0(unaff_ESI);
  }
  pfVar1 = *(float **)(unaff_ESI + 0x1c);
  *(int *)(unaff_ESI + 0x10) = *(int *)(unaff_ESI + 0x14);
  if ((_DAT_00470b68 < *pfVar1) && (*pfVar1 < _DAT_00470b64)) {
    iVar3 = *(int *)(unaff_ESI + 0x14) + 1;
    fVar2 = *(float *)(unaff_ESI + 0x18) + _DAT_00470afc;
    *(int *)(unaff_ESI + 0x14) = iVar3;
    *(float *)(unaff_ESI + 0x18) = fVar2;
    return CONCAT44(iVar3,1);
  }
  *(float *)(unaff_ESI + 0x18) = *pfVar1 + *(float *)(unaff_ESI + 0x18);
  uVar4 = FUN_00463b2c();
  *(int *)(unaff_ESI + 0x14) = (int)uVar4;
  return CONCAT44((int)(uVar4 >> 0x20),1);
}

