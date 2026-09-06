/* Raw Ghidra reference; not compilable reconstruction. Address: 0042C920 */

undefined4 * __fastcall FUN_0042c920(undefined4 param_1,undefined4 *param_2)

{
  int iVar1;
  undefined4 *puVar2;
  
  *param_2 = &PTR_FUN_0046ecf0;
  param_2[0x2c] = 0;
  param_2[9] = 0;
  param_2[0x3e] = 0;
  param_2[0x3d] = 1;
  param_2[0xb] = 999;
  param_2[0x62] = 0;
  param_2[0x3f] = 0;
  param_2[0x74] = 0;
  param_2[0x73] = 1;
  param_2[0x41] = 999;
  param_2[0x98] = 0;
  param_2[0x75] = 0;
  param_2[0xaa] = 0;
  param_2[0xa9] = 1;
  param_2[0x77] = 999;
  param_2[0xb0] = param_2[0xb0] & 0xfffffffe;
  param_2[0x1660] = 0;
  param_2[0x163d] = 0;
  param_2[0x1672] = 0;
  param_2[0x163f] = 999;
  param_2[0x1671] = 1;
  param_2[0x16ad] = 0;
  param_2[0x16ae] = 0;
  param_2[0x16af] = 0;
  param_2[0x16b0] = 0;
  param_2[0x16ac] = &PTR_FUN_004703e4;
  puVar2 = param_2;
  for (iVar1 = 0x16b3; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  param_2[1] = param_2[1] | 2;
  DAT_0047784c = param_2;
  return param_2;
}

