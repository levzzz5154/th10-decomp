/* Raw Ghidra reference; not compilable reconstruction. Address: 00459C27 */

/* WARNING: Function: __SEH_prolog replaced with injection: SEH_prolog */
/* WARNING: Function: __SEH_epilog replaced with injection: EH_epilog3 */
/* Library Function - Single Match
    __lseek
   
   Library: Visual Studio 2003 Release */

long __cdecl __lseek(int _FileHandle,long _Offset,int _Origin)

{
  int *piVar1;
  ulong *puVar2;
  int iVar3;
  DWORD local_20;
  
  if ((uint)_FileHandle < DAT_004991e4) {
    iVar3 = (_FileHandle & 0x1fU) * 0x24;
    if ((*(byte *)((&DAT_00499200)[_FileHandle >> 5] + 4 + iVar3) & 1) != 0) {
      __lock_fhandle(_FileHandle);
      if ((*(byte *)((&DAT_00499200)[_FileHandle >> 5] + 4 + iVar3) & 1) == 0) {
        piVar1 = FUN_00456af2();
        *piVar1 = 9;
        puVar2 = FUN_00456afb();
        *puVar2 = 0;
        local_20 = 0xffffffff;
      }
      else {
        local_20 = __lseek_lk(_FileHandle,_Offset,_Origin);
      }
      FUN_00459cae();
      return local_20;
    }
  }
  piVar1 = FUN_00456af2();
  *piVar1 = 9;
  puVar2 = FUN_00456afb();
  *puVar2 = 0;
  return -1;
}

