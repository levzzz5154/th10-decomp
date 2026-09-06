/* Raw Ghidra reference; not compilable reconstruction. Address: 00449090 */

void FUN_00449090(undefined4 param_1,int param_2,undefined4 param_3)

{
  undefined4 *puVar1;
  undefined4 extraout_ECX;
  
  puVar1 = FUN_00449950();
  puVar1[8] = param_3;
  puVar1[0xd7] = puVar1[0xd7] | 0x40000000;
  FUN_00449870(puVar1,param_2);
  FUN_00448b40(extraout_ECX,(int)g_pGameStateManager);
  return;
}

