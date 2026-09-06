/* Raw Ghidra reference; not compilable reconstruction. Address: 0045C3F1 */

undefined4 __cdecl FUN_0045c3f1(short param_1)

{
  uint uVar1;
  
  uVar1 = 0;
  do {
    if (param_1 == *(short *)((int)&DAT_0046bd3c + uVar1)) {
      return 0;
    }
    uVar1 = uVar1 + 2;
  } while (uVar1 < 0x14);
  return 1;
}

