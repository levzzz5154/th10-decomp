/* Raw Ghidra reference; not compilable reconstruction. Address: 0044C590 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0044c590(void)

{
  float *unaff_ESI;
  float10 fVar1;
  undefined2 unaff_retaddr;
  
  fVar1 = FUN_00452ff0((double)(*unaff_ESI * _DAT_00470b44),unaff_retaddr);
  *unaff_ESI = (float)(fVar1 * (float10)_DAT_00470b00);
  fVar1 = FUN_00452ff0((double)(unaff_ESI[1] * _DAT_00470b44),unaff_retaddr);
  unaff_ESI[1] = (float)(fVar1 * (float10)_DAT_00470b00);
  return;
}

