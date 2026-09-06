/* Raw Ghidra reference; not compilable reconstruction. Address: 00458C39 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Library Function - Single Match
    __floor_default
   
   Library: Visual Studio 2003 Release */

float10 __cdecl __floor_default(double param_1)

{
  double dVar1;
  uint uVar2;
  int iVar3;
  float10 fVar4;
  uint uVar5;
  
  uVar2 = __ctrlfp();
  if ((param_1._6_2_ & 0x7ff0) == 0x7ff0) {
    iVar3 = __sptype(SUB84(param_1,0),(uint)((ulonglong)param_1 >> 0x20));
    if (0 < iVar3) {
      if (iVar3 < 3) {
        __ctrlfp();
        return (float10)param_1;
      }
      if (iVar3 == 3) {
        fVar4 = __handle_qnan1(0xb,param_1);
        return fVar4;
      }
    }
    dVar1 = param_1 + _DAT_0046ac28;
    uVar5 = 8;
  }
  else {
    fVar4 = __frnd(param_1);
    dVar1 = (double)fVar4;
    if ((dVar1 == param_1) || ((uVar2 & 0x20) != 0)) {
      __ctrlfp();
      return (float10)dVar1;
    }
    uVar5 = 0x10;
  }
  fVar4 = FUN_0045ea31(uVar5,0xb,param_1,dVar1,uVar2);
  return fVar4;
}

