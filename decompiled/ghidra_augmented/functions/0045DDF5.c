/* Raw Ghidra reference; not compilable reconstruction. Address: 0045DDF5 */

/* Library Function - Single Match
    __cftof2
   
   Library: Visual Studio 2003 Release */

undefined1 * __cdecl __cftof2(undefined1 *param_1,size_t param_2,char param_3)

{
  int iVar1;
  int iVar2;
  int *in_EAX;
  undefined1 *puVar3;
  size_t sVar4;
  
  iVar1 = in_EAX[1];
  if ((param_3 != '\0') && (iVar1 - 1U == param_2)) {
    iVar2 = *in_EAX;
    param_1[(uint)(iVar2 == 0x2d) + (iVar1 - 1U)] = 0x30;
    (param_1 + (uint)(iVar2 == 0x2d) + (iVar1 - 1U))[1] = 0;
  }
  puVar3 = param_1;
  if (*in_EAX == 0x2d) {
    *param_1 = 0x2d;
    puVar3 = param_1 + 1;
  }
  if (in_EAX[1] < 1) {
    __shift();
    *puVar3 = 0x30;
    puVar3 = puVar3 + 1;
  }
  else {
    puVar3 = puVar3 + in_EAX[1];
  }
  if (0 < (int)param_2) {
    __shift();
    *puVar3 = DAT_00473af4;
    if (in_EAX[1] < 0) {
      sVar4 = -in_EAX[1];
      if ((param_3 != '\0') || ((int)sVar4 <= (int)param_2)) {
        param_2 = sVar4;
      }
      __shift();
      _memset(puVar3 + 1,0x30,param_2);
    }
  }
  return param_1;
}

