/* Raw Ghidra reference; not compilable reconstruction. Address: 0041D3D0 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 __fastcall FUN_0041d3d0(int *param_1)

{
  float fVar1;
  int iVar2;
  undefined4 extraout_ECX;
  float extraout_EDX;
  ulonglong uVar3;
  float fStack_18;
  float fStack_14;
  float fStack_10;
  undefined4 uStack_c;
  undefined4 uStack_8;
  float fStack_4;
  
  (**(code **)*param_1)();
  if (param_1[0x101] != 0) {
    if ((param_1[0x101] & 1U) != 0) {
      (**(code **)(*param_1 + 0x24))();
    }
    if ((*(byte *)(param_1 + 0x101) & 0x10) != 0) {
      (**(code **)(*param_1 + 0x28))();
    }
    if ((*(byte *)(param_1 + 0x101) & 0x20) != 0) {
      (**(code **)(*param_1 + 0x2c))();
    }
    if ((*(byte *)(param_1 + 0x101) & 0x40) != 0) {
      (**(code **)(*param_1 + 0x30))();
    }
    if ((param_1[0x101] & 0x100U) != 0) {
      (**(code **)(*param_1 + 0x34))();
    }
    if ((char)param_1[0x101] < '\0') {
      (**(code **)(*param_1 + 0x38))();
    }
    if ((param_1[0x101] & 0x8000c00U) != 0) {
      (**(code **)(*param_1 + 0x3c))();
    }
    if ((param_1[0x101] & 0x100000U) != 0) {
      (**(code **)(*param_1 + 0x40))();
    }
    if ((param_1[0x101] & 0x200000U) != 0) {
      (**(code **)(*param_1 + 0x44))();
    }
    if ((param_1[0x101] & 0x4000000U) != 0) {
      (**(code **)(*param_1 + 0x48))();
    }
    if ((char)((uint)param_1[0x101] >> 8) < '\0') {
      if (param_1[0x58] < 1) {
        param_1[0x101] = param_1[0x101] ^ 0x8000;
      }
      else {
        FUN_0044bf40(-1.0);
      }
    }
  }
  if ((float)param_1[0x10d] <= (float)param_1[0x10]) {
    param_1[0x13] = (int)(DAT_00476f78 * (float)param_1[0x12] + (float)param_1[0x13]);
    fVar1 = DAT_00476f78 * (float)param_1[0xd];
    fStack_4 = DAT_00476f78 * (float)param_1[0xe];
    param_1[9] = (int)(DAT_00476f78 * (float)param_1[0xc] + (float)param_1[9]);
    param_1[10] = (int)(fVar1 + (float)param_1[10]);
    param_1[0xb] = (int)(fStack_4 + (float)param_1[0xb]);
    if ((_DAT_00470b04 < (float)param_1[0x10f]) &&
       ((float)param_1[0x10f] < (float)param_1[0x13] + (float)param_1[0x10])) {
      param_1[0x10] = (int)((float)param_1[0x10f] - (float)param_1[0x13]);
      param_1[0x10d] = (int)((float)param_1[0x10f] - (float)param_1[0x13]);
      if ((float)param_1[0x10] < _DAT_00470b04 != ((float)param_1[0x10] == _DAT_00470b04)) {
        return 1;
      }
    }
  }
  else {
    fVar1 = DAT_00476f78 * (float)param_1[0x12] + (float)param_1[0x10];
    param_1[0x10] = (int)fVar1;
    if ((float)param_1[0x10d] < fVar1) {
      param_1[0x10] = param_1[0x10d];
    }
  }
  if (param_1[0x105] < 1) {
    FUN_0041f800(&fStack_18,(float)param_1[0xf],(float)param_1[0x10]);
    fStack_18 = fStack_18 + (float)param_1[9];
    fStack_14 = fStack_14 + (float)param_1[10];
    fStack_10 = fStack_10 + (float)param_1[0xb];
    iVar2 = FUN_0041f7a0(param_1 + 9,(float)param_1[0x11],(float)param_1[0x11]);
    if ((iVar2 != 0) && (iVar2 = FUN_0041f7a0(&fStack_18,extraout_EDX,extraout_EDX), iVar2 != 0)) {
      return 1;
    }
  }
  else {
    FUN_0044bf40(-1.0);
  }
  if ((_DAT_00470b48 < (float)param_1[0x10]) && (_DAT_00470bd4 < (float)param_1[0x11])) {
    FUN_0041f800(&fStack_18,(float)param_1[0xf],(float)param_1[0x10] * _DAT_00470c18);
    fStack_18 = fStack_18 + (float)param_1[9];
    fStack_14 = fStack_14 + (float)param_1[10];
    fStack_10 = fStack_10 + (float)param_1[0xb];
    if (_DAT_00470bcc <= (float)param_1[0x11]) {
      fVar1 = (float)param_1[0x11] - ((float)param_1[0x11] + _DAT_00470b48) * _DAT_00470b0c;
    }
    else {
      fVar1 = (float)param_1[0x11] * _DAT_00470b0c;
    }
    iVar2 = FUN_004267f0(DAT_00477834,(float)param_1[0xf],fVar1,(float)param_1[0x10] * _DAT_00470cc0
                        );
    if (iVar2 == 1) {
      uStack_c = 0x42000000;
      uStack_8 = 0x42000000;
      fStack_4 = 0.0;
      (**(code **)(*param_1 + 0x18))((int)DAT_00477834 + 0x3c0,&uStack_c,0);
    }
    else if ((iVar2 == 2) && (param_1[5] % 5 == 0)) {
      FUN_00448db0(*(undefined2 **)(DAT_004776f0 + 0x3e0b50));
      FUN_0043dd10();
    }
  }
  fVar1 = *(float *)(param_1[0x265] + 0x34);
  param_1[599] = param_1[599] | 8;
  param_1[399] = (int)((float)param_1[0x11] / fVar1);
  fVar1 = *(float *)(param_1[0x265] + 0x30);
  param_1[599] = param_1[599] | 8;
  param_1[400] = (int)((float)param_1[0x10] / fVar1);
  uVar3 = FUN_0043ee30(8,param_1[0x265],(int)(param_1 + 0x180));
  if ((float)param_1[0x13] == _DAT_00470b04) {
    FUN_0043ee30(extraout_ECX,(uint)(uVar3 >> 0x20),(int)(param_1 + 0x26b));
  }
  return 0;
}

