/* Raw Ghidra reference; not compilable reconstruction. Address: 0045DD85 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

int __cdecl FUN_0045dd85(undefined4 *param_1,int param_2,int param_3,int param_4)

{
  STRFLT _PtFlt;
  int local_30 [4];
  uint local_20 [6];
  uint local_8;
  
  local_8 = DAT_00473660 ^ (uint)&stack0xfffffffc;
  _PtFlt = (STRFLT)*param_1;
  FUN_00460e41(_PtFlt,param_1[1],local_30,local_20);
  __fptostr((char *)((uint)(0 < param_3) + (uint)(local_30[0] == 0x2d) + param_2),param_3 + 1,
            (int)local_30,_PtFlt);
  __cftoe2(param_3,param_4,'\0');
  return param_2;
}

