/* Raw Ghidra reference; not compilable reconstruction. Address: 0040A040 */

uint * __fastcall FUN_0040a040(undefined4 param_1,uint *param_2)

{
  int iVar1;
  uint *puVar2;
  
  param_2[4] = (uint)&PTR_FUN_004703e4;
  param_2[5] = 0;
  param_2[6] = 0;
  param_2[7] = 0;
  param_2[8] = 0;
  param_2[0x32] = 0;
  param_2[0xf] = 0;
  param_2[0x44] = 0;
  param_2[0x43] = 1;
  param_2[0x11] = 999;
  param_2[0x47] = 999;
  param_2[0x68] = 0;
  param_2[0x45] = 0;
  param_2[0x7a] = 0;
  param_2[0x79] = 1;
  param_2[0x7d] = 999;
  param_2[0x9e] = 0;
  param_2[0x7b] = 0;
  param_2[0xb0] = 0;
  param_2[0xaf] = 1;
  param_2[0xcd] = param_2[0xcd] & 0xfffffffe;
  param_2[0xde] = param_2[0xde] & 0xfffffffe;
  param_2[0xf1] = param_2[0xf1] & 0xfffffffe;
  param_2[0xfc] = param_2[0xfc] & 0xfffffffe;
  param_2[0x10f] = param_2[0x10f] & 0xfffffffe;
  param_2[0x11e] = param_2[0x11e] & 0xfffffffe;
  param_2[0x131] = param_2[0x131] & 0xfffffffe;
  param_2[0x13c] = param_2[0x13c] & 0xfffffffe;
  param_2[400] = param_2[400] & 0xfffffffe;
  puVar2 = param_2 + 0xb2;
  for (iVar1 = 0xeb; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  *(undefined2 *)(param_2 + 0x193) = 0xffff;
  puVar2 = param_2;
  for (iVar1 = 0x1a2; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  *param_2 = *param_2 | 2;
  DAT_004776f8 = param_2;
  return param_2;
}

