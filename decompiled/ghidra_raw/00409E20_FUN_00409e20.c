/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x00409E20
 * Tracking name: FUN_00409e20
 * Ghidra name: FUN_00409e20
 * Tracked span: 48 bytes
 */


void FUN_00409e20(void)

{
  uint *puVar1;
  int in_EAX;
  
  if (*(int *)(in_EAX + 8) != 0) {
    puVar1 = (uint *)(*(int *)(in_EAX + 8) + 4);
    *puVar1 = *puVar1 | 2;
  }
  if (*(int *)(in_EAX + 0xc) != 0) {
    puVar1 = (uint *)(*(int *)(in_EAX + 0xc) + 4);
    *puVar1 = *puVar1 | 2;
  }
  return;
}

