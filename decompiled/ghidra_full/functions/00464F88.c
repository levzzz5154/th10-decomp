/* Raw Ghidra reference; not compilable reconstruction. Address: 00464F88 */

uint __cdecl FUN_00464f88(undefined4 param_1,uint param_2)

{
  if ((param_2 & 0x7ff00000) != 0x7ff00000) {
    return param_2 & 0x7ff00000;
  }
  return param_2;
}

