/* Raw Ghidra reference; not compilable reconstruction. Address: 0042C6D0 */

void __fastcall FUN_0042c6d0(undefined4 param_1)

{
  int *piVar1;
  int iVar2;
  int unaff_ESI;
  int unaff_EDI;
  
  iVar2 = FUN_004491c0(param_1,(int)g_pGameStateManager,*(int *)(unaff_EDI + 0x2c4 + unaff_ESI * 4))
  ;
  if (iVar2 == 0) {
    *(undefined4 *)(unaff_EDI + 0x2c4 + unaff_ESI * 4) = 0;
    return;
  }
  *(undefined2 *)(iVar2 + 0x304) = 1;
  if (*(int *)(iVar2 + 0x18) == 0) {
    for (piVar1 = *(int **)(iVar2 + 0x14); piVar1 != (int *)0x0; piVar1 = (int *)piVar1[1]) {
      *(undefined2 *)(*piVar1 + 0x304) = 1;
    }
  }
  *(undefined4 *)(unaff_EDI + 0x2c4 + unaff_ESI * 4) = 0;
  return;
}

