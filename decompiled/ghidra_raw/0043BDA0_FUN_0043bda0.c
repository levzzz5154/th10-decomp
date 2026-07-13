/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x0043BDA0
 * Tracking name: FUN_0043bda0
 * Ghidra name: FUN_0043bda0
 * Tracked span: 512 bytes
 */


void FUN_0043bda0(void)

{
  void *pvVar1;
  undefined4 uStack_a4;
  void *pvStack_a0;
  undefined4 uStack_9c;
  undefined4 uStack_98;
  undefined4 uStack_94;
  void *pvStack_90;
  undefined4 uStack_8c;
  undefined4 uStack_88;
  undefined4 uStack_84;
  void *pvStack_80;
  undefined4 uStack_7c;
  undefined4 uStack_78;
  undefined4 uStack_74;
  void *pvStack_70;
  undefined4 uStack_6c;
  undefined4 uStack_68;
  undefined4 uStack_64;
  
  uStack_64 = 0x43bdaf;
  FUN_00442f50();
  uStack_64 = 2;
  uStack_68 = 4;
  uStack_6c = 0;
  pvStack_70 = g_pD3DDevice;
  uStack_74 = 0x43be94;
  (**(code **)(*(int *)g_pD3DDevice + 0x10c))();
  uStack_74 = 2;
  uStack_78 = 1;
  uStack_7c = 0;
  pvStack_80 = g_pD3DDevice;
  uStack_84 = 0x43bea7;
  (**(code **)(*(int *)g_pD3DDevice + 0x10c))();
  uStack_84 = 0;
  uStack_88 = 5;
  uStack_8c = 0;
  pvStack_90 = g_pD3DDevice;
  uStack_94 = 0x43beb9;
  (**(code **)(*(int *)g_pD3DDevice + 0x10c))();
  uStack_94 = 0;
  uStack_98 = 2;
  uStack_9c = 0;
  pvStack_a0 = g_pD3DDevice;
  uStack_a4 = 0x43becb;
  (**(code **)(*(int *)g_pD3DDevice + 0x10c))();
  uStack_a4 = 6;
  (**(code **)(*(int *)g_pD3DDevice + 0xe4))(g_pD3DDevice,0x14);
  (**(code **)(*(int *)g_pD3DDevice + 0x164))(g_pD3DDevice,0x44);
  (**(code **)(*(int *)g_pD3DDevice + 0x14c))(g_pD3DDevice,5,2,&uStack_a4,0x14);
  pvVar1 = g_pGameStateManager;
  *(undefined1 *)((int)g_pGameStateManager + 0x3ada6a) = 0xff;
  *(undefined4 *)((int)pvVar1 + 0x3ada70) = 0;
  *(undefined4 *)((int)pvVar1 + 0x3ada64) = 0;
  *(undefined1 *)((int)pvVar1 + 0x3ada69) = 0xff;
  *(undefined1 *)((int)pvVar1 + 0x3ada68) = 3;
  *(undefined1 *)((int)pvVar1 + 0x3ada6b) = 0xff;
  (**(code **)(*(int *)g_pD3DDevice + 0x10c))(g_pD3DDevice,0,4,4);
  (**(code **)(*(int *)g_pD3DDevice + 0x10c))(g_pD3DDevice,0,1,4);
  (**(code **)(*(int *)g_pD3DDevice + 0x10c))(g_pD3DDevice,0,5,2);
  (**(code **)(*(int *)g_pD3DDevice + 0x10c))(g_pD3DDevice,0,2,2);
  return;
}

