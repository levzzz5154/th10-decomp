/* Raw Ghidra reference; not compilable reconstruction. Address: 00405040 */

void FUN_00405040(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                 undefined4 param_5,undefined4 param_6)

{
  undefined4 *unaff_ESI;
  ulonglong uVar1;
  
  *unaff_ESI = param_1;
  unaff_ESI[1] = param_2;
  unaff_ESI[2] = param_3;
  unaff_ESI[3] = param_4;
  unaff_ESI[4] = param_5;
  unaff_ESI[5] = param_6;
  uVar1 = FUN_00463b2c();
  *(char *)(unaff_ESI + 6) = (char)uVar1;
  uVar1 = FUN_00463b2c();
  *(char *)((int)unaff_ESI + 0x19) = (char)uVar1;
  uVar1 = FUN_00463b2c();
  *(char *)((int)unaff_ESI + 0x1a) = (char)uVar1;
  uVar1 = FUN_00463b2c();
  *(char *)((int)unaff_ESI + 0x1b) = (char)uVar1;
  return;
}

