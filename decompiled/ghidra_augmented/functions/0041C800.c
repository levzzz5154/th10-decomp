/* Raw Ghidra reference; not compilable reconstruction. Address: 0041C800 */

int FUN_0041c800(void)

{
  int *piVar1;
  int *piVar2;
  int in_EAX;
  int iVar3;
  undefined4 *unaff_EBX;
  int iVar4;
  
  *(undefined4 *)(in_EAX + 0x440) = *unaff_EBX;
  *(undefined4 *)(in_EAX + 0x444) = unaff_EBX[1];
  iVar4 = 0;
  *(undefined4 *)(in_EAX + 0x448) = unaff_EBX[2];
  piVar1 = *(int **)(in_EAX + 0x18);
  while (piVar2 = piVar1, piVar2 != (int *)0x0) {
    piVar1 = (int *)piVar2[2];
    if (piVar2[3] != 1) {
      iVar3 = (**(code **)(*piVar2 + 0x1c))();
      iVar4 = iVar4 + iVar3;
    }
  }
  return iVar4;
}

