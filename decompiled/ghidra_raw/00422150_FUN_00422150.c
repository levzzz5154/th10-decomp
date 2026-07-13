/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x00422150
 * Tracking name: FUN_00422150
 * Ghidra name: FUN_00422150
 * Tracked span: 208 bytes
 */


undefined4 FUN_00422150(void)

{
  int iVar1;
  int iVar2;
  int unaff_EBX;
  
  iVar2 = FUN_00449ed0(FUN_00422a90);
  iVar1 = DAT_00491be4;
  *(uint *)(iVar2 + 4) = *(uint *)(iVar2 + 4) & 0xfffffffd;
  *(int *)(iVar2 + 0x20) = unaff_EBX;
  FUN_00449ae0(iVar1);
  *(int *)(unaff_EBX + 8) = iVar2;
  iVar2 = FUN_00449ed0(&LAB_00422aa0);
  iVar1 = DAT_00491be4;
  *(int *)(iVar2 + 0x20) = unaff_EBX;
  *(uint *)(iVar2 + 4) = *(uint *)(iVar2 + 4) & 0xfffffffd;
  FUN_00449b70(iVar1);
  *(int *)(unaff_EBX + 0xc) = iVar2;
  if ((*(uint *)(unaff_EBX + 0x20) & 1) == 0) {
    *(undefined4 *)(unaff_EBX + 0x14) = 0;
    *(undefined4 *)(unaff_EBX + 0x10) = 0xfff0bdc1;
    *(undefined4 *)(unaff_EBX + 0x18) = 0;
    *(undefined4 **)(unaff_EBX + 0x1c) = &DAT_00476f78;
    *(uint *)(unaff_EBX + 0x20) = *(uint *)(unaff_EBX + 0x20) | 1;
  }
  *(undefined4 *)(unaff_EBX + 0x14) = 0;
  *(undefined4 *)(unaff_EBX + 0x18) = 0;
  *(undefined4 *)(unaff_EBX + 0x10) = 0xffffffff;
  return 0;
}

