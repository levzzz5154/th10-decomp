/* Raw Ghidra reference; not compilable reconstruction. Address: 00442AD0 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 __thiscall FUN_00442ad0(void *this,byte param_1)

{
  float fVar1;
  float fVar2;
  byte bVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  int in_EAX;
  int iVar7;
  undefined4 uVar8;
  uint uVar9;
  uint uVar10;
  uint uVar11;
  uint uVar12;
  undefined4 extraout_ECX;
  undefined4 extraout_ECX_00;
  undefined4 extraout_ECX_01;
  undefined4 extraout_ECX_02;
  float local_c;
  float local_8;
  
  bVar3 = param_1;
  DAT_004978c0 = DAT_004978c0 + *(float *)((int)this + 0x5c);
  DAT_004978c4 = DAT_004978c4 + *(float *)((int)this + 0x60);
  DAT_004978dc = DAT_004978dc + *(float *)((int)this + 0x5c);
  DAT_004978e0 = DAT_004978e0 + *(float *)((int)this + 0x60);
  DAT_004978f8 = DAT_004978f8 + *(float *)((int)this + 0x5c);
  DAT_004978fc = DAT_004978fc + *(float *)((int)this + 0x60);
  DAT_00497914 = DAT_00497914 + *(float *)((int)this + 0x5c);
  DAT_00497918 = DAT_00497918 + *(float *)((int)this + 0x60);
  if ((param_1 & 1) != 0) {
    DAT_004978c0 = ROUND(DAT_004978c0) - _DAT_004700e8;
    DAT_004978dc = ROUND(DAT_004978dc) - _DAT_004700e8;
    DAT_004978c4 = ROUND(DAT_004978c4) - _DAT_004700e8;
    DAT_004978fc = ROUND(DAT_004978fc) - _DAT_004700e8;
    DAT_004978e0 = DAT_004978c4;
    DAT_004978f8 = DAT_004978c0;
    DAT_00497914 = DAT_004978dc;
    DAT_00497918 = DAT_004978fc;
  }
  _DAT_004978d4 = *(float *)(*(int *)(in_EAX + 0x394) + 0x28) + *(float *)(in_EAX + 0x54);
  _DAT_004978f0 = *(float *)(*(int *)(in_EAX + 0x394) + 0x20) + *(float *)(in_EAX + 0x54);
  _DAT_004978d8 = *(float *)(*(int *)(in_EAX + 0x394) + 0x24) + *(float *)(in_EAX + 0x58);
  _DAT_00497910 = *(float *)(*(int *)(in_EAX + 0x394) + 0x2c) + *(float *)(in_EAX + 0x58);
  fVar1 = DAT_004978dc;
  if (DAT_004978dc < DAT_004978c0) {
    fVar1 = DAT_004978c0;
  }
  if (fVar1 < DAT_004978f8) {
    fVar1 = DAT_004978f8;
  }
  if (fVar1 < DAT_00497914) {
    fVar1 = DAT_00497914;
  }
  if (DAT_004978c4 <= DAT_004978e0) {
    _param_1 = DAT_004978e0;
  }
  else {
    _param_1 = DAT_004978c4;
  }
  if (_param_1 < DAT_004978fc) {
    _param_1 = DAT_004978fc;
  }
  if (_param_1 < DAT_00497918) {
    _param_1 = DAT_00497918;
  }
  if (DAT_004978dc <= DAT_004978c0) {
    local_c = DAT_004978dc;
  }
  else {
    local_c = DAT_004978c0;
  }
  if (DAT_004978f8 < local_c) {
    local_c = DAT_004978f8;
  }
  if (DAT_00497914 < local_c) {
    local_c = DAT_00497914;
  }
  if (DAT_004978e0 <= DAT_004978c4) {
    local_8 = DAT_004978e0;
  }
  else {
    local_8 = DAT_004978c4;
  }
  if (DAT_004978fc < local_8) {
    local_8 = DAT_004978fc;
  }
  if (DAT_00497918 < local_8) {
    local_8 = DAT_00497918;
  }
  fVar2 = (float)*(int *)(DAT_00491fac + 0xcc);
  if (*(int *)(DAT_00491fac + 0xcc) < 0) {
    fVar2 = fVar2 + _DAT_00470b98;
  }
  _DAT_004978f4 = _DAT_004978d8;
  _DAT_0049790c = _DAT_004978d4;
  _DAT_00497928 = _DAT_004978f0;
  _DAT_0049792c = _DAT_00497910;
  if (fVar2 <= fVar1) {
    fVar1 = (float)*(int *)(DAT_00491fac + 0xd0);
    if (*(int *)(DAT_00491fac + 0xd0) < 0) {
      fVar1 = fVar1 + _DAT_00470b98;
    }
    if (fVar1 <= _param_1) {
      iVar7 = *(int *)(DAT_00491fac + 0xd4) + *(int *)(DAT_00491fac + 0xcc);
      fVar1 = (float)iVar7;
      if (iVar7 < 0) {
        fVar1 = fVar1 + _DAT_00470b98;
      }
      if (local_c <= fVar1) {
        iVar7 = *(int *)(DAT_00491fac + 0xd8) + *(int *)(DAT_00491fac + 0xd0);
        fVar1 = (float)iVar7;
        if (iVar7 < 0) {
          fVar1 = fVar1 + _DAT_00470b98;
        }
        if (local_8 <= fVar1) {
          iVar7 = *(int *)(*(int *)(in_EAX + 0x394) + 4);
          if (*(int *)((int)this + 0x3ada64) != iVar7) {
            *(int *)((int)this + 0x3ada64) = iVar7;
            FUN_00442f50();
            (**(code **)(*(int *)g_pD3DDevice + 0x104))
                      (g_pD3DDevice,0,*(undefined4 *)((int)this + 0x3ada64));
          }
          if (*(char *)((int)this + 0x3ada6a) != '\x01') {
            FUN_00442f50();
            *(undefined1 *)((int)this + 0x3ada6a) = 1;
          }
          uVar8 = DAT_004978d0;
          uVar4 = _DAT_004978ec;
          uVar5 = _DAT_00497908;
          uVar6 = _DAT_00497924;
          if ((bVar3 & 2) == 0) {
            if ((char)((uint)*(undefined4 *)(in_EAX + 0x35c) >> 8) < '\0') {
              uVar8 = *(undefined4 *)(in_EAX + 0x300);
            }
            else {
              uVar8 = *(undefined4 *)(in_EAX + 0x2fc);
            }
            uVar4 = uVar8;
            uVar5 = uVar8;
            uVar6 = uVar8;
            if (*(int *)((int)this + 0x73245c) != 0) {
              uVar9 = FUN_004423c0(CONCAT31((int3)((uint)*(int *)((int)this + 0x73245c) >> 8),
                                            *(undefined1 *)((int)this + 0x73245a)));
              uVar10 = FUN_004423c0(CONCAT31((int3)((uint)extraout_ECX >> 8),
                                             *(undefined1 *)((int)this + 0x732459)));
              uVar11 = FUN_004423c0(CONCAT31((int3)((uint)extraout_ECX_00 >> 8),
                                             *(undefined1 *)((int)this + 0x732458)));
              uVar12 = FUN_004423c0(CONCAT31((int3)((uint)extraout_ECX_01 >> 8),
                                             *(undefined1 *)((int)this + 0x73245b)));
              uVar8 = CONCAT13((char)uVar12,
                               (int3)CONCAT31(CONCAT21((short)uVar9,(char)uVar10),(char)uVar11));
              uVar4 = uVar8;
              uVar5 = uVar8;
              uVar6 = uVar8;
            }
          }
          _DAT_00497924 = uVar6;
          _DAT_00497908 = uVar5;
          _DAT_004978ec = uVar4;
          DAT_004978d0 = uVar8;
          FUN_004425a0();
          FUN_00442fe0(extraout_ECX_02,&DAT_004978c0);
        }
      }
    }
  }
  return 0;
}

