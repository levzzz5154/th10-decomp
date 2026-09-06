/* Raw Ghidra reference; not compilable reconstruction. Address: 0040C4D0 */

void __fastcall FUN_0040c4d0(undefined4 param_1)

{
  int *piVar1;
  int *in_EAX;
  int iVar2;
  
  iVar2 = FUN_004491c0(param_1,(int)g_pGameStateManager,*in_EAX);
  if ((iVar2 != 0) && (*(undefined2 *)(iVar2 + 0x304) = 3, *(int *)(iVar2 + 0x18) == 0)) {
    for (piVar1 = *(int **)(iVar2 + 0x14); piVar1 != (int *)0x0; piVar1 = (int *)piVar1[1]) {
      *(undefined2 *)(*piVar1 + 0x304) = 3;
    }
  }
  return;
}

