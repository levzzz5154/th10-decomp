/* Raw Ghidra reference; not compilable reconstruction. Address: 00447EC0 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

undefined4 __fastcall FUN_00447ec0(int param_1,int param_2)

{
  byte *pbVar1;
  size_t local_10c;
  char local_108 [260];
  uint local_4;
  
  local_4 = DAT_00473660 ^ (uint)&local_10c;
  if (*(int *)(param_2 + 0x3ad4e0 + param_1 * 4) != 0) {
    FUN_00447f70();
  }
  _sprintf(local_108,"%s");
  pbVar1 = FUN_0044b360(&local_10c,0);
  if (pbVar1 == (byte *)0x0) {
    FUN_0044b8e0(&DAT_00470150);
    return 0xffffffff;
  }
  *(byte **)(param_2 + 0x3ad5e0 + param_1 * 4) = pbVar1;
  *(size_t *)(param_2 + 0x3ad660 + param_1 * 4) = local_10c;
  return 0;
}

