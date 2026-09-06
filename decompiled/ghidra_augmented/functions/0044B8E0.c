/* Raw Ghidra reference; not compilable reconstruction. Address: 0044B8E0 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

char * __cdecl FUN_0044b8e0(char *param_1)

{
  char cVar1;
  char *pcVar2;
  undefined1 *puVar3;
  char *pcVar4;
  char *pcVar5;
  int unaff_EDI;
  char local_204 [512];
  uint local_4;
  
  local_4 = DAT_00473660 ^ (uint)local_204;
  pcVar2 = local_204;
  pcVar4 = local_204;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_004922bc);
  DAT_0049231f = DAT_0049231f + '\x01';
  _vsprintf(local_204,param_1,&stack0x00000008);
  do {
    cVar1 = *pcVar2;
    pcVar2 = pcVar2 + 1;
  } while (cVar1 != '\0');
  pcVar5 = *(char **)(unaff_EDI + 0x2000);
  if (pcVar5 + ((int)pcVar2 - (int)(local_204 + 1)) < (char *)(unaff_EDI + 0x1fffU)) {
    do {
      cVar1 = *pcVar4;
      pcVar4 = pcVar4 + 1;
      *pcVar5 = cVar1;
      pcVar5 = pcVar5 + 1;
    } while (cVar1 != '\0');
    puVar3 = (undefined1 *)(*(int *)(unaff_EDI + 0x2000) + ((int)pcVar2 - (int)(local_204 + 1)));
    *(undefined1 **)(unaff_EDI + 0x2000) = puVar3;
    *puVar3 = 0;
  }
  *(undefined1 *)(unaff_EDI + 0x2004) = 1;
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_004922bc);
  DAT_0049231f = DAT_0049231f + -1;
  return param_1;
}

