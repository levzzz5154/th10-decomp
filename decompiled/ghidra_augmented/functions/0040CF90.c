/* Raw Ghidra reference; not compilable reconstruction. Address: 0040CF90 */

int __fastcall FUN_0040cf90(int param_1)

{
  int iVar1;
  int in_EAX;
  
  iVar1 = *(int *)(in_EAX + 0x18);
  while( true ) {
    if (iVar1 == 0) {
      return 0;
    }
    if (*(int *)(iVar1 + 0x54) == param_1) break;
    iVar1 = *(int *)(iVar1 + 8);
  }
  return iVar1;
}

