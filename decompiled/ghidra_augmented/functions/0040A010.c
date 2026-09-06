/* Raw Ghidra reference; not compilable reconstruction. Address: 0040A010 */

void FUN_0040a010(void)

{
  int in_EAX;
  
  *(uint *)(*(int *)(in_EAX + 8) + 4) = *(uint *)(*(int *)(in_EAX + 8) + 4) | 2;
  *(uint *)(*(int *)(in_EAX + 0xc) + 4) = *(uint *)(*(int *)(in_EAX + 0xc) + 4) | 2;
  FUN_00426f70(in_EAX);
  return;
}

