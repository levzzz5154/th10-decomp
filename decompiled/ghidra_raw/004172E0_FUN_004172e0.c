/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x004172E0
 * Tracking name: FUN_004172e0
 * Ghidra name: FUN_004172e0
 * Tracked span: 768 bytes
 */


void __thiscall FUN_004172e0(void *this,int param_1,int param_2)

{
  bool bVar1;
  undefined4 in_EAX;
  undefined4 *puVar2;
  int iVar3;
  undefined4 *puVar4;
  undefined4 extraout_ECX;
  void *pvVar5;
  int iVar6;
  int local_24;
  undefined4 local_1c;
  
  local_24 = param_2;
  iVar6 = param_1;
  switch(in_EAX) {
  case 0:
    FUN_004492a0(this,(int)g_pGameStateManager,*(int *)(param_1 + 0x9e14));
    *(undefined4 *)(param_1 + 0x9e14) = 0;
    puVar4 = (undefined4 *)FUN_00448d00(*(undefined4 *)(param_1 + 0x9ec8),0x47,0xf);
    pvVar5 = g_pGameStateManager;
    bVar1 = false;
    param_2 = 0;
    *(undefined4 *)(param_1 + 0x9e14) = *puVar4;
    param_1 = 10000000;
    puVar4 = (undefined4 *)(iVar6 + 0x9df4);
    do {
      FUN_004492a0(*puVar4,(int)pvVar5,*puVar4);
      *puVar4 = 0;
      puVar2 = FUN_00449950();
      puVar2[8] = 0xf;
      puVar2[0xd7] = puVar2[0xd7] | 0x40000000;
      FUN_00449870(puVar2,param_2 + 0x27);
      pvVar5 = g_pGameStateManager;
      FUN_004489d0(extraout_ECX,(int)g_pGameStateManager);
      iVar6 = local_24 / param_1;
      local_24 = local_24 % param_1;
      *puVar4 = local_1c;
      if (iVar6 != 0) {
        bVar1 = true;
      }
      iVar3 = FUN_004491c0(local_1c,(int)pvVar5,local_1c);
      if (iVar3 != 0) {
        FUN_0043e5a0(*(int *)(iVar3 + 0x308),iVar6 + 8);
      }
      if (bVar1) {
        FUN_00449590();
      }
      else {
        FUN_004495e0();
      }
      param_1 = param_1 / 10;
      param_2 = param_2 + 1;
      puVar4 = puVar4 + 1;
    } while (param_2 < 8);
    return;
  case 1:
    FUN_004492a0(*(undefined4 *)(param_1 + 0x9e14),(int)g_pGameStateManager,
                 *(undefined4 *)(param_1 + 0x9e14));
    iVar6 = 0x48;
    break;
  case 2:
    FUN_004492a0(*(undefined4 *)(param_1 + 0x9e18),(int)g_pGameStateManager,
                 *(undefined4 *)(param_1 + 0x9e18));
    *(undefined4 *)(param_1 + 0x9e18) = 0;
    puVar4 = (undefined4 *)FUN_00448d00(*(undefined4 *)(param_1 + 0x9ec8),0x49,0xf);
    *(undefined4 *)(param_1 + 0x9e18) = *puVar4;
    return;
  case 3:
    FUN_004492a0(*(undefined4 *)(param_1 + 0x9e18),(int)g_pGameStateManager,
                 *(undefined4 *)(param_1 + 0x9e18));
    *(undefined4 *)(param_1 + 0x9e18) = 0;
    puVar4 = (undefined4 *)FUN_00448d00(*(undefined4 *)(param_1 + 0x9ec8),0x4a,0xf);
    *(undefined4 *)(param_1 + 0x9e18) = *puVar4;
    return;
  case 4:
    FUN_004492a0(*(undefined4 *)(param_1 + 0x9e18),(int)g_pGameStateManager,
                 *(undefined4 *)(param_1 + 0x9e18));
    *(undefined4 *)(param_1 + 0x9e18) = 0;
    puVar4 = (undefined4 *)FUN_00448d00(*(undefined4 *)(param_1 + 0x9ec8),0x4b,0xf);
    *(undefined4 *)(param_1 + 0x9e18) = *puVar4;
    return;
  case 5:
    goto switchD_004172f2_caseD_5;
  case 6:
    FUN_004492a0(*(undefined4 *)(param_1 + 0x9e14),(int)g_pGameStateManager,
                 *(undefined4 *)(param_1 + 0x9e14));
    iVar6 = 0x4c;
    break;
  default:
    return;
  }
  *(undefined4 *)(param_1 + 0x9e14) = 0;
  puVar4 = (undefined4 *)FUN_00448d00(*(undefined4 *)(param_1 + 0x9ec8),iVar6,0xf);
  *(undefined4 *)(param_1 + 0x9e14) = *puVar4;
switchD_004172f2_caseD_5:
  return;
}

