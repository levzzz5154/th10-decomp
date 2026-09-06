/* Raw Ghidra reference; not compilable reconstruction. Address: 00434A80 */

void __fastcall
FUN_00434a80(undefined4 *param_1,undefined4 *param_2,undefined4 param_3,byte param_4)

{
  int in_EAX;
  
  *(undefined4 *)(in_EAX + 0xb4) = param_3;
  *(undefined4 *)(in_EAX + 0x88) = DAT_00491c14;
  *(undefined4 *)(in_EAX + 0x8c) = DAT_00491c18;
  *(undefined4 *)(in_EAX + 0x90) = DAT_00491c1c;
  *(undefined4 *)(in_EAX + 0x94) = DAT_00491c14;
  *(undefined4 *)(in_EAX + 0x98) = DAT_00491c18;
  *(undefined4 *)(in_EAX + 0x9c) = DAT_00491c1c;
  *(uint *)(in_EAX + 0xb8) = (uint)param_4;
  *(undefined4 *)(in_EAX + 0x70) = *param_2;
  *(undefined4 *)(in_EAX + 0x74) = param_2[1];
  *(undefined4 *)(in_EAX + 0x78) = param_2[2];
  *(undefined4 *)(in_EAX + 0x7c) = *param_1;
  *(undefined4 *)(in_EAX + 0x80) = param_1[1];
  *(undefined4 *)(in_EAX + 0x84) = param_1[2];
  if ((*(uint *)(in_EAX + 0xb0) & 1) == 0) {
    *(undefined4 *)(in_EAX + 0xa4) = 0;
    *(undefined4 *)(in_EAX + 0xa0) = 0xfff0bdc1;
    *(undefined4 *)(in_EAX + 0xa8) = 0;
    *(undefined4 **)(in_EAX + 0xac) = &DAT_00476f78;
    *(uint *)(in_EAX + 0xb0) = *(uint *)(in_EAX + 0xb0) | 1;
  }
  *(undefined4 *)(in_EAX + 0xa4) = 0;
  *(undefined4 *)(in_EAX + 0xa8) = 0;
  *(undefined4 *)(in_EAX + 0xa0) = 0xffffffff;
  return;
}

