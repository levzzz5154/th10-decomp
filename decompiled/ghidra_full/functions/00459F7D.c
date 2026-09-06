/* Raw Ghidra reference; not compilable reconstruction. Address: 00459F7D */

/* Library Function - Single Match
    __isatty
   
   Library: Visual Studio 2003 Release */

int __cdecl __isatty(int _FileHandle)

{
  if (DAT_004991e4 <= (uint)_FileHandle) {
    return 0;
  }
  return (int)*(char *)((&DAT_00499200)[_FileHandle >> 5] + 4 + (_FileHandle & 0x1fU) * 0x24) & 0x40
  ;
}

