/* Raw Ghidra reference; not compilable reconstruction. Address: 0045DE91 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

undefined1 * __cdecl FUN_0045de91(undefined4 *param_1,undefined1 *param_2,size_t param_3)

{
  STRFLT _PtFlt;
  int local_30;
  int local_2c;
  uint local_20 [6];
  uint local_8;
  
  local_8 = DAT_00473660 ^ (uint)&stack0xfffffffc;
  _PtFlt = (STRFLT)*param_1;
  FUN_00460e41(_PtFlt,param_1[1],&local_30,local_20);
  __fptostr(param_2 + (local_30 == 0x2d),local_2c + param_3,(int)&local_30,_PtFlt);
  __cftof2(param_2,param_3,'\0');
  return param_2;
}

