/* Raw Ghidra reference; not compilable reconstruction. Address: 0041C510 */

undefined4 FUN_0041c510(int param_1)

{
  int iVar1;
  void *pvVar2;
  int *piVar3;
  undefined4 extraout_ECX;
  undefined4 extraout_ECX_00;
  int unaff_ESI;
  
  if (0xff < *(int *)(unaff_ESI + 0x438)) {
    return 0;
  }
  piVar3 = (int *)(unaff_ESI + 0x43c);
  *piVar3 = *piVar3 + 1;
  if (*piVar3 == 0) {
    *(undefined4 *)(unaff_ESI + 0x43c) = 1;
  }
  if (param_1 == 0) {
    pvVar2 = operator_new(0xd58);
    if (pvVar2 == (void *)0x0) {
LAB_0041c574:
      piVar3 = (int *)0x0;
    }
    else {
      piVar3 = (int *)FUN_0041c5b0(extraout_ECX_00);
    }
  }
  else {
    if (param_1 != 1) goto LAB_0041c59f;
    pvVar2 = operator_new(0xd74);
    if (pvVar2 == (void *)0x0) goto LAB_0041c574;
    piVar3 = (int *)FUN_0041c680(extraout_ECX);
  }
  piVar3[0x15] = *(int *)(unaff_ESI + 0x43c);
  iVar1 = *(int *)(unaff_ESI + 0x434);
  piVar3[1] = iVar1;
  *(int **)(iVar1 + 8) = piVar3;
  *(int *)(unaff_ESI + 0x438) = *(int *)(unaff_ESI + 0x438) + 1;
  *(int **)(unaff_ESI + 0x434) = piVar3;
  (**(code **)(*piVar3 + 4))();
LAB_0041c59f:
  return *(undefined4 *)(unaff_ESI + 0x43c);
}

