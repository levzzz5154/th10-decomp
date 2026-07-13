/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x00447F70
 * Tracking name: FUN_00447f70
 * Ghidra name: FUN_00447f70
 * Tracked span: 96 bytes
 */


void FUN_00447f70(void)

{
  int *piVar1;
  void *_Memory;
  int unaff_ESI;
  int unaff_EDI;
  
  piVar1 = *(int **)(unaff_EDI + 0x3ad4e0 + unaff_ESI * 4);
  if (piVar1 != (int *)0x0) {
    (**(code **)(*piVar1 + 8))(piVar1);
    *(undefined4 *)(unaff_EDI + 0x3ad4e0 + unaff_ESI * 4) = 0;
  }
  piVar1 = *(int **)(unaff_EDI + 0x3ad560 + unaff_ESI * 4);
  if (piVar1 != (int *)0x0) {
    (**(code **)(*piVar1 + 8))(piVar1);
    *(undefined4 *)(unaff_EDI + 0x3ad560 + unaff_ESI * 4) = 0;
  }
  _Memory = *(void **)(unaff_EDI + 0x3ad5e0 + unaff_ESI * 4);
  if (_Memory != (void *)0x0) {
    _free(_Memory);
    *(undefined4 *)(unaff_EDI + 0x3ad5e0 + unaff_ESI * 4) = 0;
  }
  *(undefined4 *)(unaff_EDI + 0x3ad5e0 + unaff_ESI * 4) = 0;
  return;
}

