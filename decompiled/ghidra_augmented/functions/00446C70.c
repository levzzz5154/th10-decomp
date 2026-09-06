/* Raw Ghidra reference; not compilable reconstruction. Address: 00446C70 */

undefined4 FUN_00446c70(void)

{
  int iVar1;
  int in_EAX;
  int iVar2;
  undefined4 unaff_EBX;
  int unaff_ESI;
  undefined4 *unaff_EDI;
  int *piVar3;
  int *piVar4;
  undefined1 *puStack_1c;
  undefined4 local_18;
  int local_14;
  int iStack_10;
  int iStack_4;
  
  puStack_1c = (undefined1 *)&local_18;
  local_14 = in_EAX;
  if (((byte)DAT_00491d78 & 1) != 0) {
    iVar1 = *(int *)(&DAT_0046f288 + in_EAX * 4);
    if ((iVar1 == 0x15) || (iVar1 == 0)) {
      local_14 = 5;
    }
    else if (iVar1 == 0x14) {
      local_14 = 3;
    }
  }
  piVar3 = (int *)*unaff_EDI;
  unaff_EDI[2] = unaff_EBX;
  local_18 = 0;
  (**(code **)(*piVar3 + 0x48))(piVar3,0);
  if (iStack_4 == 0) {
    D3DXLoadSurfaceFromFileInMemory(piVar3,0,0);
    piVar4 = piVar3;
  }
  else {
    iVar1 = *(int *)(unaff_ESI + 0x30) + unaff_ESI;
    puStack_1c = (undefined1 *)0x0;
    local_18 = 0;
    local_14 = (int)*(short *)(iVar1 + 8);
    iStack_10 = (int)*(short *)(iVar1 + 10);
    iVar2 = *(short *)(iVar1 + 6) * 4;
    piVar4 = (int *)0x0;
    D3DXLoadSurfaceFromMemory
              (piVar3,0,0,iVar1 + 0x10,*(undefined4 *)(&DAT_0046f288 + iVar2),
               (int)*(short *)(iVar1 + 8) * *(int *)(&DAT_0046f2a0 + iVar2),0,&puStack_1c,1,0);
  }
  (**(code **)(*piVar4 + 8))(piVar4);
  FUN_004465b0();
  unaff_EDI[3] = *(undefined4 *)(&DAT_0046f2a0 + (int)piVar4 * 4);
  return 0;
}

