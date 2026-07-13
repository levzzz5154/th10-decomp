/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x00405BE0
 * Tracking name: FUN_00405be0
 * Ghidra name: FUN_00405be0
 * Tracked span: 288 bytes
 */


void FUN_00405be0(void)

{
  int in_EAX;
  
  *(undefined2 *)(in_EAX + 0x446) = 0;
  if ((*(uint *)(in_EAX + 0x408) & 1) == 0) {
    *(undefined4 *)(in_EAX + 0x3fc) = 0;
    *(undefined4 *)(in_EAX + 0x3f8) = 0xfff0bdc1;
    *(undefined4 *)(in_EAX + 0x400) = 0;
    *(undefined4 **)(in_EAX + 0x404) = &DAT_00476f78;
    *(uint *)(in_EAX + 0x408) = *(uint *)(in_EAX + 0x408) | 1;
  }
  *(undefined4 *)(in_EAX + 0x3fc) = 0;
  *(undefined4 *)(in_EAX + 0x400) = 0;
  *(undefined4 *)(in_EAX + 0x3f8) = 0xffffffff;
  if ((*(uint *)(in_EAX + 0x41c) & 1) == 0) {
    *(undefined4 *)(in_EAX + 0x410) = 0;
    *(undefined4 *)(in_EAX + 0x40c) = 0xfff0bdc1;
    *(undefined4 *)(in_EAX + 0x414) = 0;
    *(undefined4 **)(in_EAX + 0x418) = &DAT_00476f78;
    *(uint *)(in_EAX + 0x41c) = *(uint *)(in_EAX + 0x41c) | 1;
  }
  *(undefined4 *)(in_EAX + 0x410) = 0;
  *(undefined4 *)(in_EAX + 0x414) = 0;
  *(undefined4 *)(in_EAX + 0x40c) = 0xffffffff;
  return;
}

