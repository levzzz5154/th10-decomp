/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x00418A00
 * Tracking name: FUN_00418a00
 * Ghidra name: FUN_00418a00
 * Tracked span: 144 bytes
 */


void FUN_00418a00(void)

{
  int in_EAX;
  
  if (0 < *(int *)(in_EAX + 0x18)) {
    FUN_0044bf40(-1.0);
    return;
  }
  if (5000 < *(int *)(in_EAX + 0xc)) {
    *(int *)(in_EAX + 0xc) = *(int *)(in_EAX + 0xc) - *(int *)(in_EAX + 0x10);
    if (*(int *)(in_EAX + 0x10) < 0x12) {
      *(undefined4 *)(in_EAX + 0x10) = 0x12;
    }
    if (*(int *)(in_EAX + 0xc) < 5000) {
      *(undefined4 *)(in_EAX + 0xc) = 5000;
    }
  }
  return;
}

