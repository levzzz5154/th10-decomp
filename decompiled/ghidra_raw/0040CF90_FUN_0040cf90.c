/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x0040CF90
 * Tracking name: FUN_0040cf90
 * Ghidra name: FUN_0040cf90
 * Tracked span: 32 bytes
 */


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

