/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x00418D40
 * Tracking name: FUN_00418d40
 * Ghidra name: FUN_00418d40
 * Tracked span: 240 bytes
 */


uint * __fastcall FUN_00418d40(undefined4 param_1,uint *param_2)

{
  int iVar1;
  uint *puVar2;
  
  puVar2 = param_2;
  for (iVar1 = 0x6a; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  *param_2 = *param_2 | 2;
  param_2[6] = (uint)param_2;
  param_2[9] = (uint)param_2;
  param_2[7] = 0;
  param_2[8] = 0;
  param_2[10] = 0;
  param_2[0xb] = 0;
  param_2[0xc] = (uint)param_2;
  param_2[0xd] = 0;
  param_2[0xe] = 0;
  param_2[0xf] = (uint)param_2;
  param_2[0x10] = 0;
  param_2[0x11] = 0;
  param_2[0x12] = (uint)param_2;
  param_2[0x13] = 0;
  param_2[0x14] = 0;
  param_2[0x15] = (uint)param_2;
  param_2[0x16] = 0;
  param_2[0x17] = 0;
  param_2[0x18] = (uint)param_2;
  param_2[0x19] = 0;
  param_2[0x1a] = 0;
  param_2[0x1b] = (uint)param_2;
  param_2[0x1c] = 0;
  param_2[0x1d] = 0;
  param_2[0x1e] = (uint)param_2;
  param_2[0x21] = (uint)param_2;
  param_2[0x1f] = 0;
  param_2[0x20] = 0;
  param_2[0x22] = 0;
  param_2[0x23] = 0;
  param_2[0x24] = (uint)param_2;
  param_2[0x25] = 0;
  param_2[0x26] = 0;
  param_2[0x27] = (uint)param_2;
  param_2[0x28] = 0;
  param_2[0x29] = 0;
  param_2[0x2a] = (uint)param_2;
  param_2[0x2b] = 0;
  param_2[0x2c] = 0;
  param_2[0x2d] = (uint)param_2;
  param_2[0x2e] = 0;
  param_2[0x2f] = 0;
  param_2[0x30] = (uint)param_2;
  param_2[0x31] = 0;
  param_2[0x32] = 0;
  param_2[0x33] = (uint)param_2;
  param_2[0x34] = 0;
  param_2[0x35] = 0;
  DAT_00477814 = param_2;
  return param_2;
}

