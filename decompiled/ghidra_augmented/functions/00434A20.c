/* Raw Ghidra reference; not compilable reconstruction. Address: 00434A20 */

void __thiscall FUN_00434a20(void *this,int param_1)

{
  char cVar1;
  char *pcVar2;
  int iVar3;
  int *unaff_EDI;
  
  cVar1 = *(char *)this;
  pcVar2 = this;
  while ((cVar1 != '\n' && (*pcVar2 != '\r'))) {
    if (*unaff_EDI == 0) {
      return;
    }
    pcVar2 = pcVar2 + 1;
    *unaff_EDI = *unaff_EDI + -1;
    cVar1 = *pcVar2;
  }
  if (*unaff_EDI != 0) {
    *pcVar2 = '\0';
    iVar3 = param_1 - (int)this;
    do {
      cVar1 = *(char *)this;
      *(char *)((int)this + iVar3) = cVar1;
      this = (void *)((int)this + 1);
    } while (cVar1 != '\0');
    iVar3 = *unaff_EDI + -1;
    *unaff_EDI = iVar3;
    while( true ) {
      pcVar2 = pcVar2 + 1;
      if (((*pcVar2 != '\n') && (*pcVar2 != '\r')) || (iVar3 == 0)) break;
      iVar3 = iVar3 + -1;
      *unaff_EDI = iVar3;
    }
  }
  return;
}

