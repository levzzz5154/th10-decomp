/* Raw Ghidra reference; not compilable reconstruction. Address: 0045F3D0 */

/* Library Function - Single Match
    ___crtMessageBoxA
   
   Library: Visual Studio 2003 Release */

int __cdecl ___crtMessageBoxA(LPCSTR _LpText,LPCSTR _LpCaption,UINT _UType)

{
  HMODULE hModule;
  int iVar1;
  int iVar2;
  undefined1 local_14 [8];
  byte local_c;
  undefined1 local_8 [4];
  
  iVar2 = 0;
  if (DAT_0047769c == (FARPROC)0x0) {
    hModule = LoadLibraryA("user32.dll");
    if ((hModule == (HMODULE)0x0) ||
       (DAT_0047769c = GetProcAddress(hModule,"MessageBoxA"), DAT_0047769c == (FARPROC)0x0)) {
      return 0;
    }
    DAT_004776a0 = GetProcAddress(hModule,"GetActiveWindow");
    DAT_004776a4 = GetProcAddress(hModule,"GetLastActivePopup");
    if ((DAT_00477470 == 2) &&
       (DAT_004776ac = GetProcAddress(hModule,"GetUserObjectInformationA"),
       DAT_004776ac != (FARPROC)0x0)) {
      DAT_004776a8 = GetProcAddress(hModule,"GetProcessWindowStation");
    }
  }
  if ((DAT_004776a8 == (FARPROC)0x0) ||
     (((iVar1 = (*DAT_004776a8)(), iVar1 != 0 &&
       (iVar1 = (*DAT_004776ac)(iVar1,1,local_14,0xc,local_8), iVar1 != 0)) && ((local_c & 1) != 0))
     )) {
    if (((DAT_004776a0 != (FARPROC)0x0) && (iVar2 = (*DAT_004776a0)(), iVar2 != 0)) &&
       (DAT_004776a4 != (FARPROC)0x0)) {
      iVar2 = (*DAT_004776a4)(iVar2);
    }
  }
  else if (DAT_0047747c < 4) {
    _UType = _UType | 0x40000;
  }
  else {
    _UType = _UType | 0x200000;
  }
  iVar2 = (*DAT_0047769c)(iVar2,_LpText,_LpCaption,_UType);
  return iVar2;
}

