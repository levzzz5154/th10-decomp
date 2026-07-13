/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x0041D880
 * Tracking name: FUN_0041d880
 * Ghidra name: FUN_0041d880
 * Tracked span: 1280 bytes
 */


/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int __thiscall FUN_0041d880(void *this,float *param_1,float *param_2,int param_3)

{
  float fVar1;
  float fVar2;
  float fVar3;
  int iVar4;
  int iVar5;
  void *this_00;
  float *pfVar6;
  char *pcVar7;
  float *pfVar8;
  float local_34c;
  float local_348;
  float local_344;
  float local_340;
  void *local_33c;
  float local_338;
  float local_334;
  float local_330;
  int local_32c;
  float *local_328;
  float local_324;
  float local_320;
  float local_31c;
  float local_318;
  float local_314;
  float local_310;
  float local_30c;
  float local_308;
  float local_304;
  int local_300;
  float local_2fc;
  float local_2f8;
  float local_2f4;
  float local_2f0 [4];
  float local_2e0;
  float local_2dc;
  char local_110 [260];
  uint local_c;
  
  local_c = DAT_00473660 ^ (uint)&stack0xfffffffc;
  local_328 = param_2;
  local_2fc = *(float *)((int)this + 0x24);
  local_2f8 = *(float *)((int)this + 0x28);
  local_2f4 = *(float *)((int)this + 0x2c);
  pcVar7 = local_110;
  for (iVar5 = 0x40; iVar5 != 0; iVar5 = iVar5 + -1) {
    pcVar7[0] = '\0';
    pcVar7[1] = '\0';
    pcVar7[2] = '\0';
    pcVar7[3] = '\0';
    pcVar7 = pcVar7 + 4;
  }
  iVar5 = 0;
  local_32c = 0;
  local_34c = 6.0;
  local_330 = 0.0;
  local_318 = *param_1 - *param_2 * _DAT_00470b0c;
  local_314 = param_1[1] - param_2[1] * _DAT_00470b0c;
  local_310 = param_1[2] - param_2[2] * _DAT_00470b0c;
  local_348 = *param_2 * _DAT_00470b0c + *param_1;
  local_344 = param_2[1] * _DAT_00470b0c + param_1[1];
  local_340 = param_2[2] * _DAT_00470b0c + param_1[2];
  local_33c = this;
  local_324 = local_348;
  local_320 = local_344;
  local_31c = local_340;
  FUN_0041f800(&local_338,*(float *)((int)this + 0x3c),6.0);
  local_348 = local_338 + *(float *)((int)this + 0x24);
  local_344 = local_334 + *(float *)((int)this + 0x28);
  local_304 = local_330 + *(float *)((int)this + 0x2c);
  local_338 = local_338 + local_338;
  local_340 = 0.0;
  local_334 = local_334 + local_334;
  local_330 = local_330 + local_330;
  local_30c = local_348;
  local_308 = local_344;
  if (_DAT_00470cd8 < *(float *)((int)this + 0x40) ==
      (_DAT_00470cd8 == *(float *)((int)this + 0x40))) {
    return local_32c;
  }
  do {
    if ((((local_318 <= local_348) && (local_348 <= local_324)) && (local_314 <= local_344)) &&
       (local_344 <= local_320)) {
      local_32c = local_32c + 1;
      local_110[iVar5] = '\x01';
      if ((param_3 != 0) && (iVar4 = FUN_0041f7a0(&local_348,32.0,32.0), iVar4 == 0)) {
        FUN_0041bb00(this_00,8,0xffffffff,-1.5707964,0.6);
      }
      FUN_00448db0(*(undefined2 **)(DAT_0047781c + 0x458));
      this = local_33c;
    }
    iVar5 = iVar5 + 1;
    local_348 = local_338 + local_348;
    local_344 = local_334 + local_344;
    local_340 = local_340 + local_330;
    local_34c = local_34c + _DAT_00470cd8;
  } while (local_34c + _DAT_00470d1c < *(float *)((int)this + 0x40) !=
           (local_34c + _DAT_00470d1c == *(float *)((int)this + 0x40)));
  if (local_32c == 0) {
    return 0;
  }
  if (iVar5 <= local_32c) {
    *(undefined1 *)((int)this + 0x50) = 1;
    return local_32c;
  }
  local_300 = 0;
  if (0 < iVar5) {
    do {
      if (local_110[local_300] == '\0') break;
      local_300 = local_300 + 1;
    } while (local_300 < iVar5);
    if (local_300 != 0) {
      fVar2 = (float)local_300;
      *(float *)((int)local_33c + 0x24) = local_338 * fVar2 + *(float *)((int)local_33c + 0x24);
      *(float *)((int)local_33c + 0x28) = local_334 * fVar2 + *(float *)((int)local_33c + 0x28);
      *(float *)((int)local_33c + 0x2c) = fVar2 * local_330 + *(float *)((int)local_33c + 0x2c);
      fVar3 = _DAT_00470c0c;
      fVar2 = fVar2 * _DAT_00470cd8;
      fVar1 = *(float *)((int)local_33c + 0x40) - fVar2;
      *(float *)((int)local_33c + 0x40) = fVar1;
      if (fVar1 <= fVar3) {
        *(undefined1 *)((int)local_33c + 0x50) = 1;
        return local_32c;
      }
      *(float *)((int)local_33c + 0x434) = fVar1;
      *(float *)((int)local_33c + 0x4c) = fVar2;
    }
  }
  iVar4 = 0;
  while( true ) {
    if (iVar5 <= local_300) {
      return local_32c;
    }
    if (local_110[local_300] != '\0') break;
    local_300 = local_300 + 1;
    iVar4 = iVar4 + 1;
  }
  if (iVar5 <= local_300) {
    return local_32c;
  }
  fVar2 = (float)iVar4 * _DAT_00470cd8;
  *(float *)((int)local_33c + 0x434) =
       *(float *)((int)local_33c + 0x434) - (*(float *)((int)local_33c + 0x40) - fVar2);
  *(float *)((int)local_33c + 0x40) = fVar2;
  local_328 = (float *)iVar5;
  if (fVar2 < _DAT_00470c0c) {
    *(undefined1 *)((int)local_33c + 0x50) = 1;
  }
  do {
    while( true ) {
      if ((int)local_328 <= local_300) {
        return local_32c;
      }
      if (local_110[local_300] == '\0') break;
      local_300 = local_300 + 1;
    }
    if ((int)local_328 <= local_300) {
      return local_32c;
    }
    iVar4 = 0;
    iVar5 = local_300;
    do {
      if (local_110[iVar5] != '\0') break;
      iVar5 = iVar5 + 1;
      iVar4 = iVar4 + 1;
    } while (iVar5 < (int)local_328);
    fVar2 = (float)iVar4 * _DAT_00470cd8;
    pfVar6 = (float *)((int)local_33c + 0x424);
    pfVar8 = local_2f0;
    for (iVar4 = 0x77; iVar4 != 0; iVar4 = iVar4 + -1) {
      *pfVar8 = *pfVar6;
      pfVar6 = pfVar6 + 1;
      pfVar8 = pfVar8 + 1;
    }
    if (_DAT_00470c0c < fVar2) {
      fVar1 = (float)local_300;
      local_314 = local_334 * fVar1;
      local_310 = fVar1 * local_330;
      local_30c = local_2fc + local_338 * fVar1;
      local_308 = local_2f8 + local_314;
      local_304 = local_2f4 + local_310;
      local_2f0[0] = local_30c;
      local_2f0[1] = local_308;
      local_2f0[2] = local_304;
      local_2e0 = fVar2;
      local_2dc = fVar2;
      FUN_0041c510(0);
    }
    local_300 = iVar5;
    if ((int)local_328 <= iVar5) {
      return local_32c;
    }
  } while( true );
}

