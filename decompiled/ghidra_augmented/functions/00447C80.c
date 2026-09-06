/* Raw Ghidra reference; not compilable reconstruction. Address: 00447C80 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

undefined4 __fastcall FUN_00447c80(int param_1,undefined4 param_2,int param_3)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  int iVar3;
  int iVar4;
  int *local_118;
  byte *local_114;
  undefined4 *local_110;
  size_t local_10c;
  char local_108 [260];
  uint local_4;
  
  local_4 = DAT_00473660 ^ (uint)&local_118;
  local_110 = (undefined4 *)(param_1 + 0x3ad4e0 + param_3 * 4);
  if (*(int *)(param_1 + 0x3ad4e0 + param_3 * 4) != 0) {
    FUN_00447f70();
  }
  local_114 = *(byte **)(param_1 + 0x3ad5e0 + param_3 * 4);
  if (local_114 == (byte *)0x0) {
    _sprintf(local_108,"%s",param_2);
    local_114 = FUN_0044b360(&local_10c,0);
    if (local_114 == (byte *)0x0) {
      FUN_0044b8e0(&DAT_00470150);
      return 0xffffffff;
    }
  }
  else {
    local_10c = *(size_t *)(param_1 + 0x3ad660 + param_3 * 4);
    *(undefined4 *)(param_1 + 0x3ad5e0 + param_3 * 4) = 0;
  }
  iVar3 = (**(code **)(*(int *)g_pD3DDevice + 0x90))
                    (g_pD3DDevice,0x280,0x400,DAT_00491d14,3,&local_118,0);
  if (iVar3 == 0) {
    iVar3 = param_3 * 0x1c + param_1;
    puVar1 = (undefined4 *)(iVar3 + 0x3ad6e0);
    iVar4 = D3DXLoadSurfaceFromFileInMemory(local_118,0,0,local_114,local_10c,0,1,0,puVar1);
    if ((iVar4 == 0) &&
       ((iVar4 = (**(code **)(*(int *)g_pD3DDevice + 0x70))
                           (g_pD3DDevice,*puVar1,*(undefined4 *)(iVar3 + 0x3ad6e4),DAT_00491d14,0,0,
                            1,local_110,0), iVar4 == 0 ||
        (iVar4 = (**(code **)(*(int *)g_pD3DDevice + 0x90))
                           (g_pD3DDevice,*puVar1,*(undefined4 *)(iVar3 + 0x3ad6e4),DAT_00491d14,3,
                            local_110,0), iVar4 == 0)))) {
      puVar2 = (undefined4 *)(param_1 + 0x3ad560 + param_3 * 4);
      iVar3 = (**(code **)(*(int *)g_pD3DDevice + 0x90))
                        (g_pD3DDevice,*puVar1,*(undefined4 *)(iVar3 + 0x3ad6e4),DAT_00491d14,3,
                         puVar2,0);
      if ((iVar3 == 0) &&
         ((iVar3 = D3DXLoadSurfaceFromSurface(*local_110,0,0,local_118,0,0,1,0), iVar3 == 0 &&
          (iVar3 = D3DXLoadSurfaceFromSurface(*puVar2,0,0,local_118,0,0,1,0), iVar3 == 0)))) {
        if (local_118 != (int *)0x0) {
          (**(code **)(*local_118 + 8))(local_118);
          local_118 = (int *)0x0;
        }
        if (local_114 != (byte *)0x0) {
          _free(local_114);
        }
        return 0;
      }
    }
    if (local_118 != (int *)0x0) {
      (**(code **)(*local_118 + 8))(local_118);
      local_118 = (int *)0x0;
    }
    if (local_114 != (byte *)0x0) {
      _free(local_114);
    }
  }
  return 0xffffffff;
}

