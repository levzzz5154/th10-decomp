/* Raw Ghidra reference; not compilable reconstruction. Address: 0045F6D4 */

/* Library Function - Single Match
    __get_osfhandle
   
   Library: Visual Studio 2003 Release */

intptr_t __cdecl __get_osfhandle(int _FileHandle)

{
  intptr_t *piVar1;
  int *piVar2;
  ulong *puVar3;
  
  if (((uint)_FileHandle < DAT_004991e4) &&
     (piVar1 = (intptr_t *)((&DAT_00499200)[_FileHandle >> 5] + (_FileHandle & 0x1fU) * 0x24),
     (*(byte *)(piVar1 + 1) & 1) != 0)) {
    return *piVar1;
  }
  piVar2 = FUN_00456af2();
  *piVar2 = 9;
  puVar3 = FUN_00456afb();
  *puVar3 = 0;
  return -1;
}

