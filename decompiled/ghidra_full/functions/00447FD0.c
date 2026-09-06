/* Raw Ghidra reference; not compilable reconstruction. Address: 00447FD0 */

void FUN_00447fd0(void)

{
  undefined4 *puVar1;
  int in_EAX;
  int iVar2;
  int iVar3;
  int unaff_EBX;
  int *piVar4;
  undefined4 uStack_2c;
  undefined4 uStack_28;
  undefined1 *puStack_24;
  undefined4 local_1c;
  undefined4 uStack_18;
  undefined1 *puStack_10;
  undefined4 uStack_8;
  undefined4 uStack_4;
  
  puStack_24 = (undefined1 *)&local_1c;
  if (*(int *)(unaff_EBX + 0x3ad560 + in_EAX * 4) != 0) {
    uStack_28 = 0;
    uStack_2c = 0;
    iVar2 = (**(code **)(*(int *)g_pD3DDevice + 0x48))(g_pD3DDevice);
    if (iVar2 != 0) {
      return;
    }
    puVar1 = (undefined4 *)(unaff_EBX + 0x3ad4e0 + in_EAX * 4);
    if (*(int *)(unaff_EBX + 0x3ad4e0 + in_EAX * 4) == 0) {
      iVar2 = in_EAX * 0x1c + unaff_EBX;
      iVar3 = (**(code **)(*(int *)g_pD3DDevice + 0x70))
                        (g_pD3DDevice,*(undefined4 *)(iVar2 + 0x3ad6e0),
                         *(undefined4 *)(iVar2 + 0x3ad6e4),DAT_00491d14,0,0,1,puVar1,0);
      if (((iVar3 != 0) &&
          (iVar2 = (**(code **)(*(int *)g_pD3DDevice + 0x90))
                             (g_pD3DDevice,*(undefined4 *)(iVar2 + 0x3ad6e0),
                              *(undefined4 *)(iVar2 + 0x3ad6e4),DAT_00491d14,3,puVar1,0), iVar2 != 0
          )) || (iVar2 = D3DXLoadSurfaceFromSurface
                                   (*puVar1,0,0,*(undefined4 *)(unaff_EBX + 0x3ad560 + in_EAX * 4),0
                                    ,0,1,0), iVar2 != 0)) {
        (**(code **)(iRam00000000 + 8))(0);
        return;
      }
    }
    local_1c = *(undefined4 *)(in_EAX * 0x1c + 0x3ad6e0 + unaff_EBX);
    puStack_24 = puStack_10;
    uStack_18 = *(undefined4 *)(in_EAX * 0x1c + unaff_EBX + 0x3ad6e4);
    uStack_28 = uStack_4;
    piVar4 = (int *)0x0;
    uStack_2c = uStack_8;
    (**(code **)(*(int *)g_pD3DDevice + 0x78))(g_pD3DDevice,*puVar1,&puStack_24,0,&uStack_2c);
    (**(code **)(*piVar4 + 8))(piVar4);
  }
  return;
}

