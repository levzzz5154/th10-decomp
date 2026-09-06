/* Raw Ghidra reference; not compilable reconstruction. Address: 00401690 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __cdecl AppendMarkedGameThreadRecord(char *param_1)

{
  int unaff_ESI;
  char local_204 [512];
  uint local_4;
  
  local_4 = DAT_00473660 ^ (uint)local_204;
  _vsprintf(local_204,param_1,&stack0x00000008);
  AppendGameThreadRecord(unaff_ESI);
  *(undefined4 *)(*(int *)(unaff_ESI + 0x896c) * 0x68 + 0x764 + unaff_ESI) = 1;
  return;
}

