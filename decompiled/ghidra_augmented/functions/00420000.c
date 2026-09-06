/* Raw Ghidra reference; not compilable reconstruction. Address: 00420000 */

undefined4 __fastcall FUN_00420000(int param_1)

{
  void *pvVar1;
  
  pvVar1 = g_pGameStateManager;
  *(undefined4 *)((int)g_pGameStateManager + 0x3ada70) = 0;
  *(undefined4 *)((int)pvVar1 + 0x3ada64) = 0;
  *(undefined1 *)((int)pvVar1 + 0x3ada69) = 0xff;
  *(undefined1 *)((int)pvVar1 + 0x3ada68) = 3;
  *(undefined1 *)((int)pvVar1 + 0x3ada6b) = 0xff;
  *(undefined1 *)((int)pvVar1 + 0x3ada6c) = 0xff;
  *(undefined4 *)((int)pvVar1 + 0x73245c) = 0;
  *(undefined4 *)((int)pvVar1 + 0x732458) = 0x80808080;
  *(undefined1 *)((int)pvVar1 + 0x3ada6e) = 0xff;
  *(undefined4 *)((int)pvVar1 + 0x60) = 0;
  *(undefined4 *)((int)pvVar1 + 0x5c) = 0;
  *(undefined1 *)((int)pvVar1 + 0x3ada6a) = 0xff;
  *(int *)(param_1 + 900) = param_1 + 0x26c;
  FUN_004215a0();
  (**(code **)(**(int **)(param_1 + 8) + 0xbc))
            (*(int **)(param_1 + 8),*(int *)(param_1 + 900) + 0xcc);
  *(undefined4 *)(param_1 + 0x388) = 1;
  (**(code **)(*(int *)g_pD3DDevice + 0xac))(g_pD3DDevice,0,0,1,DAT_004923a8,0x3f800000,0);
  return 1;
}

