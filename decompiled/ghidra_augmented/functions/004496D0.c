/* Raw Ghidra reference; not compilable reconstruction. Address: 004496D0 */

void FUN_004496d0(int param_1)

{
  undefined4 *in_EAX;
  int iVar1;
  
  iVar1 = FUN_004491c0(*in_EAX,(int)g_pGameStateManager,*in_EAX);
  if (iVar1 != 0) {
    FUN_0043e8b0(param_1,*(undefined2 **)(iVar1 + 0x308));
  }
  return;
}

