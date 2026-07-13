/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x004423E0
 * Tracking name: FUN_004423e0
 * Ghidra name: FUN_004423e0
 * Tracked span: 448 bytes
 */


void FUN_004423e0(void)

{
  byte bVar1;
  char cVar2;
  int in_EAX;
  uint uVar3;
  uint uVar4;
  int unaff_EBX;
  undefined4 uVar5;
  undefined4 uStack_4;
  
  if (*(byte *)(in_EAX + 0x3ada68) == ((byte)(*(uint *)(unaff_EBX + 0x35c) >> 4) & 3))
  goto LAB_00442448;
  FUN_00442f50();
  uVar3 = *(uint *)(unaff_EBX + 0x35c) >> 4;
  bVar1 = (byte)uVar3 & 3;
  *(byte *)(in_EAX + 0x3ada68) = bVar1;
  if ((uVar3 & 3) == 0) {
    uVar5 = 6;
  }
  else {
    if (bVar1 == 1) {
      (**(code **)(*(int *)g_pD3DDevice + 0xe4))(g_pD3DDevice,0x14,2);
      goto LAB_00442448;
    }
    if (bVar1 != 2) goto LAB_00442448;
    uVar5 = 2;
  }
  (**(code **)(*(int *)g_pD3DDevice + 0xe4))(g_pD3DDevice,0x14,uVar5);
LAB_00442448:
  if ((char)((uint)*(undefined4 *)(unaff_EBX + 0x35c) >> 8) < '\0') {
    uVar3 = *(uint *)(unaff_EBX + 0x300);
  }
  else {
    uVar3 = *(uint *)(unaff_EBX + 0x2fc);
  }
  uStack_4 = uVar3;
  if (*(int *)(in_EAX + 0x73245c) != 0) {
    uVar4 = (uint)*(byte *)(in_EAX + 0x73245a) * (uVar3 >> 0x10 & 0xff) >> 7;
    if (0xff < uVar4) {
      uVar4 = 0xff;
    }
    uStack_4._3_1_ = (undefined1)(uVar3 >> 0x18);
    uStack_4._0_3_ = CONCAT12((char)uVar4,(short)uVar3);
    uVar3 = (uint)*(byte *)(in_EAX + 0x732459) * (((uint3)uStack_4 & 0xff00) >> 8) >> 7;
    if (0xff < uVar3) {
      uVar3 = 0xff;
    }
    uVar4 = (uint)(uint3)uStack_4;
    uVar4 = (uint)*(byte *)(in_EAX + 0x732458) * (uVar4 & 0xff) >> 7;
    if (0xff < uVar4) {
      uVar4 = 0xff;
    }
    uStack_4 = CONCAT31(CONCAT21(uStack_4._2_2_,(char)uVar3),(char)uVar4);
    uVar3 = (uint)*(byte *)(in_EAX + 0x73245b) * (uint)(uStack_4._2_2_ >> 8) >> 7;
    if (0xff < uVar3) {
      uVar3 = 0xff;
    }
    uStack_4 = CONCAT13((char)uVar3,(uint3)uStack_4);
  }
  if (*(uint *)(in_EAX + 0x3ada60) != uStack_4) {
    FUN_00442f50();
    *(uint *)(in_EAX + 0x3ada60) = uStack_4;
    (**(code **)(*(int *)g_pD3DDevice + 0xe4))(g_pD3DDevice,0x3c,uStack_4);
  }
  if (*(char *)(in_EAX + 0x3ada6e) != (char)-(char)((int)*(undefined4 *)(unaff_EBX + 0x35c) >> 0x1f)
     ) {
    FUN_00442f50();
    cVar2 = -(char)((int)*(undefined4 *)(unaff_EBX + 0x35c) >> 0x1f);
    *(char *)(in_EAX + 0x3ada6e) = cVar2;
    if (cVar2 == '\0') {
      (**(code **)(*(int *)g_pD3DDevice + 0x114))(g_pD3DDevice,0,5,2);
      uVar5 = 2;
    }
    else {
      (**(code **)(*(int *)g_pD3DDevice + 0x114))(g_pD3DDevice,0,5,1);
      uVar5 = 1;
    }
    (**(code **)(*(int *)g_pD3DDevice + 0x114))(g_pD3DDevice,0,6,uVar5);
  }
  *(int *)(in_EAX + 0x54) = *(int *)(in_EAX + 0x54) + 1;
  return;
}

