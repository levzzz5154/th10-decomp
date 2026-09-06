/* Raw Ghidra reference; not compilable reconstruction. Address: 00402CA0 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_00402ca0(int param_1)

{
  undefined4 uVar1;
  void *pvVar2;
  int iVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  
  if ((*(uint *)(param_1 + 0x2a18) & 8) == 0) {
    if (((*(uint *)(param_1 + 0x2a18) & 4) == 0) || (*(int *)(param_1 + 0x2a20) < 0x3c)) {
      FUN_00442f50();
      *(undefined4 *)(param_1 + 0x2b34) = DAT_00491e64;
      *(undefined4 *)(param_1 + 0x2b38) = DAT_00491e68;
      puVar4 = (undefined4 *)(param_1 + 0x2a4c);
      puVar5 = &DAT_00491d7c;
      for (iVar3 = 0x46; iVar3 != 0; iVar3 = iVar3 + -1) {
        *puVar5 = *puVar4;
        puVar4 = puVar4 + 1;
        puVar5 = puVar5 + 1;
      }
      DAT_00491fac = &DAT_00491d7c;
      FUN_004215a0();
      (**(code **)(*(int *)g_pD3DDevice + 0xbc))(g_pD3DDevice,DAT_00491fac + 0x33);
      _DAT_00491fb0 = 0;
      if (DAT_00492378 != 1) {
        FUN_00442f50();
        DAT_00492378 = 1;
        (**(code **)(*(int *)g_pD3DDevice + 0xe4))(g_pD3DDevice,0x1c,1);
      }
      FUN_00442f50();
      (**(code **)(*(int *)g_pD3DDevice + 0xe4))(g_pD3DDevice,0xe,0);
      FUN_00442f50();
      (**(code **)(*(int *)g_pD3DDevice + 0xe4))(g_pD3DDevice,0x17,8);
      FUN_00448980();
      FUN_00442f50();
      (**(code **)(*(int *)g_pD3DDevice + 0xe4))(g_pD3DDevice,0x17,4);
      if (DAT_00492378 != 0) {
        FUN_00442f50();
        DAT_00492378 = 0;
        (**(code **)(*(int *)g_pD3DDevice + 0xe4))(g_pD3DDevice,0x1c,0);
      }
      FUN_00448980();
      FUN_00442f50();
      (**(code **)(*(int *)g_pD3DDevice + 0xe4))(g_pD3DDevice,0x17,4);
      uVar1 = *(undefined4 *)(param_1 + 0x2b60);
      FUN_00442f50();
      (**(code **)(*(int *)g_pD3DDevice + 0xe4))(g_pD3DDevice,0x22,uVar1);
      uVar1 = *(undefined4 *)(param_1 + 0x2b48);
      FUN_00442f50();
      (**(code **)(*(int *)g_pD3DDevice + 0xe4))(g_pD3DDevice,0x24,uVar1);
      uVar1 = *(undefined4 *)(param_1 + 0x2b4c);
      FUN_00442f50();
      (**(code **)(*(int *)g_pD3DDevice + 0xe4))(g_pD3DDevice,0x25,uVar1);
    }
    if (((*(uint *)(param_1 + 0x2a18) & 4) != 0) && (0x1d < *(int *)(param_1 + 0x2a20))) {
      *(undefined1 *)(param_1 + 0x1eeb) = 0;
    }
    if ((*(uint *)(param_1 + 0x2a18) & 1) != 0) {
      FUN_00442f50();
      (**(code **)(*(int *)g_pD3DDevice + 0xe4))(g_pD3DDevice,0xe,0);
      if (DAT_00492378 != 1) {
        FUN_00442f50();
        DAT_00492378 = 1;
        (**(code **)(*(int *)g_pD3DDevice + 0xe4))(g_pD3DDevice,0x1c,1);
      }
      FUN_00403a30(param_1);
      FUN_00403a30(param_1);
      FUN_00403a30(param_1);
      FUN_00403a30(param_1);
      FUN_00442f50();
    }
    pvVar2 = g_pGameStateManager;
    *(undefined4 *)((int)g_pGameStateManager + 0x73245c) = 0;
    *(undefined4 *)((int)pvVar2 + 0x732458) = 0x80808080;
    if (*(int *)(param_1 + 0x1eec) != 0) {
      *(undefined4 *)((int)pvVar2 + 0x73245c) = 1;
      *(undefined4 *)((int)pvVar2 + 0x732458) = 0xff404040;
    }
    FUN_00442f50();
    (**(code **)(*(int *)g_pD3DDevice + 0xe4))(g_pD3DDevice,0xe,0);
    FUN_00442f50();
    (**(code **)(*(int *)g_pD3DDevice + 0xe4))(g_pD3DDevice,0x17,8);
    if ((0 < *(int *)(param_1 + 0x2a20)) && (FUN_0044bf40(-1.0), *(int *)(param_1 + 0x2a20) < 1)) {
      *(undefined1 *)(param_1 + 0x1eeb) = 0xff;
      if ((*(uint *)(param_1 + 0x2a18) & 2) != 0) {
        *(uint *)(param_1 + 0x2a18) = *(uint *)(param_1 + 0x2a18) | 8;
      }
      *(undefined4 *)(param_1 + 0x1ee8) = 0xffffff;
      *(uint *)(param_1 + 0x2a18) = *(uint *)(param_1 + 0x2a18) & 0xfffffff9;
    }
    FUN_00442f50();
    (**(code **)(*(int *)g_pD3DDevice + 0xe4))(g_pD3DDevice,0xe,0);
    FUN_00442f50();
    (**(code **)(*(int *)g_pD3DDevice + 0xe4))(g_pD3DDevice,0x17,8);
    if (DAT_00492378 != 0) {
      FUN_00442f50();
      DAT_00492378 = 0;
      (**(code **)(*(int *)g_pD3DDevice + 0xe4))(g_pD3DDevice,0x1c,0);
    }
    return 1;
  }
  return 1;
}

