/* Raw Ghidra reference; not compilable reconstruction. Address: 00452ABC */

undefined4 __cdecl FUN_00452abc(LPCSTR param_1)

{
  BOOL BVar1;
  ulong uVar2;
  
  BVar1 = CreateDirectoryA(param_1,(LPSECURITY_ATTRIBUTES)0x0);
  if (BVar1 == 0) {
    uVar2 = GetLastError();
  }
  else {
    uVar2 = 0;
  }
  if (uVar2 != 0) {
    __dosmaperr(uVar2);
    return 0xffffffff;
  }
  return 0;
}

