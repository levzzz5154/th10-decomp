/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x00434F70
 * Tracking name: FUN_00434f70
 * Ghidra name: FUN_00434f70
 * Tracked span: 352 bytes
 */


uint FUN_00434f70(undefined4 param_1)

{
  uint in_EAX;
  byte *pbVar1;
  int iVar2;
  size_t _Size;
  byte *_Memory;
  int iVar3;
  int *piVar4;
  undefined4 extraout_EAX;
  byte *extraout_EAX_00;
  byte *extraout_EAX_01;
  int unaff_EBX;
  int *unaff_EBP;
  undefined4 *unaff_ESI;
  int iStack_10;
  int iStack_c;
  
  if ((undefined4 *)unaff_ESI[3] == (undefined4 *)0x0) {
    return in_EAX & 0xffffff00;
  }
  pbVar1 = (byte *)(*(code *)**(undefined4 **)unaff_ESI[3])(param_1,PTR_DAT_00474908);
  if ((char)pbVar1 != '\0') {
    iVar2 = (**(code **)(*(int *)unaff_ESI[3] + 8))(&stack0xffffffe8,0x10);
    pbVar1 = (byte *)0x0;
    if ((iVar2 != 0) &&
       (pbVar1 = FUN_0044b0d0(&stack0xffffffe8,0x10,'7',0x10,0x10), unaff_EBX == 0x31414854)) {
      unaff_ESI[1] = iStack_c + -0x8180754;
      _Size = iStack_10 + 0xc521974f;
      iVar2 = (**(code **)(*(int *)unaff_ESI[3] + 0x14))();
      (**(code **)(*(int *)unaff_ESI[3] + 0x18))(iVar2 - _Size,0);
      _Memory = _malloc(_Size);
      pbVar1 = (byte *)0x0;
      if (_Memory != (byte *)0x0) {
        iVar3 = (**(code **)(*(int *)unaff_ESI[3] + 8))(_Memory,_Size);
        if (iVar3 != 0) {
          FUN_0044b0d0(_Memory,_Size,-0x65,0x80,_Size);
          unaff_EBP = (int *)FUN_00435dc0(_Memory,_Size,(undefined1 *)0x0,(undefined1 *)0xf8a432eb);
          if (unaff_EBP != (int *)0x0) {
            piVar4 = FUN_004350d0(unaff_EBP,unaff_ESI[1],iVar2 - _Size);
            *unaff_ESI = piVar4;
            if (piVar4 != (int *)0x0) {
              _free(_Memory);
              _free(unaff_EBP);
              return CONCAT31((int3)((uint)extraout_EAX >> 8),1);
            }
          }
        }
        _free(_Memory);
        pbVar1 = extraout_EAX_00;
        if (unaff_EBP != (int *)0x0) {
          _free(unaff_EBP);
          pbVar1 = extraout_EAX_01;
        }
      }
    }
  }
  if ((int *)unaff_ESI[3] != (int *)0x0) {
    pbVar1 = (byte *)(**(code **)(*(int *)unaff_ESI[3] + 0x1c))(1);
  }
  unaff_ESI[3] = 0;
  return (uint)pbVar1 & 0xffffff00;
}

