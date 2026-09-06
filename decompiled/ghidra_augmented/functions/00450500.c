/* Raw Ghidra reference; not compilable reconstruction. Address: 00450500 */

undefined4 * FUN_00450500(byte *param_1)

{
  undefined4 *puVar1;
  int iVar2;
  undefined4 unaff_EDI;
  
  puVar1 = operator_new(0x103c);
  if (puVar1 == (undefined4 *)0x0) {
    puVar1 = (undefined4 *)0x0;
  }
  else {
    *puVar1 = &PTR_FUN_0046d0d8;
    puVar1[0x404] = 0;
    puVar1[0x405] = 0;
  }
  puVar1[0x40b] = unaff_EDI;
  iVar2 = FUN_00450470(param_1);
  *(int *)(puVar1[1] + 4) = iVar2;
  *(undefined4 *)puVar1[1] = 0;
  return puVar1;
}

