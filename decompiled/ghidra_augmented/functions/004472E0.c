/* Raw Ghidra reference; not compilable reconstruction. Address: 004472E0 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

undefined4 __fastcall FUN_004472e0(int param_1,int param_2,int param_3)

{
  byte *pbVar1;
  char *pcVar2;
  size_t local_10c;
  char local_108 [260];
  uint local_4;
  
  local_4 = DAT_00473660 ^ (uint)&local_10c;
  if (param_3 == 0) {
    pcVar2 = &DAT_00470274;
  }
  else {
    if (*(int *)(param_3 + 0x28) == 4) {
      if ((*(char *)(param_3 + 0x34) == '\0') &&
         (pcVar2 = (char *)(*(int *)(param_3 + 0x1c) + param_3), *pcVar2 != '@')) {
        _sprintf(local_108,"%s",pcVar2);
        pbVar1 = FUN_0044b360(&local_10c,1);
        if (pbVar1 == (byte *)0x0) {
          FUN_0044b8e0(&DAT_00470210);
          return 0xffffffff;
        }
        *(size_t *)(*(int *)(param_2 + 0x120) + 8 + param_1 * 0x10) = local_10c;
        *(byte **)(*(int *)(param_2 + 0x120) + 4 + param_1 * 0x10) = pbVar1;
      }
      return 1;
    }
    pcVar2 = &DAT_00470254;
  }
  FUN_0044b8e0(pcVar2);
  return 0xffffffff;
}

