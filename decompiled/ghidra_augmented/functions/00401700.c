/* Raw Ghidra reference; not compilable reconstruction. Address: 00401700 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

int __cdecl FUN_00401700(char *param_1)

{
  char cVar1;
  char *pcVar2;
  char local_204 [512];
  uint local_4;
  
  local_4 = DAT_00473660 ^ (uint)local_204;
  _vsprintf(local_204,param_1,&stack0x00000008);
  pcVar2 = local_204;
  FUN_004015c0(local_204);
  do {
    cVar1 = *pcVar2;
    pcVar2 = pcVar2 + 1;
  } while (cVar1 != '\0');
  return (int)pcVar2 - (int)(local_204 + 1);
}

