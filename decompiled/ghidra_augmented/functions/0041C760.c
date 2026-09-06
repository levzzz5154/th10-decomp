/* Raw Ghidra reference; not compilable reconstruction. Address: 0041C760 */

int FUN_0041c760(undefined4 *param_1)

{
  int *piVar1;
  int *piVar2;
  int in_EAX;
  int iVar3;
  undefined4 *unaff_EBX;
  int iVar4;
  
  *(undefined4 *)(in_EAX + 0x440) = *param_1;
  *(undefined4 *)(in_EAX + 0x444) = param_1[1];
  *(undefined4 *)(in_EAX + 0x448) = param_1[2];
  *(undefined4 *)(in_EAX + 0x44c) = *unaff_EBX;
  *(undefined4 *)(in_EAX + 0x450) = unaff_EBX[1];
  iVar4 = 0;
  *(undefined4 *)(in_EAX + 0x454) = unaff_EBX[2];
  piVar1 = *(int **)(in_EAX + 0x18);
  while (piVar2 = piVar1, piVar2 != (int *)0x0) {
    piVar1 = (int *)piVar2[2];
    if (piVar2[3] != 1) {
      iVar3 = (**(code **)(*piVar2 + 0x18))(param_1);
      iVar4 = iVar4 + iVar3;
    }
  }
  return iVar4;
}

