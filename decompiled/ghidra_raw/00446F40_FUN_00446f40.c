/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x00446F40
 * Tracking name: FUN_00446f40
 * Ghidra name: FUN_00446f40
 * Tracked span: 272 bytes
 */


undefined4 __thiscall FUN_00446f40(void *this,undefined4 param_1,int *param_2)

{
  int in_EAX;
  int iVar1;
  undefined4 *unaff_EBX;
  void **ppvVar2;
  int **ppiVar3;
  void *pvStack_3c;
  undefined4 uStack_38;
  int *piStack_34;
  undefined4 uStack_30;
  undefined4 uStack_2c;
  undefined4 uStack_28;
  undefined4 uStack_24;
  
  if (((byte)DAT_00491d78 & 1) != 0) {
    iVar1 = *(int *)(&DAT_0046f288 + in_EAX * 4);
    if ((iVar1 == 0x15) || (iVar1 == 0)) {
      in_EAX = 5;
    }
    else if (iVar1 == 0x14) {
      in_EAX = 3;
    }
  }
  uStack_28 = *(undefined4 *)(&DAT_0046f288 + in_EAX * 4);
  uStack_24 = 1;
  uStack_2c = 0;
  uStack_30 = 1;
  piStack_34 = param_2;
  uStack_38 = param_1;
  pvStack_3c = g_pD3DDevice;
  iVar1 = D3DXCreateTexture();
  if (iVar1 != 0) {
    if (piStack_34 != (int *)0x0) {
      (**(code **)(*piStack_34 + 8))(piStack_34);
    }
    return 0xffffffff;
  }
  ppiVar3 = &piStack_34;
  (**(code **)(*(int *)*unaff_EBX + 0x48))((int *)*unaff_EBX,0,ppiVar3);
  iVar1 = *(short *)((int)this + 6) * 4;
  ppvVar2 = &pvStack_3c;
  D3DXLoadSurfaceFromMemory
            (ppiVar3,0,ppvVar2,(int)this + 0x10,*(undefined4 *)(&DAT_0046f288 + iVar1),
             (int)*(short *)((int)this + 8) * *(int *)(&DAT_0046f2a0 + iVar1),0,&pvStack_3c,1,0);
  unaff_EBX[3] = *(undefined4 *)(&DAT_0046f2a0 + in_EAX * 4);
  if (ppvVar2 != (void **)0x0) {
    (**(code **)((int)*ppvVar2 + 8))(ppvVar2);
  }
  return 0;
}

