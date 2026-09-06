/* Raw Ghidra reference; not compilable reconstruction. Address: 0041C880 */

int FUN_0041c880(undefined4 param_1,undefined4 param_2)

{
  int *piVar1;
  int *piVar2;
  int in_EAX;
  int iVar3;
  int iVar4;
  
  iVar4 = 0;
  piVar1 = *(int **)(in_EAX + 0x18);
  while (piVar2 = piVar1, piVar2 != (int *)0x0) {
    piVar1 = (int *)piVar2[2];
    if (piVar2[3] != 1) {
      iVar3 = (**(code **)(*piVar2 + 0x20))(param_1,param_2);
      iVar4 = iVar4 + iVar3;
    }
  }
  return iVar4;
}

