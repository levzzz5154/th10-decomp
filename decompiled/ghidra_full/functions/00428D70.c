/* Raw Ghidra reference; not compilable reconstruction. Address: 00428D70 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 __thiscall FUN_00428d70(void *this,float param_1,float param_2)

{
  float fVar1;
  
  if ((((param_1 + *(float *)this < _DAT_00470b40 == (param_1 + *(float *)this == _DAT_00470b40)) &&
       (*(float *)this - param_1 < _DAT_00470b3c)) &&
      (fVar1 = param_2 + *(float *)((int)this + 4),
      fVar1 < _DAT_00470b04 == (fVar1 == _DAT_00470b04))) &&
     (*(float *)((int)this + 4) - param_2 < _DAT_00470b38)) {
    return 0;
  }
  return 1;
}

