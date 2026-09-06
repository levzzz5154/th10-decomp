/* Raw Ghidra reference; not compilable reconstruction. Address: 00460636 */

/* Library Function - Single Match
    _xtoa
   
   Library: Visual Studio 2003 Release */

void __cdecl xtoa(uint param_1,int param_2)

{
  ulonglong uVar1;
  char *pcVar2;
  uint in_EAX;
  char *in_ECX;
  char *pcVar3;
  char cVar4;
  
  pcVar2 = in_ECX;
  if (param_2 != 0) {
    *in_ECX = '-';
    in_ECX = in_ECX + 1;
    in_EAX = -in_EAX;
    pcVar2 = in_ECX;
  }
  do {
    pcVar3 = pcVar2;
    uVar1 = (ulonglong)in_EAX;
    in_EAX = in_EAX / param_1;
    cVar4 = (char)(uVar1 % (ulonglong)param_1);
    if ((uint)(uVar1 % (ulonglong)param_1) < 10) {
      cVar4 = cVar4 + '0';
    }
    else {
      cVar4 = cVar4 + 'W';
    }
    *pcVar3 = cVar4;
    pcVar2 = pcVar3 + 1;
  } while (in_EAX != 0);
  pcVar3[1] = '\0';
  do {
    cVar4 = *pcVar3;
    *pcVar3 = *in_ECX;
    pcVar3 = pcVar3 + -1;
    *in_ECX = cVar4;
    in_ECX = in_ECX + 1;
  } while (in_ECX < pcVar3);
  return;
}

