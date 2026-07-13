/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x00401630
 * Tracking name: FUN_00401630
 * Ghidra name: FUN_00401630
 * Tracked span: 96 bytes
 */


/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __cdecl FUN_00401630(int param_1,char *param_2)

{
  char local_204 [512];
  uint local_4;
  
  local_4 = DAT_00473660 ^ (uint)local_204;
  _vsprintf(local_204,param_2,&stack0x0000000c);
  FUN_00401530(param_1);
  return;
}

