/* Raw Ghidra reference; not compilable reconstruction. Address: 00450190 */

void ResetEclVariableBindings(void)

{
  int *piVar1;
  int *piVar2;
  int in_EAX;
  
  piVar2 = *(int **)(in_EAX + 0x1034);
  while (piVar2 != (int *)0x0) {
    piVar1 = (int *)piVar2[1];
    *(undefined4 *)(*piVar2 + 4) = 0;
    piVar2 = piVar1;
  }
  return;
}

