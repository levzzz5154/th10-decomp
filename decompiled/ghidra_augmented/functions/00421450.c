/* Raw Ghidra reference; not compilable reconstruction. Address: 00421450 */

void FUN_00421450(void)

{
  int in_EAX;
  LPCRITICAL_SECTION lpCriticalSection;
  int iVar1;
  
  lpCriticalSection = (LPCRITICAL_SECTION)(in_EAX + 0x64c);
  iVar1 = 7;
  do {
    DeleteCriticalSection(lpCriticalSection);
    lpCriticalSection = lpCriticalSection + 1;
    iVar1 = iVar1 + -1;
  } while (iVar1 != 0);
  return;
}

