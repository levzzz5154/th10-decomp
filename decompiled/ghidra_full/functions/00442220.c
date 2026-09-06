/* Raw Ghidra reference; not compilable reconstruction. Address: 00442220 */

void __fastcall
ConfigureColorPlaybackState(byte *param_1,byte *param_2,undefined4 param_3,byte param_4)

{
  byte bVar1;
  byte bVar2;
  byte bVar3;
  byte bVar4;
  byte bVar5;
  int in_EAX;
  
  *(undefined4 *)(in_EAX + 0x100) = param_3;
  *(undefined4 *)(in_EAX + 0xd4) = 0;
  *(undefined4 *)(in_EAX + 0xd8) = 0;
  *(undefined4 *)(in_EAX + 0xdc) = 0;
  *(undefined4 *)(in_EAX + 0xe0) = 0;
  *(undefined4 *)(in_EAX + 0xe4) = 0;
  *(undefined4 *)(in_EAX + 0xe8) = 0;
  *(uint *)(in_EAX + 0x104) = (uint)param_4;
  bVar1 = param_1[2];
  bVar2 = param_1[1];
  bVar3 = *param_1;
  bVar4 = param_2[2];
  bVar5 = param_2[1];
  *(uint *)(in_EAX + 0xbc) = (uint)*param_2;
  *(uint *)(in_EAX + 0xc0) = (uint)bVar5;
  *(uint *)(in_EAX + 0xc4) = (uint)bVar4;
  *(uint *)(in_EAX + 200) = (uint)bVar3;
  *(uint *)(in_EAX + 0xcc) = (uint)bVar2;
  *(uint *)(in_EAX + 0xd0) = (uint)bVar1;
  if ((*(uint *)(in_EAX + 0xfc) & 1) == 0) {
    *(undefined4 *)(in_EAX + 0xf0) = 0;
    *(undefined4 *)(in_EAX + 0xec) = 0xfff0bdc1;
    *(undefined4 *)(in_EAX + 0xf4) = 0;
    *(undefined4 **)(in_EAX + 0xf8) = &DAT_00476f78;
    *(uint *)(in_EAX + 0xfc) = *(uint *)(in_EAX + 0xfc) | 1;
  }
  *(undefined4 *)(in_EAX + 0xf0) = 0;
  *(undefined4 *)(in_EAX + 0xf4) = 0;
  *(undefined4 *)(in_EAX + 0xec) = 0xffffffff;
  return;
}

