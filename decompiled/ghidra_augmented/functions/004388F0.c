/* Raw Ghidra reference; not compilable reconstruction. Address: 004388F0 */

undefined4 * __fastcall FUN_004388f0(undefined4 param_1,undefined4 *param_2)

{
  int iVar1;
  undefined4 *puVar2;
  
  puVar2 = param_2;
  for (iVar1 = 0x2801; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  param_2[0x2800] = 0;
  return param_2;
}

