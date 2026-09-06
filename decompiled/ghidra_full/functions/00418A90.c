/* Raw Ghidra reference; not compilable reconstruction. Address: 00418A90 */

void FUN_00418a90(void)

{
  int in_EAX;
  int iVar1;
  
  iVar1 = *(int *)(in_EAX + 0x50) + 1;
  *(int *)(in_EAX + 0x50) = iVar1;
  if (9 < iVar1) {
    *(undefined4 *)(in_EAX + 0x50) = 9;
  }
  return;
}

