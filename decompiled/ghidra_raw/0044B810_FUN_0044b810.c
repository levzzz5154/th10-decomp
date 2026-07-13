/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x0044B810
 * Tracking name: FUN_0044b810
 * Ghidra name: FUN_0044b810
 * Tracked span: 208 bytes
 */


/* WARNING: Function: __chkstk replaced with injection: alloca_probe */
/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

char * __thiscall FUN_0044b810(void *this,char *param_1)

{
  char cVar1;
  char *pcVar2;
  undefined1 *puVar3;
  char *pcVar4;
  char *pcVar5;
  char local_2004 [8192];
  uint local_4;
  
  local_4 = DAT_00473660 ^ (uint)local_2004;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_004922bc);
  DAT_0049231f = DAT_0049231f + '\x01';
  _vsprintf(local_2004,param_1,&stack0x00000008);
  pcVar2 = local_2004;
  do {
    cVar1 = *pcVar2;
    pcVar2 = pcVar2 + 1;
  } while (cVar1 != '\0');
  pcVar5 = *(char **)((int)this + 0x2000);
  if (pcVar5 + ((int)pcVar2 - (int)(local_2004 + 1)) < (char *)((int)this + 0x1fffU)) {
    pcVar4 = local_2004;
    do {
      cVar1 = *pcVar4;
      pcVar4 = pcVar4 + 1;
      *pcVar5 = cVar1;
      pcVar5 = pcVar5 + 1;
    } while (cVar1 != '\0');
    puVar3 = (undefined1 *)(*(int *)((int)this + 0x2000) + ((int)pcVar2 - (int)(local_2004 + 1)));
    *(undefined1 **)((int)this + 0x2000) = puVar3;
    *puVar3 = 0;
  }
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_004922bc);
  DAT_0049231f = DAT_0049231f + -1;
  return param_1;
}

