/* Raw Ghidra reference; not compilable reconstruction. Address: 004506D0 */

undefined4 PopEclScratchValue(void)

{
  undefined4 uVar1;
  int in_EAX;
  int iVar2;
  
  iVar2 = *(int *)(in_EAX + 0x1000) + -4;
  uVar1 = *(undefined4 *)(&DAT_00001004 + in_EAX);
  if (-1 < iVar2) {
    *(int *)(in_EAX + 0x1000) = iVar2;
    *(undefined4 *)(&DAT_00001004 + in_EAX) = *(undefined4 *)(iVar2 + in_EAX);
  }
  *(undefined4 *)(in_EAX + 0x1000) = uVar1;
  return 0;
}

