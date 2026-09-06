/* Raw Ghidra reference; not compilable reconstruction. Address: 00449350 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __fastcall FUN_00449350(undefined4 param_1,int param_2,int param_3)

{
  int *piVar1;
  int iVar2;
  float *unaff_ESI;
  
  iVar2 = FUN_004491c0(param_1,param_2,param_3);
  if (iVar2 != 0) {
    *(float *)(iVar2 + 0x340) = *unaff_ESI + _DAT_00470b4c;
    *(float *)(iVar2 + 0x344) = unaff_ESI[1] + _DAT_00470b48;
    *(float *)(iVar2 + 0x348) = unaff_ESI[2];
    if (*(int *)(iVar2 + 0x18) == 0) {
      for (piVar1 = *(int **)(iVar2 + 0x14); piVar1 != (int *)0x0; piVar1 = (int *)piVar1[1]) {
        iVar2 = *piVar1;
        *(float *)(iVar2 + 0x340) = *unaff_ESI + _DAT_00470b4c;
        *(float *)(iVar2 + 0x344) = unaff_ESI[1] + _DAT_00470b48;
        *(float *)(iVar2 + 0x348) = unaff_ESI[2];
      }
    }
  }
  return;
}

