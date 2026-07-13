/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x0044D5B0
 * Tracking name: FUN_0044d5b0
 * Ghidra name: FUN_0044d5b0
 * Tracked span: 32 bytes
 */


undefined4 __fastcall FUN_0044d5b0(int param_1)

{
  int *piVar1;
  undefined4 uVar2;
  
  if (*(undefined4 **)(param_1 + 4) == (undefined4 *)0x0) {
    return 0x800401f0;
  }
  *(undefined4 *)(param_1 + 0x30) = 0;
  piVar1 = (int *)**(undefined4 **)(param_1 + 4);
  uVar2 = (**(code **)(*piVar1 + 0x48))(piVar1);
  return uVar2;
}

