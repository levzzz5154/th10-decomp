/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x0042C620
 * Tracking name: FUN_0042c620
 * Ghidra name: FUN_0042c620
 * Tracked span: 80 bytes
 */


void __fastcall FUN_0042c620(undefined4 param_1)

{
  int in_EAX;
  
  *(undefined4 *)(in_EAX + 0x20) = param_1;
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

