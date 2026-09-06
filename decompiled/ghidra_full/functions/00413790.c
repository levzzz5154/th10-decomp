/* Raw Ghidra reference; not compilable reconstruction. Address: 00413790 */

void __fastcall SetAnimationActiveCount(int param_1)

{
  int in_EAX;
  uint *puVar1;
  int iVar2;
  
  iVar2 = 0;
  if (0 < param_1) {
    puVar1 = (uint *)(in_EAX + 0x4cdc);
    iVar2 = param_1;
    do {
      *puVar1 = *puVar1 | 2;
      puVar1 = puVar1 + 0xeb;
      iVar2 = iVar2 + -1;
    } while (iVar2 != 0);
    iVar2 = param_1;
    if (8 < param_1) {
      return;
    }
  }
  puVar1 = (uint *)(iVar2 * 0x3ac + 0x4cdc + in_EAX);
  iVar2 = 9 - iVar2;
  do {
    *puVar1 = *puVar1 & 0xfffffffd;
    puVar1 = puVar1 + 0xeb;
    iVar2 = iVar2 + -1;
  } while (iVar2 != 0);
  return;
}

