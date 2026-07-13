/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x004450E0
 * Tracking name: FUN_004450e0
 * Ghidra name: FUN_004450e0
 * Tracked span: 224 bytes
 */


undefined4 __fastcall FUN_004450e0(int param_1)

{
  int iVar1;
  int in_EAX;
  undefined4 uVar2;
  void *pvVar3;
  
  if (*(int *)(param_1 + 0x3adac8) != 0) {
    FUN_00442f50();
  }
  if (*(char *)(param_1 + 0x3ada6a) != '\x03') {
    (**(code **)(*(int *)g_pD3DDevice + 0x164))(g_pD3DDevice,0x144);
    *(undefined1 *)(param_1 + 0x3ada6a) = 3;
  }
  FUN_004425a0();
  iVar1 = *(int *)(*(int *)(in_EAX + 0x394) + 4);
  if (*(int *)(param_1 + 0x3ada64) != iVar1) {
    *(int *)(param_1 + 0x3ada64) = iVar1;
    (**(code **)(*(int *)g_pD3DDevice + 0x104))(g_pD3DDevice,0,iVar1);
  }
  FUN_00442f50();
  (**(code **)(*(int *)g_pD3DDevice + 0xe4))(g_pD3DDevice,0xe,0);
  pvVar3 = g_pD3DDevice;
  (**(code **)(*(int *)g_pD3DDevice + 0x10c))(g_pD3DDevice,0,6,0);
  uVar2 = 0;
  (**(code **)(*(int *)g_pD3DDevice + 0x10c))(g_pD3DDevice,0,3,0);
  (**(code **)(*(int *)g_pD3DDevice + 0x14c))(g_pD3DDevice,6,(int)pvVar3 + -2,uVar2,0x1c);
  return 0;
}

