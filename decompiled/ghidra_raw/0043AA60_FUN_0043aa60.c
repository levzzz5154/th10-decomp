/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x0043AA60
 * Tracking name: FUN_0043aa60
 * Ghidra name: FUN_0043aa60
 * Tracked span: 112 bytes
 */


void FUN_0043aa60(void)

{
  void *_Memory;
  int iVar1;
  int unaff_ESI;
  int iVar2;
  
  iVar1 = 0;
  if (0 < *(int *)(unaff_ESI + 0x118)) {
    iVar2 = 0;
    do {
      _Memory = *(void **)(iVar2 + 0x10 + *(int *)(unaff_ESI + 0x138));
      if (_Memory != (void *)0x0) {
        _free(_Memory);
        *(undefined4 *)(iVar2 + 0x10 + *(int *)(unaff_ESI + 0x138)) = 0;
      }
      iVar1 = iVar1 + 1;
      iVar2 = iVar2 + 0x20;
    } while (iVar1 < *(int *)(unaff_ESI + 0x118));
  }
  if (*(void **)(unaff_ESI + 0x138) != (void *)0x0) {
    _free(*(void **)(unaff_ESI + 0x138));
    *(undefined4 *)(unaff_ESI + 0x138) = 0;
  }
  *(undefined4 *)(unaff_ESI + 0x138) = 0;
  *(undefined4 *)(unaff_ESI + 0x118) = 0;
  return;
}

