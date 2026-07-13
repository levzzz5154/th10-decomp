/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x00422AB0
 * Tracking name: FUN_00422ab0
 * Ghidra name: FUN_00422ab0
 * Tracked span: 384 bytes
 */


void FUN_00422ab0(int param_1)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 extraout_ECX;
  void *this;
  undefined4 extraout_ECX_00;
  undefined4 extraout_ECX_01;
  undefined4 extraout_ECX_02;
  
  *(undefined4 *)(param_1 + 4) = 1;
  if ((*(uint *)(param_1 + 0x20) & 1) == 0) {
    *(undefined4 *)(param_1 + 0x14) = 0;
    *(undefined4 *)(param_1 + 0x10) = 0xfff0bdc1;
    *(undefined4 *)(param_1 + 0x18) = 0;
    *(undefined4 **)(param_1 + 0x1c) = &DAT_00476f78;
    *(uint *)(param_1 + 0x20) = *(uint *)(param_1 + 0x20) | 1;
  }
  iVar1 = DAT_00477810;
  *(undefined4 *)(param_1 + 0x14) = 0;
  *(undefined4 *)(param_1 + 0x18) = 0;
  *(undefined4 *)(param_1 + 0x10) = 0xffffffff;
  *(uint *)(iVar1 + 0x58) = *(uint *)(iVar1 + 0x58) | 0x10;
  puVar2 = FUN_00449950();
  puVar2[8] = 0xf;
  puVar2[0xd7] = puVar2[0xd7] | 0x40000000;
  FUN_00449870(puVar2,0);
  FUN_00448ac0(extraout_ECX,(int)g_pGameStateManager);
  *(int *)(param_1 + 0x1d8) = param_1;
  FUN_00424480(this,param_1,0x20,0x10,0x180,0x1c0);
  *(undefined4 *)(param_1 + 0x2c4) = *(undefined4 *)(DAT_0047770c + 0x9ec8);
  puVar2 = FUN_00449950();
  puVar2[8] = 0xf;
  puVar2[0xd7] = puVar2[0xd7] | 0x40000000;
  FUN_00449870(puVar2,0x79);
  FUN_00448ac0(extraout_ECX_00,(int)g_pGameStateManager);
  *(int *)(param_1 + 0x1d4) = param_1;
  FUN_0040c4d0(extraout_ECX_01);
  FUN_0043dc90(&DAT_00492590,0);
  FUN_0043e460(extraout_ECX_02,"Pause",6,0);
  if (*(int *)(DAT_00477810 + 0x5c) != 0) {
    puVar2 = (undefined4 *)FUN_004497d0(*(int *)(DAT_00477810 + 0x5c));
    FUN_004492a0(*puVar2,(int)g_pGameStateManager,*puVar2);
    *puVar2 = 0;
  }
  *(undefined4 *)(param_1 + 0x2c0) = DAT_00476f78;
  DAT_00476f78 = 0x3f800000;
  return;
}

