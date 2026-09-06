/* Raw Ghidra reference; not compilable reconstruction. Address: 00425090 */

void __fastcall FUN_00425090(void *param_1)

{
  void *unaff_ESI;
  
  if (unaff_ESI != (void *)0x0) {
    FUN_00424ed0(param_1,(int)unaff_ESI);
    _free(unaff_ESI);
  }
  return;
}

