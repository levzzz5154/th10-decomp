/* Raw Ghidra reference; not compilable reconstruction. Address: 0043C230 */

undefined8 __fastcall FUN_0043c230(int param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 extraout_EDX;
  ulonglong uVar2;
  
  if (DAT_004918a4 == 0) {
    iVar1 = *(int *)(param_1 + 0x1c);
    if (iVar1 != 0) {
      if (*(int *)(param_1 + 0x34) < iVar1) {
        uVar2 = FUN_00463b2c();
        param_2 = (undefined4)(uVar2 >> 0x20);
        *(int *)(param_1 + 0x18) = (int)uVar2;
      }
      else {
        *(undefined4 *)(param_1 + 0x18) = 0xff;
      }
      if (*(int *)(param_1 + 0x18) < 0) {
        *(undefined4 *)(param_1 + 0x18) = 0;
      }
    }
    if (*(int *)(param_1 + 0x34) < iVar1 + 2) {
      if ((DAT_00477810 == 0) ||
         (((*(uint *)(DAT_00477810 + 0x58) >> 2 | *(uint *)(DAT_00477810 + 0x58)) & 1) == 0)) {
        FUN_00404ed0();
        param_2 = extraout_EDX;
      }
      return CONCAT44(param_2,1);
    }
  }
  return CONCAT44(param_2,7);
}

