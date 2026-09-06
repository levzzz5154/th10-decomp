/* Raw Ghidra reference; not compilable reconstruction. Address: 00449ED0 */

void FUN_00449ed0(undefined4 param_1)

{
  undefined4 *puVar1;
  
  puVar1 = operator_new(0x24);
  if (puVar1 == (undefined4 *)0x0) {
    puVar1 = (undefined4 *)0x0;
  }
  else {
    puVar1[2] = 0;
    puVar1[3] = 0;
    puVar1[4] = 0;
    *puVar1 = 0;
    puVar1[1] = puVar1[1] & 0xfffffffe;
    puVar1[5] = puVar1;
    puVar1[6] = 0;
    puVar1[7] = 0;
  }
  puVar1[3] = 0;
  puVar1[4] = 0;
  puVar1[2] = param_1;
  puVar1[1] = puVar1[1] | 1;
  return;
}

