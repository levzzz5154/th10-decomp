/* Raw Ghidra reference; not compilable reconstruction. Address: 0041C030 */

undefined4 * __fastcall FUN_0041c030(undefined4 param_1,undefined4 *param_2)

{
  uint *puVar1;
  int iVar2;
  undefined4 *puVar3;
  
  *param_2 = &PTR_LAB_0046dab0;
  param_2[8] = param_2[8] & 0xfffffffe;
  puVar1 = param_2 + 0x1a;
  iVar2 = 0x12;
  do {
    *puVar1 = *puVar1 & 0xfffffffe;
    puVar1 = puVar1 + 0xd;
    iVar2 = iVar2 + -1;
  } while (iVar2 != 0);
  param_2[0x108] = param_2[0x108] & 0xfffffffe;
  puVar3 = param_2;
  for (iVar2 = 0x109; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar3 = 0;
    puVar3 = puVar3 + 1;
  }
  if ((param_2[8] & 1) == 0) {
    param_2[5] = 0;
    param_2[4] = 0xfff0bdc1;
    param_2[6] = 0;
    param_2[7] = &DAT_00476f78;
    param_2[8] = param_2[8] | 1;
  }
  param_2[5] = 0;
  param_2[6] = 0;
  param_2[4] = 0xffffffff;
  return param_2;
}

