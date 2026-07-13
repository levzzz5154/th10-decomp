/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x0040D6B0
 * Tracking name: FUN_0040d6b0
 * Ghidra name: FUN_0040d6b0
 * Tracked span: 160 bytes
 */


uint * FUN_0040d6b0(undefined4 param_1)

{
  uint *_Memory;
  int iVar1;
  void *extraout_ECX;
  uint *puVar2;
  
  _Memory = operator_new(0x68);
  if (_Memory == (uint *)0x0) {
    _Memory = (uint *)0x0;
  }
  else {
    _Memory[0x14] = _Memory[0x14] & 0xfffffffe;
    puVar2 = _Memory;
    for (iVar1 = 0x1a; iVar1 != 0; iVar1 = iVar1 + -1) {
      *puVar2 = 0;
      puVar2 = puVar2 + 1;
    }
    *_Memory = *_Memory | 2;
    DAT_00477704 = _Memory;
  }
  iVar1 = FUN_0040d280(param_1);
  if (iVar1 != 0) {
    if (_Memory != (uint *)0x0) {
      FUN_0040d530(extraout_ECX);
      _free(_Memory);
    }
    return (uint *)0x0;
  }
  return _Memory;
}

