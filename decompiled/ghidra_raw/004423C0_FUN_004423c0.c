/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x004423C0
 * Tracking name: FUN_004423c0
 * Ghidra name: FUN_004423c0
 * Tracked span: 32 bytes
 */


uint __fastcall FUN_004423c0(uint param_1)

{
  uint in_EAX;
  uint uVar1;
  
  uVar1 = (in_EAX & 0xff) * (param_1 & 0xff) >> 7;
  if (0xff < uVar1) {
    uVar1 = 0xff;
  }
  return uVar1;
}

