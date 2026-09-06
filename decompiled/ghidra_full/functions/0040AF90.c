/* Raw Ghidra reference; not compilable reconstruction. Address: 0040AF90 */

uint * FUN_0040af90(void)

{
  uint *_Memory;
  int iVar1;
  
  _Memory = operator_new(0x18);
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
    *_Memory = *_Memory | 2;
    DAT_004776fc = _Memory;
  }
  iVar1 = FUN_0040ae70();
  if (iVar1 != 0) {
    if (_Memory != (uint *)0x0) {
      FUN_0040af00((int)_Memory);
      _free(_Memory);
    }
    return (uint *)0x0;
  }
  return _Memory;
}

