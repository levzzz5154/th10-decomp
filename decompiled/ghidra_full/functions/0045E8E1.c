/* Raw Ghidra reference; not compilable reconstruction. Address: 0045E8E1 */

/* Library Function - Single Match
    __umatherr
   
   Library: Visual Studio 2003 Release */

float10 __cdecl __umatherr(int param_1,int param_2)

{
  int iVar1;
  undefined4 in_stack_0000001c;
  undefined4 in_stack_00000020;
  
  iVar1 = 0;
  do {
    if ((&DAT_00473c98)[iVar1 * 2] == param_2) {
      iVar1 = *(int *)(iVar1 * 8 + 0x473c9c);
      goto LAB_0045e8fd;
    }
    iVar1 = iVar1 + 1;
  } while (iVar1 < 0x1d);
  iVar1 = 0;
LAB_0045e8fd:
  if (iVar1 != 0) {
    __ctrlfp();
    iVar1 = FUN_0045e3a0();
    if (iVar1 == 0) {
      FID_conflict___set_errno_from_matherr(param_1);
    }
    return (float10)(double)CONCAT44(in_stack_00000020,in_stack_0000001c);
  }
  __ctrlfp();
  FID_conflict___set_errno_from_matherr(param_1);
  return (float10)(double)CONCAT44(in_stack_00000020,in_stack_0000001c);
}

