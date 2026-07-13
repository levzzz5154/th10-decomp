/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x00444760
 * Tracking name: FUN_00444760
 * Ghidra name: FUN_00444760
 * Tracked span: 944 bytes
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_00444760(int param_1)

{
  float *pfVar1;
  float fVar2;
  int in_EAX;
  uint uVar3;
  int iVar4;
  int iVar5;
  float *pfVar6;
  undefined4 *puVar7;
  float *pfVar8;
  undefined4 *puVar9;
  undefined4 local_c0 [12];
  float fStack_90;
  float fStack_8c;
  float afStack_88 [2];
  undefined1 local_80 [52];
  undefined4 auStack_4c [8];
  float fStack_2c;
  float fStack_28;
  
  if (((*(uint *)(in_EAX + 0x35c) & 1) == 0) || ((*(uint *)(in_EAX + 0x35c) & 2) == 0)) {
    return 0xffffffff;
  }
  if (*(char *)(in_EAX + 0x2ff) == '\0') {
    return 0xffffffff;
  }
  if (*(int *)(param_1 + 0x3adac8) != 0) {
    FUN_00442f50();
  }
  uVar3 = *(uint *)(in_EAX + 0x35c);
  if (((uVar3 & 0x4000) == 0) && ((uVar3 & 0xc) != 0)) {
    fVar2 = *(float *)(in_EAX + 0x3c);
    pfVar1 = (float *)(in_EAX + 0x27c);
    pfVar6 = (float *)(in_EAX + 0x23c);
    pfVar8 = pfVar1;
    for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
      *pfVar8 = *pfVar6;
      pfVar6 = pfVar6 + 1;
      pfVar8 = pfVar8 + 1;
    }
    *pfVar1 = fVar2 * *pfVar1;
    *(float *)(in_EAX + 0x290) = *(float *)(in_EAX + 0x40) * *(float *)(in_EAX + 0x290);
    fVar2 = (float)_DAT_00470b70;
    *(uint *)(in_EAX + 0x35c) = uVar3 & 0xfffffff7;
    if (fVar2 != *(float *)(in_EAX + 0x24)) {
      D3DXMatrixRotationX(local_80,*(undefined4 *)(in_EAX + 0x24));
      D3DXMatrixMultiply(pfVar1,pfVar1,afStack_88);
    }
    if ((float)_DAT_00470b70 != *(float *)(in_EAX + 0x28)) {
      D3DXMatrixRotationY(local_80,*(undefined4 *)(in_EAX + 0x28));
      D3DXMatrixMultiply(pfVar1,pfVar1,afStack_88);
    }
    if ((float)_DAT_00470b70 != *(float *)(in_EAX + 0x2c)) {
      D3DXMatrixRotationZ(local_80,*(undefined4 *)(in_EAX + 0x2c));
      D3DXMatrixMultiply(pfVar1,pfVar1,afStack_88);
    }
    *(uint *)(in_EAX + 0x35c) = *(uint *)(in_EAX + 0x35c) & 0xfffffffb;
  }
  puVar7 = (undefined4 *)(in_EAX + 0x27c);
  puVar9 = local_c0;
  for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
    *puVar9 = *puVar7;
    puVar7 = puVar7 + 1;
    puVar9 = puVar9 + 1;
  }
  uVar3 = *(uint *)(in_EAX + 0x35c) >> 0x12 & 3;
  if (uVar3 == 0) {
    fVar2 = *(float *)(in_EAX + 0x34c);
LAB_0044490d:
    fStack_90 = fVar2 + *(float *)(in_EAX + 0x340) + *(float *)(in_EAX + 0x334);
  }
  else if (uVar3 == 1) {
    fStack_90 = (*(float *)(in_EAX + 0x34c) + *(float *)(in_EAX + 0x340) +
                *(float *)(in_EAX + 0x334)) -
                ABS(*(float *)(in_EAX + 0x4c) * *(float *)(in_EAX + 0x3c) * _DAT_00470b0c);
  }
  else if (uVar3 == 2) {
    fVar2 = ABS(*(float *)(in_EAX + 0x4c) * *(float *)(in_EAX + 0x3c) * _DAT_00470b0c) +
            *(float *)(in_EAX + 0x34c);
    goto LAB_0044490d;
  }
  uVar3 = *(uint *)(in_EAX + 0x35c) >> 0x14 & 3;
  if (uVar3 == 0) {
    fVar2 = *(float *)(in_EAX + 0x350);
  }
  else {
    if (uVar3 == 1) {
      fStack_8c = (*(float *)(in_EAX + 0x350) + *(float *)(in_EAX + 0x344) +
                  *(float *)(in_EAX + 0x338)) -
                  ABS(*(float *)(in_EAX + 0x50) * *(float *)(in_EAX + 0x40) * _DAT_00470b0c);
      goto LAB_00444982;
    }
    if (uVar3 != 2) goto LAB_00444982;
    fVar2 = ABS(*(float *)(in_EAX + 0x50) * *(float *)(in_EAX + 0x40) * _DAT_00470b0c) +
            *(float *)(in_EAX + 0x350);
  }
  fStack_8c = fVar2 + *(float *)(in_EAX + 0x344) + *(float *)(in_EAX + 0x338);
