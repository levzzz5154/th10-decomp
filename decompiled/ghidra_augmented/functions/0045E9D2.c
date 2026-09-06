/* Raw Ghidra reference; not compilable reconstruction. Address: 0045E9D2 */

/* Library Function - Single Match
    __handle_qnan2
   
   Library: Visual Studio 2003 Release */

float10 __cdecl __handle_qnan2(int param_1,double param_2,double param_3)

{
  int *piVar1;
  float10 fVar2;
  
  if (DAT_00473c90 == 0) {
    fVar2 = __umatherr(1,param_1);
    return fVar2;
  }
  piVar1 = FUN_00456af2();
  *piVar1 = 0x21;
  __ctrlfp();
  return (float10)(param_2 + param_3);
}

