/* Raw Ghidra reference; not compilable reconstruction. Address: 004563C8 */

/* WARNING: Function: __SEH_prolog replaced with injection: SEH_prolog */
/* WARNING: Function: __SEH_epilog replaced with injection: EH_epilog3 */
/* Library Function - Single Match
    __freefls@4
   
   Library: Visual Studio 2003 Release */

void __freefls_4(void *param_1)

{
  int *piVar1;
  
  if (param_1 != (void *)0x0) {
    if (*(void **)((int)param_1 + 0x24) != (void *)0x0) {
      _free(*(void **)((int)param_1 + 0x24));
    }
    if (*(void **)((int)param_1 + 0x2c) != (void *)0x0) {
      _free(*(void **)((int)param_1 + 0x2c));
    }
    if (*(void **)((int)param_1 + 0x34) != (void *)0x0) {
      _free(*(void **)((int)param_1 + 0x34));
    }
    if (*(void **)((int)param_1 + 0x3c) != (void *)0x0) {
      _free(*(void **)((int)param_1 + 0x3c));
    }
    if (*(void **)((int)param_1 + 0x44) != (void *)0x0) {
      _free(*(void **)((int)param_1 + 0x44));
    }
    if (*(void **)((int)param_1 + 0x48) != (void *)0x0) {
      _free(*(void **)((int)param_1 + 0x48));
    }
    if (*(undefined **)((int)param_1 + 0x54) != &DAT_004735d0) {
      _free(*(undefined **)((int)param_1 + 0x54));
    }
    __lock(0xd);
    piVar1 = *(int **)((int)param_1 + 0x60);
    if (((piVar1 != (int *)0x0) && (*piVar1 = *piVar1 + -1, *piVar1 == 0)) &&
       (piVar1 != DAT_00497f94)) {
      _free(piVar1);
    }
    FUN_004564fa();
    __lock(0xc);
    piVar1 = *(int **)((int)param_1 + 100);
    if (piVar1 != (int *)0x0) {
      *piVar1 = *piVar1 + -1;
      if (piVar1[0xb] != 0) {
        *(int *)piVar1[0xb] = *(int *)piVar1[0xb] + -1;
      }
      if (piVar1[0xd] != 0) {
        *(int *)piVar1[0xd] = *(int *)piVar1[0xd] + -1;
      }
      if (piVar1[0xc] != 0) {
        *(int *)piVar1[0xc] = *(int *)piVar1[0xc] + -1;
      }
      if (piVar1[0x10] != 0) {
        *(int *)piVar1[0x10] = *(int *)piVar1[0x10] + -1;
      }
      *(int *)(piVar1[0x13] + 0xb4) = *(int *)(piVar1[0x13] + 0xb4) + -1;
      if (((piVar1 != (int *)PTR_DAT_0047320c) && (piVar1 != &DAT_004731b8)) && (*piVar1 == 0)) {
        ___freetlocinfo(piVar1);
      }
    }
    FUN_00456506();
    _free(param_1);
  }
  return;
}

