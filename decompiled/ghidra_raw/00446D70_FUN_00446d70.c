/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x00446D70
 * Tracking name: FUN_00446d70
 * Ghidra name: FUN_00446d70
 * Tracked span: 320 bytes
 */


undefined4 __thiscall FUN_00446d70(void *this,int param_1,undefined4 *param_2,undefined4 param_3)

{
  int iVar1;
  int in_EAX;
  int iVar2;
  int unaff_EDI;
  int *unaff_retaddr;
  undefined4 **ppuVar3;
  undefined4 *puStack_44;
  int local_34;
  int *piStack_2c;
  void *pvStack_28;
  int iStack_24;
  int iStack_20;
  undefined4 uStack_8;
  
  local_34 = in_EAX;
  if (((byte)DAT_00491d78 & 1) != 0) {
    iVar1 = *(int *)(&DAT_0046f288 + in_EAX * 4);
    if ((iVar1 == 0x15) || (iVar1 == 0)) {
      local_34 = 5;
    }
    else if (iVar1 == 0x14) {
      local_34 = 3;
    }
  }
  puStack_44 = &param_3;
  param_2[2] = param_3;
  param_3 = 0;
  (**(code **)(*(int *)*param_2 + 0x48))((int *)*param_2,0);
  if (param_1 == 0) {
    (**(code **)(*unaff_retaddr + 0x30))(unaff_retaddr,&piStack_2c);
    ppuVar3 = &puStack_44;
    puStack_44 = (undefined4 *)0x0;
    D3DXLoadSurfaceFromFileInMemory(uStack_8,0);
  }
  else {
    iVar1 = *(int *)(unaff_EDI + 0x30) + unaff_EDI;
    local_34 = (int)*(short *)(iVar1 + 8);
    piStack_2c = (int *)0x0;
    iStack_24 = (int)*(short *)(iVar1 + 8);
    iStack_20 = (int)*(short *)(iVar1 + 10) + (int)this;
    iVar2 = *(short *)(iVar1 + 6) * 4;
    ppuVar3 = (undefined4 **)0x0;
    pvStack_28 = this;
    D3DXLoadSurfaceFromMemory
              (unaff_retaddr,0,&piStack_2c,iVar1 + 0x10,*(undefined4 *)(&DAT_0046f288 + iVar2),
               (int)*(short *)(iVar1 + 8) * *(int *)(&DAT_0046f2a0 + iVar2),0,&stack0xffffffc4,1,0);
  }
  (**(code **)(*piStack_2c + 8))(piStack_2c);
  FUN_004465b0();
  *(undefined4 *)(local_34 + 0xc) = *(undefined4 *)(&DAT_0046f2a0 + (int)ppuVar3 * 4);
  return 0;
}

