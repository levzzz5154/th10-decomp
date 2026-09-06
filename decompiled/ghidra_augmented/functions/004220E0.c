/* Raw Ghidra reference; not compilable reconstruction. Address: 004220E0 */

uint * __fastcall InitializeTimerState(undefined4 param_1,uint *param_2)

{
  int iVar1;
  uint *puVar2;
  
  param_2[8] = param_2[8] & 0xfffffffe;
  param_2[0x2c] = 0;
  param_2[9] = 0;
  param_2[0x3e] = 0;
  param_2[0x3d] = 1;
  param_2[0xb] = 999;
  param_2[0x41] = 999;
  param_2[0x62] = 0;
  param_2[0x3f] = 0;
  param_2[0x74] = 0;
  param_2[0x73] = 1;
  puVar2 = param_2;
  for (iVar1 = 0xb2; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  *param_2 = *param_2 | 2;
  DAT_00477830 = param_2;
  return param_2;
}

