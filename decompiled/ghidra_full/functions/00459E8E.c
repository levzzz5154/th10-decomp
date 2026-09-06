/* Raw Ghidra reference; not compilable reconstruction. Address: 00459E8E */

/* WARNING: Function: __SEH_prolog replaced with injection: SEH_prolog */
/* WARNING: Function: __SEH_epilog replaced with injection: EH_epilog3 */
/* Library Function - Multiple Matches With Different Base Names
    __lseek
    __write
   
   Library: Visual Studio 2003 Release */

int __cdecl __write(int _FileHandle,void *_Buf,uint _MaxCharCount)

{
  int *piVar1;
  ulong *puVar2;
  int iVar3;
  int local_20;
  
  if ((uint)_FileHandle < DAT_004991e4) {
    iVar3 = (_FileHandle & 0x1fU) * 0x24;
    if ((*(byte *)((&DAT_00499200)[_FileHandle >> 5] + 4 + iVar3) & 1) != 0) {
      __lock_fhandle(_FileHandle);
      if ((*(byte *)((&DAT_00499200)[_FileHandle >> 5] + 4 + iVar3) & 1) == 0) {
        piVar1 = FUN_00456af2();
        *piVar1 = 9;
        puVar2 = FUN_00456afb();
        *puVar2 = 0;
        local_20 = -1;
      }
      else {
        local_20 = FUN_00459cd2(_FileHandle,_Buf,_MaxCharCount);
      }
      FUN_00459f15();
      return local_20;
    }
  }
  piVar1 = FUN_00456af2();
  *piVar1 = 9;
  puVar2 = FUN_00456afb();
  *puVar2 = 0;
  return -1;
}

