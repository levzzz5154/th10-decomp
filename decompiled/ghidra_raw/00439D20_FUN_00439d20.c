/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x00439D20
 * Tracking name: FUN_00439d20
 * Ghidra name: FUN_00439d20
 * Tracked span: 720 bytes
 */


void __fastcall FUN_00439d20(undefined4 param_1)

{
  void *pvVar1;
  
  (**(code **)(*(int *)g_pD3DDevice + 0xe4))(g_pD3DDevice,7,1,param_1);
  (**(code **)(*(int *)g_pD3DDevice + 0xe4))(g_pD3DDevice,0x89,0);
  (**(code **)(*(int *)g_pD3DDevice + 0xe4))(g_pD3DDevice,0x16,1);
  (**(code **)(*(int *)g_pD3DDevice + 0xe4))(g_pD3DDevice,0x1b,1);
  (**(code **)(*(int *)g_pD3DDevice + 0xe4))(g_pD3DDevice,9,2);
  (**(code **)(*(int *)g_pD3DDevice + 0xe4))(g_pD3DDevice,0x13,5);
  (**(code **)(*(int *)g_pD3DDevice + 0xe4))(g_pD3DDevice,0x14,6);
  (**(code **)(*(int *)g_pD3DDevice + 0xe4))(g_pD3DDevice,0x17,8);
  (**(code **)(*(int *)g_pD3DDevice + 0xe4))(g_pD3DDevice,0xf,1);
  (**(code **)(*(int *)g_pD3DDevice + 0xe4))(g_pD3DDevice,0x18,1);
  (**(code **)(*(int *)g_pD3DDevice + 0xe4))(g_pD3DDevice,0x19,7);
  (**(code **)(*(int *)g_pD3DDevice + 0xe4))(g_pD3DDevice,0x1c,1);
  (**(code **)(*(int *)g_pD3DDevice + 0xe4))(g_pD3DDevice,0x26,0x3f800000);
  (**(code **)(*(int *)g_pD3DDevice + 0xe4))(g_pD3DDevice,0x23,0);
  (**(code **)(*(int *)g_pD3DDevice + 0xe4))(g_pD3DDevice,0x8c,3);
  (**(code **)(*(int *)g_pD3DDevice + 0xe4))(g_pD3DDevice,0x22,0xffa0a0a0);
  (**(code **)(*(int *)g_pD3DDevice + 0xe4))(g_pD3DDevice,0x24,0x447a0000);
  (**(code **)(*(int *)g_pD3DDevice + 0xe4))(g_pD3DDevice,0x25,0x459c4000);
  (**(code **)(*(int *)g_pD3DDevice + 0xe4))(g_pD3DDevice,0xa1,0);
  (**(code **)(*(int *)g_pD3DDevice + 0x10c))(g_pD3DDevice,0,4,4);
  (**(code **)(*(int *)g_pD3DDevice + 0x10c))(g_pD3DDevice,0,5,2);
  (**(code **)(*(int *)g_pD3DDevice + 0x10c))(g_pD3DDevice,0,6,3);
  (**(code **)(*(int *)g_pD3DDevice + 0x10c))(g_pD3DDevice,0,1,4);
  (**(code **)(*(int *)g_pD3DDevice + 0x10c))(g_pD3DDevice,0,2,2);
  (**(code **)(*(int *)g_pD3DDevice + 0x10c))(g_pD3DDevice,0,3,3);
  (**(code **)(*(int *)g_pD3DDevice + 0x10c))(g_pD3DDevice,0,0x18,2);
  (**(code **)(*(int *)g_pD3DDevice + 0x10c))(g_pD3DDevice,0,0xb,0);
  (**(code **)(*(int *)g_pD3DDevice + 0x114))(g_pD3DDevice,0,7,0);
  (**(code **)(*(int *)g_pD3DDevice + 0x114))(g_pD3DDevice,0,5,2);
  (**(code **)(*(int *)g_pD3DDevice + 0x114))(g_pD3DDevice,0,6,2);
  (**(code **)(*(int *)g_pD3DDevice + 0x114))(g_pD3DDevice,0,3,3);
  (**(code **)(*(int *)g_pD3DDevice + 0x114))(g_pD3DDevice,0,1,1);
  (**(code **)(*(int *)g_pD3DDevice + 0x114))(g_pD3DDevice,0,2,1);
  pvVar1 = g_pGameStateManager;
  if (g_pGameStateManager != (void *)0x0) {
    *(undefined1 *)((int)g_pGameStateManager + 0x3ada68) = 3;
    *(undefined1 *)((int)pvVar1 + 0x3ada69) = 0xff;
    *(undefined1 *)((int)pvVar1 + 0x3ada6a) = 0xff;
    *(undefined4 *)((int)pvVar1 + 0x3ada64) = 0;
    *(undefined1 *)((int)pvVar1 + 0x3ada6c) = 0xff;
  }
  return;
}

