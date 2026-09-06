/* Raw Ghidra reference; not compilable reconstruction. Address: 00457395 */

/* WARNING: Function: __SEH_prolog replaced with injection: SEH_prolog */
/* WARNING: Function: __SEH_epilog replaced with injection: EH_epilog3 */

int * __cdecl FUN_00457395(int *param_1,uint *param_2)

{
  int *piVar1;
  int iVar2;
  uint *puVar3;
  uint *local_24;
  int *local_20;
  
  if (param_1 == (int *)0x0) {
    piVar1 = _malloc((size_t)param_2);
    return piVar1;
  }
  if (param_2 == (uint *)0x0) {
    _free(param_1);
    return (int *)0x0;
  }
  if (DAT_00499344 == 3) {
    do {
      local_20 = (int *)0x0;
      if ((uint *)0xffffffe0 < param_2) {
LAB_00457538:
        __callnewh((size_t)param_2);
        return (int *)0x0;
      }
      __lock(4);
      local_24 = (uint *)___sbh_find_block((int)param_1);
      if (local_24 != (uint *)0x0) {
        if (param_2 <= DAT_00499330) {
          iVar2 = ___sbh_resize_block(local_24,(int)param_1,(int)param_2);
          if (iVar2 == 0) {
            local_20 = ___sbh_alloc_block(param_2);
            if (local_20 != (int *)0x0) {
              puVar3 = (uint *)(param_1[-1] - 1U);
              if (param_2 <= (uint *)(param_1[-1] - 1U)) {
                puVar3 = param_2;
              }
              _memcpy(local_20,param_1,(size_t)puVar3);
              local_24 = (uint *)___sbh_find_block((int)param_1);
              ___sbh_free_block(local_24,(int)param_1);
            }
          }
          else {
            local_20 = param_1;
          }
        }
        if (local_20 == (int *)0x0) {
          if (param_2 == (uint *)0x0) {
            param_2 = (uint *)0x1;
          }
          param_2 = (uint *)((int)param_2 + 0xfU & 0xfffffff0);
          local_20 = HeapAlloc(DAT_00499340,0,(SIZE_T)param_2);
          if (local_20 != (int *)0x0) {
            puVar3 = (uint *)(param_1[-1] - 1U);
            if (param_2 <= (uint *)(param_1[-1] - 1U)) {
              puVar3 = param_2;
            }
            _memcpy(local_20,param_1,(size_t)puVar3);
            ___sbh_free_block(local_24,(int)param_1);
          }
        }
      }
      FUN_004574fd();
      if (local_24 == (uint *)0x0) {
        if (param_2 == (uint *)0x0) {
          param_2 = (uint *)0x1;
        }
        param_2 = (uint *)((int)param_2 + 0xfU & 0xfffffff0);
        local_20 = HeapReAlloc(DAT_00499340,0,param_1,(SIZE_T)param_2);
      }
      if (local_20 != (int *)0x0) {
        return local_20;
      }
      if (DAT_00477364 == 0) {
        return (int *)0x0;
      }
      iVar2 = __callnewh((size_t)param_2);
    } while (iVar2 != 0);
  }
  else {
    do {
      if ((uint *)0xffffffe0 < param_2) goto LAB_00457538;
      if (param_2 == (uint *)0x0) {
        param_2 = (uint *)0x1;
      }
      piVar1 = HeapReAlloc(DAT_00499340,0,param_1,(SIZE_T)param_2);
      if (piVar1 != (int *)0x0) {
        return piVar1;
      }
      if (DAT_00477364 == 0) {
        return (int *)0x0;
      }
      iVar2 = __callnewh((size_t)param_2);
    } while (iVar2 != 0);
  }
  return (int *)0x0;
}

