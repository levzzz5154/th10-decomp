/* Raw Ghidra reference; not compilable reconstruction. Address: 004055C0 */

undefined4 InstallEnabledResourcePair(void)

{
  int iVar1;
  int iVar2;
  int unaff_EBX;
  
  iVar2 = FUN_00449ed0(FUN_00405840);
  *(uint *)(iVar2 + 4) = *(uint *)(iVar2 + 4) | 2;
  iVar1 = DAT_00491be4;
  *(int *)(iVar2 + 0x20) = unaff_EBX;
  FUN_00449ae0(iVar1);
  *(int *)(unaff_EBX + 8) = iVar2;
  iVar2 = FUN_00449ed0(FUN_00405850);
  *(uint *)(iVar2 + 4) = *(uint *)(iVar2 + 4) | 2;
  iVar1 = DAT_00491be4;
  *(int *)(iVar2 + 0x20) = unaff_EBX;
  FUN_00449b70(iVar1);
  *(int *)(unaff_EBX + 0xc) = iVar2;
  return 0;
}

