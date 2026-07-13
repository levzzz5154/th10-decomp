/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x004175E0
 * Tracking name: FUN_004175e0
 * Ghidra name: FUN_004175e0
 * Tracked span: 400 bytes
 */


void FUN_004175e0(void)

{
  int in_EAX;
  
  if (*(int *)(in_EAX + 0x3c) < 7) {
    *(int *)(in_EAX + 0x3c) = *(int *)(in_EAX + 0x3c) + 1;
  }
  DAT_00477848 = &DAT_00474788 + *(int *)(in_EAX + 0x3c) * 0x30;
  return;
}

