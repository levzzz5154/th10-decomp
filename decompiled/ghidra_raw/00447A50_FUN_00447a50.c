/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x00447A50
 * Tracking name: FUN_00447a50
 * Ghidra name: FUN_00447a50
 * Tracked span: 144 bytes
 */


/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __cdecl FUN_00447a50(undefined4 param_1,COLORREF param_2,char *param_3)

{
  int unaff_ESI;
  char local_84 [128];
  uint local_4;
  
  local_4 = DAT_00473660 ^ (uint)local_84;
  _vsprintf(local_84,param_3,&stack0x00000010);
  FUN_004479d0(*(int **)(*(int *)(unaff_ESI + 0x394) + 4),0,param_2,
               *(uint *)(unaff_ESI + 0x360) >> 1 & 1);
  *(uint *)(unaff_ESI + 0x35c) = *(uint *)(unaff_ESI + 0x35c) | 1;
  return;
}

