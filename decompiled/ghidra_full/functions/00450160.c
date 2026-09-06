/* Raw Ghidra reference; not compilable reconstruction. Address: 00450160 */

int * __fastcall FindEclVariable(int param_1)

{
  int in_EAX;
  int *piVar1;
  
  piVar1 = (int *)(in_EAX + 0x1030);
  while( true ) {
    if (piVar1 == (int *)0x0) {
      return (int *)0x0;
    }
    if (*(int *)(*piVar1 + 0x1010) == param_1) break;
    piVar1 = (int *)piVar1[1];
  }
  return piVar1;
}

