/* Raw Ghidra reference; not compilable reconstruction. Address: 004462F0 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_004462f0(void)

{
  undefined4 *puVar1;
  int in_EAX;
  int iVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  undefined4 uStack_20;
  undefined4 *puStack_1c;
  undefined4 uStack_18;
  
  *(undefined4 *)(in_EAX + 0x3ada80) = 0;
  *(undefined4 *)(in_EAX + 0x3adabc) = 0;
  *(undefined4 *)(in_EAX + 0x3adaa8) = 0;
  *(undefined4 *)(in_EAX + 0x3ada94) = 0;
  *(undefined4 *)(in_EAX + 0x3adaac) = 0;
  *(undefined4 *)(in_EAX + 0x3ada84) = 0;
  *(undefined4 *)(in_EAX + 0x3ada9c) = 0;
  *(undefined4 *)(in_EAX + 0x3ada88) = 0;
  *(undefined4 *)(in_EAX + 0x3adab4) = 0x43000000;
  *(undefined4 *)(in_EAX + 0x3ada8c) = 0x43000000;
  *(undefined4 *)(in_EAX + 0x3adab8) = 0x43000000;
  *(undefined4 *)(in_EAX + 0x3adaa4) = 0x43000000;
  *(undefined4 *)(in_EAX + 0x3adac4) = 0x3f800000;
  *(undefined4 *)(in_EAX + 0x3adab0) = 0x3f800000;
  *(undefined4 *)(in_EAX + 0x3adac0) = 0x3f800000;
  *(undefined4 *)(in_EAX + 0x3ada98) = 0x3f800000;
  *(undefined4 *)(in_EAX + 0x3adaa0) = 0xc3000000;
  *(undefined4 *)(in_EAX + 0x3ada78) = 0xc3000000;
  *(undefined4 *)(in_EAX + 0x3ada90) = 0xc3000000;
  *(undefined4 *)(in_EAX + 0x3ada7c) = 0xc3000000;
  _DAT_00497930 = *(undefined4 *)(in_EAX + 0x3ada78);
  _DAT_00497934 = *(undefined4 *)(in_EAX + 0x3ada7c);
  _DAT_00497938 = *(undefined4 *)(in_EAX + 0x3ada80);
  _DAT_00497948 = *(undefined4 *)(in_EAX + 0x3ada8c);
  _DAT_0049794c = *(undefined4 *)(in_EAX + 0x3ada90);
  _DAT_00497950 = *(undefined4 *)(in_EAX + 0x3ada94);
  _DAT_00497960 = *(undefined4 *)(in_EAX + 0x3adaa0);
  _DAT_00497964 = *(undefined4 *)(in_EAX + 0x3adaa4);
  _DAT_00497968 = *(undefined4 *)(in_EAX + 0x3adaa8);
  _DAT_00497978 = *(undefined4 *)(in_EAX + 0x3adab4);
  _DAT_0049797c = *(undefined4 *)(in_EAX + 0x3adab8);
  _DAT_00497980 = *(undefined4 *)(in_EAX + 0x3adabc);
  _DAT_00497940 = *(undefined4 *)(in_EAX + 0x3ada84);
  _DAT_00497944 = *(undefined4 *)(in_EAX + 0x3ada88);
  _DAT_00497958 = *(undefined4 *)(in_EAX + 0x3ada98);
  _DAT_0049795c = *(undefined4 *)(in_EAX + 0x3ada9c);
  _DAT_00497970 = *(undefined4 *)(in_EAX + 0x3adaac);
  uStack_18 = 0;
  _DAT_00497974 = *(undefined4 *)(in_EAX + 0x3adab0);
  puVar1 = (undefined4 *)(in_EAX + 0x3ada74);
  uStack_20 = 1;
  _DAT_00497988 = *(undefined4 *)(in_EAX + 0x3adac0);
  _DAT_0049798c = *(undefined4 *)(in_EAX + 0x3adac4);
  puStack_1c = puVar1;
  (**(code **)(*(int *)g_pD3DDevice + 0x68))(g_pD3DDevice,0x50,0,0x102);
  (**(code **)(*(int *)*puVar1 + 0x2c))((int *)*puVar1,0,0,&uStack_20);
  puVar3 = (undefined4 *)(in_EAX + 0x3ada78);
  puVar4 = (undefined4 *)0x0;
  for (iVar2 = 0x14; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar4 = *puVar3;
    puVar3 = puVar3 + 1;
    puVar4 = puVar4 + 1;
  }
  (**(code **)(*(int *)*puVar1 + 0x30))((int *)*puVar1);
  (**(code **)(*(int *)g_pD3DDevice + 400))(g_pD3DDevice,0,*puVar1,0,0x14);
  return;
}

