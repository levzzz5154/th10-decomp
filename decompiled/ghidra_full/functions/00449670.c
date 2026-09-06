/* Raw Ghidra reference; not compilable reconstruction. Address: 00449670 */

void FUN_00449670(int param_1)

{
  undefined4 *in_EAX;
  int iVar1;
  
  iVar1 = FUN_004491c0(*in_EAX,(int)g_pGameStateManager,*in_EAX);
  if (iVar1 != 0) {
    FUN_0043e5a0(*(int *)(iVar1 + 0x308),param_1);
  }
  return;
}

