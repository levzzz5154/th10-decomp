/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x00401A50
 * Tracking name: FUN_00401a50
 * Ghidra name: FUN_00401a50
 * Tracked span: 720 bytes
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_00401a50(void)

{
  byte *pbVar1;
  int iVar2;
  float fVar3;
  byte bVar4;
  undefined4 uVar5;
  int iVar6;
  bool bVar7;
  int unaff_EBX;
  byte *pbVar8;
  byte *pbVar9;
  int local_10;
  int local_4;
  
  *(uint *)(unaff_EBX + 0x370) = *(uint *)(unaff_EBX + 0x370) & 0xffd7ffff | 0x140001;
  local_10 = 1;
  pbVar8 = (byte *)(unaff_EBX + 0x6f6c);
  local_4 = 0;
  if (0 < *(int *)(unaff_EBX + 0x8970)) {
    do {
      *(undefined4 *)(unaff_EBX + 0x348) = *(undefined4 *)(pbVar8 + 0x40);
      *(undefined4 *)(unaff_EBX + 0x34c) = *(undefined4 *)(pbVar8 + 0x44);
      *(undefined4 *)(unaff_EBX + 0x350) = *(undefined4 *)(pbVar8 + 0x48);
      uVar5 = *(undefined4 *)(pbVar8 + 0x50);
      *(undefined4 *)(unaff_EBX + 0x54) = *(undefined4 *)(pbVar8 + 0x54);
      *(undefined4 *)(unaff_EBX + 0x50) = uVar5;
      *(uint *)(unaff_EBX + 0x370) = *(uint *)(unaff_EBX + 0x370) | 8;
      iVar2 = *(int *)(unaff_EBX + 0x898c);
      iVar6 = *(int *)(pbVar8 + 0x5c);
      fVar3 = *(float *)(pbVar8 + 0x50);
      if (local_10 != iVar6) {
        FUN_00442f50();
        if (iVar6 == 0) {
          DAT_00491fac = (undefined4 *)&DAT_00491e94;
          FUN_004215a0();
          (**(code **)(*(int *)g_pD3DDevice + 0xbc))(g_pD3DDevice,DAT_00491fac + 0x33);
        }
        else {
          DAT_00491fac = &DAT_00491d7c;
          FUN_004215a0();
          (**(code **)(*(int *)g_pD3DDevice + 0xbc))(g_pD3DDevice,DAT_00491fac + 0x33);
        }
        _DAT_00491fb0 = (uint)(iVar6 == 0);
        local_10 = iVar6;
      }
      bVar4 = *pbVar8;
      pbVar9 = pbVar8;
      while (bVar4 != 0) {
        bVar4 = *pbVar9;
        if (bVar4 == 10) {
          *(float *)(unaff_EBX + 0x34c) =
               *(float *)(pbVar8 + 0x54) * _DAT_00470c88 + *(float *)(unaff_EBX + 0x34c);
          *(undefined4 *)(unaff_EBX + 0x348) = *(undefined4 *)(pbVar8 + 0x40);
        }
        else {
          if (bVar4 != 0x20) {
            bVar7 = *(float *)(unaff_EBX + 0x50) == _DAT_00470afc;
            *(uint *)(unaff_EBX + 0x3a8) =
                 (bVar4 - 0x20) * 0x44 + *(int *)(*(int *)(unaff_EBX + 0x8994) + 0x118);
            *(undefined4 *)(unaff_EBX + 0x310) = *(undefined4 *)(pbVar8 + 0x4c);
            if (bVar7) {
              FUN_00443080(g_pGameStateManager);
            }
            else {
              FUN_00443290(g_pGameStateManager);
            }
          }
          *(float *)(unaff_EBX + 0x348) = (float)iVar2 * fVar3 + *(float *)(unaff_EBX + 0x348);
        }
        pbVar1 = pbVar9 + 1;
        pbVar9 = pbVar9 + 1;
        bVar4 = *pbVar1;
      }
      local_4 = local_4 + 1;
      pbVar8 = pbVar8 + 0x68;
    } while (local_4 < *(int *)(unaff_EBX + 0x8970));
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

