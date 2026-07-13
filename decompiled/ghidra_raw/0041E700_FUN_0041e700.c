/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x0041E700
 * Tracking name: FUN_0041e700
 * Ghidra name: FUN_0041e700
 * Tracked span: 1024 bytes
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

ulonglong __fastcall FUN_0041e700(int *param_1)

{
  float fVar1;
  int iVar2;
  int iVar3;
  undefined4 extraout_ECX;
  int extraout_EDX;
  int extraout_EDX_00;
  uint uVar4;
  float10 fVar5;
  ulonglong uVar6;
  float local_18;
  float local_14;
  float local_10;
  undefined4 local_c;
  undefined4 local_8;
  float local_4;
  
  if (((float)param_1[0x10] < (float)param_1[0x111]) &&
     (fVar1 = DAT_00476f78 * (float)param_1[0x12] + (float)param_1[0x10], param_1[0x10] = (int)fVar1
     , (float)param_1[0x111] < fVar1)) {
    param_1[0x10] = param_1[0x111];
  }
  fVar5 = (float10)FUN_0044bc10((float)param_1[0xf],DAT_00476f78 * (float)param_1[0x110]);
  param_1[0xf] = (int)(float)fVar5;
  iVar3 = extraout_EDX;
  if (((*(byte *)(param_1 + 0x11a) & 1) != 0) &&
     (iVar2 = *(int *)(DAT_00477704 + 0x10), iVar3 = DAT_00477704, iVar2 != 0)) {
    param_1[9] = *(int *)(iVar2 + 0x1068);
    iVar3 = *(int *)(iVar2 + 0x106c);
    param_1[10] = iVar3;
    param_1[0xb] = *(int *)(iVar2 + 0x1070);
  }
  fVar1 = DAT_00476f78 * (float)param_1[0x10d];
  local_4 = DAT_00476f78 * (float)param_1[0x10e];
  param_1[9] = (int)(DAT_00476f78 * (float)param_1[0x10c] + (float)param_1[9]);
  param_1[10] = (int)(fVar1 + (float)param_1[10]);
  param_1[0xb] = (int)(local_4 + (float)param_1[0xb]);
  switch(param_1[3]) {
  case 3:
    if (param_1[0x115] <= param_1[5]) {
      FUN_00405410(0);
      param_1[3] = 4;
    }
    break;
  case 4:
    if (param_1[5] < param_1[0x116]) {
      param_1[0x11] = (int)(((float)param_1[0x113] * (float)param_1[6]) / (float)param_1[0x116]);
      break;
    }
    FUN_00405410(0);
    param_1[3] = 2;
    param_1[0x11] = param_1[0x113];
  case 2:
    if (param_1[0x117] <= param_1[5]) {
      FUN_00405410(0);
      param_1[3] = 5;
      iVar3 = extraout_EDX_00;
switchD_0041e7d4_caseD_5:
      if (param_1[0x118] <= param_1[5]) {
        return CONCAT44(iVar3,1);
      }
      param_1[0x11] =
           (int)((float)param_1[0x113] -
                ((float)param_1[0x113] * (float)param_1[6]) / (float)param_1[0x118]);
    }
    break;
  case 5:
    goto switchD_0041e7d4_caseD_5;
  }
  if (((param_1[3] == 4) || (param_1[3] == 2)) && (_DAT_00470b48 < (float)param_1[0x10])) {
    FUN_0041f800(&local_18,(float)param_1[0xf],(float)param_1[0x10] * _DAT_00470c18);
    local_18 = local_18 + (float)param_1[9];
    local_14 = local_14 + (float)param_1[10];
    local_10 = local_10 + (float)param_1[0xb];
    if (_DAT_00470bcc <= (float)param_1[0x11]) {
      fVar1 = (float)param_1[0x11] - ((float)param_1[0x11] + _DAT_00470b48) * _DAT_00470cc4;
    }
    else {
      fVar1 = (float)param_1[0x11] * _DAT_00470b0c;
    }
    iVar3 = FUN_004267f0(DAT_00477834,(float)param_1[0xf],fVar1,(float)param_1[0x10] * _DAT_00470cc0
                        );
    if (iVar3 == 1) {
      local_c = 0x42000000;
      local_8 = 0x42000000;
      local_4 = 0.0;
      (**(code **)(*param_1 + 0x18))((int)DAT_00477834 + 0x3c0,&local_c,0);
    }
    else if ((iVar3 == 2) && (param_1[5] % 5 == 0)) {
      FUN_00448db0(*(undefined2 **)(DAT_004776f0 + 0x3e0b50));
      FUN_0043dd10();
    }
  }
  fVar1 = *(float *)(param_1[0x26c] + 0x34);
  param_1[0x25e] = param_1[0x25e] | 8;
  param_1[0x196] = (int)((float)param_1[0x11] / fVar1);
  fVar1 = *(float *)(param_1[0x26c] + 0x30);
  param_1[0x25e] = param_1[0x25e] | 8;
  param_1[0x197] = (int)((float)param_1[0x10] / fVar1);
  uVar6 = FUN_0043ee30(8,param_1[0x26c],(int)(param_1 + 0x187));
  uVar4 = (uint)(uVar6 >> 0x20);
  uVar6 = (ulonglong)uVar4 << 0x20;
  if ((float)param_1[0x13] == _DAT_00470b04) {
    uVar6 = FUN_0043ee30(extraout_ECX,uVar4,(int)(param_1 + 0x272));
  }
  return uVar6 & 0xffffffff00000000;
}

