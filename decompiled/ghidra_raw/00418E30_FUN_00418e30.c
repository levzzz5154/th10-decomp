/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x00418E30
 * Tracking name: FUN_00418e30
 * Ghidra name: FUN_00418e30
 * Tracked span: 176 bytes
 */


undefined4 FUN_00418e30(void)

{
  int iVar1;
  int iVar2;
  int unaff_EBX;
  
  iVar2 = FUN_00449ed0(FUN_004198a0);
  iVar1 = DAT_00491be4;
  *(int *)(iVar2 + 0x20) = unaff_EBX;
  *(uint *)(iVar2 + 4) = *(uint *)(iVar2 + 4) & 0xfffffffd;
  FUN_00449ae0(iVar1);
  *(int *)(unaff_EBX + 8) = iVar2;
  iVar2 = FUN_00449ed0(&LAB_004198b0);
  iVar1 = DAT_00491be4;
  *(uint *)(iVar2 + 4) = *(uint *)(iVar2 + 4) & 0xfffffffd;
  *(int *)(iVar2 + 0x20) = unaff_EBX;
  FUN_00449b70(iVar1);
  *(int *)(unaff_EBX + 0xc) = iVar2;
  *(undefined4 *)(unaff_EBX + 0x10) = 0;
  if (DAT_00491d6a != '\0') {
    FUN_00419960(unaff_EBX,0x46d6d8,0);
    FUN_00419960(unaff_EBX,0x46d6c4,1);
  }
  return 0;
}

