/* Raw Ghidra reference; not compilable reconstruction. Address: 0045A0EB */

/* Library Function - Single Match
    __unlock_file2
   
   Libraries: Visual Studio 2003 Release, Visual Studio 2005 Release */

void __cdecl __unlock_file2(int _Index,void *_File)

{
  if (_Index < 0x14) {
    FUN_00453b3f(_Index + 0x10);
    return;
  }
  LeaveCriticalSection((LPCRITICAL_SECTION)((int)_File + 0x20));
  return;
}

