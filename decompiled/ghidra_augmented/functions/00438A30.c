/* Raw Ghidra reference; not compilable reconstruction. Address: 00438A30 */

void FUN_00438a30(void)

{
  int *piVar1;
  int in_EAX;
  int *piVar2;
  int iVar3;
  
  piVar2 = (int *)(in_EAX + 0x3ad4e0);
  iVar3 = 0x20;
  do {
    piVar1 = (int *)*piVar2;
    if (piVar1 != (int *)0x0) {
      (**(code **)(*piVar1 + 8))(piVar1);
      *piVar2 = 0;
    }
    piVar2 = piVar2 + 1;
    iVar3 = iVar3 + -1;
  } while (iVar3 != 0);
  return;
}

