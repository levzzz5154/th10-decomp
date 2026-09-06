/* Raw Ghidra reference; not compilable reconstruction. Address: 0041C290 */

undefined4 * FUN_0041c290(void)

{
  undefined4 *_Memory;
  undefined4 extraout_ECX;
  int iVar1;
  undefined4 *puVar2;
  
  _Memory = operator_new(0x45c);
  if (_Memory == (undefined4 *)0x0) {
    _Memory = (undefined4 *)0x0;
  }
  else {
    FUN_0041c030(extraout_ECX,_Memory + 4);
    puVar2 = _Memory;
    for (iVar1 = 0x117; DAT_0047781c = _Memory, iVar1 != 0; iVar1 = iVar1 + -1) {
      *puVar2 = 0;
      puVar2 = puVar2 + 1;
    }
  }
  iVar1 = FUN_0041c120();
  if (iVar1 == 0) {
    return _Memory;
  }
  if (_Memory != (undefined4 *)0x0) {
    FUN_0041c1c0((int)_Memory);
    _free(_Memory);
  }
  return (undefined4 *)0x0;
}

