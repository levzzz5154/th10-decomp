/* Raw Ghidra reference; not compilable reconstruction. Address: 004297B0 */

void DestroyPlatformResource(void)

{
  void *unaff_ESI;
  
  if (unaff_ESI != (void *)0x0) {
    FUN_004294a0((int)unaff_ESI);
    _free(unaff_ESI);
  }
  return;
}

