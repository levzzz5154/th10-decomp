/* Raw Ghidra reference; not compilable reconstruction. Address: 00443B60 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_00443b60(void)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float10 fVar5;
  undefined1 *puVar6;
  undefined1 *puVar7;
  undefined1 *puVar8;
  undefined1 *puVar9;
  int in_EAX;
  uint uVar10;
  undefined1 *unaff_ESI;
  float10 fVar11;
  undefined4 *puStack_c0;
  undefined4 *puStack_b8;
  undefined1 *puStack_b4;
  float fStack_b0;
  float fStack_ac;
  float fStack_98;
  undefined4 local_90;
  float local_8c;
  undefined4 local_88;
  float fStack_80;
  float fStack_7c;
  float fStack_78;
  float fStack_74;
  undefined1 local_70 [12];
  undefined1 auStack_64 [8];
  float local_5c;
  undefined4 auStack_58 [6];
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  float local_10;
  float local_c;
  float local_8;
  undefined4 local_4;
  
  local_5c = *(float *)(in_EAX + 0x2c);
  fVar5 = (float10)fcos((float10)local_5c);
  fVar11 = (float10)fsin((float10)local_5c);
  fVar1 = (float)fVar5;
  fVar2 = (float)fVar11;
  local_10 = *(float *)(in_EAX + 0x34c) + *(float *)(in_EAX + 0x340) + *(float *)(in_EAX + 0x334);
  puStack_b4 = (undefined1 *)(DAT_00491fac + 0xcc);
  puStack_b8 = &local_90;
  local_c = *(float *)(in_EAX + 0x350) + *(float *)(in_EAX + 0x344) + *(float *)(in_EAX + 0x338);
  puVar9 = local_70;
  local_90 = 0;
  local_8c = 0.0;
  local_88 = 0;
  local_14 = 0;
  local_1c = 0;
  local_20 = 0;
  local_8 = *(float *)(in_EAX + 0x354) + *(float *)(in_EAX + 0x348) + *(float *)(in_EAX + 0x33c);
  local_24 = 0;
  local_28 = 0;
  local_30 = 0;
  local_34 = 0;
  local_38 = 0;
  local_3c = 0;
  local_4 = 0x3f800000;
  local_18 = 0x3f800000;
  local_2c = 0x3f800000;
  local_40 = 0x3f800000;
  D3DXVec3Project();
  if (((float)_DAT_00470b04 <= fStack_80) && (fStack_80 <= _DAT_00470afc)) {
    puStack_c0 = auStack_58;
    D3DXVec3Project(auStack_64,DAT_00491fac + 0x30,DAT_00491fac + 0xcc,DAT_00491fac + 0x8c,
                    DAT_00491fac + 0x4c);
    fStack_b0 = fStack_7c - fVar1;
    fStack_ac = fStack_78 - fVar2;
    puVar6 = (undefined1 *)(fStack_74 - fStack_98);
    fVar3 = SQRT(fStack_b0 * fStack_b0 + fStack_ac * fStack_ac + (float)puVar6 * (float)puVar6) *
            _DAT_00470b0c;
    puVar7 = (undefined1 *)(*(float *)(in_EAX + 0x4c) * *(float *)(in_EAX + 0x3c) * fVar3);
    _DAT_0049791c = fStack_98;
    _DAT_00497900 = fStack_98;
    _DAT_004978e4 = fStack_98;
    puVar8 = (undefined1 *)(*(float *)(in_EAX + 0x50) * *(float *)(in_EAX + 0x40) * fVar3);
    _DAT_004978c8 = fStack_98;
    fVar5 = (float10)fcos((float10)local_8c);
    fVar11 = (float10)fsin((float10)local_8c);
    fVar3 = (float)fVar5;
    fVar4 = (float)fVar11;
    uVar10 = *(uint *)(in_EAX + 0x35c) >> 0x12 & 3;
    if (uVar10 == 0) {
      puStack_c0 = (undefined4 *)((float)puVar7 * _DAT_00470b78);
      puStack_b4 = (undefined1 *)((float)puVar7 * _DAT_00470b0c);
      puStack_b8 = puStack_c0;
      puVar9 = puStack_b4;
    }
    else if (uVar10 == 1) {
      puStack_b8 = (undefined4 *)0x0;
      puStack_c0 = (undefined4 *)0x0;
      puStack_b4 = puVar7;
      puVar9 = puVar7;
    }
    else if (uVar10 == 2) {
      puStack_b4 = (undefined1 *)0x0;
      puStack_c0 = (undefined4 *)-(float)puVar7;
      puStack_b8 = puStack_c0;
      puVar9 = _DAT_00470b04;
    }
    uVar10 = *(uint *)(in_EAX + 0x35c) >> 0x14 & 3;
    if (uVar10 == 0) {
      fStack_b0 = (float)puVar8 * _DAT_00470b78;
      unaff_ESI = (undefined1 *)((float)puVar8 * _DAT_00470b0c);
      fStack_ac = fStack_b0;
      puVar6 = unaff_ESI;
    }
    else if (uVar10 == 1) {
      fStack_ac = 0.0;
      fStack_b0 = 0.0;
      unaff_ESI = puVar8;
      puVar6 = puVar8;
    }
    else if (uVar10 == 2) {
      fStack_b0 = -(float)puVar8;
      fStack_ac = fStack_b0;
      unaff_ESI = (undefined1 *)0x0;
      puVar6 = _DAT_00470b04;
    }
    DAT_004978c0 = ((float)puStack_c0 * fVar3 - fStack_b0 * fVar4) + fVar1;
    DAT_004978c4 = (float)puStack_c0 * fVar4 + fStack_b0 * fVar3 + fVar2;
    DAT_004978dc = ((float)puVar9 * fVar3 - fStack_ac * fVar4) + fVar1;
    DAT_004978e0 = fStack_ac * fVar3 + (float)puVar9 * fVar4 + fVar2;
    DAT_004978f8 = ((float)puStack_b8 * fVar3 - (float)puVar6 * fVar4) + fVar1;
    DAT_004978fc = (float)puStack_b8 * fVar4 + fVar3 * (float)puVar6 + fVar2;
    DAT_00497914 = ((float)puStack_b4 * fVar3 - (float)unaff_ESI * fVar4) + fVar1;
    DAT_00497918 = (float)puStack_b4 * fVar4 + (float)unaff_ESI * fVar3 + fVar2;
    return 0;
  }
  return 0xffffffff;
}

