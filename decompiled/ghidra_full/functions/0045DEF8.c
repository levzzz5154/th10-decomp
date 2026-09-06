/* Raw Ghidra reference; not compilable reconstruction. Address: 0045DEF8 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __cdecl FUN_0045def8(undefined4 *param_1,undefined1 *param_2,size_t param_3,int param_4)

{
  char *pcVar1;
  int iVar2;
  char *pcVar3;
  STRFLT _PtFlt;
  int local_30;
  int local_2c;
  uint local_20 [6];
  uint local_8;
  
  local_8 = DAT_00473660 ^ (uint)&stack0xfffffffc;
  _PtFlt = (STRFLT)*param_1;
  FUN_00460e41(_PtFlt,param_1[1],&local_30,local_20);
  iVar2 = local_2c + -1;
  __fptostr(param_2 + (local_30 == 0x2d),param_3,(int)&local_30,_PtFlt);
  local_2c = local_2c + -1;
  if ((local_2c < -4) || ((int)param_3 <= local_2c)) {
    __cftoe2(param_3,param_4,'\x01');
  }
  else {
    pcVar1 = param_2 + (local_30 == 0x2d);
    if (iVar2 < local_2c) {
      do {
        pcVar3 = pcVar1;
        pcVar1 = pcVar3 + 1;
      } while (*pcVar3 != '\0');
      pcVar3[-1] = '\0';
    }
    __cftof2(param_2,param_3,'\x01');
  }
  return;
}

