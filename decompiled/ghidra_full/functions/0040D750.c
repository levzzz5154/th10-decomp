/* Raw Ghidra reference; not compilable reconstruction. Address: 0040D750 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 FUN_0040d750(void)

{
  int *piVar1;
  int *piVar2;
  float *pfVar3;
  float fVar4;
  int *piVar5;
  int iVar6;
  int unaff_EDI;
  ulonglong uVar7;
  
  piVar5 = *(int **)(unaff_EDI + 0x58);
  while (piVar5 != (int *)0x0) {
    piVar1 = (int *)piVar5[1];
    if (((*(uint *)(*piVar5 + 0x2480) & 0x20000) == 0) &&
       (iVar6 = FUN_0040dc80((undefined4 *)(*piVar5 + 0x103c)), iVar6 == 0)) {
      *(uint *)(*piVar5 + 0x2480) = *(uint *)(*piVar5 + 0x2480) & 0xfffffbff;
      piVar5 = piVar1;
    }
    else {
      piVar2 = (int *)*piVar5;
      piVar5 = piVar1;
      if (piVar2 != (int *)0x0) {
        (**(code **)(*piVar2 + 0x14))(1);
      }
    }
  }
  pfVar3 = *(float **)(unaff_EDI + 0x4c);
  *(int *)(unaff_EDI + 0x40) = *(int *)(unaff_EDI + 0x44);
  if ((_DAT_00470b68 < *pfVar3) && (*pfVar3 < _DAT_00470b64)) {
    iVar6 = *(int *)(unaff_EDI + 0x44) + 1;
    fVar4 = *(float *)(unaff_EDI + 0x48) + _DAT_00470afc;
    *(int *)(unaff_EDI + 0x44) = iVar6;
    *(float *)(unaff_EDI + 0x48) = fVar4;
    return CONCAT44(iVar6,1);
  }
  *(float *)(unaff_EDI + 0x48) = *pfVar3 + *(float *)(unaff_EDI + 0x48);
  uVar7 = FUN_00463b2c();
  *(int *)(unaff_EDI + 0x44) = (int)uVar7;
  return CONCAT44((int)(uVar7 >> 0x20),1);
}

