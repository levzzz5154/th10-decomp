/* Raw Ghidra reference; not compilable reconstruction. Address: 00448FB0 */

void FUN_00448fb0(undefined2 *param_1)

{
  undefined4 *puVar1;
  undefined4 extraout_ECX;
  undefined4 *unaff_EDI;
  
  puVar1 = FUN_00449950();
  puVar1[0xd7] = puVar1[0xd7] | 0x40000000;
  puVar1[8] = 0;
  puVar1[0xd0] = *unaff_EDI;
  puVar1[0xd1] = unaff_EDI[1];
  puVar1[0xd2] = unaff_EDI[2];
  FUN_0043e710(param_1);
  FUN_00448ac0(extraout_ECX,(int)g_pGameStateManager);
  return;
}

