/* Raw Ghidra reference; not compilable reconstruction. Address: 004175E0 */

void FUN_004175e0(void)

{
  int in_EAX;
  
  if (*(int *)(in_EAX + 0x3c) < 7) {
    *(int *)(in_EAX + 0x3c) = *(int *)(in_EAX + 0x3c) + 1;
  }
  DAT_00477848 = &DAT_00474788 + *(int *)(in_EAX + 0x3c) * 0x30;
  return;
}

