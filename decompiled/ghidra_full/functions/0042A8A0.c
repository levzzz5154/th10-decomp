/* Raw Ghidra reference; not compilable reconstruction. Address: 0042A8A0 */

bool __fastcall
FUN_0042a8a0(undefined4 param_1,undefined2 param_2,undefined2 param_3,undefined2 param_4)

{
  int in_EAX;
  int iVar1;
  
  **(undefined2 **)(in_EAX + 0x5460) = param_2;
  *(undefined2 *)(*(int *)(in_EAX + 0x5460) + 2) = param_3;
  *(undefined2 *)(*(int *)(in_EAX + 0x5460) + 4) = param_4;
  iVar1 = *(int *)(in_EAX + 0x5460) + 6;
  *(int *)(in_EAX + 0x5460) = iVar1;
  return 0xe0f < (iVar1 - in_EAX) / 6;
}

