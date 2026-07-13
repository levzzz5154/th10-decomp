/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x0040CF40
 * Tracking name: FUN_0040cf40
 * Ghidra name: FUN_0040cf40
 * Tracked span: 32 bytes
 */


undefined4 * __fastcall FUN_0040cf40(undefined4 param_1,undefined4 *param_2)

{
  int iVar1;
  undefined4 *puVar2;
  
  puVar2 = param_2;
  for (iVar1 = 0x7e; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  param_2[0xb] = 0x41000000;
  return param_2;
}

