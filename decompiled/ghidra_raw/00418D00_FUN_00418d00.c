/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x00418D00
 * Tracking name: FUN_00418d00
 * Ghidra name: FUN_00418d00
 * Tracked span: 64 bytes
 */


undefined4 * __fastcall FUN_00418d00(undefined4 param_1,undefined4 *param_2)

{
  int iVar1;
  undefined4 *puVar2;
  
  puVar2 = param_2;
  for (iVar1 = 0x22; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  param_2[4] = 0;
  param_2[5] = 0;
  param_2[3] = param_2;
  param_2[0x21] = 0xffffffff;
  param_2[0x1c] = 0xffffffff;
  param_2[0x1b] = 300;
  param_2[0x1f] = 0x3f800000;
  return param_2;
}

