/* Raw Ghidra reference; not compilable reconstruction. Address: 0040A130 */

undefined4 FUN_0040a130(void)

{
  int iVar1;
  int iVar2;
  int unaff_EBX;
  
  DAT_00477848 = &DAT_00474788;
  DAT_00474c7c = 0;
  DAT_00474c80 = 0;
  iVar2 = FUN_00449ed0(FUN_0040abe0);
  *(uint *)(iVar2 + 4) = *(uint *)(iVar2 + 4) | 2;
  iVar1 = DAT_00491be4;
  *(int *)(iVar2 + 0x20) = unaff_EBX;
  FUN_00449ae0(iVar1);
  *(int *)(unaff_EBX + 8) = iVar2;
  iVar2 = FUN_00449ed0(FUN_0040abf0);
  *(uint *)(iVar2 + 4) = *(uint *)(iVar2 + 4) | 2;
  iVar1 = DAT_00491be4;
  *(int *)(iVar2 + 0x20) = unaff_EBX;
  FUN_00449b70(iVar1);
  *(int *)(unaff_EBX + 0xc) = iVar2;
  return 0;
}

