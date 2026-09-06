/* Raw Ghidra reference; not compilable reconstruction. Address: 004601A1 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

long __cdecl FUN_004601a1(LCID param_1)

{
  int iVar1;
  long lVar2;
  CHAR local_10 [6];
  undefined1 local_a;
  uint local_8;
  
  local_8 = DAT_00473660 ^ (uint)&stack0xfffffffc;
  local_a = 0;
  iVar1 = GetLocaleInfoA(param_1,0x1004,local_10,6);
  if (iVar1 == 0) {
    lVar2 = -1;
  }
  else {
    lVar2 = _atol(local_10);
  }
  return lVar2;
}

