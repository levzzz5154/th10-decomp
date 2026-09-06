/* Raw Ghidra reference; not compilable reconstruction. Address: 00401760 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_00401760(float param_1)

{
  byte *pbVar1;
  byte bVar2;
  undefined4 uVar3;
  float fVar4;
  void *pvVar5;
  float fVar6;
  int iVar7;
  byte *pbVar8;
  byte *pbVar9;
  int local_10;
  float local_8;
  int local_4;
  
  fVar6 = param_1;
  *(uint *)((int)param_1 + 0x370) = *(uint *)((int)param_1 + 0x370) & 0xffd7ffff | 0x140001;
  local_10 = 1;
  pbVar8 = (byte *)((int)param_1 + 0x76c);
  local_4 = 0;
  if (0 < *(int *)((int)param_1 + 0x896c)) {
    do {
      *(undefined4 *)((int)fVar6 + 0x348) = *(undefined4 *)(pbVar8 + 0x40);
      *(undefined4 *)((int)fVar6 + 0x34c) = *(undefined4 *)(pbVar8 + 0x44);
      *(undefined4 *)((int)fVar6 + 0x350) = *(undefined4 *)(pbVar8 + 0x48);
      uVar3 = *(undefined4 *)(pbVar8 + 0x50);
      *(undefined4 *)((int)fVar6 + 0x54) = *(undefined4 *)(pbVar8 + 0x54);
      *(undefined4 *)((int)fVar6 + 0x50) = uVar3;
      *(uint *)((int)fVar6 + 0x370) = *(uint *)((int)fVar6 + 0x370) | 8;
      if (*(int *)(pbVar8 + 0x60) == 1) {
        param_1 = 7.0;
        local_8 = 9.0;
      }
      else {
        local_8 = 14.0;
        param_1 = (float)*(int *)((int)fVar6 + 0x898c) * *(float *)(pbVar8 + 0x50);
      }
      iVar7 = *(int *)(pbVar8 + 0x5c);
      if (local_10 != iVar7) {
        FUN_00442f50();
        if (iVar7 == 0) {
          DAT_00491fac = (undefined4 *)&DAT_00491e94;
          FUN_004215a0();
          (**(code **)(*(int *)g_pD3DDevice + 0xbc))(g_pD3DDevice,DAT_00491fac + 0x33);
        }
        else {
          DAT_00491fac = &DAT_00491d7c;
          FUN_004215a0();
          (**(code **)(*(int *)g_pD3DDevice + 0xbc))(g_pD3DDevice,DAT_00491fac + 0x33);
        }
        _DAT_00491fb0 = (uint)(iVar7 == 0);
        local_10 = iVar7;
      }
      bVar2 = *pbVar8;
      pbVar9 = pbVar8;
      while (bVar2 != 0) {
        bVar2 = *pbVar9;
        if (bVar2 == 10) {
          *(float *)((int)fVar6 + 0x34c) =
               local_8 * *(float *)(pbVar8 + 0x54) + *(float *)((int)fVar6 + 0x34c);
          *(undefined4 *)((int)fVar6 + 0x348) = *(undefined4 *)(pbVar8 + 0x40);
        }
        else {
          if (bVar2 != 0x20) {
            iVar7 = (*(int *)(pbVar8 + 0x60) * 0x62 + -0x20 + (uint)bVar2) * 0x44 +
                    *(int *)(*(int *)((int)fVar6 + 0x8994) + 0x118);
            *(int *)((int)fVar6 + 0x3a8) = iVar7;
            uVar3 = *(undefined4 *)(iVar7 + 0x30);
            *(undefined4 *)((int)fVar6 + 0x60) = *(undefined4 *)(iVar7 + 0x34);
            *(undefined4 *)((int)fVar6 + 100) = uVar3;
            *(uint *)((int)fVar6 + 0x370) = *(uint *)((int)fVar6 + 0x370) | 8;
            pvVar5 = g_pGameStateManager;
            if (*(int *)(pbVar8 + 100) != 0) {
              fVar4 = *(float *)((int)fVar6 + 0x348) + _DAT_00470b08;
              *(uint *)((int)fVar6 + 0x310) = *(uint *)(pbVar8 + 0x4c) & 0xff000000;
              uVar3 = *(undefined4 *)(pbVar8 + 0x4c);
              *(float *)((int)fVar6 + 0x348) = fVar4;
              fVar4 = *(float *)((int)fVar6 + 0x34c) + _DAT_00470b08;
              *(byte *)((int)fVar6 + 0x313) = (byte)((uint)uVar3 >> 0x19);
              *(float *)((int)fVar6 + 0x34c) = fVar4;
              FUN_00443080(pvVar5);
              *(float *)((int)fVar6 + 0x348) = *(float *)((int)fVar6 + 0x348) - _DAT_00470b08;
              *(float *)((int)fVar6 + 0x34c) = *(float *)((int)fVar6 + 0x34c) - _DAT_00470b08;
            }
            pvVar5 = g_pGameStateManager;
            *(undefined4 *)((int)fVar6 + 0x310) = *(undefined4 *)(pbVar8 + 0x4c);
            FUN_00443080(pvVar5);
          }
          *(float *)((int)fVar6 + 0x348) = param_1 + *(float *)((int)fVar6 + 0x348);
        }
        pbVar1 = pbVar9 + 1;
        pbVar9 = pbVar9 + 1;
        bVar2 = *pbVar1;
      }
      local_4 = local_4 + 1;
      pbVar8 = pbVar8 + 0x68;
    } while (local_4 < *(int *)((int)fVar6 + 0x896c));
    if (local_10 == 0) {
      return 1;
    }
  }
  FUN_00442f50();
  DAT_00491fac = (undefined4 *)&DAT_00491e94;
  FUN_004215a0();
  (**(code **)(*(int *)g_pD3DDevice + 0xbc))(g_pD3DDevice,(undefined *)((int)DAT_00491fac + 0xcc));
  _DAT_00491fb0 = 1;
  return 1;
}

