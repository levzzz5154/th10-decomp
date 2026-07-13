/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x00449210
 * Tracking name: FUN_00449210
 * Ghidra name: FUN_00449210
 * Tracked span: 64 bytes
 */


void __fastcall FUN_00449210(undefined4 param_1,int param_2,int param_3)

{
  int *piVar1;
  int iVar2;
  undefined2 unaff_SI;
  
  iVar2 = FUN_004491c0(param_1,param_2,param_3);
  if ((iVar2 != 0) && (*(undefined2 *)(iVar2 + 0x304) = unaff_SI, *(int *)(iVar2 + 0x18) == 0)) {
    for (piVar1 = *(int **)(iVar2 + 0x14); piVar1 != (int *)0x0; piVar1 = (int *)piVar1[1]) {
      *(undefined2 *)(*piVar1 + 0x304) = unaff_SI;
    }
  }
  return;
}

