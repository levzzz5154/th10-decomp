/* Raw Ghidra reference; not compilable reconstruction. Address: 0044D5B0 */

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

