
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 __thiscall
FUN_0041bb00(void *this,int param_1,undefined4 param_2,float param_3,float param_4)

{
  float *pfVar1;
  void *this_00;
  int in_EAX;
  int iVar2;
  uint uVar3;
  void *extraout_ECX;
  void *this_01;
  void *extraout_ECX_00;
  int extraout_EDX;
  int iVar4;
  
  if (param_1 == 8) {
    uVar3 = *(uint *)(in_EAX + 0x21ceb8);
    iVar4 = *(int *)(in_EAX + 0x21cebc) + 1;
    iVar2 = uVar3 * 0x3f0 + 0x24eb4 + in_EAX;
    *(int *)(in_EAX + 0x21cebc) = iVar4;
    if (*(int *)(iVar2 + 0x3dc) == 0) {
      if (iVar4 < 0x400) {
        if (iVar4 < 0x200) {
          if (iVar4 < 0x100) {
            uVar3 = uVar3 & 0x80000003;
            if ((int)uVar3 < 0) {
              uVar3 = (uVar3 - 1 | 0xfffffffc) + 1;
            }
          }
          else {
            uVar3 = uVar3 & 0x80000007;
            if ((int)uVar3 < 0) {
              uVar3 = (uVar3 - 1 | 0xfffffff8) + 1;
            }
            uVar3 = uVar3 + 4;
          }
        }
        else {
          uVar3 = uVar3 & 0x8000000f;
          if ((int)uVar3 < 0) {
            uVar3 = (uVar3 - 1 | 0xfffffff0) + 1;
          }
          uVar3 = uVar3 + 8;
        }
      }
      else {
        uVar3 = uVar3 & 0x8000001f;
        if ((int)uVar3 < 0) {
          uVar3 = (uVar3 - 1 | 0xffffffe0) + 1;
        }
        uVar3 = uVar3 + 0x10;
      }
      *(uint *)(iVar2 + 0x3ec) = uVar3;
      *(undefined4 *)(iVar2 + 0x3e0) = 8;
      *(undefined4 *)(iVar2 + 0x3e4) = 8;
      *(undefined4 *)(iVar2 + 0x3dc) = 5;
      *(undefined4 *)(iVar2 + 0x3ac) = *(undefined4 *)this;
      *(undefined4 *)(iVar2 + 0x3b0) = *(undefined4 *)((int)this + 4);
      *(undefined4 *)(iVar2 + 0x3b4) = *(undefined4 *)((int)this + 8);
      PolarVector2_0041BEB0::SetScorePolar((PolarVector2_0041BEB0 *)(iVar2 + 0x3b8),param_3,param_4)
      ;
      *(undefined4 *)(extraout_EDX + 0x3c0) = 0;
      if ((*(uint *)(extraout_EDX + 0x3d8) & 1) == 0) {
        *(undefined4 *)(extraout_EDX + 0x3cc) = 0;
        *(undefined4 *)(extraout_EDX + 0x3c8) = 0xfff0bdc1;
        *(undefined4 *)(extraout_EDX + 0x3d0) = 0;
        *(undefined4 **)(extraout_EDX + 0x3d4) = &DAT_00476f78;
        *(uint *)(extraout_EDX + 0x3d8) = *(uint *)(extraout_EDX + 0x3d8) | 1;
      }
      *(undefined4 *)(extraout_EDX + 0x3cc) = 0;
      *(undefined4 *)(extraout_EDX + 0x3d0) = 0;
      *(undefined4 *)(extraout_EDX + 0x3c8) = 0xffffffff;
      *(undefined4 *)(extraout_EDX + 0x3c4) = 0;
    }
    uVar3 = *(int *)(in_EAX + 0x21ceb8) + 1U & 0x800007ff;
    if ((int)uVar3 < 0) {
      uVar3 = (uVar3 - 1 | 0xfffff800) + 1;
    }
    *(uint *)(in_EAX + 0x21ceb8) = uVar3;
    return 0;
  }
  iVar4 = in_EAX + 0x14;
  iVar2 = 0;
  while (*(int *)(iVar4 + 0x3dc) != 0) {
    iVar2 = iVar2 + 1;
    iVar4 = iVar4 + 0x3f0;
    if (0x95 < iVar2) {
      return 0;
    }
  }
  *(undefined4 *)(iVar4 + 0x3dc) = 1;
  pfVar1 = (float *)(iVar4 + 0x3ac);
  *pfVar1 = *(float *)this;
  *(undefined4 *)(iVar4 + 0x3b0) = *(undefined4 *)((int)this + 4);
  *(undefined4 *)(iVar4 + 0x3b4) = *(undefined4 *)((int)this + 8);
  if (*pfVar1 < _DAT_00470b40 == (*pfVar1 == _DAT_00470b40)) {
    if (_DAT_00470b3c <= *pfVar1) {
      *pfVar1 = 192.0;
    }
  }
  else {
    *pfVar1 = -192.0;
  }
  PolarVector2_0041BEB0::SetScorePolar((PolarVector2_0041BEB0 *)(iVar4 + 0x3b8),param_3,param_4);
  *(undefined4 *)(iVar4 + 0x3c0) = 0;
  if ((*(uint *)(iVar4 + 0x3d8) & 1) == 0) {
    *(undefined4 *)(iVar4 + 0x3cc) = 0;
    *(undefined4 *)(iVar4 + 0x3c8) = 0xfff0bdc1;
    *(undefined4 *)(iVar4 + 0x3d0) = 0;
    *(undefined4 **)(iVar4 + 0x3d4) = &DAT_00476f78;
    *(uint *)(iVar4 + 0x3d8) = *(uint *)(iVar4 + 0x3d8) | 1;
  }
  *(undefined4 *)(iVar4 + 0x3cc) = 0;
  *(undefined4 *)(iVar4 + 0x3d0) = 0;
  *(undefined4 *)(iVar4 + 0x3c8) = 0xffffffff;
  *(undefined4 *)(iVar4 + 0x3c4) = 0;
  this_01 = extraout_ECX;
  if ((99 < DAT_00474c48) && (param_1 - 1U < 0xb)) {
    this_01 = (void *)(uint)*(byte *)((int)&PTR_caseD_2_0041be24 + param_1 + 3);
    switch(param_1) {
    case 1:
    case 4:
      param_1 = 9;
      break;
    case 10:
    case 0xb:
      param_1 = 5;
    }
  }
  if (*(int *)(iVar4 + 0x3e0) == 3) {
    FUN_00448db0(*(undefined2 **)((int)DAT_004776f0 + 0x3e0b50));
    this_01 = extraout_ECX_00;
  }
  *(int *)(iVar4 + 0x3e0) = param_1;
  *(int *)(iVar4 + 0x3e4) = param_1;
  this_00 = DAT_004776f0;
  if (param_1 != 10) {
    if (param_1 == 0xb) {
      *(undefined4 *)(iVar4 + 0x3e4) = 4;
    }
    FUN_00404f30(this_00,*(undefined2 **)((int)this_00 + 0x3e0b50));
    *(undefined4 *)(iVar4 + 0x2fc) = param_2;
    return 0;
  }
  *(undefined4 *)(iVar4 + 0x3e4) = 1;
  FUN_00404f30(this_01,*(undefined2 **)((int)this_00 + 0x3e0b50));
  *(undefined4 *)(iVar4 + 0x2fc) = param_2;
  return 0;
}

