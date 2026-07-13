/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x00448270
 * Tracking name: FUN_00448270
 * Ghidra name: FUN_00448270
 * Tracked span: 480 bytes
 */


void __thiscall FUN_00448270(void *this)

{
  int in_EAX;
  int iVar1;
  int unaff_EBX;
  int *piVar2;
  void *pvVar3;
  int iStack_40;
  int iStack_3c;
  int iStack_38;
  undefined1 *puStack_34;
  int iStack_1c;
  int iStack_18;
  int iStack_14;
  int iStack_10;
  int *piStack_8;
  
  if (*(int *)(in_EAX * 0x10 + *(int *)(*(int *)((int)this + unaff_EBX * 4 + 0x3ad06c) + 0x120)) !=
      0) {
    puStack_34 = (undefined1 *)0x44829d;
    FUN_00442f50();
    puStack_34 = &stack0x00000018;
    iStack_38 = 0;
    iStack_3c = 0;
    iStack_40 = 0;
    pvVar3 = g_pD3DDevice;
    iVar1 = (**(code **)(*(int *)g_pD3DDevice + 0x48))(g_pD3DDevice);
    if (iVar1 == 0) {
      piVar2 = *(int **)(in_EAX * 0x10 +
                        *(int *)(*(int *)((int)this + unaff_EBX * 4 + 0x3ad06c) + 0x120));
      iVar1 = (**(code **)(*piVar2 + 0x48))(piVar2,0,&iStack_38);
      if (iVar1 == 0) {
        iStack_40 = iStack_1c;
        iStack_38 = iStack_1c + iStack_14;
        iStack_3c = iStack_18;
        puStack_34 = (undefined1 *)(iStack_18 + iStack_10);
        piVar2 = piStack_8;
        D3DXLoadSurfaceFromSurface(pvVar3,0,&stack0xffffffd0,piStack_8,0,&iStack_40,2,0);
        (**(code **)(*piVar2 + 8))(piVar2);
      }
      (**(code **)(*piStack_8 + 8))(piStack_8);
    }
  }
  return;
}

