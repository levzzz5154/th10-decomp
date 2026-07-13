/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x00423370
 * Tracking name: FUN_00423370
 * Ghidra name: FUN_00423370
 * Tracked span: 416 bytes
 */


void __fastcall FUN_00423370(int param_1)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 extraout_ECX;
  void *this;
  undefined4 extraout_ECX_00;
  undefined4 extraout_ECX_01;
  undefined4 extraout_ECX_02;
  undefined4 uVar3;
  int unaff_EDI;
  
  iVar1 = DAT_00477810;
  if (*(int *)(DAT_00477810 + 0x5c) == 1) {
    DAT_00491fb8 = (-(uint)((DAT_00491ff4 & 0x1000) != 0) & 0xfffffffe) + 4;
    return;
  }
  *(undefined4 *)(unaff_EDI + 4) = 6;
  if ((*(uint *)(unaff_EDI + 0x20) & 1) == 0) {
    *(undefined4 *)(unaff_EDI + 0x14) = 0;
    *(undefined4 *)(unaff_EDI + 0x10) = 0xfff0bdc1;
    *(undefined4 *)(unaff_EDI + 0x18) = 0;
    *(undefined4 **)(unaff_EDI + 0x1c) = &DAT_00476f78;
    *(uint *)(unaff_EDI + 0x20) = *(uint *)(unaff_EDI + 0x20) | 1;
  }
  *(undefined4 *)(unaff_EDI + 0x14) = 0;
  *(undefined4 *)(unaff_EDI + 0x18) = 0;
  *(undefined4 *)(unaff_EDI + 0x10) = 0xffffffff;
  *(uint *)(iVar1 + 0x58) = *(uint *)(iVar1 + 0x58) | 0x10;
  puVar2 = FUN_00449950();
  puVar2[0xd7] = puVar2[0xd7] | 0x40000000;
  puVar2[8] = 0xf;
  FUN_00449870(puVar2,0);
  FUN_00448ac0(extraout_ECX,(int)g_pGameStateManager);
  *(int *)(unaff_EDI + 0x1d8) = param_1;
  FUN_00424480(this,param_1,0x20,0x10,0x180,0x1c0);
  *(undefined4 *)(unaff_EDI + 0x2c4) = *(undefined4 *)(DAT_0047770c + 0x9ec8);
  puVar2 = FUN_00449950();
  puVar2[0xd7] = puVar2[0xd7] | 0x40000000;
  puVar2[8] = 0xf;
  FUN_00449870(puVar2,0x81);
  FUN_00448ac0(extraout_ECX_00,(int)g_pGameStateManager);
  *(int *)(unaff_EDI + 0x1d4) = param_1;
  FUN_00420a90(0,"bgm/th10_17.wav");
  uVar3 = extraout_ECX_01;
  if (((byte)DAT_00491d78 & 0x10) != 0) {
    FUN_0043e460(extraout_ECX_01,"dummy",4,0);
    uVar3 = extraout_ECX_02;
  }
  FUN_0043e460(uVar3,"dummy",2,0);
  *(undefined1 *)(DAT_0047783c + 0x1d8a3) = 1;
  *(undefined4 *)(unaff_EDI + 0x1e4) = 1;
  *(undefined4 *)(unaff_EDI + 0x2c0) = DAT_00476f78;
  DAT_00476f78 = 0x3f800000;
  return;
}

