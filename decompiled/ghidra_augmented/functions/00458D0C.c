/* Raw Ghidra reference; not compilable reconstruction. Address: 00458D0C */

/* Library Function - Single Match
    __mbctoupper
   
   Library: Visual Studio 2003 Release */

uint __cdecl __mbctoupper(uint _Ch)

{
  _ptiddata p_Var1;
  pthreadmbcinfo ptVar2;
  uint uVar3;
  undefined2 local_c;
  CHAR local_8;
  undefined1 local_7;
  undefined2 uStack_6;
  
  p_Var1 = __getptd();
  ptVar2 = p_Var1->_tpxcptinfoptrs;
  if (ptVar2 != DAT_00497f94) {
    ptVar2 = ___updatetmbcinfo();
  }
  if (_Ch < 0x100) {
    if ((ptVar2->mbctype[_Ch + 5] & 0x20) != 0) {
      _Ch = (uint)(char)ptVar2->mbcasemap[_Ch + 4];
    }
  }
  else {
    _local_8 = CONCAT11((char)_Ch,(char)(_Ch >> 8));
    if (((ptVar2->mbctype[(_Ch >> 8 & 0xff) + 5] & 4) != 0) &&
       (uVar3 = FUN_0045ee1d(*(LCID *)ptVar2->mbulinfo,0x200,&local_8,2,(int *)&local_c,2,
                             ptVar2->mbcodepage,1), uVar3 != 0)) {
      _Ch = (uint)CONCAT11((undefined1)local_c,local_c._1_1_);
    }
  }
  return _Ch;
}

