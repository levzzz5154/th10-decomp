/* Raw Ghidra reference; not compilable reconstruction. Address: 00421180 */

void FUN_00421180(int param_1)

{
  undefined4 *puVar1;
  undefined4 extraout_ECX;
  undefined4 extraout_ECX_00;
  undefined4 extraout_ECX_01;
  undefined4 extraout_ECX_02;
  undefined4 extraout_ECX_03;
  int *piVar2;
  
  piVar2 = g_pGameStateManager;
  if (*(int *)(param_1 + 0x6fc) == 0) {
    puVar1 = FUN_00449950();
    puVar1[8] = 0xf;
    puVar1[0xd7] = puVar1[0xd7] | 0x40000000;
    FUN_00449870(puVar1,0);
    FUN_004489d0(extraout_ECX,(int)g_pGameStateManager);
    DAT_00477824 = param_1;
    puVar1 = FUN_00449950();
    puVar1[0xd7] = puVar1[0xd7] | 0x40000000;
    puVar1[8] = 0xf;
    FUN_00449870(puVar1,1);
    FUN_004489d0(extraout_ECX_00,(int)g_pGameStateManager);
    DAT_00477828 = param_1;
    puVar1 = FUN_00449950();
    puVar1[8] = 0xf;
    puVar1[0xd7] = puVar1[0xd7] | 0x40000000;
    FUN_00449870(puVar1,2);
    piVar2 = g_pGameStateManager;
    FUN_004489d0(extraout_ECX_01,(int)g_pGameStateManager);
    DAT_0047782c = param_1;
    *(undefined4 *)(param_1 + 0x6fc) = 1;
    FUN_004492f0(extraout_ECX_02,(int)piVar2,DAT_00477824);
    FUN_004492f0(DAT_00477828,(int)piVar2,DAT_00477828);
    FUN_004492f0(extraout_ECX_03,(int)piVar2,DAT_0047782c);
  }
  if (*piVar2 < 0) {
    *piVar2 = 8;
    piVar2[0xb] = 0;
    piVar2[0xc] = 0;
    piVar2[0xd] = 0x280;
    piVar2[0xe] = 0x1e0;
    piVar2[0xf] = 0;
    piVar2[0x10] = 0;
    piVar2[0x11] = 0x280;
    piVar2[0x12] = 0x1e0;
  }
  return;
}

