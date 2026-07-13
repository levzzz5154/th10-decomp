/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x00432690
 * Tracking name: FUN_00432690
 * Ghidra name: FUN_00432690
 * Tracked span: 864 bytes
 */


/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

undefined4 __fastcall FUN_00432690(int param_1)

{
  char cVar1;
  int iVar2;
  int iVar3;
  void *pvVar4;
  char *pcVar5;
  int *piVar6;
  int *piVar7;
  int iVar8;
  uint uVar9;
  uint uVar10;
  int iVar11;
  int *local_c0;
  int local_bc;
  int local_b8;
  int local_b4;
  int local_b0;
  char local_ac [168];
  uint local_4;
  
  local_4 = DAT_00473660 ^ (uint)&local_c0;
  iVar11 = 0;
  iVar8 = 0;
  local_bc = 0;
  if (0 < *(int *)(param_1 + 0x1d4) * 10 + -10) {
    do {
      if ((int)(char)(&DAT_004743c0)[iVar11] == *(int *)(param_1 + 0xfc)) {
        iVar8 = iVar8 + 1;
      }
      iVar11 = iVar11 + 1;
      local_bc = iVar11;
    } while (iVar8 < *(int *)(param_1 + 0x1d4) * 10 + -10);
  }
  local_c0 = (int *)(param_1 + 0x5d4);
  *(undefined4 *)(param_1 + 0x2ac) = 0;
  local_b8 = 0;
  local_b4 = param_1;
LAB_00432710:
  pvVar4 = g_pGameStateManager;
  if (local_bc < 0x6e) {
    while (iVar8 = local_bc, (int)(char)(&DAT_004743c0)[local_bc] != *(int *)(local_b4 + 0xfc)) {
      local_bc = local_bc + 1;
      if (0x6d < local_bc) goto LAB_00432735;
    }
    if (0x6d < local_bc) goto LAB_00432735;
    local_b0 = local_bc * 0x90;
    if (*(int *)(local_b0 + 0x19b10 + DAT_0047783c) == 0) {
      iVar11 = *local_c0;
      if (iVar11 != 0) {
        for (piVar6 = *(int **)((int)g_pGameStateManager + 0x72dad4); piVar6 != (int *)0x0;
            piVar6 = (int *)piVar6[1]) {
          if (*(int *)*piVar6 == iVar11) goto LAB_004328ef;
        }
        for (piVar6 = *(int **)((int)g_pGameStateManager + 0x72dadc); piVar6 != (int *)0x0;
            piVar6 = (int *)piVar6[1]) {
          if (*(int *)*piVar6 == iVar11) goto LAB_004328ef;
        }
      }
      goto LAB_004328f5;
    }
    pcVar5 = (char *)(local_b0 + 0x19a8c + DAT_0047783c);
    iVar11 = -(int)pcVar5;
    do {
      cVar1 = *pcVar5;
      pcVar5[(int)(local_ac + iVar11)] = cVar1;
      pcVar5 = pcVar5 + 1;
    } while (cVar1 != '\0');
    pcVar5 = local_ac;
    do {
      cVar1 = *pcVar5;
      pcVar5 = pcVar5 + 1;
    } while (cVar1 != '\0');
    iVar11 = (int)pcVar5 - (int)(local_ac + 1);
    if (iVar11 < 0x2a) {
      uVar10 = 0x2a - iVar11;
      uVar9 = uVar10 >> 2;
      pcVar5 = local_ac + iVar11;
      while (uVar9 != 0) {
        uVar9 = uVar9 - 1;
        builtin_strncpy(pcVar5,"    ",4);
        pcVar5 = pcVar5 + 4;
      }
      for (uVar9 = uVar10 & 3; uVar9 != 0; uVar9 = uVar9 - 1) {
        *pcVar5 = ' ';
        pcVar5 = pcVar5 + 1;
      }
      iVar11 = iVar11 + uVar10;
    }
    iVar2 = *(int *)(local_b4 + 0x24);
    local_ac[iVar11] = '\0';
    iVar3 = *local_c0;
    iVar11 = iVar2 * 0x437c + 0x624 + DAT_0047783c;
    if (iVar3 != 0) {
      for (piVar6 = *(int **)((int)g_pGameStateManager + 0x72dad4); piVar6 != (int *)0x0;
          piVar6 = (int *)piVar6[1]) {
        if (*(int *)*piVar6 == iVar3) goto LAB_00432848;
      }
      for (piVar6 = *(int **)((int)g_pGameStateManager + 0x72dadc); piVar6 != (int *)0x0;
          piVar6 = (int *)piVar6[1]) {
        if (*(int *)*piVar6 == iVar3) goto LAB_00432848;
      }
    }
    goto LAB_0043284e;
  }
LAB_00432735:
  if (9 < local_b8) {
    return 0;
  }
  piVar6 = (int *)(local_b4 + 0x5d4 + local_b8 * 4);
  iVar8 = 10 - local_b8;
  goto LAB_00432750;
LAB_004328ef:
  if (*piVar6 == 0) {
LAB_004328f5:
    *local_c0 = 0;
  }
  FUN_00447bb0(pvVar4,0x808080,&DAT_0046eebc);
  goto LAB_00432926;
LAB_00432848:
  if (*piVar6 == 0) {
LAB_0043284e:
    *local_c0 = 0;
  }
  FUN_00447bb0(pvVar4,(-(uint)(*(int *)(local_b0 + iVar11) != 0) & 0x100f91) + 0xefefef,
               "No.%3d %s %4d/%4d");
LAB_00432926:
  local_bc = iVar8 + 1;
  *(int *)(local_b4 + 0x2ac) = *(int *)(local_b4 + 0x2ac) + 1;
  local_b8 = local_b8 + 1;
  local_c0 = local_c0 + 1;
  if (9 < local_b8) {
    return 0;
  }
  goto LAB_00432710;
LAB_00432750:
  pvVar4 = g_pGameStateManager;
  iVar11 = *piVar6;
  if (iVar11 != 0) {
    for (piVar7 = *(int **)((int)g_pGameStateManager + 0x72dad4); piVar7 != (int *)0x0;
        piVar7 = (int *)piVar7[1]) {
      if (*(int *)*piVar7 == iVar11) goto LAB_0043299f;
    }
    for (piVar7 = *(int **)((int)g_pGameStateManager + 0x72dadc); piVar7 != (int *)0x0;
        piVar7 = (int *)piVar7[1]) {
      if (*(int *)*piVar7 == iVar11) goto LAB_0043299f;
    }
  }
  goto LAB_004329a5;
LAB_0043299f:
  if (*piVar7 == 0) {
LAB_004329a5:
    *piVar6 = 0;
  }
  FUN_00447bb0(pvVar4,0xffffffff," ");
  piVar6 = piVar6 + 1;
  iVar8 = iVar8 + -1;
  if (iVar8 == 0) {
    return 0;
  }
  goto LAB_00432750;
}

