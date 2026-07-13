/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x00442050
 * Tracking name: FUN_00442050
 * Ghidra name: FUN_00442050
 * Tracked span: 464 bytes
 */


void __fastcall FUN_00442050(byte *param_1,byte *param_2,undefined4 param_3,byte param_4)

{
  byte bVar1;
  byte bVar2;
  byte bVar3;
  byte bVar4;
  byte bVar5;
  int in_EAX;
  
  *(undefined4 *)(in_EAX + 0x200) = param_3;
  *(undefined4 *)(in_EAX + 0x1d4) = 0;
  *(undefined4 *)(in_EAX + 0x1d8) = 0;
  *(undefined4 *)(in_EAX + 0x1dc) = 0;
  *(undefined4 *)(in_EAX + 0x1e0) = 0;
  *(undefined4 *)(in_EAX + 0x1e4) = 0;
  *(undefined4 *)(in_EAX + 0x1e8) = 0;
  *(uint *)(in_EAX + 0x204) = (uint)param_4;
  bVar1 = param_1[2];
  bVar2 = param_1[1];
  bVar3 = *param_1;
  bVar4 = param_2[2];
  bVar5 = param_2[1];
  *(uint *)(in_EAX + 0x1bc) = (uint)*param_2;
  *(uint *)(in_EAX + 0x1c0) = (uint)bVar5;
  *(uint *)(in_EAX + 0x1c4) = (uint)bVar4;
  *(uint *)(in_EAX + 0x1c8) = (uint)bVar3;
  *(uint *)(in_EAX + 0x1cc) = (uint)bVar2;
  *(uint *)(in_EAX + 0x1d0) = (uint)bVar1;
  if ((*(uint *)(in_EAX + 0x1fc) & 1) == 0) {
    *(undefined4 *)(in_EAX + 0x1f0) = 0;
    *(undefined4 *)(in_EAX + 0x1ec) = 0xfff0bdc1;
    *(undefined4 *)(in_EAX + 500) = 0;
    *(undefined4 **)(in_EAX + 0x1f8) = &DAT_00476f78;
    *(uint *)(in_EAX + 0x1fc) = *(uint *)(in_EAX + 0x1fc) | 1;
  }
  *(undefined4 *)(in_EAX + 0x1f0) = 0;
  *(undefined4 *)(in_EAX + 500) = 0;
  *(undefined4 *)(in_EAX + 0x1ec) = 0xffffffff;
  return;
}

