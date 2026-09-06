/* Raw Ghidra reference; not compilable reconstruction. Address: 0042BB30 */

uint * __fastcall FUN_0042bb30(undefined4 param_1,uint *param_2)

{
  int iVar1;
  uint *puVar2;
  
  param_2[5] = 0;
  param_2[6] = 0;
  param_2[7] = 0;
  param_2[8] = 0;
  param_2[4] = (uint)&PTR_FUN_004703e4;
  param_2[0x32] = 0;
  param_2[0xf] = 0;
  param_2[0x44] = 0;
  param_2[0x43] = 1;
  param_2[0x11] = 999;
  param_2[0x68] = 0;
  param_2[0x45] = 0;
  param_2[0x7a] = 0;
  param_2[0x47] = 999;
  param_2[0x79] = 1;
  param_2[0x7d] = 999;
  param_2[0x9e] = 0;
  param_2[0x7b] = 0;
  param_2[0xb0] = 0;
  param_2[0xaf] = 1;
  puVar2 = param_2;
  for (iVar1 = 0xb9; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  *param_2 = *param_2 | 2;
  DAT_00477844 = param_2;
  return param_2;
}

