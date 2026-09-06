/* Raw Ghidra reference; not compilable reconstruction. Address: 004056B0 */

uint * FUN_004056b0(void)

{
  uint *_Memory;
  int iVar1;
  uint *puVar2;
  
  _Memory = operator_new(0x48);
  if (_Memory == (uint *)0x0) {
    _Memory = (uint *)0x0;
  }
  else {
    _Memory[9] = _Memory[9] & 0xfffffffe;
    puVar2 = _Memory;
    for (iVar1 = 0x12; iVar1 != 0; iVar1 = iVar1 + -1) {
      *puVar2 = 0;
      puVar2 = puVar2 + 1;
    }
    *_Memory = *_Memory | 2;
    DAT_004776ec = _Memory;
  }
  iVar1 = InstallEnabledResourcePair();
  if (iVar1 != 0) {
    if (_Memory != (uint *)0x0) {
      FUN_00405620((int)_Memory);
      _free(_Memory);
    }
    return (uint *)0x0;
  }
  return _Memory;
}

