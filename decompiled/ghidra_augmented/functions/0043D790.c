/* Raw Ghidra reference; not compilable reconstruction. Address: 0043D790 */

undefined4 __fastcall FUN_0043d790(void *param_1)

{
  int in_EAX;
  int iVar1;
  
  if (*(int *)(in_EAX + 21000) == 0) {
    return 0xffffffff;
  }
  iVar1 = FUN_0043d2a0(param_1,in_EAX);
  SelectStreamRecord(iVar1 * 0x34 + *(int *)(in_EAX + 0x1f84));
  return 0;
}

