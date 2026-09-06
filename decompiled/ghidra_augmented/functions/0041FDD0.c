/* Raw Ghidra reference; not compilable reconstruction. Address: 0041FDD0 */

undefined4 FUN_0041fdd0(int param_1)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  undefined4 extraout_ECX;
  
  if (*(int *)(param_1 + 0x3e4) == 1) {
    puVar1 = FUN_00449950();
    puVar1[8] = 0xf;
    puVar1[0xd7] = puVar1[0xd7] | 0x40000000;
    FUN_00449870(puVar1,0);
    FUN_004489d0(extraout_ECX,(int)g_pGameStateManager);
    *(int *)(param_1 + 0x3dc) = param_1;
    *(int *)(param_1 + 0x3e4) = *(int *)(param_1 + 0x3e4) + 1;
  }
  if (*(int *)(param_1 + 1000) == 1) {
    puVar1 = (undefined4 *)((int)g_pGameThread + 0x89a4);
    if (*(int *)((int)g_pGameThread + 0x89a4) == 0) {
      puVar2 = (undefined4 *)FUN_00448d50(*(undefined2 **)((int)g_pGameThread + 0x8994));
      *puVar1 = *puVar2;
    }
    *(int *)(param_1 + 1000) = *(int *)(param_1 + 1000) + 1;
  }
  *(int *)(param_1 + 0x3ec) = *(int *)(param_1 + 0x3ec) + 1;
  return 1;
}

