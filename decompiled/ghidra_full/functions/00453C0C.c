/* Raw Ghidra reference; not compilable reconstruction. Address: 00453C0C */

/* Library Function - Single Match
    __lock
   
   Library: Visual Studio 2003 Release */

void __cdecl __lock(int _File)

{
  int iVar1;
  
  if ((&DAT_00473080)[_File * 2] == 0) {
    iVar1 = __mtinitlocknum(_File);
    if (iVar1 == 0) {
      __amsg_exit(0x11);
    }
  }
  EnterCriticalSection((LPCRITICAL_SECTION)(&DAT_00473080)[_File * 2]);
  return;
}

