/* Raw Ghidra reference; not compilable reconstruction. Address: 004451C0 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 __fastcall FUN_004451c0(void *param_1)

{
  float fVar1;
  float fVar2;
  float10 fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  uint uVar8;
  int in_EAX;
  undefined4 uVar9;
  float unaff_ESI;
  float unaff_EDI;
  float10 fVar10;
  float local_20;
  float local_1c;
  float local_18;
  float local_14;
  float in_stack_fffffff0;
  float in_stack_fffffff4;
  
  uVar8 = *(uint *)(in_EAX + 0x35c);
  if ((((uVar8 & 1) != 0) && ((uVar8 & 2) != 0)) && (*(char *)(in_EAX + 0x2ff) != '\0')) {
    switch(uVar8 >> 0x16 & 0xf) {
    case 0:
      uVar9 = FUN_00443080(param_1);
      return uVar9;
    case 1:
      goto LAB_004436c0;
    case 2:
      uVar9 = FUN_00443290(param_1);
      return uVar9;
    case 3:
      if (*(float *)(in_EAX + 0x2c) != _DAT_00470b04) {
        fVar3 = (float10)fcos((float10)*(float *)(in_EAX + 0x2c));
        fVar10 = (float10)fsin((float10)*(float *)(in_EAX + 0x2c));
        fVar1 = (float)fVar3;
        fVar2 = (float)fVar10;
        fVar5 = *(float *)(in_EAX + 0x34c) + *(float *)(in_EAX + 0x340) + *(float *)(in_EAX + 0x334)
        ;
        uVar8 = *(uint *)(in_EAX + 0x35c) >> 0x12 & 3;
        fVar6 = *(float *)(in_EAX + 0x350) + *(float *)(in_EAX + 0x344) + *(float *)(in_EAX + 0x338)
        ;
        fVar7 = *(float *)(in_EAX + 0x4c) * *(float *)(in_EAX + 0x3c);
        fVar4 = *(float *)(in_EAX + 0x50) * *(float *)(in_EAX + 0x40);
        if (uVar8 == 0) {
          in_stack_fffffff0 = _DAT_00470b78 * fVar7;
          unaff_ESI = fVar7 * _DAT_00470b0c;
          unaff_EDI = in_stack_fffffff0;
          in_stack_fffffff4 = unaff_ESI;
        }
        else if (uVar8 == 1) {
          in_stack_fffffff0 = 0.0;
          unaff_EDI = 0.0;
          unaff_ESI = fVar7;
          in_stack_fffffff4 = fVar7;
        }
        else if (uVar8 == 2) {
          in_stack_fffffff0 = -fVar7;
          unaff_EDI = in_stack_fffffff0;
          unaff_ESI = 0.0;
          in_stack_fffffff4 = _DAT_00470b04;
        }
        uVar8 = *(uint *)(in_EAX + 0x35c) >> 0x14 & 3;
        if (uVar8 == 0) {
          local_20 = fVar4 * _DAT_00470b78;
          local_14 = fVar4 * _DAT_00470b0c;
          local_1c = local_20;
          local_18 = local_14;
        }
        else if (uVar8 == 1) {
          local_1c = 0.0;
          local_20 = 0.0;
          local_14 = fVar4;
          local_18 = fVar4;
        }
        else if (uVar8 == 2) {
          local_14 = 0.0;
          local_20 = -fVar4;
          local_1c = local_20;
          local_18 = _DAT_00470b04;
        }
        DAT_004978c0 = (in_stack_fffffff0 * fVar1 - local_20 * fVar2) + fVar5;
        DAT_004978c4 = in_stack_fffffff0 * fVar2 + local_20 * fVar1 + fVar6;
        DAT_004978dc = (in_stack_fffffff4 * fVar1 - local_1c * fVar2) + fVar5;
        DAT_004978e0 = local_1c * fVar1 + in_stack_fffffff4 * fVar2 + fVar6;
        DAT_004978f8 = (unaff_EDI * fVar1 - local_18 * fVar2) + fVar5;
        DAT_004978fc = unaff_EDI * fVar2 + fVar1 * local_18 + fVar6;
        DAT_00497914 = (unaff_ESI * fVar1 - local_14 * fVar2) + fVar5;
        DAT_00497918 = unaff_ESI * fVar2 + local_14 * fVar1 + fVar6;
        _DAT_004978c8 =
             *(float *)(in_EAX + 0x354) + *(float *)(in_EAX + 0x348) + *(float *)(in_EAX + 0x33c);
        _DAT_004978e4 = _DAT_004978c8;
        _DAT_00497900 = _DAT_004978c8;
        _DAT_0049791c = _DAT_004978c8;
        uVar9 = FUN_00442670(param_1,0);
        return uVar9;
      }
      uVar9 = FUN_00443290(param_1);
      return uVar9;
    case 4:
      uVar9 = FUN_00443f80(param_1);
      return uVar9;
    case 5:
      uVar9 = FUN_00444580();
      return uVar9;
    case 6:
      uVar9 = FUN_00443fb0();
      return uVar9;
    case 7:
      uVar9 = FUN_004445c0(param_1,in_EAX);
      return uVar9;
    case 8:
      uVar9 = FUN_00444760((int)param_1);
      return uVar9;
    case 9:
      uVar9 = FUN_00444ce0((int)param_1);
      return uVar9;
    default:
      return 0;
    }
  }
  return 0xffffffff;
LAB_004436c0:
  if (*(float *)(in_EAX + 0x2c) != _DAT_00470b04) {
    fVar3 = (float10)fcos((float10)*(float *)(in_EAX + 0x2c));
    fVar10 = (float10)fsin((float10)*(float *)(in_EAX + 0x2c));
    fVar1 = (float)fVar3;
    fVar2 = (float)fVar10;
    fVar5 = *(float *)(in_EAX + 0x34c) + *(float *)(in_EAX + 0x340) + *(float *)(in_EAX + 0x334);
    uVar8 = *(uint *)(in_EAX + 0x35c) >> 0x12 & 3;
    fVar6 = *(float *)(in_EAX + 0x350) + *(float *)(in_EAX + 0x344) + *(float *)(in_EAX + 0x338);
    fVar7 = *(float *)(in_EAX + 0x4c) * *(float *)(in_EAX + 0x3c);
    fVar4 = *(float *)(in_EAX + 0x50) * *(float *)(in_EAX + 0x40);
    if (uVar8 == 0) {
      in_stack_fffffff0 = _DAT_00470b78 * fVar7;
      unaff_ESI = fVar7 * _DAT_00470b0c;
      unaff_EDI = in_stack_fffffff0;
      in_stack_fffffff4 = unaff_ESI;
    }
    else if (uVar8 == 1) {
      in_stack_fffffff0 = 0.0;
      unaff_EDI = 0.0;
      unaff_ESI = fVar7;
      in_stack_fffffff4 = fVar7;
    }
    else if (uVar8 == 2) {
      in_stack_fffffff0 = -fVar7;
      unaff_EDI = in_stack_fffffff0;
      unaff_ESI = 0.0;
      in_stack_fffffff4 = _DAT_00470b04;
    }
    uVar8 = *(uint *)(in_EAX + 0x35c) >> 0x14 & 3;
    if (uVar8 == 0) {
      local_20 = fVar4 * _DAT_00470b78;
      local_14 = fVar4 * _DAT_00470b0c;
      local_1c = local_20;
      local_18 = local_14;
    }
    else if (uVar8 == 1) {
      local_1c = 0.0;
      local_20 = 0.0;
      local_14 = fVar4;
      local_18 = fVar4;
    }
    else if (uVar8 == 2) {
      local_14 = 0.0;
      local_20 = -fVar4;
      local_1c = local_20;
      local_18 = _DAT_00470b04;
    }
    DAT_004978c0 = (in_stack_fffffff0 * fVar1 - local_20 * fVar2) + fVar5;
    DAT_004978c4 = in_stack_fffffff0 * fVar2 + local_20 * fVar1 + fVar6;
    DAT_004978dc = (in_stack_fffffff4 * fVar1 - local_1c * fVar2) + fVar5;
    DAT_004978e0 = local_1c * fVar1 + in_stack_fffffff4 * fVar2 + fVar6;
    DAT_004978f8 = (unaff_EDI * fVar1 - local_18 * fVar2) + fVar5;
    DAT_004978fc = unaff_EDI * fVar2 + fVar1 * local_18 + fVar6;
    DAT_00497914 = (unaff_ESI * fVar1 - local_14 * fVar2) + fVar5;
    DAT_00497918 = unaff_ESI * fVar2 + local_14 * fVar1 + fVar6;
    _DAT_004978c8 =
         *(float *)(in_EAX + 0x354) + *(float *)(in_EAX + 0x348) + *(float *)(in_EAX + 0x33c);
    _DAT_004978e4 = _DAT_004978c8;
    _DAT_00497900 = _DAT_004978c8;
    _DAT_0049791c = _DAT_004978c8;
    uVar9 = FUN_00442670(param_1,0);
    return uVar9;
  }
  uVar9 = FUN_00443290(param_1);
  return uVar9;
}

