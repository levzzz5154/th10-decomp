/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x00420A90
 * Tracking name: FUN_00420a90
 * Ghidra name: FUN_00420a90
 * Tracked span: 128 bytes
 */


/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

undefined4 FUN_00420a90(undefined4 param_1,char *param_2)

{
  char cVar1;
  int iVar2;
  char *pcVar3;
  char local_104 [256];
  uint local_4;
  
  local_4 = DAT_00473660 ^ (uint)local_104;
  iVar2 = -(int)param_2;
  do {
    cVar1 = *param_2;
    param_2[(int)(local_104 + iVar2)] = cVar1;
    param_2 = param_2 + 1;
  } while (cVar1 != '\0');
  pcVar3 = _strrchr(local_104,0x2e);
  pcVar3[1] = 'w';
  pcVar3[2] = 'a';
  pcVar3[3] = 'v';
  FUN_0043e460(param_1,local_104,1,param_1);
  return 1;
}

