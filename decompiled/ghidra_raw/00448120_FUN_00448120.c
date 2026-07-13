/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x00448120
 * Tracking name: FUN_00448120
 * Ghidra name: FUN_00448120
 * Tracked span: 336 bytes
 */


void FUN_00448120(int param_1,undefined4 param_2)

{
  undefined4 *puVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int unaff_EBX;
  undefined4 uStack_2c;
  undefined4 uStack_28;
  int *piStack_24;
  int *piStack_20;
  int *piStack_10;
  int *piStack_4;
  
  iVar4 = param_1;
  if (*(int *)(param_1 + 0x3ad560 + unaff_EBX * 4) != 0) {
    piStack_20 = &param_1;
    piStack_24 = (int *)0x0;
    uStack_28 = 0;
    uStack_2c = 0;
    iVar2 = (**(code **)(*(int *)g_pD3DDevice + 0x48))(g_pD3DDevice);
    if (iVar2 != 0) {
      return;
    }
    puVar1 = (undefined4 *)(iVar4 + 0x3ad4e0 + unaff_EBX * 4);
    if (*(int *)(iVar4 + 0x3ad4e0 + unaff_EBX * 4) == 0) {
      iVar2 = unaff_EBX * 0x1c + iVar4;
      iVar3 = (**(code **)(*(int *)g_pD3DDevice + 0x70))
                        (g_pD3DDevice,*(undefined4 *)(iVar2 + 0x3ad6e0),
                         *(undefined4 *)(iVar2 + 0x3ad6e4),DAT_00491d14,0,0,1,puVar1,0);
      if (((iVar3 != 0) &&
          (iVar2 = (**(code **)(*(int *)g_pD3DDevice + 0x90))
                             (g_pD3DDevice,*(undefined4 *)(iVar2 + 0x3ad6e0),
                              *(undefined4 *)(iVar2 + 0x3ad6e4),DAT_00491d14,3,puVar1,0), iVar2 != 0
          )) || (iVar4 = D3DXLoadSurfaceFromSurface
                                   (*puVar1,0,0,*(undefined4 *)(iVar4 + 0x3ad560 + unaff_EBX * 4),0,
                                    0,1,0), iVar4 != 0)) {
        (**(code **)(*piStack_10 + 8))(piStack_10);
        return;
      }
    }
    piStack_24 = piStack_4;
    (**(code **)(*(int *)g_pD3DDevice + 0x78))
              (g_pD3DDevice,*puVar1,&piStack_24,piStack_10,&uStack_2c);
    (**(code **)(*piStack_24 + 8))(piStack_24);
  }
  return;
}

