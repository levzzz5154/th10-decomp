/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x00442300
 * Tracking name: FUN_00442300
 * Ghidra name: FUN_00442300
 * Tracked span: 192 bytes
 */


void __thiscall FUN_00442300(void *this,byte param_1,byte param_2,byte param_3)

{
  int in_EAX;
  
  *(void **)(in_EAX + 300) = this;
  *(uint *)(in_EAX + 0x130) = (uint)param_1;
  *(uint *)(in_EAX + 0x108) = (uint)param_2;
  *(undefined4 *)(in_EAX + 0x110) = 0;
  *(undefined4 *)(in_EAX + 0x114) = 0;
  *(uint *)(in_EAX + 0x10c) = (uint)param_3;
  if ((*(uint *)(in_EAX + 0x128) & 1) == 0) {
    *(undefined4 *)(in_EAX + 0x11c) = 0;
    *(undefined4 *)(in_EAX + 0x118) = 0xfff0bdc1;
    *(undefined4 *)(in_EAX + 0x120) = 0;
    *(undefined4 **)(in_EAX + 0x124) = &DAT_00476f78;
    *(uint *)(in_EAX + 0x128) = *(uint *)(in_EAX + 0x128) | 1;
  }
  *(undefined4 *)(in_EAX + 0x11c) = 0;
  *(undefined4 *)(in_EAX + 0x120) = 0;
  *(undefined4 *)(in_EAX + 0x118) = 0xffffffff;
  return;
}

