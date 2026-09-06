/* Raw Ghidra reference; not compilable reconstruction. Address: 0041E260 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int __thiscall FUN_0041e260(void *this,int param_1)

{
  undefined4 *puVar1;
  undefined2 *puVar2;
  int iVar3;
  float fVar4;
  void *pvVar5;
  undefined4 *puVar6;
  int iVar7;
  int extraout_EDX;
  float local_30;
  int local_28;
  float local_24;
  float local_20;
  float local_1c;
  float local_18;
  float local_14;
  float local_10;
  float local_c;
  float local_8;
  float local_4;
  
  local_28 = 0;
  local_30 = 6.0;
  FUN_0041f800(&local_18,*(float *)((int)this + 0x3c),6.0);
  local_24 = local_18 + *(float *)(extraout_EDX + 0x24);
  local_1c = *(float *)(extraout_EDX + 0x2c);
  local_10 = 0.0;
  local_20 = local_14 + *(float *)(extraout_EDX + 0x28);
  local_18 = local_18 + local_18;
  local_14 = local_14 + local_14;
  local_c = local_24;
  local_8 = local_20;
  local_4 = local_1c;
  if (*(float *)(extraout_EDX + 0x40) <= _DAT_00470cd8) {
    *(undefined4 *)(extraout_EDX + 0xc) = 1;
    return 0;
  }
  do {
    puVar2 = *(undefined2 **)(DAT_0047781c + 0x458);
    local_28 = local_28 + 1;
    puVar6 = FUN_00449950();
    fVar4 = local_24 + _DAT_00470b4c;
    puVar6[0xd7] = puVar6[0xd7] | 0x40000000;
    puVar6[8] = 0;
    puVar6[0xd0] = fVar4;
    puVar6[0xd2] = local_1c;
    puVar6[0xd1] = local_20 + _DAT_00470b48;
    FUN_0043e710(puVar2);
    puVar1 = puVar6 + 1;
    puVar6[2] = 0;
    puVar6[3] = 0;
    pvVar5 = g_pGameStateManager;
    *puVar1 = puVar6;
    if (*(int *)((int)pvVar5 + 0x72dad4) == 0) {
      *(undefined4 **)((int)pvVar5 + 0x72dad4) = puVar1;
    }
    else {
      iVar3 = *(int *)((int)pvVar5 + 0x72dad8);
      if (*(int *)(iVar3 + 4) != 0) {
        puVar6[2] = *(int *)(iVar3 + 4);
        *(undefined4 **)(*(int *)(iVar3 + 4) + 8) = puVar1;
      }
      *(undefined4 **)(iVar3 + 4) = puVar1;
      puVar6[3] = iVar3;
    }
    *(undefined4 **)((int)pvVar5 + 0x72dad8) = puVar1;
    iVar3 = *(int *)((int)pvVar5 + 0x732454);
    iVar7 = iVar3 + 1;
    *(int *)((int)pvVar5 + 0x732454) = iVar7;
    if (iVar7 == 0) {
      *(int *)((int)pvVar5 + 0x732454) = iVar3 + 2;
    }
    *puVar6 = *(undefined4 *)((int)pvVar5 + 0x732454);
    if ((((param_1 != 0) &&
         (local_24 + _DAT_00470bcc < _DAT_00470b40 == (local_24 + _DAT_00470bcc == _DAT_00470b40)))
        && (local_24 - _DAT_00470bcc < _DAT_00470b3c)) &&
       ((local_20 + _DAT_00470bcc < _DAT_00470b04 == (local_20 + _DAT_00470bcc == _DAT_00470b04) &&
        (local_20 - _DAT_00470bcc < _DAT_00470b38)))) {
      FUN_0041bb00(&local_24,8,0xffffffff,-1.5707964,0.6);
    }
    local_24 = local_24 + local_18;
    local_20 = local_20 + local_14;
    local_1c = local_1c + local_10;
    local_30 = local_30 + _DAT_00470cd8;
  } while (local_30 + _DAT_00470d1c < *(float *)((int)this + 0x40));
  *(undefined4 *)((int)this + 0xc) = 1;
  return local_28;
}

