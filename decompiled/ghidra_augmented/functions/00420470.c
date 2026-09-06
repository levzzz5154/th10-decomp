/* Raw Ghidra reference; not compilable reconstruction. Address: 00420470 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int FUN_00420470(void)

{
  int iVar1;
  int iVar2;
  
  _DAT_00491fb4 = 0xfffffffe;
  DAT_00491fb8 = 0;
  _DAT_00491fc0 = 0;
  iVar1 = FUN_00449ed0(FUN_0041ff80);
  iVar2 = DAT_00491be4;
  *(uint *)(iVar1 + 4) = *(uint *)(iVar1 + 4) | 2;
  *(undefined **)(iVar1 + 0x20) = &DAT_00491c28;
  *(code **)(iVar1 + 0xc) = FUN_004201b0;
  iVar2 = FUN_00449ae0(iVar2);
  if (iVar2 == 0) {
    iVar1 = FUN_00449ed0(FUN_00420000);
    iVar2 = DAT_00491be4;
    *(uint *)(iVar1 + 4) = *(uint *)(iVar1 + 4) | 2;
    *(undefined **)(iVar1 + 0x20) = &DAT_00491c28;
    FUN_00449b70(iVar2);
    iVar1 = FUN_00449ed0(FUN_004200c0);
    *(uint *)(iVar1 + 4) = *(uint *)(iVar1 + 4) | 2;
    iVar2 = DAT_00491be4;
    *(undefined **)(iVar1 + 0x20) = &DAT_00491c28;
    FUN_00449b70(iVar2);
    iVar1 = FUN_00449ed0(FUN_004200d0);
    *(uint *)(iVar1 + 4) = *(uint *)(iVar1 + 4) | 2;
    iVar2 = DAT_00491be4;
    *(undefined **)(iVar1 + 0x20) = &DAT_00491c28;
    FUN_00449b70(iVar2);
    iVar2 = 0;
  }
  return iVar2;
}

