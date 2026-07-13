/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x004425A0
 * Tracking name: FUN_004425a0
 * Ghidra name: FUN_004425a0
 * Tracked span: 208 bytes
 */


void FUN_004425a0(void)

{
  byte bVar1;
  char cVar2;
  int in_EAX;
  uint uVar3;
  int unaff_EDI;
  undefined4 uVar4;
  
  if (*(byte *)(in_EAX + 0x3ada68) != ((byte)(*(uint *)(unaff_EDI + 0x35c) >> 4) & 3)) {
    FUN_00442f50();
    uVar3 = *(uint *)(unaff_EDI + 0x35c) >> 4;
    bVar1 = (byte)uVar3 & 3;
    *(byte *)(in_EAX + 0x3ada68) = bVar1;
    if ((uVar3 & 3) == 0) {
      (**(code **)(*(int *)g_pD3DDevice + 0xe4))(g_pD3DDevice,0x14,6);
    }
    else if (bVar1 == 1) {
      (**(code **)(*(int *)g_pD3DDevice + 0xe4))(g_pD3DDevice,0x14,2);
    }
  }
  if (*(char *)(in_EAX + 0x3ada6e) != (char)-(char)((int)*(undefined4 *)(unaff_EDI + 0x35c) >> 0x1f)
     ) {
    FUN_00442f50();
    cVar2 = -(char)((int)*(undefined4 *)(unaff_EDI + 0x35c) >> 0x1f);
    *(char *)(in_EAX + 0x3ada6e) = cVar2;
    if (cVar2 == '\0') {
      (**(code **)(*(int *)g_pD3DDevice + 0x114))(g_pD3DDevice,0,5,2);
      uVar4 = 2;
    }
    else {
      (**(code **)(*(int *)g_pD3DDevice + 0x114))(g_pD3DDevice,0,5,1);
      uVar4 = 1;
    }
    (**(code **)(*(int *)g_pD3DDevice + 0x114))(g_pD3DDevice,0,6,uVar4);
  }
  *(int *)(in_EAX + 0x54) = *(int *)(in_EAX + 0x54) + 1;
  return;
}

