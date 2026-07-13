/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x0040B940
 * Tracking name: FUN_0040b940
 * Ghidra name: FUN_0040b940
 * Tracked span: 144 bytes
 */


uint * FUN_0040b940(void)

{
  uint *_Memory;
  int iVar1;
  
  _Memory = operator_new(0x28);
  if (_Memory == (uint *)0x0) {
    _Memory = (uint *)0x0;
  }
  else {
    *_Memory = 0;
    _Memory[1] = 0;
    _Memory[2] = 0;
    _Memory[3] = 0;
    _Memory[4] = 0;
    _Memory[5] = 0;
    _Memory[6] = 0;
    _Memory[7] = 0;
    _Memory[8] = 0;
    _Memory[9] = 0;
    *_Memory = *_Memory | 2;
    DAT_00477700 = _Memory;
  }
  iVar1 = FUN_0040b560((int)_Memory);
  if (iVar1 != 0) {
    if (_Memory != (uint *)0x0) {
      FUN_0040b7b0((int)_Memory);
      _free(_Memory);
    }
    return (uint *)0x0;
  }
  return _Memory;
}

