/* Raw Ghidra reference; not compilable reconstruction. Address: 004557FC */

/* Library Function - Single Match
    ___freetlocinfo
   
   Library: Visual Studio 2003 Release */

void __cdecl ___freetlocinfo(void *param_1)

{
  int *piVar1;
  undefined4 *puVar2;
  
  if (((*(int *)((int)param_1 + 0x3c) != DAT_00477624) && (*(int *)((int)param_1 + 0x3c) != 0)) &&
     (**(int **)((int)param_1 + 0x2c) == 0)) {
    piVar1 = *(int **)((int)param_1 + 0x34);
    if (((piVar1 != (int *)0x0) && (*piVar1 == 0)) && (piVar1 != DAT_004981c8)) {
      _free(piVar1);
      ___free_lconv_mon(*(int *)((int)param_1 + 0x3c));
    }
    piVar1 = *(int **)((int)param_1 + 0x30);
    if (((piVar1 != (int *)0x0) && (*piVar1 == 0)) && (piVar1 != DAT_004981d0)) {
      _free(piVar1);
      ___free_lconv_num(*(undefined4 **)((int)param_1 + 0x3c));
    }
    _free(*(void **)((int)param_1 + 0x2c));
    _free(*(void **)((int)param_1 + 0x3c));
  }
  piVar1 = *(int **)((int)param_1 + 0x40);
  if (((piVar1 != DAT_004981c4) && (piVar1 != (int *)0x0)) && (*piVar1 == 0)) {
    _free(piVar1);
    _free((void *)(*(int *)((int)param_1 + 0x44) + -0xfe));
  }
  puVar2 = *(undefined4 **)((int)param_1 + 0x50);
  if (((puVar2 != DAT_00477620) && (puVar2 != (undefined4 *)0x0)) && (puVar2[0x2d] == 0)) {
    ___free_lc_time(puVar2);
    _free(*(void **)((int)param_1 + 0x50));
  }
  _free(param_1);
  return;
}

