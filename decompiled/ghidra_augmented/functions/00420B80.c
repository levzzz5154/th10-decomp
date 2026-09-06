/* Raw Ghidra reference; not compilable reconstruction. Address: 00420B80 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

undefined4 FUN_00420b80(char *param_1)

{
  char cVar1;
  int iVar2;
  char *pcVar3;
  int unaff_ESI;
  char local_104 [256];
  uint local_4;
  
  local_4 = DAT_00473660 ^ (uint)local_104;
  iVar2 = -(int)param_1;
  do {
    cVar1 = *param_1;
    param_1[(int)(local_104 + iVar2)] = cVar1;
    param_1 = param_1 + 1;
  } while (cVar1 != '\0');
  pcVar3 = _strrchr(local_104,0x2e);
  iVar2 = DAT_0047783c;
  pcVar3[1] = 'w';
  pcVar3[2] = 'a';
  pcVar3[3] = 'v';
  *(undefined1 *)(iVar2 + 0x1d892 + unaff_ESI) = 1;
  FUN_0043e460(iVar2,local_104,2,0xffffffff);
  return 0;
}

