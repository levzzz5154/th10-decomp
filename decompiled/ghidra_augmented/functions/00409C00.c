/* Raw Ghidra reference; not compilable reconstruction. Address: 00409C00 */

void __fastcall FUN_00409c00(undefined4 param_1)

{
  undefined4 *puVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  void *pvVar5;
  int in_EAX;
  undefined4 *puVar6;
  undefined4 extraout_ECX;
  undefined4 extraout_ECX_00;
  undefined4 extraout_ECX_01;
  undefined4 extraout_ECX_02;
  
  if ((*(byte *)(in_EAX + 0x378c) & 1) != 0) {
    *(uint *)(DAT_004776e8 + 0x2a18) = *(uint *)(DAT_004776e8 + 0x2a18) | 1;
    FUN_00409e50(param_1);
    FUN_00409e50(extraout_ECX);
    FUN_00409e50(extraout_ECX_00);
    pvVar5 = g_pGameStateManager;
    *(uint *)(in_EAX + 0x378c) = *(uint *)(in_EAX + 0x378c) & 0xfffffffe;
    FUN_004492a0(extraout_ECX_01,(int)pvVar5,*(int *)(in_EAX + 0x774));
    *(undefined4 *)(in_EAX + 0x774) = 0;
    iVar3 = DAT_0047770c;
    if ((*(byte *)(in_EAX + 0x378c) & 2) != 0) {
      pvVar5 = (void *)(*(int *)(in_EAX + 0x3790) / 10);
      DAT_00474c44 = DAT_00474c44 + (int)pvVar5;
      if (999999999 < DAT_00474c44) {
        DAT_00474c44 = 999999999;
      }
      FUN_004172e0(pvVar5,DAT_0047770c,*(int *)(in_EAX + 0x3790));
      iVar3 = DAT_0047783c;
      if (*(int *)(DAT_00477838 + 0x10) != 1) {
        iVar2 = *(int *)(in_EAX + 0x3788) * 0x90 + 0x5a4 +
                (DAT_00474c6c + DAT_00474c68 * 3) * 0x437c + DAT_0047783c;
        iVar4 = *(int *)(iVar2 + 0x80);
        if (iVar4 < 99999) {
          *(int *)(iVar2 + 0x80) = iVar4 + 1;
        }
        iVar3 = *(int *)(in_EAX + 0x3788) * 0x90 + 0x19a8c + iVar3;
        iVar2 = *(int *)(iVar3 + 0x80);
        if (iVar2 < 99999) {
          *(int *)(iVar3 + 0x80) = iVar2 + 1;
        }
      }
      FUN_0043dc90(&DAT_00492590,0);
      return;
    }
    puVar1 = (undefined4 *)(DAT_0047770c + 0x9e14);
    FUN_004492a0(extraout_ECX_02,(int)pvVar5,*(int *)(DAT_0047770c + 0x9e14));
    *puVar1 = 0;
    puVar6 = (undefined4 *)FUN_00448d00(*(undefined4 *)(iVar3 + 0x9ec8),0x48,0xf);
    *puVar1 = *puVar6;
  }
  return;
}

