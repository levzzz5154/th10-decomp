/* Raw Ghidra reference; not compilable reconstruction. Address: 00447810 */

void __fastcall FUN_00447810(undefined4 param_1)

{
  int *piVar1;
  int iVar2;
  undefined4 *puVar3;
  int unaff_EDI;
  int local_4;
  
  if (*(int *)(unaff_EDI + 0x108) != 0) {
    FUN_004493e0(param_1,unaff_EDI);
    local_4 = 0;
    if (0 < *(int *)(unaff_EDI + 0x10c)) {
      iVar2 = 0;
      do {
        piVar1 = *(int **)(*(int *)(unaff_EDI + 0x120) + iVar2);
        puVar3 = (undefined4 *)(*(int *)(unaff_EDI + 0x120) + iVar2);
        if (piVar1 != (int *)0x0) {
          (**(code **)(*piVar1 + 8))(piVar1);
          *puVar3 = 0;
        }
        if ((void *)puVar3[1] != (void *)0x0) {
          _free((void *)puVar3[1]);
          puVar3[1] = 0;
        }
        local_4 = local_4 + 1;
        iVar2 = iVar2 + 0x10;
      } while (local_4 < *(int *)(unaff_EDI + 0x10c));
    }
    if (*(void **)(unaff_EDI + 0x120) != (void *)0x0) {
      _free(*(void **)(unaff_EDI + 0x120));
      *(undefined4 *)(unaff_EDI + 0x120) = 0;
    }
    if (*(void **)(unaff_EDI + 0x118) != (void *)0x0) {
      _free(*(void **)(unaff_EDI + 0x118));
      *(undefined4 *)(unaff_EDI + 0x118) = 0;
    }
    if (*(void **)(unaff_EDI + 0x11c) != (void *)0x0) {
      _free(*(void **)(unaff_EDI + 0x11c));
      *(undefined4 *)(unaff_EDI + 0x11c) = 0;
    }
    if (*(void **)(unaff_EDI + 300) != (void *)0x0) {
      _free(*(void **)(unaff_EDI + 300));
      *(undefined4 *)(unaff_EDI + 300) = 0;
    }
    if (*(void **)(unaff_EDI + 0x108) != (void *)0x0) {
      _free(*(void **)(unaff_EDI + 0x108));
      *(undefined4 *)(unaff_EDI + 0x108) = 0;
    }
  }
  return;
}

