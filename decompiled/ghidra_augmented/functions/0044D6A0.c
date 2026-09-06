/* Raw Ghidra reference; not compilable reconstruction. Address: 0044D6A0 */

void FUN_0044d6a0(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  undefined4 *puVar1;
  undefined4 *unaff_ESI;
  
  *unaff_ESI = &PTR_DestroyPlatformCollection_004705d8;
  puVar1 = operator_new(4);
  unaff_ESI[1] = puVar1;
  *puVar1 = param_1;
  unaff_ESI[3] = param_3;
  unaff_ESI[2] = param_2;
  unaff_ESI[4] = 1;
  FUN_0044d110(*(int **)unaff_ESI[1]);
  (**(code **)(**(int **)unaff_ESI[1] + 0x34))(*(int **)unaff_ESI[1],0);
  unaff_ESI[0xc] = 0;
  unaff_ESI[0x17] = 0;
  unaff_ESI[0x18] = 0;
  unaff_ESI[0x19] = 0;
  unaff_ESI[0x1a] = 0;
  *unaff_ESI = &PTR_DestroyPlatformVtable_004705d4;
  unaff_ESI[0x1b] = param_2;
  return;
}

