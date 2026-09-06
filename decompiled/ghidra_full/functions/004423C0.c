/* Raw Ghidra reference; not compilable reconstruction. Address: 004423C0 */

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

