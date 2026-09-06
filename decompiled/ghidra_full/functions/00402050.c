/* Raw Ghidra reference; not compilable reconstruction. Address: 00402050 */

undefined4 * __fastcall ConstructEntity(undefined4 *param_1)

{
  int iVar1;
  undefined4 *puVar2;
  
  param_1[0x1b] = param_1[0x1b] & 0xfffffffe;
  param_1[0x2c] = param_1[0x2c] & 0xfffffffe;
  param_1[0x3f] = param_1[0x3f] & 0xfffffffe;
  param_1[0x4a] = param_1[0x4a] & 0xfffffffe;
  param_1[0x5d] = param_1[0x5d] & 0xfffffffe;
  param_1[0x6c] = param_1[0x6c] & 0xfffffffe;
  param_1[0x7f] = param_1[0x7f] & 0xfffffffe;
  param_1[0x8a] = param_1[0x8a] & 0xfffffffe;
  param_1[0xde] = param_1[0xde] & 0xfffffffe;
  puVar2 = param_1;
  for (iVar1 = 0xeb; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  *(undefined2 *)(param_1 + 0xe1) = 0xffff;
  return param_1;
}

