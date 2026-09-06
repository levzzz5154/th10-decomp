/* Raw Ghidra reference; not compilable reconstruction. Address: 00406160 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 __thiscall FUN_00406160(void *this,float param_1,float param_2)

{
  float fVar1;
  
  fVar1 = param_1 * _DAT_00470b0c + *(float *)this;
  if ((((fVar1 < _DAT_00470b40 == (fVar1 == _DAT_00470b40)) &&
       (*(float *)this - param_1 * _DAT_00470b0c < _DAT_00470b3c)) &&
      (fVar1 = param_2 * _DAT_00470b0c + *(float *)((int)this + 4),
      fVar1 < _DAT_00470b5c == (fVar1 == _DAT_00470b5c))) &&
     (*(float *)((int)this + 4) - param_2 * _DAT_00470b0c < _DAT_00470b38)) {
    return 0;
  }
  return 1;
}

