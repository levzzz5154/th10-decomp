/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x0044CBF0
 * Tracking name: FUN_0044cbf0
 * Ghidra name: FUN_0044cbf0
 * Tracked span: 656 bytes
 */


/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

undefined4 __fastcall
FUN_0044cbf0(int *param_1,uint param_2,int *param_3,undefined4 param_4,undefined4 param_5,
            undefined4 param_6,undefined4 param_7,undefined4 param_8,undefined4 param_9,
            undefined4 param_10,uint param_11,int param_12,undefined4 param_13)

{
  undefined4 *puVar1;
  int iVar2;
  void *_Memory;
  uint uVar3;
  int iVar4;
  uint *puVar5;
  undefined4 *puVar6;
  uint *puVar7;
  int *local_58;
  undefined4 *local_54;
  int *local_50;
  int *local_4c;
  void *pvStack_48;
  uint local_44 [5];
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  uint local_10;
  void *local_c;
  undefined1 *puStack_8;
  undefined4 uStack_4;
  
  uStack_4 = 0xffffffff;
  puStack_8 = &LAB_0046531b;
  local_c = ExceptionList;
  local_10 = DAT_00473660 ^ (uint)&local_58;
  local_1c = param_8;
  local_14 = param_10;
  local_20 = param_7;
  local_50 = param_3;
  local_18 = param_9;
  if (*param_3 == 0) {
    return 0x800401f0;
  }
  local_54 = (undefined4 *)0x0;
  local_58 = (int *)0x0;
  ExceptionList = &local_c;
  local_4c = param_1;
  puVar1 = operator_new(0x94);
  puVar6 = (undefined4 *)0x0;
  if (puVar1 != (undefined4 *)0x0) {
    puVar1[0x24] = 0;
    *puVar1 = 0;
    puVar1[0xb] = 0;
    puVar1[0x1f] = 0;
    puVar6 = puVar1;
  }
  puVar6[0x24] = param_6;
  puVar6[0x22] = param_5;
  puVar6[0x20] = param_4;
  puVar6[0x21] = param_4;
  puVar6[0x1f] = 1;
  local_44[3] = 0;
  local_30 = local_20;
  local_28 = local_18;
  local_2c = local_1c;
  local_44[0] = 0x24;
  local_44[1] = param_2 | 0x18188;
  local_24 = local_14;
  local_44[4] = puVar6[0x24] + 0x20;
  local_44[2] = param_11 * param_12;
  iVar2 = (**(code **)(*(int *)*local_50 + 0xc))((int *)*local_50,local_44,&local_54,0);
  if ((-1 < iVar2) && (iVar2 = (**(code **)*local_54)(local_54,&DAT_0046743c,&local_58), -1 < iVar2)
     ) {
    _Memory = operator_new(param_11 * 8);
    if (_Memory == (void *)0x0) {
      ExceptionList = local_c;
      return 0x8007000e;
    }
    uVar3 = 0;
    if (param_11 != 0) {
      iVar2 = param_12 + -1;
      do {
        *(undefined4 *)((int)_Memory + uVar3 * 8 + 4) = param_13;
        *(int *)((int)_Memory + uVar3 * 8) = iVar2;
        uVar3 = uVar3 + 1;
        iVar2 = iVar2 + param_12;
      } while (uVar3 < param_11);
    }
    iVar2 = (**(code **)(*local_58 + 0xc))(local_58,param_11,_Memory);
    if (-1 < iVar2) {
      if (local_58 != (int *)0x0) {
        (**(code **)(*local_58 + 8))(local_58);
        local_58 = (int *)0x0;
      }
      _free(_Memory);
      pvStack_48 = operator_new(0x78);
      uStack_4 = 0;
      if (pvStack_48 == (void *)0x0) {
        iVar2 = 0;
      }
      else {
        iVar2 = FUN_0044d6a0(local_54,param_11 * param_12,puVar6);
      }
      *local_4c = iVar2;
      puVar5 = local_44;
      puVar7 = (uint *)(iVar2 + 0x34);
      for (iVar4 = 9; iVar4 != 0; iVar4 = iVar4 + -1) {
        *puVar7 = *puVar5;
        puVar5 = puVar5 + 1;
        puVar7 = puVar7 + 1;
      }
      *(int **)(*local_4c + 0x58) = local_50;
      *(undefined4 *)(*local_4c + 0x70) = param_13;
      *(undefined4 *)(*local_4c + 0x74) = 0;
      ExceptionList = local_c;
      return 0;
    }
    if (local_58 != (int *)0x0) {
      (**(code **)(*local_58 + 8))(local_58);
      local_58 = (int *)0x0;
    }
    _free(_Memory);
  }
  ExceptionList = local_c;
  return 0x80004005;
}

