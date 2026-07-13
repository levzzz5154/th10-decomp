/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x0043C8B0
 * Tracking name: FUN_0043c8b0
 * Ghidra name: FUN_0043c8b0
 * Tracked span: 192 bytes
 */


uint * FUN_0043c8b0(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                   undefined4 param_5)

{
  uint *puVar1;
  uint *puVar2;
  int iVar3;
  
  puVar1 = operator_new(0x44);
  puVar2 = (uint *)0x0;
  if (puVar1 != (uint *)0x0) {
    puVar1[0x10] = puVar1[0x10] & 0xfffffffe;
    puVar2 = puVar1;
    for (iVar3 = 0x11; iVar3 != 0; iVar3 = iVar3 + -1) {
      *puVar2 = 0;
      puVar2 = puVar2 + 1;
    }
    *puVar1 = *puVar1 | 2;
    FUN_0043c970(param_1,param_2,param_3,param_4,param_5);
    puVar2 = puVar1;
  }
  return puVar2;
}

