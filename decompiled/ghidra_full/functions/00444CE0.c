/* Raw Ghidra reference; not compilable reconstruction. Address: 00444CE0 */

undefined4 __fastcall FUN_00444ce0(int param_1)

{
  int iVar1;
  int in_EAX;
  undefined4 uVar2;
  void *pvVar3;
  
  if (((*(uint *)(in_EAX + 0x35c) & 1) != 0) && ((*(uint *)(in_EAX + 0x35c) & 2) != 0)) {
    if (*(char *)(in_EAX + 0x2ff) == '\0') {
      return 0xffffffff;
    }
    if (*(int *)(param_1 + 0x3adac8) != 0) {
      FUN_00442f50();
    }
    iVar1 = *(int *)(*(int *)(in_EAX + 0x394) + 4);
    if (*(int *)(param_1 + 0x3ada64) != iVar1) {
      *(int *)(param_1 + 0x3ada64) = iVar1;
      (**(code **)(*(int *)g_pD3DDevice + 0x104))(g_pD3DDevice,0,iVar1);
    }
    if (*(char *)(param_1 + 0x3ada6a) != '\x03') {
      (**(code **)(*(int *)g_pD3DDevice + 0x164))(g_pD3DDevice,0x144);
      *(undefined1 *)(param_1 + 0x3ada6a) = 3;
    }
    FUN_004425a0();
    pvVar3 = g_pD3DDevice;
    (**(code **)(*(int *)g_pD3DDevice + 0x10c))(g_pD3DDevice,0,6,0);
    uVar2 = 0;
    (**(code **)(*(int *)g_pD3DDevice + 0x10c))(g_pD3DDevice,0,3,0);
    (**(code **)(*(int *)g_pD3DDevice + 0x14c))(g_pD3DDevice,5,(int)pvVar3 + -2,uVar2,0x1c);
    return 0;
  }
  return 0xffffffff;
}

