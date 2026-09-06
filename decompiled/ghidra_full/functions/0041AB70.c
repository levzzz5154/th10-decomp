/* Raw Ghidra reference; not compilable reconstruction. Address: 0041AB70 */

void __fastcall
FUN_0041ab70(undefined4 *param_1,undefined4 *param_2,undefined4 param_3,byte param_4)

{
  int in_EAX;
  
  *(undefined4 *)(in_EAX + 0x1b4) = param_3;
  *(uint *)(in_EAX + 0x1b8) = (uint)param_4;
  *(undefined4 *)(in_EAX + 0x180) = *param_2;
  *(undefined4 *)(in_EAX + 0x184) = param_2[1];
  *(undefined4 *)(in_EAX + 0x188) = *param_1;
  *(undefined4 *)(in_EAX + 0x18c) = param_1[1];
  if ((*(uint *)(in_EAX + 0x1b0) & 1) == 0) {
    *(undefined4 *)(in_EAX + 0x1a4) = 0;
    *(undefined4 *)(in_EAX + 0x1a0) = 0xfff0bdc1;
    *(undefined4 *)(in_EAX + 0x1a8) = 0;
    *(undefined4 **)(in_EAX + 0x1ac) = &DAT_00476f78;
    *(uint *)(in_EAX + 0x1b0) = *(uint *)(in_EAX + 0x1b0) | 1;
  }
  *(undefined4 *)(in_EAX + 0x1a4) = 0;
  *(undefined4 *)(in_EAX + 0x1a8) = 0;
  *(undefined4 *)(in_EAX + 0x1a0) = 0xffffffff;
  return;
}

