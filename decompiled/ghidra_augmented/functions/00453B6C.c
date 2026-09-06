/* Raw Ghidra reference; not compilable reconstruction. Address: 00453B6C */

/* WARNING: Function: __SEH_prolog replaced with injection: SEH_prolog */
/* WARNING: Function: __SEH_epilog replaced with injection: EH_epilog3 */
/* Library Function - Single Match
    __mtinitlocknum
   
   Library: Visual Studio 2003 Release */

int __cdecl __mtinitlocknum(int _LockNum)

{
  void *_Memory;
  int *piVar1;
  int iVar2;
  undefined1 local_14 [8];
  undefined4 uStack_c;
  undefined *local_8;
  
  local_8 = &DAT_0046a780;
  uStack_c = 0x453b78;
  piVar1 = &DAT_00473080 + _LockNum * 2;
  if (*piVar1 == 0) {
    _Memory = _malloc(0x18);
    if (_Memory == (void *)0x0) {
      piVar1 = FUN_00456af2();
      *piVar1 = 0xc;
      return 0;
    }
    __lock(10);
    local_8 = (undefined *)0x0;
    if (*piVar1 == 0) {
      iVar2 = ___crtInitCritSecAndSpinCount(_Memory,4000);
      if (iVar2 == 0) {
        _free(_Memory);
        piVar1 = FUN_00456af2();
        *piVar1 = 0xc;
        __local_unwind2((int)local_14,-1);
        return 0;
      }
      *piVar1 = (int)_Memory;
    }
    else {
      _free(_Memory);
    }
    local_8 = (undefined *)0xffffffff;
    FUN_00453c03();
  }
  return 1;
}

