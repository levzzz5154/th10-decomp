/* Raw Ghidra reference; not compilable reconstruction. Address: 00401630 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __cdecl AppendFormattedGameThreadRecord(int param_1,char *param_2)

{
  char local_204 [512];
  uint local_4;
  
  local_4 = DAT_00473660 ^ (uint)local_204;
  _vsprintf(local_204,param_2,&stack0x0000000c);
  AppendGameThreadRecord(param_1);
  return;
}

