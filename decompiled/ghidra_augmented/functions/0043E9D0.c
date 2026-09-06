/* Raw Ghidra reference; not compilable reconstruction. Address: 0043E9D0 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void FUN_0043e9d0(void)

{
  int *piVar1;
  char cVar2;
  char *pcVar3;
  int iVar4;
  byte *pbVar5;
  int unaff_ESI;
  undefined4 uStackY_11c;
  size_t local_10c;
  char local_108 [260];
  uint local_4;
  
  local_4 = DAT_00473660 ^ (uint)&local_10c;
  uStackY_11c = 0x43e9fb;
  _sprintf(local_108,"%s");
  pcVar3 = local_108;
  do {
    cVar2 = *pcVar3;
    pcVar3 = pcVar3 + 1;
  } while (cVar2 != '\0');
  iVar4 = -(int)&stack0xfffffee8;
  pcVar3[(int)&uStackY_11c + iVar4] = 'm';
  pcVar3[(int)&uStackY_11c + iVar4 + 1] = 'a';
  pcVar3[(int)&uStackY_11c + iVar4 + 2] = 'p';
  iVar4 = ProbeFileExists(local_108);
  if (iVar4 == 0) {
    *(undefined4 *)(unaff_ESI + 300) = 0;
  }
  else {
    pbVar5 = FUN_0044b360(&local_10c,1);
    *(byte **)(unaff_ESI + 300) = pbVar5;
    iVar4 = 0;
    if (0 < *(int *)(unaff_ESI + 0x110) + *(int *)(unaff_ESI + 0x114)) {
      do {
        piVar1 = (int *)(*(int *)(unaff_ESI + 300) + iVar4 * 4);
        *piVar1 = *piVar1 + *(int *)(unaff_ESI + 300);
        iVar4 = iVar4 + 1;
      } while (iVar4 < *(int *)(unaff_ESI + 0x110) + *(int *)(unaff_ESI + 0x114));
      return;
    }
  }
  return;
}

