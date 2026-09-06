/* Raw Ghidra reference; not compilable reconstruction. Address: 0046218A */

/* WARNING: Function: __SEH_prolog replaced with injection: SEH_prolog */
/* WARNING: Function: __SEH_epilog replaced with injection: EH_epilog3 */

undefined4 __cdecl FUN_0046218a(uint param_1)

{
  int *piVar1;
  ulong *puVar2;
  int iVar3;
  undefined4 local_20;
  
  if (param_1 < DAT_004991e4) {
    iVar3 = (param_1 & 0x1f) * 0x24;
    if ((*(byte *)((&DAT_00499200)[(int)param_1 >> 5] + 4 + iVar3) & 1) != 0) {
      __lock_fhandle(param_1);
      if ((*(byte *)((&DAT_00499200)[(int)param_1 >> 5] + 4 + iVar3) & 1) == 0) {
        piVar1 = FUN_00456af2();
        *piVar1 = 9;
        local_20 = 0xffffffff;
      }
      else {
        local_20 = __close_lk(param_1);
      }
      FUN_00462201();
      return local_20;
    }
  }
  piVar1 = FUN_00456af2();
  *piVar1 = 9;
  puVar2 = FUN_00456afb();
  *puVar2 = 0;
  return 0xffffffff;
}

