/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x0041EB00
 * Tracking name: FUN_0041eb00
 * Ghidra name: FUN_0041eb00
 * Tracked span: 1184 bytes
 */


/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int __thiscall FUN_0041eb00(void *this,float *param_1,float *param_2,int param_3)

{
  float fVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  void *this_00;
  char *pcVar5;
  float *pfVar6;
  float local_34c;
  float local_348;
  float local_344;
  float local_340;
  void *local_33c;
  float local_338;
  float local_334;
  float local_330;
  float *local_32c;
  int local_328;
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
  float local_2d8;
  undefined4 local_2d4;
  undefined4 local_2d0;
  undefined2 local_2cc;
  undefined2 local_2ca;
  char local_110 [260];
  uint local_c;
  
  local_c = DAT_00473660 ^ (uint)&stack0xfffffffc;
  local_32c = param_2;
  local_2fc = *(float *)((int)this + 0x24);
  local_2f8 = *(float *)((int)this + 0x28);
  local_2f4 = *(float *)((int)this + 0x2c);
  pcVar5 = local_110;
  for (iVar4 = 0x40; iVar4 != 0; iVar4 = iVar4 + -1) {
    pcVar5[0] = '\0';
    pcVar5[1] = '\0';
    pcVar5[2] = '\0';
    pcVar5[3] = '\0';
    pcVar5 = pcVar5 + 4;
  }
  iVar4 = 0;
  local_328 = 0;
  local_34c = 6.0;
  local_30c = *param_1 - *param_2 * _DAT_00470b0c;
  local_308 = param_1[1] - param_2[1] * _DAT_00470b0c;
  local_304 = param_1[2] - param_2[2] * _DAT_00470b0c;
  local_348 = *param_2 * _DAT_00470b0c + *param_1;
  local_344 = param_2[1] * _DAT_00470b0c + param_1[1];
  local_31c = param_2[2] * _DAT_00470b0c + param_1[2];
  local_340 = 0.0;
  local_33c = this;
  local_324 = local_348;
  local_320 = local_344;
  FUN_0041f800(&local_348,*(float *)((int)this + 0x3c),6.0);
  local_338 = local_348 + *(float *)((int)this + 0x24);
  local_334 = local_344 + *(float *)((int)this + 0x28);
  local_310 = local_340 + *(float *)((int)this + 0x2c);
  local_348 = local_348 + local_348;
  local_330 = 0.0;
  local_344 = local_344 + local_344;
  local_340 = local_340 + local_340;
  local_318 = local_338;
  local_314 = local_334;
  if (_DAT_00470cd8 < *(float *)((int)this + 0x40)) {
    do {
      if ((((local_30c <= local_338) && (local_338 <= local_324)) && (local_308 <= local_334)) &&
         (local_334 <= local_320)) {
        local_328 = local_328 + 1;
        local_110[iVar4] = '\x01';
        if ((param_3 != 0) && (iVar2 = FUN_0041f7a0(&local_338,32.0,32.0), iVar2 == 0)) {
          FUN_0041bb00(this_00,8,0xffffffff,-1.5707964,0.6);
        }
        FUN_00448db0(*(undefined2 **)(DAT_0047781c + 0x458));
        this = local_33c;
      }
      iVar4 = iVar4 + 1;
      local_338 = local_348 + local_338;
      local_334 = local_344 + local_334;
      local_330 = local_330 + local_340;
      local_34c = local_34c + _DAT_00470cd8;
    } while (local_34c + _DAT_00470d1c < *(float *)((int)this + 0x40));
    if (local_328 != 0) {
      iVar3 = 0;
      iVar2 = 0;
      if (0 < iVar4) {
        iVar2 = 0;
        do {
          if (local_110[iVar2] == '\0') break;
          iVar2 = iVar2 + 1;
        } while (iVar2 < iVar4);
        if (iVar2 != 0) {
          *(undefined4 *)((int)local_33c + 0x40) = 0;
LAB_0041ee27:
          local_32c = (float *)iVar4;
          if (iVar4 <= iVar2) {
            return local_328;
          }
          do {
            local_300 = iVar2;
            if ((int)local_32c <= iVar2) {
              return local_328;
            }
            while (local_110[local_300] != '\0') {
              local_300 = local_300 + 1;
              if ((int)local_32c <= local_300) {
                return local_328;
              }
            }
            if ((int)local_32c <= local_300) {
              return local_328;
            }
            iVar4 = 0;
            iVar2 = local_300;
            do {
              if (local_110[iVar2] != '\0') break;
              iVar2 = iVar2 + 1;
              iVar4 = iVar4 + 1;
            } while (iVar2 < (int)local_32c);
            pfVar6 = local_2f0;
            for (iVar3 = 0x77; iVar3 != 0; iVar3 = iVar3 + -1) {
              *pfVar6 = 0.0;
              pfVar6 = pfVar6 + 1;
            }
            fVar1 = (float)local_300;
            local_2d0 = 0x41000000;
            local_308 = local_344 * fVar1;
            local_304 = fVar1 * local_340;
            local_318 = local_2fc + local_348 * fVar1;
            local_314 = local_2f8 + local_308;
            local_310 = local_2f4 + local_304;
            local_2f0[3] = *(float *)((int)local_33c + 0x3c);
            local_2cc = *(undefined2 *)((int)local_33c + 0x464);
            local_2d4 = *(undefined4 *)((int)local_33c + 0x44);
            local_2ca = *(undefined2 *)((int)local_33c + 0x466);
            local_2d8 = *(float *)((int)local_33c + 0x444) - fVar1 * _DAT_00470cd8;
            local_2f0[0] = local_318;
            local_2f0[1] = local_314;
            local_2f0[2] = local_310;
            local_2e0 = (float)iVar4 * _DAT_00470cd8;
            local_2dc = (float)iVar4 * _DAT_00470cd8;
            FUN_0041c510(0);
            if ((int)local_32c <= iVar2) {
              return local_328;
            }
          } while( true );
        }
      }
      if (0 < iVar4) {
        do {
          if (local_110[iVar2] != '\0') {
            if (iVar4 <= iVar2) {
              return local_328;
            }
            *(float *)((int)local_33c + 0x40) = (float)iVar3 * _DAT_00470cd8;
            goto LAB_0041ee27;
          }
          iVar2 = iVar2 + 1;
          iVar3 = iVar3 + 1;
        } while (iVar2 < iVar4);
      }
    }
  }
  return local_328;
}

