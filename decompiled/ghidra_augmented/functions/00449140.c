/* Raw Ghidra reference; not compilable reconstruction. Address: 00449140 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00449140(undefined2 *param_1)

{
  undefined4 *puVar1;
  undefined4 extraout_ECX;
  float *unaff_EDI;
  
  puVar1 = FUN_00449950();
  puVar1[8] = 0;
  puVar1[0xd7] = puVar1[0xd7] | 0x40000000;
  puVar1[0xd0] = *unaff_EDI + _DAT_00470b4c;
  puVar1[0xd1] = unaff_EDI[1] + _DAT_00470b48;
  puVar1[0xd2] = unaff_EDI[2];
  FUN_0043e710(param_1);
  FUN_00448b40(extraout_ECX,(int)g_pGameStateManager);
  return;
}

