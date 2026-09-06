/* Raw Ghidra reference; not compilable reconstruction. Address: 0045794D */

/* WARNING: Function: __SEH_prolog replaced with injection: SEH_prolog */
/* WARNING: Function: __SEH_epilog replaced with injection: EH_epilog3 */

int * __cdecl FUN_0045794d(uint param_1,uint param_2)

{
  int iVar1;
  uint *_Size;
  uint *dwBytes;
  int *_Dst;
  
  if ((param_1 == 0) || (param_2 <= 0xffffffe0 / param_1)) {
    _Size = (uint *)(param_1 * param_2);
    dwBytes = _Size;
    if (_Size == (uint *)0x0) {
      dwBytes = (uint *)0x1;
    }
    do {
      _Dst = (int *)0x0;
      if (dwBytes < (uint *)0xffffffe1) {
        if ((DAT_00499344 == 3) &&
           (dwBytes = (uint *)((int)dwBytes + 0xfU & 0xfffffff0), _Size <= DAT_00499330)) {
          __lock(4);
          _Dst = ___sbh_alloc_block(_Size);
          FUN_00457a13();
          if (_Dst != (int *)0x0) {
            _memset(_Dst,0,(size_t)_Size);
            goto LAB_004579db;
          }
        }
        else {
LAB_004579db:
          if (_Dst != (int *)0x0) {
            return _Dst;
          }
        }
        _Dst = HeapAlloc(DAT_00499340,8,(SIZE_T)dwBytes);
      }
      if (_Dst != (int *)0x0) {
        return _Dst;
      }
      if (DAT_00477364 == 0) {
        return (int *)0x0;
      }
      iVar1 = __callnewh((size_t)dwBytes);
    } while (iVar1 != 0);
  }
  return (int *)0x0;
}

