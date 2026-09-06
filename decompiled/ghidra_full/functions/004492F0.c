/* Raw Ghidra reference; not compilable reconstruction. Address: 004492F0 */

void __fastcall FUN_004492f0(undefined4 param_1,int param_2,int param_3)

{
  int *piVar1;
  int iVar2;
  undefined4 *unaff_ESI;
  
  iVar2 = FUN_004491c0(param_1,param_2,param_3);
  if (iVar2 != 0) {
    *(undefined4 *)(iVar2 + 0x340) = *unaff_ESI;
    *(undefined4 *)(iVar2 + 0x344) = unaff_ESI[1];
    *(undefined4 *)(iVar2 + 0x348) = unaff_ESI[2];
    if (*(int *)(iVar2 + 0x18) == 0) {
      for (piVar1 = *(int **)(iVar2 + 0x14); piVar1 != (int *)0x0; piVar1 = (int *)piVar1[1]) {
        iVar2 = *piVar1;
        *(undefined4 *)(iVar2 + 0x340) = *unaff_ESI;
        *(undefined4 *)(iVar2 + 0x344) = unaff_ESI[1];
        *(undefined4 *)(iVar2 + 0x348) = unaff_ESI[2];
      }
    }
  }
  return;
}

