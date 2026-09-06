/* Raw Ghidra reference; not compilable reconstruction. Address: 0043A5C0 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __fastcall FUN_0043a5c0(UINT_PTR param_1)

{
  char cVar1;
  CHAR *pCVar2;
  int iVar3;
  int unaff_ESI;
  tagMIDIOUTCAPSA local_38;
  uint local_4;
  
  local_4 = DAT_00473660 ^ (uint)&local_38;
  midiOutGetDevCapsA(param_1,&local_38,0x34);
  pCVar2 = local_38.szPname;
  iVar3 = unaff_ESI - (int)pCVar2;
  do {
    cVar1 = *pCVar2;
    pCVar2[iVar3] = cVar1;
    pCVar2 = pCVar2 + 1;
  } while (cVar1 != '\0');
  return;
}

