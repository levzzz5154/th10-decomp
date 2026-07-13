/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x00402850
 * Tracking name: FUN_00402850
 * Ghidra name: FUN_00402850
 * Tracked span: 1104 bytes
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_00402850(int param_1)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 *puVar3;
  void *pvVar4;
  undefined4 *puVar5;
  int iVar6;
  undefined4 uStack_80;
  undefined4 uStack_7c;
  undefined4 uStack_78;
  void *pvStack_74;
  undefined4 uStack_70;
  undefined4 uStack_6c;
  void *pvStack_68;
  undefined4 uStack_64;
  undefined4 uStack_60;
  void *pvStack_5c;
  undefined4 uStack_58;
  undefined4 uStack_54;
  void *pvStack_50;
  undefined4 *puStack_4c;
  void *pvStack_48;
  
  if ((*(uint *)(param_1 + 0x2a18) & 8) == 0) {
    if (((*(uint *)(param_1 + 0x2a18) & 4) == 0) || (*(int *)(param_1 + 0x2a20) < 0x3c)) {
      FUN_00442f50();
      *(undefined4 *)(param_1 + 0x2b34) = DAT_00491e64;
      *(undefined4 *)(param_1 + 0x2b38) = DAT_00491e68;
      puVar3 = (undefined4 *)(param_1 + 0x2a4c);
      puVar5 = &DAT_00491d7c;
      for (iVar2 = 0x46; iVar2 != 0; iVar2 = iVar2 + -1) {
        *puVar5 = *puVar3;
        puVar3 = puVar3 + 1;
        puVar5 = puVar5 + 1;
      }
      DAT_00491fac = &DAT_00491d7c;
      FUN_004215a0();
      (**(code **)(*(int *)g_pD3DDevice + 0xbc))();
      _DAT_00491fb0 = 0;
      FUN_00442f50();
      pvStack_48 = (void *)0x402906;
      (**(code **)(*(int *)g_pD3DDevice + 0xe4))();
      pvStack_48 = (void *)0x402911;
      FUN_00442f50();
      pvStack_48 = (void *)0x4;
      puStack_4c = (undefined4 *)0x17;
      pvStack_50 = g_pD3DDevice;
      uStack_54 = 0x402923;
      (**(code **)(*(int *)g_pD3DDevice + 0xe4))();
      uVar1 = *(undefined4 *)(param_1 + 0x2b60);
      uStack_54 = 0x402934;
      FUN_00442f50();
      uStack_58 = 0x22;
      pvStack_5c = g_pD3DDevice;
      uStack_60 = 0x402945;
      uStack_54 = uVar1;
      (**(code **)(*(int *)g_pD3DDevice + 0xe4))();
      uVar1 = *(undefined4 *)(param_1 + 0x2b48);
      uStack_60 = 0x402956;
      FUN_00442f50();
      uStack_64 = 0x24;
      pvStack_68 = g_pD3DDevice;
      uStack_6c = 0x402967;
      uStack_60 = uVar1;
      (**(code **)(*(int *)g_pD3DDevice + 0xe4))();
      uVar1 = *(undefined4 *)(param_1 + 0x2b4c);
      uStack_6c = 0x402978;
      FUN_00442f50();
      uStack_70 = 0x25;
      pvStack_74 = g_pD3DDevice;
      uStack_78 = 0x402989;
      uStack_6c = uVar1;
      (**(code **)(*(int *)g_pD3DDevice + 0xe4))();
      uStack_78 = 0;
      uStack_7c = 0x3f800000;
      uStack_80 = 0;
      (**(code **)(*(int *)g_pD3DDevice + 0xac))(g_pD3DDevice,0,0,2);
      if (((*(byte *)(param_1 + 0x2a18) & 4) == 0) || (0x21 < *(int *)(param_1 + 0x2a34))) {
        uStack_70 = 0x20;
        uStack_6c = 0x10;
        pvStack_68 = (void *)0x1a0;
        uStack_64 = 0x1d0;
        (**(code **)(*(int *)g_pD3DDevice + 0xac))
                  (g_pD3DDevice,1,&uStack_70,1,*(uint *)(param_1 + 0x2b60) & 0xffffff,0x3f800000,0);
      }
      else {
        uStack_80 = 0x20;
        uStack_7c = 0x10;
        uStack_78 = 0x1a0;
        pvStack_74 = (void *)0x1d0;
        (**(code **)(*(int *)g_pD3DDevice + 0xac))(g_pD3DDevice,1,&uStack_80,1,0,0x3f800000,0);
      }
    }
    if ((*(uint *)(param_1 + 0x2a18) & 4) != 0) {
      if (*(int *)(param_1 + 0x2a20) < 0x1e) {
        pvStack_48 = (void *)0x402a66;
        FUN_0043c8b0(3,0x1e,0,0,0);
        *(uint *)(param_1 + 0x2a18) = *(uint *)(param_1 + 0x2a18) | 1;
        FUN_00405410(1);
      }
      else {
        *(undefined1 *)(param_1 + 0x1eeb) = 0;
        *(uint *)(param_1 + 0x2a18) = *(uint *)(param_1 + 0x2a18) & 0xfffffffe;
      }
    }
    pvVar4 = g_pGameStateManager;
    if (*(char *)(param_1 + 0x1eeb) != '\0') {
      uVar1 = *(undefined4 *)(param_1 + 0x1ee8);
      *(undefined4 *)((int)g_pGameStateManager + 0x73245c) = 1;
      *(undefined4 *)((int)pvVar4 + 0x732458) = uVar1;
    }
    *(undefined4 *)(param_1 + 0x2a0c) = 0;
    *(undefined4 *)(param_1 + 0x2a10) = 0;
    *(undefined4 *)(param_1 + 0x2a14) = 0;
    if ((*(byte *)(param_1 + 0x2a18) & 1) != 0) {
      if (*(int *)(param_1 + 0x514) != 0) {
        FUN_00405300();
        FUN_00420cd0();
        FUN_00442f50();
        FUN_00442f50();
        (**(code **)(*(int *)g_pD3DDevice + 0xe4))();
        iVar2 = param_1 + 0x180;
        iVar6 = 8;
        do {
          if (*(int *)(iVar2 + 0x394) != 0) {
            FUN_004451c0(g_pGameStateManager);
          }
          iVar2 = iVar2 + 0x3ac;
          iVar6 = iVar6 + -1;
        } while (iVar6 != 0);
        FUN_00442f50();
        pvStack_48 = g_pD3DDevice;
        puStack_4c = (undefined4 *)0x402b6d;
        (**(code **)(*(int *)g_pD3DDevice + 0xe4))();
        DAT_00491fac = &DAT_00491d7c;
        puStack_4c = (undefined4 *)0x402b7d;
        FUN_004215a0();
        puStack_4c = DAT_00491fac + 0x33;
        pvStack_50 = g_pD3DDevice;
        uStack_54 = 0x402b98;
        (**(code **)(*(int *)g_pD3DDevice + 0xbc))();
        _DAT_00491fb0 = 0;
      }
      if (DAT_00492378 != 1) {
        FUN_00442f50();
        DAT_00492378 = 1;
        (**(code **)(*(int *)g_pD3DDevice + 0xe4))();
      }
      FUN_00403a30(param_1);
      FUN_00403a30(param_1);
      FUN_00403a30(param_1);
      FUN_00403a30(param_1);
      FUN_00403a30(param_1);
      FUN_00403a30(param_1);
      FUN_00403a30(param_1);
      FUN_00403a30(param_1);
      FUN_00442f50();
      pvVar4 = g_pGameStateManager;
      if (*(int *)(param_1 + 0x1ee4) != 0) {
        *(int *)(param_1 + 0x1ee4) = *(int *)(param_1 + 0x1ee4) + 1;
      }
    }
    *(undefined4 *)((int)pvVar4 + 0x73245c) = 0;
    *(undefined4 *)((int)pvVar4 + 0x732458) = 0x80808080;
    if (*(int *)(param_1 + 0x1eec) != 0) {
      *(undefined4 *)((int)pvVar4 + 0x73245c) = 1;
      *(undefined4 *)((int)pvVar4 + 0x732458) = 0xff404040;
    }
    FUN_00442f50();
    (**(code **)(*(int *)g_pD3DDevice + 0xe4))();
    FUN_00442f50();
    pvStack_48 = g_pD3DDevice;
    puStack_4c = (undefined4 *)0x402c8f;
    (**(code **)(*(int *)g_pD3DDevice + 0xe4))();
    return 1;
  }
  return 1;
}

