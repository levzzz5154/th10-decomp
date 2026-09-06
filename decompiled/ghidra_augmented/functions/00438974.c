/* Raw Ghidra reference; not compilable reconstruction. Address: 00438974 */

void FUN_00438974(void)

{
  char cVar1;
  LPCSTR pCVar2;
  LPCSTR unaff_ESI;
  LPCSTR in_stack_ffffb905;
  UINT in_stack_ffffb909;
  
  MessageBoxA((HWND)0x0,unaff_ESI,in_stack_ffffb905,in_stack_ffffb909);
  pCVar2 = unaff_ESI;
  do {
    cVar1 = *pCVar2;
    pCVar2 = pCVar2 + 1;
  } while (cVar1 != '\0');
  WriteWholeFile("./log.txt",unaff_ESI);
  return;
}

