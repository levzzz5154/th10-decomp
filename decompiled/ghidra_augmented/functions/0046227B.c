/* Raw Ghidra reference; not compilable reconstruction. Address: 0046227B */

uint * __cdecl FUN_0046227b(uint *param_1,uint param_2)

{
  byte bVar1;
  byte bVar2;
  _ptiddata p_Var3;
  pthreadmbcinfo ptVar4;
  uint *puVar5;
  uint uVar6;
  
  p_Var3 = __getptd();
  ptVar4 = p_Var3->_tpxcptinfoptrs;
  if (ptVar4 != DAT_00497f94) {
    ptVar4 = ___updatetmbcinfo();
  }
  if (ptVar4->ismbcodepage == 0) {
    puVar5 = FUN_00452730(param_1,(char)param_2);
    return puVar5;
  }
  while( true ) {
    bVar2 = (byte)*param_1;
    uVar6 = (uint)bVar2;
    if (bVar2 == 0) break;
    if ((ptVar4->mbctype[uVar6 + 5] & 4) == 0) {
      puVar5 = param_1;
      if (param_2 == uVar6) break;
    }
    else {
      bVar1 = *(byte *)((int)param_1 + 1);
      if (bVar1 == 0) {
        return (uint *)0x0;
      }
      puVar5 = (uint *)((int)param_1 + 1);
      if (param_2 == CONCAT11(bVar2,bVar1)) {
        return param_1;
      }
    }
    param_1 = (uint *)((int)puVar5 + 1);
  }
  return (uint *)(~-(uint)(param_2 != uVar6) & (uint)param_1);
}

