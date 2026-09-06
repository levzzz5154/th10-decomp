/* Raw Ghidra reference; not compilable reconstruction. Address: 00421F60 */

void FUN_00421f60(void)

{
  int iVar1;
  int in_EAX;
  
  iVar1 = DAT_00474c44;
  *(int *)(in_EAX + 0x9e78) = DAT_00474c44;
  if (DAT_00474c40 < iVar1) {
    DAT_00474c40 = iVar1;
  }
  return;
}

