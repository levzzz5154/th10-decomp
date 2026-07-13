/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x0041DD80
 * Tracking name: FUN_0041dd80
 * Ghidra name: FUN_0041dd80
 * Tracked span: 1248 bytes
 */


/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int __thiscall FUN_0041dd80(void *this,float *param_1,float param_2,int param_3)

{
  undefined2 *puVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  undefined4 *puVar5;
  int iVar6;
  int iVar7;
  undefined4 extraout_ECX;
  float extraout_EDX;
  float fVar8;
  float *pfVar9;
  char *pcVar10;
  float *pfVar11;
  float local_338;
  float local_334;
  float local_330;
  float local_32c;
  float local_328;
  float local_324;
  float local_320;
  int local_31c;
  float local_318;
  float local_314;
  float local_310;
  void *local_30c;
  float *local_308;
  float local_304;
  float local_300;
  float local_2fc;
  float local_2f8;
  float local_2f0 [4];
  float local_2e0;
  float local_2dc;
  char local_110 [260];
  uint local_c;
  
  local_c = DAT_00473660 ^ (uint)&stack0xfffffffc;
  pfVar9 = (float *)((int)this + 0x24);
  local_300 = *pfVar9;
  local_2fc = *(float *)((int)this + 0x28);
  local_2f8 = *(float *)((int)this + 0x2c);
  pcVar10 = local_110;
  for (iVar7 = 0x40; iVar7 != 0; iVar7 = iVar7 + -1) {
    pcVar10[0] = '\0';
    pcVar10[1] = '\0';
    pcVar10[2] = '\0';
    pcVar10[3] = '\0';
    pcVar10 = pcVar10 + 4;
  }
  local_31c = 0;
  local_304 = 0.0;
  local_338 = 6.0;
  local_320 = 0.0;
  local_30c = this;
  local_308 = pfVar9;
  FUN_0041f800(&local_328,*(float *)((int)this + 0x3c),6.0);
  local_334 = local_328 + *pfVar9;
  local_330 = local_324 + *(float *)((int)this + 0x28);
  local_310 = local_320 + *(float *)((int)this + 0x2c);
  local_328 = local_328 + local_328;
  local_324 = local_324 + local_324;
  local_320 = local_320 + local_320;
  fVar8 = extraout_EDX;
  local_32c = extraout_EDX;
  local_318 = local_334;
  local_314 = local_330;
  if (_DAT_00470cd8 < *(float *)((int)this + 0x40) ==
      (_DAT_00470cd8 == *(float *)((int)this + 0x40))) {
    return local_31c;
  }
  do {
    if ((param_1[1] - local_330) * (param_1[1] - local_330) +
        (*param_1 - local_334) * (*param_1 - local_334) <= param_2 * param_2) {
      local_31c = local_31c + 1;
      local_110[(int)fVar8] = '\x01';
      if ((((param_3 != 0) &&
           (local_334 + _DAT_00470bcc < _DAT_00470b40 ==
            (local_334 + _DAT_00470bcc == _DAT_00470b40))) &&
          (local_334 - _DAT_00470bcc < _DAT_00470b3c)) &&
         ((local_330 + _DAT_00470bcc < _DAT_00470b04 == (local_330 + _DAT_00470bcc == _DAT_00470b04)
          && (local_330 - _DAT_00470bcc < _DAT_00470b38)))) {
        FUN_0041bb00(&local_334,8,0xffffffff,-1.5707964,0.6);
      }
      puVar1 = *(undefined2 **)(DAT_0047781c + 0x458);
      puVar5 = FUN_00449950();
      fVar8 = local_334 + _DAT_00470b4c;
      puVar5[0xd7] = puVar5[0xd7] | 0x40000000;
      puVar5[8] = 0;
      puVar5[0xd0] = fVar8;
      fVar8 = local_330 + _DAT_00470b48;
      puVar5[0xd2] = local_32c;
      puVar5[0xd1] = fVar8;
      FUN_0043e710(puVar1);
      FUN_004489d0(extraout_ECX,(int)g_pGameStateManager);
      fVar8 = local_304;
      this = local_30c;
      pfVar9 = local_308;
    }
    fVar8 = (float)((int)fVar8 + 1);
    local_334 = local_334 + local_328;
    local_330 = local_330 + local_324;
    local_32c = local_32c + local_320;
    local_338 = local_338 + _DAT_00470cd8;
    local_304 = fVar8;
  } while (local_338 + _DAT_00470d1c < *(float *)((int)this + 0x40) !=
           (local_338 + _DAT_00470d1c == *(float *)((int)this + 0x40)));
  if (local_31c == 0) {
    return 0;
  }
  if ((int)fVar8 <= local_31c) {
    *(undefined1 *)((int)this + 0x50) = 1;
    return local_31c;
  }
  local_308 = (float *)0x0;
  if (0 < (int)fVar8) {
    do {
      if (local_110[(int)local_308] == '\0') break;
      local_308 = (float *)((int)local_308 + 1);
    } while ((int)local_308 < (int)fVar8);
    if (local_308 != (float *)0x0) {
      fVar2 = (float)(int)local_308;
      *pfVar9 = local_328 * fVar2 + *pfVar9;
      pfVar9[1] = local_324 * fVar2 + pfVar9[1];
      pfVar9[2] = fVar2 * local_320 + pfVar9[2];
      fVar4 = _DAT_00470c0c;
      fVar2 = fVar2 * _DAT_00470cd8;
      fVar3 = *(float *)((int)local_30c + 0x40) - fVar2;
      *(float *)((int)local_30c + 0x40) = fVar3;
      if (fVar3 <= fVar4) {
        *(undefined1 *)((int)local_30c + 0x50) = 1;
        return local_31c;
      }
      *(float *)((int)local_30c + 0x434) = fVar3;
      *(float *)((int)local_30c + 0x4c) = fVar2;
    }
  }
  iVar7 = 0;
  while( true ) {
    if ((int)fVar8 <= (int)local_308) {
      return local_31c;
    }
    if (local_110[(int)local_308] != '\0') break;
    local_308 = (float *)((int)local_308 + 1);
    iVar7 = iVar7 + 1;
  }
  if ((int)fVar8 <= (int)local_308) {
    return local_31c;
  }
  fVar2 = (float)iVar7 * _DAT_00470cd8;
  *(float *)((int)local_30c + 0x434) =
       *(float *)((int)local_30c + 0x434) - (*(float *)((int)local_30c + 0x40) - fVar2);
  *(float *)((int)local_30c + 0x40) = fVar2;
  if (fVar2 < _DAT_00470c0c) {
    *(undefined1 *)((int)local_30c + 0x50) = 1;
  }
  do {
    while( true ) {
      if ((int)fVar8 <= (int)local_308) {
        return local_31c;
      }
      if (local_110[(int)local_308] == '\0') break;
      local_308 = (float *)((int)local_308 + 1);
    }
    if ((int)fVar8 <= (int)local_308) {
      return local_31c;
    }
    iVar6 = 0;
    iVar7 = (int)local_308;
    do {
      if (local_110[iVar7] != '\0') break;
      iVar7 = iVar7 + 1;
      iVar6 = iVar6 + 1;
    } while (iVar7 < (int)fVar8);
    fVar2 = (float)iVar6 * _DAT_00470cd8;
    pfVar9 = (float *)((int)local_30c + 0x424);
    pfVar11 = local_2f0;
    for (iVar6 = 0x77; iVar6 != 0; iVar6 = iVar6 + -1) {
      *pfVar11 = *pfVar9;
      pfVar9 = pfVar9 + 1;
      pfVar11 = pfVar11 + 1;
    }
    if (_DAT_00470c0c < fVar2) {
      fVar8 = (float)(int)local_308;
      local_330 = fVar8 * local_324;
      local_32c = fVar8 * local_320;
      local_318 = local_300 + local_328 * fVar8;
      local_314 = local_2fc + local_330;
      local_310 = local_2f8 + local_32c;
      local_2f0[0] = local_318;
      local_2f0[1] = local_314;
      local_2f0[2] = local_310;
      local_2e0 = fVar2;
      local_2dc = fVar2;
      FUN_0041c510(0);
      fVar8 = local_304;
    }
    local_308 = (float *)iVar7;
    if ((int)fVar8 <= iVar7) {
      return local_31c;
    }
  } while( true );
}

