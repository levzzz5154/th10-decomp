/* Raw Ghidra reference; not compilable reconstruction. Address: 0045DB86 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

uint __cdecl FUN_0045db86(_LDOUBLE *param_1,int *param_2,byte *param_3,int param_4)

{
  uint uVar1;
  INTRNCVT_STATUS IVar2;
  _LDBL12 local_14;
  uint local_8;
  
  local_8 = DAT_00473660 ^ (uint)&stack0xfffffffc;
  uVar1 = FUN_0045d746((undefined2 *)&local_14,param_2,param_3,param_4,0,0,0);
  IVar2 = __ld12told(&local_14,param_1);
  if (IVar2 == INTRNCVT_OVERFLOW) {
    uVar1 = uVar1 | 2;
  }
  return uVar1;
}

