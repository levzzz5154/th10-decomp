/* Raw Ghidra reference; not compilable reconstruction. Address: 0043D250 */

char * __thiscall FUN_0043d250(void *this,char *param_1)

{
  int in_EAX;
  int iVar1;
  int *unaff_EDI;
  
  while( true ) {
    if (in_EAX == 0) {
      return (char *)0x0;
    }
    *unaff_EDI = *(int *)((int)this + 4);
    iVar1 = _strncmp(this,param_1,4);
    if (iVar1 == 0) break;
    in_EAX = in_EAX + (-8 - *unaff_EDI);
    this = (void *)((int)this + *unaff_EDI + 8);
  }
  return (char *)((int)this + 8);
}

