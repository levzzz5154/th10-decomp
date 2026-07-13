/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x0043D790
 * Tracking name: FUN_0043d790
 * Ghidra name: FUN_0043d790
 * Tracked span: 64 bytes
 */


undefined4 __fastcall FUN_0043d790(void *param_1)

{
  int in_EAX;
  int iVar1;
  
  if (*(int *)(in_EAX + 21000) == 0) {
    return 0xffffffff;
  }
  iVar1 = FUN_0043d2a0(param_1,in_EAX);
  FUN_0044dca0(iVar1 * 0x34 + *(int *)(in_EAX + 0x1f84));
  return 0;
}

