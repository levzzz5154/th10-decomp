/* Raw Ghidra reference; not compilable reconstruction. Address: 004606DF */

/* Library Function - Multiple Matches With Different Base Names
    @x64toa@20
    _x64toa@20
   
   Libraries: Visual Studio 2003 Release, Visual Studio 2005 Release */

void FID_conflict__x64toa_20(int param_1,int param_2,uint param_3,int param_4)

{
  char *pcVar1;
  char *in_EAX;
  char cVar2;
  uint extraout_ECX;
  char *pcVar3;
  bool bVar4;
  longlong lVar5;
  
  if (param_4 != 0) {
    *in_EAX = '-';
    in_EAX = in_EAX + 1;
    bVar4 = param_1 != 0;
    param_1 = -param_1;
    param_2 = -(param_2 + (uint)bVar4);
  }
  lVar5 = CONCAT44(param_2,param_1);
  pcVar1 = in_EAX;
  do {
    pcVar3 = pcVar1;
    lVar5 = __aulldvrm((uint)lVar5,(uint)((ulonglong)lVar5 >> 0x20),param_3,0);
    if (extraout_ECX < 10) {
      cVar2 = (char)extraout_ECX + '0';
    }
    else {
      cVar2 = (char)extraout_ECX + 'W';
    }
    *pcVar3 = cVar2;
    pcVar1 = pcVar3 + 1;
  } while (lVar5 != 0);
  pcVar3[1] = '\0';
  do {
    cVar2 = *pcVar3;
    *pcVar3 = *in_EAX;
    pcVar3 = pcVar3 + -1;
    *in_EAX = cVar2;
    in_EAX = in_EAX + 1;
  } while (in_EAX < pcVar3);
  return;
}

