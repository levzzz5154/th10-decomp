/* Raw Ghidra reference; not compilable reconstruction. Address: 00421C50 */

void FUN_00421c50(void)

{
  char *pcVar1;
  int unaff_ESI;
  int unaff_EDI;
  
  LeaveCriticalSection((LPCRITICAL_SECTION)(unaff_EDI + 0x64c + unaff_ESI * 0x18));
  pcVar1 = (char *)(unaff_ESI + 0x6f4 + unaff_EDI);
  *pcVar1 = *pcVar1 + -1;
  return;
}

