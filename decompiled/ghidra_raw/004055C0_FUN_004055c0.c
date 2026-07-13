/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x004055C0
 * Tracking name: FUN_004055c0
 * Ghidra name: FUN_004055c0
 * Tracked span: 96 bytes
 */


undefined4 FUN_004055c0(void)

{
  int iVar1;
  int iVar2;
  int unaff_EBX;
  
  iVar2 = FUN_00449ed0(&LAB_00405840);
  *(uint *)(iVar2 + 4) = *(uint *)(iVar2 + 4) | 2;
  iVar1 = DAT_00491be4;
  *(int *)(iVar2 + 0x20) = unaff_EBX;
  FUN_00449ae0(iVar1);
  *(int *)(unaff_EBX + 8) = iVar2;
  iVar2 = FUN_00449ed0(&LAB_00405850);
  *(uint *)(iVar2 + 4) = *(uint *)(iVar2 + 4) | 2;
  iVar1 = DAT_00491be4;
  *(int *)(iVar2 + 0x20) = unaff_EBX;
  FUN_00449b70(iVar1);
  *(int *)(unaff_EBX + 0xc) = iVar2;
  return 0;
}

