/* Raw Ghidra reference; not compilable reconstruction. Address: 00412DB0 */

void ResetRecoveryTimer(void)

{
  int in_EAX;
  
  if ((*(uint *)(in_EAX + 0x30) & 1) == 0) {
    *(undefined4 *)(in_EAX + 0x24) = 0;
    *(undefined4 *)(in_EAX + 0x20) = 0xfff0bdc1;
    *(undefined4 *)(in_EAX + 0x28) = 0;
    *(undefined4 **)(in_EAX + 0x2c) = &DAT_00476f78;
    *(uint *)(in_EAX + 0x30) = *(uint *)(in_EAX + 0x30) | 1;
  }
  *(undefined4 *)(in_EAX + 0x24) = 0;
  *(undefined4 *)(in_EAX + 0x28) = 0;
  *(undefined4 *)(in_EAX + 0x20) = 0xffffffff;
  return;
}