LAB_00444982:
  afStack_88[0] = *(float *)(in_EAX + 0x33c) + *(float *)(in_EAX + 0x348);
  FUN_004423e0();
  afStack_88[0] =
       *(float *)(in_EAX + 0x354) + *(float *)(in_EAX + 0x33c) + *(float *)(in_EAX + 0x348);
  (**(code **)(*(int *)g_pD3DDevice + 0xb0))(g_pD3DDevice,0x100,local_c0);
  iVar4 = *(int *)(*(int *)(in_EAX + 0x394) + 4);
  if (*(int *)(param_1 + 0x3ada64) != iVar4) {
    *(int *)(param_1 + 0x3ada64) = iVar4;
    (**(code **)(*(int *)g_pD3DDevice + 0x104))(g_pD3DDevice,0,iVar4);
  }
  if (((*(int *)(param_1 + 0x3ada70) != *(int *)(in_EAX + 0x394)) ||
      (*(float *)(in_EAX + 0x54) != _DAT_00470b04)) || (*(float *)(in_EAX + 0x54) != _DAT_00470b04))
  {
    *(int *)(param_1 + 0x3ada70) = *(int *)(in_EAX + 0x394);
    iVar4 = *(int *)(in_EAX + 0x394);
    puVar7 = (undefined4 *)(in_EAX + 700);
    puVar9 = auStack_4c;
    for (iVar5 = 0x10; iVar5 != 0; iVar5 = iVar5 + -1) {
      *puVar9 = *puVar7;
      puVar7 = puVar7 + 1;
      puVar9 = puVar9 + 1;
    }
    fStack_2c = *(float *)(iVar4 + 0x20) + *(float *)(in_EAX + 0x54);
    fStack_28 = *(float *)(iVar4 + 0x24) + *(float *)(in_EAX + 0x58);
    (**(code **)(*(int *)g_pD3DDevice + 0xb0))(g_pD3DDevice,0x10,auStack_4c);
  }
  if (*(char *)(param_1 + 0x3ada6a) != '\x02') {
    (**(code **)(*(int *)g_pD3DDevice + 400))
              (g_pD3DDevice,0,*(undefined4 *)(param_1 + 0x3ada74),0,0x14);
    (**(code **)(*(int *)g_pD3DDevice + 0x164))(g_pD3DDevice,0x102);
    (**(code **)(*(int *)g_pD3DDevice + 0x10c))(g_pD3DDevice,0,6,3);
    (**(code **)(*(int *)g_pD3DDevice + 0x10c))(g_pD3DDevice,0,3,3);
    *(undefined1 *)(param_1 + 0x3ada6a) = 2;
  }
  (**(code **)(*(int *)g_pD3DDevice + 0x144))(g_pD3DDevice,5,0,2);
  return 0;
}

