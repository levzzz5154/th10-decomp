/* Raw Ghidra reference; not compilable reconstruction. Address: 0040B9F0 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_0040b9f0(void)

{
  uint uVar1;
  int iVar2;
  undefined4 uVar3;
  int unaff_EDI;
  
  iVar2 = TickRecoveryState();
  if (iVar2 != 0) {
    DAT_00491fb8 = (-(uint)((DAT_00491ff4 & 0x1000) != 0) & 0xfffffff3) + 0xf;
    return 1;
  }
  iVar2 = *(int *)(unaff_EDI + 0x24) + 1;
  *(int *)(unaff_EDI + 0x24) = iVar2;
  uVar1 = *(uint *)(*(int *)(unaff_EDI + 0x18) + 0x74);
  if (((((uVar1 & 4) != 0) || ((*(byte *)(unaff_EDI + 0x20) & 2) != 0)) || ((uVar1 & 2) == 0)) ||
     (((_DAT_00474e30 & 0x100) == 0 || (uVar3 = 6, iVar2 % 0xc == 0)))) {
    uVar3 = 1;
  }
  return uVar3;
}

