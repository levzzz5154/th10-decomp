/* Raw Ghidra reference; not compilable reconstruction. Address: 00434D70 */

undefined4 * FUN_00434d70(byte param_1)

{
  undefined4 *unaff_ESI;
  
  if ((param_1 & 2) != 0) {
    _eh_vector_destructor_iterator_(unaff_ESI,0x10,unaff_ESI[-1],FUN_00435250);
    if ((param_1 & 1) != 0) {
      _free(unaff_ESI + -1);
    }
    return unaff_ESI + -1;
  }
  if ((void *)*unaff_ESI != (void *)0x0) {
    _free((void *)*unaff_ESI);
    *unaff_ESI = 0;
  }
  if ((param_1 & 1) != 0) {
    _free(unaff_ESI);
  }
  return unaff_ESI;
}

