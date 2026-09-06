/* Raw Ghidra reference; not compilable reconstruction. Address: 0045D15C */

/* WARNING: Function: __SEH_prolog replaced with injection: SEH_prolog */
/* WARNING: Function: __SEH_epilog replaced with injection: EH_epilog3 */
/* Library Function - Single Match
    __setmbcp
   
   Library: Visual Studio 2003 Release */

int __cdecl __setmbcp(int _CodePage)

{
  int *_Memory;
  int iVar1;
  int local_24;
  
  local_24 = -1;
  __lock(0xd);
  DAT_00477690 = 0;
  if (_CodePage == -2) {
    DAT_00477690 = 1;
    _CodePage = GetOEMCP();
  }
  else if (_CodePage == -3) {
    DAT_00477690 = 1;
    _CodePage = GetACP();
  }
  else if (_CodePage == -4) {
    DAT_00477690 = 1;
    _CodePage = DAT_00477664;
  }
  if (_CodePage == DAT_004980a4) {
    local_24 = 0;
  }
  else {
    if ((DAT_00497f94 == (int *)0x0) || (_Memory = DAT_00497f94, *DAT_00497f94 != 0)) {
      _Memory = _malloc(0x220);
    }
    if ((_Memory != (int *)0x0) && (local_24 = FUN_0045cfb8(_CodePage), local_24 == 0)) {
      *_Memory = 0;
      _Memory[1] = DAT_004980a4;
      _Memory[2] = DAT_00497f98;
      _Memory[3] = DAT_00497f90;
      for (iVar1 = 0; iVar1 < 5; iVar1 = iVar1 + 1) {
        *(undefined2 *)((int)_Memory + iVar1 * 2 + 0x10) =
             *(undefined2 *)((int)&DAT_004980b0 + iVar1 * 2);
      }
      for (iVar1 = 0; iVar1 < 0x101; iVar1 = iVar1 + 1) {
        *(undefined1 *)(iVar1 + 0x1c + (int)_Memory) = *(undefined1 *)((int)&DAT_00497fa0 + iVar1);
      }
      for (iVar1 = 0; DAT_00497f94 = _Memory, iVar1 < 0x100; iVar1 = iVar1 + 1) {
        *(undefined1 *)(iVar1 + 0x11d + (int)_Memory) = (&DAT_004980c0)[iVar1];
      }
    }
    if ((local_24 == -1) && (_Memory != DAT_00497f94)) {
      _free(_Memory);
    }
  }
  FUN_0045d2a3();
  return local_24;
}

