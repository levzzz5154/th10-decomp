/* Raw Ghidra reference; not compilable reconstruction. Address: 0043BD40 */

undefined8 __fastcall FUN_0043bd40(int param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 extraout_EDX;
  ulonglong uVar2;
  
  if (DAT_004918a4 == 0) {
    iVar1 = *(int *)(param_1 + 0x1c);
    if (iVar1 != 0) {
      uVar2 = FUN_00463b2c();
      param_2 = (undefined4)(uVar2 >> 0x20);
      *(int *)(param_1 + 0x18) = (int)uVar2;
      if ((int)uVar2 < 0) {
        *(undefined4 *)(param_1 + 0x18) = 0;
      }
    }
    if (*(int *)(param_1 + 0x34) < iVar1) {
      FUN_00404ed0();
      return CONCAT44(extraout_EDX,1);
    }
  }
  return CONCAT44(param_2,7);
}

