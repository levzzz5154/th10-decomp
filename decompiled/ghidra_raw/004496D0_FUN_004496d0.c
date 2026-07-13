/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x004496D0
 * Tracking name: FUN_004496d0
 * Ghidra name: FUN_004496d0
 * Tracked span: 256 bytes
 */


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

