/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x00448D00
 * Tracking name: FUN_00448d00
 * Ghidra name: FUN_00448d00
 * Tracked span: 80 bytes
 */


void FUN_00448d00(undefined4 param_1,int param_2,undefined4 param_3)

{
  undefined4 *puVar1;
  undefined4 extraout_ECX;
  
  puVar1 = FUN_00449950();
  puVar1[8] = param_3;
  puVar1[0xd7] = puVar1[0xd7] | 0x40000000;
  FUN_00449870(puVar1,param_2);
  FUN_004489d0(extraout_ECX,(int)g_pGameStateManager);
  return;
}

