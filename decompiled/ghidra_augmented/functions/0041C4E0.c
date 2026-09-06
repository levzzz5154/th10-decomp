/* Raw Ghidra reference; not compilable reconstruction. Address: 0041C4E0 */

undefined4 __fastcall FUN_0041c4e0(int param_1)

{
  int *piVar1;
  int *piVar2;
  
  if ((*(byte *)(DAT_00477810 + 0x58) & 4) == 0) {
    piVar1 = *(int **)(param_1 + 0x18);
    while (piVar2 = piVar1, piVar2 != (int *)0x0) {
      piVar1 = (int *)piVar2[2];
      if (piVar2[3] != 1) {
        (**(code **)(*piVar2 + 0xc))();
      }
    }
  }
  return 1;
}

