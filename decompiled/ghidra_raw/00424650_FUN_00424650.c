/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x00424650
 * Tracking name: FUN_00424650
 * Ghidra name: FUN_00424650
 * Tracked span: 112 bytes
 */


void FUN_00424650(char *param_1)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  int *piVar4;
  undefined4 *puVar5;
  int unaff_ESI;
  
  piVar4 = *(int **)(unaff_ESI + 0x7c + DAT_00474c7c * 0xc);
  while (piVar4 != (int *)0x0) {
    piVar1 = (int *)piVar4[1];
    iVar2 = *piVar4;
    iVar3 = *(int *)(iVar2 + 0x70);
    piVar4 = piVar1;
    if (0 < iVar3) {
      *(int *)(iVar2 + 0x70) = iVar3 + -1;
    }
  }
  puVar5 = FUN_0041a120(unaff_ESI,param_1);
  iVar2 = puVar5[0x18];
  puVar5[0x18] = iVar2 + -0x3c;
  if (iVar2 + -0x3c < 1) {
    puVar5[0x18] = 1;
  }
  puVar5[0x1b] = 0x5a;
  puVar5[0x21] = 0xffff8080;
  puVar5[0x1c] = 0x1e;
  return;
}

