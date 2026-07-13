/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x00444240
 * Tracking name: FUN_00444240
 * Ghidra name: FUN_00444240
 * Tracked span: 832 bytes
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_00444240(void)

{
  float *pfVar1;
  float fVar2;
  float fVar3;
  int in_EAX;
  uint uVar4;
  int iVar5;
  float *pfVar6;
  undefined4 *puVar7;
  int *piVar8;
  float *pfVar9;
  undefined4 *puVar10;
  int *piVar11;
  int aiStack_e0 [2];
  undefined4 *puStack_d8;
  float *pfStack_d4;
  float *pfStack_d0;
  float *pfStack_cc;
  undefined1 *puStack_c8;
  int iStack_c4;
  undefined4 uStack_b0;
  undefined4 uStack_ac;
  undefined4 uStack_a8;
  undefined4 uStack_a4;
  undefined4 uStack_a0;
  undefined4 uStack_9c;
  undefined4 uStack_98;
  undefined4 uStack_94;
  undefined4 uStack_90;
  undefined4 uStack_8c;
  undefined4 uStack_88;
  undefined4 uStack_84;
  undefined4 local_80 [9];
  int iStack_5c;
  float fStack_50;
  float fStack_4c;
  float afStack_48 [2];
  undefined1 local_40 [64];
  
  uVar4 = *(uint *)(in_EAX + 0x35c);
  if (((uVar4 & 0x4000) == 0) && ((uVar4 & 0xc) != 0)) {
    fVar2 = *(float *)(in_EAX + 0x3c);
    pfVar1 = (float *)(in_EAX + 0x27c);
    pfVar6 = (float *)(in_EAX + 0x23c);
    pfVar9 = pfVar1;
    for (iVar5 = 0x10; iVar5 != 0; iVar5 = iVar5 + -1) {
      *pfVar9 = *pfVar6;
      pfVar6 = pfVar6 + 1;
      pfVar9 = pfVar9 + 1;
    }
    *pfVar1 = fVar2 * *pfVar1;
    *(float *)(in_EAX + 0x290) = *(float *)(in_EAX + 0x40) * *(float *)(in_EAX + 0x290);
    fVar2 = (float)_DAT_00470b70;
    *(uint *)(in_EAX + 0x35c) = uVar4 & 0xfffffff7;
    if (fVar2 != *(float *)(in_EAX + 0x24)) {
      iStack_c4 = *(undefined4 *)(in_EAX + 0x24);
      puStack_c8 = local_40;
      pfStack_cc = (float *)0x4442bc;
      D3DXMatrixRotationX();
      pfStack_cc = afStack_48;
      puStack_d8 = (undefined4 *)0x4442cb;
      pfStack_d4 = pfVar1;
      pfStack_d0 = pfVar1;
      D3DXMatrixMultiply();
    }
    if ((float)_DAT_00470b70 != *(float *)(in_EAX + 0x28)) {
      iStack_c4 = *(undefined4 *)(in_EAX + 0x28);
      puStack_c8 = local_40;
      pfStack_cc = (float *)0x4442ee;
      D3DXMatrixRotationY();
      pfStack_cc = afStack_48;
      puStack_d8 = (undefined4 *)0x4442fd;
      pfStack_d4 = pfVar1;
      pfStack_d0 = pfVar1;
      D3DXMatrixMultiply();
    }
    if ((float)_DAT_00470b70 != *(float *)(in_EAX + 0x2c)) {
      iStack_c4 = *(undefined4 *)(in_EAX + 0x2c);
      puStack_c8 = local_40;
      pfStack_cc = (float *)0x444320;
      D3DXMatrixRotationZ();
      pfStack_cc = afStack_48;
      puStack_d8 = (undefined4 *)0x44432f;
      pfStack_d4 = pfVar1;
      pfStack_d0 = pfVar1;
      D3DXMatrixMultiply();
    }
    *(uint *)(in_EAX + 0x35c) = *(uint *)(in_EAX + 0x35c) & 0xfffffffb;
  }
  fVar2 = *(float *)(in_EAX + 0x34c);
  fVar3 = *(float *)(in_EAX + 0x340);
  puVar7 = (undefined4 *)(in_EAX + 0x27c);
  puVar10 = local_80;
  for (iVar5 = 0x10; iVar5 != 0; iVar5 = iVar5 + -1) {
    *puVar10 = *puVar7;
    puVar7 = puVar7 + 1;
    puVar10 = puVar10 + 1;
  }
  fStack_50 = fVar2 + fVar3 + *(float *)(in_EAX + 0x334) + fStack_50;
  fStack_4c = *(float *)(in_EAX + 0x350) + *(float *)(in_EAX + 0x344) + *(float *)(in_EAX + 0x338) +
              fStack_4c;
  afStack_48[0] =
       *(float *)(in_EAX + 0x354) + *(float *)(in_EAX + 0x348) + *(float *)(in_EAX + 0x33c);
  uVar4 = *(uint *)(in_EAX + 0x35c) >> 0x12 & 3;
  if (uVar4 == 0) {
    uStack_98 = 0xc3000000;
    uStack_b0 = 0xc3000000;
    uStack_8c = 0x43000000;
    uStack_a4 = 0x43000000;
  }
  else if (uVar4 == 1) {
    uStack_98 = 0;
    uStack_b0 = 0;
    uStack_8c = 0x43800000;
    uStack_a4 = 0x43800000;
  }
  else if (uVar4 == 2) {
    uStack_98 = 0xc3800000;
    uStack_b0 = 0xc3800000;
    uStack_8c = 0;
    uStack_a4 = 0;
  }
  uVar4 = *(uint *)(in_EAX + 0x35c) >> 0x14 & 3;
  if (uVar4 == 0) {
    uStack_a0 = 0xc3000000;
    uStack_ac = 0xc3000000;
    uStack_88 = 0x43000000;
    uStack_94 = 0x43000000;
  }
  else if (uVar4 == 1) {
    uStack_a0 = 0;
    uStack_ac = 0;
    uStack_88 = 0x43800000;
    uStack_94 = 0x43800000;
  }
  else if (uVar4 == 2) {
    uStack_a0 = 0xc3800000;
    uStack_ac = 0xc3800000;
    uStack_88 = 0;
    uStack_94 = 0;
  }
  iStack_c4 = DAT_00491fac + 0x4c;
  puStack_c8 = (undefined1 *)(DAT_00491fac + 0x8c);
  pfStack_cc = (float *)(DAT_00491fac + 0xcc);
  pfStack_d0 = (float *)&uStack_b0;
  pfStack_d4 = (float *)&DAT_004978c0;
  uStack_84 = 0;
  uStack_90 = 0;
  uStack_9c = 0;
  uStack_a8 = 0;
  puStack_d8 = (undefined4 *)0x4444ce;
  D3DXVec3Project();
  puStack_d8 = &uStack_98;
  aiStack_e0[1] = DAT_00491fac + 0x4c;
  aiStack_e0[0] = DAT_00491fac + 0x8c;
  D3DXVec3Project(&DAT_004978dc,&stack0xffffff44,DAT_00491fac + 0xcc);
  D3DXVec3Project(&DAT_004978f8,&puStack_c8,DAT_00491fac + 0xcc,DAT_00491fac + 0x8c,
                  DAT_00491fac + 0x4c,&uStack_b0);
  D3DXVec3Project(&DAT_00497914,&pfStack_d4,DAT_00491fac + 0xcc,DAT_00491fac + 0x8c,
                  DAT_00491fac + 0x4c,&puStack_c8);
  piVar8 = aiStack_e0;
  piVar11 = (int *)(iStack_5c + 0x3ad0f0);
  for (iVar5 = 0x10; iVar5 != 0; iVar5 = iVar5 + -1) {
    *piVar11 = *piVar8;
    piVar8 = piVar8 + 1;
    piVar11 = piVar11 + 1;
  }
  return 0;
}

