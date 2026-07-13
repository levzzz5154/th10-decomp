/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x00405500
 * Tracking name: FUN_00405500
 * Ghidra name: FUN_00405500
 * Tracked span: 192 bytes
 */


void FUN_00405500(void)

{
  int in_EAX;
  
  if (0x3b < *(int *)(in_EAX + 0x3738)) {
    *(undefined4 *)(in_EAX + 0x3790) = 0;
    *(uint *)(in_EAX + 0x378c) = *(uint *)(in_EAX + 0x378c) & 0xfffffffd;
    *(uint *)(in_EAX + 0xad4) = *(uint *)(in_EAX + 0xad4) & 0xfffffffd;
    *(uint *)(in_EAX + 0xe80) = *(uint *)(in_EAX + 0xe80) & 0xfffffffd;
    *(uint *)(in_EAX + 0x15d8) = *(uint *)(in_EAX + 0x15d8) & 0xfffffffd;
    *(uint *)(in_EAX + 0x1984) = *(uint *)(in_EAX + 0x1984) & 0xfffffffd;
    *(uint *)(in_EAX + 0x1d30) = *(uint *)(in_EAX + 0x1d30) & 0xfffffffd;
    *(uint *)(in_EAX + 0x20dc) = *(uint *)(in_EAX + 0x20dc) & 0xfffffffd;
    *(uint *)(in_EAX + 0x2488) = *(uint *)(in_EAX + 0x2488) & 0xfffffffd;
  }
  return;
}

