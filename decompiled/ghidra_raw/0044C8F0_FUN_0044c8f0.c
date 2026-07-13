/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x0044C8F0
 * Tracking name: FUN_0044c8f0
 * Ghidra name: FUN_0044c8f0
 * Tracked span: 768 bytes
 */


/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

undefined4 __fastcall
FUN_0044c8f0(int *param_1,uint param_2,int *param_3,LPCSTR param_4,undefined4 param_5,
            undefined4 param_6,undefined4 param_7,undefined4 param_8,uint param_9,int param_10,
            undefined4 param_11,int param_12)

{
  undefined4 *_Memory;
  int iVar1;
  void *_Memory_00;
  uint uVar2;
  int iVar3;
  uint *puVar4;
  uint *puVar5;
  int *local_5c;
  undefined4 *local_58;
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
  puStack_8 = &LAB_0046533b;
  local_c = ExceptionList;
  local_10 = DAT_00473660 ^ (uint)&local_5c;
  local_20 = param_5;
  local_1c = param_6;
  local_18 = param_7;
  local_14 = param_8;
  local_50 = param_3;
  if (*param_3 == 0) {
    return 0x800401f0;
  }
  local_54 = (undefined4 *)0x0;
  local_5c = (int *)0x0;
  ExceptionList = &local_c;
  local_4c = param_1;
  local_58 = operator_new(0x94);
  if (local_58 == (undefined4 *)0x0) {
    local_58 = (undefined4 *)0x0;
  }
  else {
    local_58[0x24] = 0;
    *local_58 = 0;
    local_58[0xb] = 0;
    local_58[0x1f] = 0;
  }
  _Memory = local_58;
  iVar1 = FUN_0044dbf0(param_4,param_12);
  if (iVar1 == 0) {
    local_44[3] = 0;
    local_30 = local_20;
    local_2c = local_1c;
    local_24 = local_14;
    local_28 = local_18;
    local_44[0] = 0x24;
    local_44[1] = param_2 | 0x18188;
    local_44[4] = local_58[0x24] + 0x20;
    local_44[2] = param_9 * param_10;
    iVar1 = (**(code **)(*(int *)*local_50 + 0xc))((int *)*local_50,local_44,&local_54,0);
    if ((-1 < iVar1) &&
       (iVar1 = (**(code **)*local_54)(local_54,&DAT_0046743c,&local_5c), -1 < iVar1)) {
      _Memory_00 = operator_new(param_9 * 8);
      if (_Memory_00 == (void *)0x0) {
        ExceptionList = local_c;
        return 0x8007000e;
      }
      uVar2 = 0;
      if (param_9 != 0) {
        iVar1 = param_10 + -1;
        do {
          *(int *)((int)_Memory_00 + uVar2 * 8) = iVar1;
          *(undefined4 *)((int)_Memory_00 + uVar2 * 8 + 4) = param_11;
          uVar2 = uVar2 + 1;
          iVar1 = iVar1 + param_10;
        } while (uVar2 < param_9);
      }
      iVar1 = (**(code **)(*local_5c + 0xc))(local_5c,param_9,_Memory_00);
      if (-1 < iVar1) {
        if (local_5c != (int *)0x0) {
          (**(code **)(*local_5c + 8))(local_5c);
          local_5c = (int *)0x0;
        }
        _free(_Memory_00);
        pvStack_48 = operator_new(0x78);
        uStack_4 = 0;
        if (pvStack_48 == (void *)0x0) {
          iVar1 = 0;
        }
        else {
          iVar1 = FUN_0044d6a0(local_54,param_9 * param_10,local_58);
        }
        *local_4c = iVar1;
        puVar4 = local_44;
        puVar5 = (uint *)(iVar1 + 0x34);
        for (iVar3 = 9; iVar3 != 0; iVar3 = iVar3 + -1) {
          *puVar5 = *puVar4;
          puVar4 = puVar4 + 1;
          puVar5 = puVar5 + 1;
        }
        *(int **)(*local_4c + 0x58) = local_50;
        *(undefined4 *)(*local_4c + 0x70) = param_11;
        *(undefined4 *)(*local_4c + 0x74) = 0;
        ExceptionList = local_c;
        return 0;
      }
      if (local_5c != (int *)0x0) {
        (**(code **)(*local_5c + 8))(local_5c);
        local_5c = (int *)0x0;
      }
      _free(_Memory_00);
    }
  }
  else if (_Memory != (undefined4 *)0x0) {
    if (_Memory[0x1e] == 1) {
      CloseHandle((HANDLE)_Memory[0x23]);
      _Memory[0x23] = 0xffffffff;
    }
    _free(_Memory);
    ExceptionList = local_c;
    return 0x80004005;
  }
  ExceptionList = local_c;
  return 0x80004005;
}

