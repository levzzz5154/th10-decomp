/* Raw Ghidra reference; not compilable reconstruction. Address: 0041F400 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

float __thiscall FUN_0041f400(int param_1,int param_2)

{
  undefined2 *puVar1;
  float fVar2;
  float fVar3;
  undefined4 *puVar4;
  undefined4 extraout_ECX;
  float extraout_EDX;
  float local_30;
  float local_2c;
  float local_24;
  float local_20;
  float local_1c;
  float local_18;
  float local_14;
  float local_10;
  float local_c;
  float local_8;
  float local_4;
  
  local_2c = 0.0;
  local_30 = 6.0;
  FUN_0041f800(&local_18,*(float *)(param_1 + 0x3c),6.0);
  local_24 = local_18 + *(float *)(param_1 + 0x24);
  local_1c = *(float *)(param_1 + 0x2c);
  local_20 = local_14 + *(float *)(param_1 + 0x28);
  local_18 = local_18 + local_18;
  local_14 = local_14 + local_14;
  local_10 = extraout_EDX;
  local_c = local_24;
  local_8 = local_20;
  local_4 = local_1c;
  if (*(float *)(param_1 + 0x40) <= _DAT_00470cd8) {
    *(undefined4 *)(param_1 + 0xc) = 1;
    return extraout_EDX;
  }
  do {
    local_2c = (float)((int)local_2c + 1);
    if ((((local_24 + _DAT_00470b48 < _DAT_00470b40 == (local_24 + _DAT_00470b48 == _DAT_00470b40))
         && (local_24 - _DAT_00470b48 < _DAT_00470b3c)) &&
        (fVar2 = local_20 + _DAT_00470b48, fVar2 < _DAT_00470b04 == (fVar2 == _DAT_00470b04))) &&
       (local_20 - _DAT_00470b48 < _DAT_00470b38)) {
      puVar1 = *(undefined2 **)(DAT_0047781c + 0x458);
      puVar4 = FUN_00449950();
      fVar3 = local_24 + _DAT_00470b4c;
      puVar4[0xd7] = puVar4[0xd7] | 0x40000000;
      puVar4[8] = 0;
      puVar4[0xd2] = local_1c;
      puVar4[0xd0] = fVar3;
      puVar4[0xd1] = fVar2;
      FUN_0043e710(puVar1);
      FUN_004489d0(extraout_ECX,(int)g_pGameStateManager);
      if (((param_2 != 0) &&
          (local_24 + _DAT_00470bcc < _DAT_00470b40 == (local_24 + _DAT_00470bcc == _DAT_00470b40)))
         && ((local_24 - _DAT_00470bcc < _DAT_00470b3c &&
             ((local_20 + _DAT_00470bcc < _DAT_00470b04 ==
               (local_20 + _DAT_00470bcc == _DAT_00470b04) &&
              (local_20 - _DAT_00470bcc < _DAT_00470b38)))))) {
        FUN_0041bb00(&local_24,8,0xffffffff,-1.5707964,0.6);
      }
    }
    local_24 = local_24 + local_18;
    local_20 = local_20 + local_14;
    local_1c = local_1c + local_10;
    local_30 = local_30 + _DAT_00470cd8;
  } while (local_30 + _DAT_00470d1c < *(float *)(param_1 + 0x40));
  *(undefined4 *)(param_1 + 0xc) = 1;
  return local_2c;
}

