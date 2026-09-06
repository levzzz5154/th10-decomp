/* Raw Ghidra reference; not compilable reconstruction. Address: 004493E0 */

void __fastcall FUN_004493e0(undefined4 param_1,int param_2)

{
  uint *puVar1;
  int *piVar2;
  int iVar3;
  int *piVar4;
  int in_EAX;
  
  piVar4 = *(int **)(in_EAX + 0x72dad4);
  while (piVar4 != (int *)0x0) {
    piVar2 = (int *)piVar4[1];
    iVar3 = *piVar4;
    piVar4 = piVar2;
    if (*(int *)(iVar3 + 0x308) == param_2) {
      puVar1 = (uint *)(iVar3 + 0x35c);
      *puVar1 = *puVar1 | 0x4000000;
    }
  }
  piVar4 = *(int **)(in_EAX + 0x72dadc);
  while (piVar4 != (int *)0x0) {
    piVar2 = (int *)piVar4[1];
    iVar3 = *piVar4;
    piVar4 = piVar2;
    if (*(int *)(iVar3 + 0x308) == param_2) {
      puVar1 = (uint *)(iVar3 + 0x35c);
      *puVar1 = *puVar1 | 0x4000000;
    }
  }
  return;
}

