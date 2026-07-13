/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x0040C730
 * Tracking name: FUN_0040c730
 * Ghidra name: FUN_0040c730
 * Tracked span: 624 bytes
 */


void FUN_0040c730(void)

{
  undefined4 *puVar1;
  int in_EAX;
  
  puVar1 = (undefined4 *)(in_EAX + 8);
  *(uint *)(in_EAX + 0x1028) = *(uint *)(in_EAX + 0x1028) & 0xfffffffe;
  *puVar1 = 0;
  *(undefined4 *)(in_EAX + 0xc) = 0;
  *(int *)(in_EAX + 0x101c) = in_EAX;
  *(undefined4 *)(in_EAX + 0x1018) = 0xffffffff;
  *(undefined4 *)(in_EAX + 0x1020) = 0;
  *(undefined4 **)(in_EAX + 4) = puVar1;
  *(undefined4 **)(in_EAX + 0x1030) = puVar1;
  *(undefined4 *)(in_EAX + 0x1034) = 0;
  *(undefined4 *)(in_EAX + 0x1038) = 0;
  return;
}

