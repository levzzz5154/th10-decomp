/* Raw Ghidra reference; not compilable reconstruction. Address: 00417800 */

undefined4 ResetPathState(void)

{
  int in_EAX;
  
  if ((*(uint *)(in_EAX + 0x50) & 1) == 0) {
    *(undefined4 *)(in_EAX + 0x44) = 0;
    *(undefined4 *)(in_EAX + 0x40) = 0xfff0bdc1;
    *(undefined4 *)(in_EAX + 0x48) = 0;
    *(undefined4 **)(in_EAX + 0x4c) = &DAT_00476f78;
    *(uint *)(in_EAX + 0x50) = *(uint *)(in_EAX + 0x50) | 1;
  }
  *(undefined4 *)(in_EAX + 0x44) = 0;
  *(undefined4 *)(in_EAX + 0x48) = 0;
  *(undefined4 *)(in_EAX + 0x40) = 0xffffffff;
  *(undefined4 *)(in_EAX + 0x58) = 0;
  *(undefined4 *)(in_EAX + 0x5c) = 0;
  return 0;
}

