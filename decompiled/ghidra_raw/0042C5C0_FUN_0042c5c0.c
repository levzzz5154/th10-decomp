/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x0042C5C0
 * Tracking name: FUN_0042c5c0
 * Ghidra name: FUN_0042c5c0
 * Tracked span: 96 bytes
 */


void __fastcall FUN_0042c5c0(undefined4 param_1)

{
  int in_EAX;
  
  *(undefined4 *)(in_EAX + 0x1c) = param_1;
  *(undefined4 *)(in_EAX + 0x20) = 0;
  if ((*(uint *)(in_EAX + 0x2c0) & 1) == 0) {
    *(undefined4 *)(in_EAX + 0x2b4) = 0;
    *(undefined4 *)(in_EAX + 0x2b0) = 0xfff0bdc1;
    *(undefined4 *)(in_EAX + 0x2b8) = 0;
    *(undefined4 **)(in_EAX + 700) = &DAT_00476f78;
    *(uint *)(in_EAX + 0x2c0) = *(uint *)(in_EAX + 0x2c0) | 1;
  }
  *(undefined4 *)(in_EAX + 0x2b4) = 0;
  *(undefined4 *)(in_EAX + 0x2b8) = 0;
  *(undefined4 *)(in_EAX + 0x2b0) = 0xffffffff;
  return;
}

