/* Raw Ghidra reference; not compilable reconstruction. Address: 00456B04 */

/* Library Function - Single Match
    __dosmaperr
   
   Library: Visual Studio 2003 Release */

void __cdecl __dosmaperr(ulong param_1)

{
  _ptiddata p_Var1;
  uint uVar2;
  
  p_Var1 = __getptd();
  p_Var1->_tdoserrno = param_1;
  uVar2 = 0;
  do {
    if (param_1 == (&DAT_004733b8)[uVar2 * 2]) {
      p_Var1 = __getptd();
      p_Var1->_terrno = *(int *)(uVar2 * 8 + 0x4733bc);
      return;
    }
    uVar2 = uVar2 + 1;
  } while (uVar2 < 0x2d);
  if ((0x12 < param_1) && (param_1 < 0x25)) {
    p_Var1 = __getptd();
    p_Var1->_terrno = 0xd;
    return;
  }
  if ((0xbb < param_1) && (param_1 < 0xcb)) {
    p_Var1 = __getptd();
    p_Var1->_terrno = 8;
    return;
  }
  p_Var1 = __getptd();
  p_Var1->_terrno = 0x16;
  return;
}

