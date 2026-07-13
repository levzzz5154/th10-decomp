/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x00401690
 * Tracking name: FUN_00401690
 * Ghidra name: FUN_00401690
 * Tracked span: 208 bytes
 */


/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __cdecl FUN_00401690(char *param_1)

{
  int unaff_ESI;
  char local_204 [512];
  uint local_4;
  
  local_4 = DAT_00473660 ^ (uint)local_204;
  _vsprintf(local_204,param_1,&stack0x00000008);
  FUN_00401530(unaff_ESI);
  *(undefined4 *)(*(int *)(unaff_ESI + 0x896c) * 0x68 + 0x764 + unaff_ESI) = 1;
  return;
}

