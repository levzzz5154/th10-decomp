/* Raw Ghidra reference; not compilable reconstruction. Address: 0041AD90 */

undefined4 InstallDisabledResourcePair(void)

{
  int iVar1;
  int iVar2;
  int unaff_EBX;
  
  iVar2 = FUN_00449ed0(FUN_0041ba00);
  *(uint *)(iVar2 + 4) = *(uint *)(iVar2 + 4) & 0xfffffffd;
  iVar1 = DAT_00491be4;
  *(int *)(iVar2 + 0x20) = unaff_EBX;
  FUN_00449ae0(iVar1);
  *(int *)(unaff_EBX + 8) = iVar2;
  iVar2 = FUN_00449ed0(FUN_0041ba30);
  *(uint *)(iVar2 + 4) = *(uint *)(iVar2 + 4) & 0xfffffffd;
  iVar1 = DAT_00491be4;
  *(int *)(iVar2 + 0x20) = unaff_EBX;
  FUN_00449b70(iVar1);
  *(int *)(unaff_EBX + 0xc) = iVar2;
  return 0;
}

