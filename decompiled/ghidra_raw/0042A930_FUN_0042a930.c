/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x0042A930
 * Tracking name: FUN_0042a930
 * Ghidra name: FUN_0042a930
 * Tracked span: 288 bytes
 */


void FUN_0042a930(int param_1)

{
  int in_EAX;
  
  if ((*(uint *)(in_EAX + 0x24) & 1) == 0) {
    *(undefined4 *)(in_EAX + 0x18) = 0;
    *(undefined4 *)(in_EAX + 0x14) = 0xfff0bdc1;
    *(undefined4 *)(in_EAX + 0x1c) = 0;
    *(undefined4 **)(in_EAX + 0x20) = &DAT_00476f78;
    *(uint *)(in_EAX + 0x24) = *(uint *)(in_EAX + 0x24) | 1;
  }
  *(int *)(in_EAX + 0x18) = param_1;
  *(int *)(in_EAX + 0x14) = param_1 + -1;
  *(float *)(in_EAX + 0x1c) = (float)param_1;
  return;
}

