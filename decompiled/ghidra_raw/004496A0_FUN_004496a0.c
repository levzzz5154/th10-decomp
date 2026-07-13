/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x004496A0
 * Tracking name: FUN_004496a0
 * Ghidra name: FUN_004496a0
 * Tracked span: 48 bytes
 */


void FUN_004496a0(int param_1,int param_2)

{
  undefined4 *in_EAX;
  int iVar1;
  
  iVar1 = FUN_004491c0(*in_EAX,(int)g_pGameStateManager,*in_EAX);
  if (iVar1 != 0) {
    FUN_0043e5a0(param_1,param_2);
  }
  return;
}

