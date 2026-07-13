/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x0042C770
 * Tracking name: FUN_0042c770
 * Ghidra name: FUN_0042c770
 * Tracked span: 224 bytes
 */


void __fastcall FUN_0042c770(int param_1)

{
  int *piVar1;
  int in_EAX;
  int iVar2;
  undefined2 unaff_SI;
  
  iVar2 = FUN_004491c0(param_1,(int)g_pGameStateManager,*(int *)(in_EAX + 0x2c4 + param_1 * 4));
  if ((iVar2 != 0) && (*(undefined2 *)(iVar2 + 0x304) = unaff_SI, *(int *)(iVar2 + 0x18) == 0)) {
    for (piVar1 = *(int **)(iVar2 + 0x14); piVar1 != (int *)0x0; piVar1 = (int *)piVar1[1]) {
      *(undefined2 *)(*piVar1 + 0x304) = unaff_SI;
    }
  }
  return;
}

