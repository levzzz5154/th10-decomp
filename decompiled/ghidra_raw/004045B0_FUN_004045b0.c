/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x004045B0
 * Tracking name: FUN_004045b0
 * Ghidra name: FUN_004045b0
 * Tracked span: 96 bytes
 */


void FUN_004045b0(void)

{
  int in_EAX;
  
  if ((*(uint *)(in_EAX + 0x2a2c) & 1) == 0) {
    *(undefined4 *)(in_EAX + 0x2a20) = 0;
    *(undefined4 *)(in_EAX + 0x2a1c) = 0xfff0bdc1;
    *(undefined4 *)(in_EAX + 0x2a24) = 0;
    *(undefined4 **)(in_EAX + 0x2a28) = &DAT_00476f78;
    *(uint *)(in_EAX + 0x2a2c) = *(uint *)(in_EAX + 0x2a2c) | 1;
  }
  *(undefined4 *)(in_EAX + 0x2a20) = 0x3c;
  *(undefined4 *)(in_EAX + 0x2a24) = 0x42700000;
  *(undefined4 *)(in_EAX + 0x2a1c) = 0x3b;
  *(uint *)(in_EAX + 0x2a18) = *(uint *)(in_EAX + 0x2a18) | 4;
  return;
}

