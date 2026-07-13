/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x00448980
 * Tracking name: FUN_00448980
 * Ghidra name: FUN_00448980
 * Tracked span: 80 bytes
 */


undefined4 FUN_00448980(void)

{
  int iVar1;
  int in_EAX;
  void *unaff_EDI;
  
  for (iVar1 = *(int *)(in_EAX * 0x3ac + 0x72db00 + (int)unaff_EDI); iVar1 != 0;
      iVar1 = *(int *)(iVar1 + 0x1c)) {
    if ((*(uint *)(iVar1 + 0x35c) & 0x4000000) == 0) {
      if (*(code **)(iVar1 + 0x39c) != (code *)0x0) {
        (**(code **)(iVar1 + 0x39c))();
      }
      FUN_004451c0(unaff_EDI);
    }
  }
  return 1;
}

