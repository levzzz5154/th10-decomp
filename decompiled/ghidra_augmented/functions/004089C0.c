/* Raw Ghidra reference; not compilable reconstruction. Address: 004089C0 */

undefined4 FUN_004089c0(void)

{
  int iVar1;
  int iVar2;
  int unaff_EBX;
  
  iVar2 = FUN_00449ed0(FUN_00409220);
  iVar1 = DAT_00491be4;
  *(int *)(iVar2 + 0x20) = unaff_EBX;
  *(uint *)(iVar2 + 4) = *(uint *)(iVar2 + 4) & 0xfffffffd;
  FUN_00449ae0(iVar1);
  *(int *)(unaff_EBX + 8) = iVar2;
  iVar2 = FUN_00449ed0(FUN_00409230);
  iVar1 = DAT_00491be4;
  *(uint *)(iVar2 + 4) = *(uint *)(iVar2 + 4) & 0xfffffffd;
  *(int *)(iVar2 + 0x20) = unaff_EBX;
  FUN_00449b70(iVar1);
  *(int *)(unaff_EBX + 0xc) = iVar2;
  iVar2 = FUN_00449ed0(FUN_00409270);
  iVar1 = DAT_00491be4;
  *(int *)(iVar2 + 0x20) = unaff_EBX;
  *(uint *)(iVar2 + 4) = *(uint *)(iVar2 + 4) & 0xfffffffd;
  FUN_00449b70(iVar1);
  *(int *)(unaff_EBX + 0x37ac) = iVar2;
  if ((*(uint *)(unaff_EBX + 0x3744) & 1) == 0) {
    *(undefined4 *)(unaff_EBX + 0x3738) = 0;
    *(undefined4 *)(unaff_EBX + 0x3734) = 0xfff0bdc1;
    *(undefined4 *)(unaff_EBX + 0x373c) = 0;
    *(undefined4 **)(unaff_EBX + 0x3740) = &DAT_00476f78;
    *(uint *)(unaff_EBX + 0x3744) = *(uint *)(unaff_EBX + 0x3744) | 1;
  }
  *(undefined4 *)(unaff_EBX + 0x3738) = 0;
  *(undefined4 *)(unaff_EBX + 0x373c) = 0;
  *(undefined4 *)(unaff_EBX + 0x3734) = 0xffffffff;
  return 0;
}

