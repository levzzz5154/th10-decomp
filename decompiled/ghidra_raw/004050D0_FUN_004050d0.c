/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x004050D0
 * Tracking name: FUN_004050d0
 * Ghidra name: FUN_004050d0
 * Tracked span: 560 bytes
 */


void FUN_004050d0(void)

{
  int in_EAX;
  
  if ((*(uint *)(in_EAX + 0x40) & 1) == 0) {
    *(undefined4 *)(in_EAX + 0x34) = 0;
    *(undefined4 *)(in_EAX + 0x30) = 0xfff0bdc1;
    *(undefined4 *)(in_EAX + 0x38) = 0;
    *(undefined4 **)(in_EAX + 0x3c) = &DAT_00476f78;
    *(uint *)(in_EAX + 0x40) = *(uint *)(in_EAX + 0x40) | 1;
  }
  *(undefined4 *)(in_EAX + 0x34) = 0;
  *(undefined4 *)(in_EAX + 0x38) = 0;
  *(undefined4 *)(in_EAX + 0x30) = 0xffffffff;
  return;
}

