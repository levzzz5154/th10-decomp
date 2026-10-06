
/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int __thiscall FUN_0041efa0(void *this,float *param_1,float param_2,int param_3)

{
  undefined2 *puVar1;
  undefined4 *puVar2;
  int iVar3;
  int iVar4;
  undefined4 extraout_ECX;
  int iVar5;
  float extraout_EDX;
  float fVar6;
  char *pcVar7;
  float *pfVar8;
  float local_334;
  float local_330;
  float local_32c;
  float local_328;
  float local_324;
  float local_320;
  float local_31c;
  int local_318;
  float local_314;
  float local_310;
  float local_30c;
  float local_308;
  void *local_304;
  int local_300;
  float local_2fc;
  float local_2f8;
  float local_2f4;
  float local_2f0 [4];
  float local_2e0;
  float local_2dc;
  float local_2d8;
  undefined4 local_2d4;
  undefined4 local_2d0;
  undefined2 local_2cc;
  undefined2 local_2ca;
  char local_110 [260];
  uint local_c;
  
  local_c = DAT_00473660 ^ (uint)&stack0xfffffffc;
  local_2fc = *(float *)((int)this + 0x24);
  local_2f8 = *(float *)((int)this + 0x28);
  local_2f4 = *(float *)((int)this + 0x2c);
  pcVar7 = local_110;
  for (iVar4 = 0x40; iVar4 != 0; iVar4 = iVar4 + -1) {
    pcVar7[0] = '\0';
    pcVar7[1] = '\0';
    pcVar7[2] = '\0';
    pcVar7[3] = '\0';
    pcVar7 = pcVar7 + 4;
  }
  local_318 = 0;
  local_314 = 0.0;
  local_334 = 6.0;
  local_31c = 0.0;
  local_304 = this;
  FUN_0041f800(&local_324,*(float *)((int)this + 0x3c),6.0);
  local_330 = local_324 + *(float *)((int)this + 0x24);
  local_32c = local_320 + *(float *)((int)this + 0x28);
  local_308 = local_31c + *(float *)((int)this + 0x2c);
  local_324 = local_324 + local_324;
  local_320 = local_320 + local_320;
  local_31c = local_31c + local_31c;
  fVar6 = extraout_EDX;
  local_328 = extraout_EDX;
  local_310 = local_330;
  local_30c = local_32c;
  if (_DAT_00470cd8 < *(float *)((int)this + 0x40)) {
    do {
      if ((param_1[1] - local_32c) * (param_1[1] - local_32c) +
          (*param_1 - local_330) * (*param_1 - local_330) <= param_2 * param_2) {
        local_318 = local_318 + 1;
        local_110[(int)fVar6] = '\x01';
        if ((((param_3 != 0) &&
             (local_330 + _DAT_00470bcc < _DAT_00470b40 ==
              (local_330 + _DAT_00470bcc == _DAT_00470b40))) &&
            (local_330 - _DAT_00470bcc < _DAT_00470b3c)) &&
           ((local_32c + _DAT_00470bcc < _DAT_00470b04 ==
             (local_32c + _DAT_00470bcc == _DAT_00470b04) &&
            (local_32c - _DAT_00470bcc < _DAT_00470b38)))) {
          FUN_0041bb00(&local_330,8,0xffffffff,-1.5707964,0.6);
        }
        puVar1 = *(undefined2 **)(DAT_0047781c + 0x458);
        puVar2 = FUN_00449950();
        fVar6 = local_330 + _DAT_00470b4c;
        puVar2[0xd7] = puVar2[0xd7] | 0x40000000;
        puVar2[8] = 0;
        puVar2[0xd0] = fVar6;
        fVar6 = local_32c + _DAT_00470b48;
        puVar2[0xd2] = local_328;
        puVar2[0xd1] = fVar6;
        FUN_0043e710(puVar1);
        FUN_004489d0(extraout_ECX,(int)g_pGameStateManager);
        fVar6 = local_314;
        this = local_304;
      }
      fVar6 = (float)((int)fVar6 + 1);
      local_330 = local_330 + local_324;
      local_32c = local_32c + local_320;
      local_328 = local_328 + local_31c;
      local_334 = local_334 + _DAT_00470cd8;
      local_314 = fVar6;
    } while (local_334 + _DAT_00470d1c < *(float *)((int)this + 0x40));
    if (local_318 != 0) {
      iVar3 = 0;
      iVar4 = 0;
      if (0 < (int)fVar6) {
        do {
          if (local_110[iVar4] == '\0') break;
          iVar4 = iVar4 + 1;
        } while (iVar4 < (int)fVar6);
        if (iVar4 != 0) {
          *(undefined4 *)((int)this + 0x40) = 0;
LAB_0041f298:
          if ((int)fVar6 <= iVar4) {
            return local_318;
          }
          do {
            local_300 = iVar4;
            if ((int)local_314 <= iVar4) {
              return local_318;
            }
            while (local_110[local_300] != '\0') {
              local_300 = local_300 + 1;
              if ((int)local_314 <= local_300) {
                return local_318;
              }
            }
            if ((int)local_314 <= local_300) {
              return local_318;
            }
            iVar3 = 0;
            iVar4 = local_300;
            do {
              if (local_110[iVar4] != '\0') break;
              iVar4 = iVar4 + 1;
              iVar3 = iVar3 + 1;
            } while (iVar4 < (int)local_314);
            pfVar8 = local_2f0;
            for (iVar5 = 0x77; iVar5 != 0; iVar5 = iVar5 + -1) {
              *pfVar8 = 0.0;
              pfVar8 = pfVar8 + 1;
            }
            fVar6 = (float)local_300;
            local_2d0 = 0x41000000;
            local_32c = local_320 * fVar6;
            local_328 = fVar6 * local_31c;
            local_310 = local_2fc + local_324 * fVar6;
            local_2f0[3] = *(float *)((int)this + 0x3c);
            local_30c = local_2f8 + local_32c;
            local_2ca = *(undefined2 *)((int)this + 0x466);
            local_308 = local_2f4 + local_328;
            local_2d4 = *(undefined4 *)((int)this + 0x44);
            local_2cc = *(undefined2 *)((int)this + 0x464);
            local_2d8 = *(float *)((int)this + 0x444) - fVar6 * _DAT_00470cd8;
            local_2f0[0] = local_310;
            local_2f0[1] = local_30c;
            local_2f0[2] = local_308;
            local_2e0 = (float)iVar3 * _DAT_00470cd8;
            local_2dc = (float)iVar3 * _DAT_00470cd8;
            FUN_0041c510(0);
            this = local_304;
            if ((int)local_314 <= iVar4) {
              return local_318;
            }
          } while( true );
        }
      }
      if (0 < (int)fVar6) {
        do {
          if (local_110[iVar4] != '\0') {
            if ((int)fVar6 <= iVar4) {
              return local_318;
            }
            *(float *)((int)this + 0x40) = (float)iVar3 * _DAT_00470cd8;
            goto LAB_0041f298;
          }
          iVar4 = iVar4 + 1;
          iVar3 = iVar3 + 1;
        } while (iVar4 < (int)fVar6);
      }
    }
  }
  return local_318;
}

