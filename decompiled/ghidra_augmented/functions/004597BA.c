/* Raw Ghidra reference; not compilable reconstruction. Address: 004597BA */

/* WARNING: Function: __SEH_prolog replaced with injection: SEH_prolog */
/* WARNING: Function: __SEH_epilog replaced with injection: EH_epilog3 */

void FUN_004597ba(void)

{
  undefined4 *local_20;
  
  for (local_20 = &DAT_00471130; local_20 < &DAT_00471130; local_20 = local_20 + 1) {
    if ((code *)*local_20 != (code *)0x0) {
      (*(code *)*local_20)();
    }
  }
  return;
}

