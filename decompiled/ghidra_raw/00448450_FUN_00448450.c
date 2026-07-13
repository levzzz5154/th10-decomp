/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x00448450
 * Tracking name: FUN_00448450
 * Ghidra name: FUN_00448450
 * Tracked span: 1040 bytes
 */


void FUN_00448450(int param_1,undefined4 param_2,int param_3,undefined4 param_4,int param_5)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  int in_EAX;
  int *piVar3;
  int iVar4;
  int iVar5;
  undefined4 in_stack_00000024;
  undefined4 uStack_58;
  undefined4 uStack_54;
  undefined4 uStack_50;
  undefined4 *puStack_4c;
  undefined4 uStack_48;
  void *pvStack_44;
  undefined4 uStack_40;
  undefined4 uStack_3c;
  undefined4 uStack_38;
  undefined4 *puStack_34;
  
  puStack_34 = (undefined4 *)0x448464;
  FUN_00442f50();
  puVar1 = (undefined4 *)(in_EAX + 0x3ad4e0 + param_1 * 4);
  if (*(int *)(in_EAX + 0x3ad4e0 + param_1 * 4) != 0) {
    puStack_34 = (undefined4 *)0x44847f;
    FUN_00447f70();
  }
  piVar3 = (int *)(param_3 + param_5);
  puStack_34 = &stack0x00000024;
  uStack_38 = 0;
  uStack_3c = 0;
  uStack_40 = 0;
  pvStack_44 = g_pD3DDevice;
  uStack_48 = 0x4484d9;
  iVar4 = (**(code **)(*(int *)g_pD3DDevice + 0x48))();
  if (iVar4 == 0) {
    uStack_48 = 0;
    uStack_50 = 1;
    uStack_54 = 0;
    iVar5 = param_1 * 0x1c + in_EAX;
    *(int *)(iVar5 + 0x3ad6e0) = param_3;
    *(undefined4 *)(iVar5 + 0x3ad6e4) = in_stack_00000024;
    uStack_58 = 0;
    puStack_4c = puVar1;
    iVar4 = (**(code **)(*(int *)g_pD3DDevice + 0x70))(g_pD3DDevice,param_3);
    if ((iVar4 == 0) ||
       (iVar4 = (**(code **)(*(int *)g_pD3DDevice + 0x90))
                          (g_pD3DDevice,*(undefined4 *)(iVar5 + 0x3ad6e0),
                           *(undefined4 *)(iVar5 + 0x3ad6e4),DAT_00491d14,3,puVar1,0), iVar4 == 0))
    {
      puVar2 = (undefined4 *)(in_EAX + 0x3ad560 + (int)puStack_34 * 4);
      iVar4 = (**(code **)(*(int *)g_pD3DDevice + 0x90))
                        (g_pD3DDevice,*(undefined4 *)(iVar5 + 0x3ad6e0),
                         *(undefined4 *)(iVar5 + 0x3ad6e4),DAT_00491d14,3,puVar2,0);
      if ((iVar4 == 0) &&
         (iVar4 = D3DXLoadSurfaceFromSurface(*puVar1,0,&uStack_48,piVar3,0,&uStack_58,0xffffffff,0),
         iVar4 == 0)) {
        D3DXLoadSurfaceFromSurface(*puVar2,0,0,*puVar1,0,0,0xffffffff,0);
      }
    }
    if (piVar3 != (int *)0x0) {
      (**(code **)(*piVar3 + 8))(piVar3);
    }
    return;
  }
  return;
}

