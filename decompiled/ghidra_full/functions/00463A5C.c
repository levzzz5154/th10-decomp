/* Raw Ghidra reference; not compilable reconstruction. Address: 00463A5C */

int FUN_00463a5c(int *param_1)

{
  int *piVar1;
  int iVar2;
  
  piVar1 = (int *)*param_1;
  if (((*piVar1 == -0x1f928c9d) && (piVar1[4] == 3)) &&
     ((piVar1[5] == 0x19930520 || (piVar1[5] == 0x19930521)))) {
    terminate();
  }
  if ((DAT_004776d8 != (_func_int *)0x0) && (iVar2 = _ValidateExecute(DAT_004776d8), iVar2 != 0)) {
    iVar2 = (*DAT_004776d8)(param_1);
    return iVar2;
  }
  return 0;
}

