/* Raw Ghidra reference; not compilable reconstruction. Address: 00415DB0 */

void FUN_00415db0(void)

{
  undefined4 *puVar1;
  int *piVar2;
  int unaff_ESI;
  int unaff_EDI;
  bool bVar3;
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_0046582b;
  local_c = ExceptionList;
  ExceptionList = &local_c;
  puVar1 = operator_new(0x90);
  local_4 = 0;
  if (puVar1 == (undefined4 *)0x0) {
    piVar2 = (int *)0x0;
  }
  else {
    piVar2 = FUN_00415b00(puVar1,*(int *)(*(int *)(unaff_EDI + 0x9ebc) + 4 + unaff_ESI * 8) +
                                 *(int *)(unaff_EDI + 0x9ebc));
  }
  *(int **)(unaff_EDI + 0x9eb8) = piVar2;
  *piVar2 = unaff_ESI;
  bVar3 = DAT_00474c84 != unaff_ESI + 1;
  DAT_00474c84 = unaff_ESI + 1;
  if (bVar3) {
    DAT_00474c8c = 0;
  }
  ExceptionList = local_c;
  return;
}

