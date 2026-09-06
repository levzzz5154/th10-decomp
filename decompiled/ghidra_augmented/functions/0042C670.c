/* Raw Ghidra reference; not compilable reconstruction. Address: 0042C670 */

void FUN_0042c670(int param_1)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  undefined4 extraout_ECX;
  int unaff_EDI;
  
  uVar1 = *(undefined4 *)(param_1 + 0x14);
  puVar2 = FUN_00449950();
  puVar2[8] = 0xf;
  puVar2[0xd7] = puVar2[0xd7] | 0x40000000;
  FUN_00449870(puVar2,unaff_EDI);
  FUN_004489d0(extraout_ECX,(int)g_pGameStateManager);
  *(undefined4 *)(param_1 + 0x2c4 + unaff_EDI * 4) = uVar1;
  return;
}

