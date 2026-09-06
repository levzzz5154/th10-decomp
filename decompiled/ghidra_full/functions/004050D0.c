/* Raw Ghidra reference; not compilable reconstruction. Address: 004050D0 */

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

