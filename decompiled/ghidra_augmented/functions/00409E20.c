/* Raw Ghidra reference; not compilable reconstruction. Address: 00409E20 */

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

