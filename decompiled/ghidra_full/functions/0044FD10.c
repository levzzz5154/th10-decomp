/* Raw Ghidra reference; not compilable reconstruction. Address: 0044FD10 */

undefined4 FUN_0044fd10(float param_1)

{
  undefined4 *puVar1;
  bool bVar2;
  undefined4 *_Memory;
  int iVar3;
  int unaff_EDI;
  
  bVar2 = true;
  puVar1 = (undefined4 *)(unaff_EDI + 0x1030);
  while( true ) {
    while( true ) {
      _Memory = puVar1;
      if (_Memory == (undefined4 *)0x0) {
        *(int *)(unaff_EDI + 4) = unaff_EDI + 8;
        return 0;
      }
      puVar1 = (undefined4 *)_Memory[1];
      *(undefined4 *)(unaff_EDI + 4) = *_Memory;
      if (bVar2) break;
      iVar3 = FUN_0044e1a0(param_1);
      if (iVar3 != 0) {
        _free(*(void **)(unaff_EDI + 4));
        if (_Memory[1] != 0) {
          *(undefined4 *)(_Memory[1] + 8) = _Memory[2];
        }
        if (_Memory[2] != 0) {
          *(undefined4 *)(_Memory[2] + 4) = _Memory[1];
        }
        _Memory[1] = 0;
        _Memory[2] = 0;
        _free(_Memory);
      }
    }
    iVar3 = FUN_0044e1a0(param_1);
    if (iVar3 != 0) break;
    bVar2 = false;
  }
  return 0xffffffff;
}

