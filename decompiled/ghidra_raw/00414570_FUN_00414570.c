/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x00414570
 * Tracking name: FUN_00414570
 * Ghidra name: FUN_00414570
 * Tracked span: 128 bytes
 */


void __fastcall FUN_00414570(undefined4 param_1)

{
  void *_Memory;
  undefined4 extraout_ECX;
  int unaff_EBX;
  int *piVar1;
  
  _Memory = *(void **)(unaff_EBX + 0x9eb8);
  if (_Memory != (void *)0x0) {
    FUN_004136c0(param_1);
    _free(_Memory);
    *(undefined4 *)(unaff_EBX + 0x9eb8) = 0;
    param_1 = extraout_ECX;
  }
  if (((byte)DAT_00474ca0 & 9) == 0) {
    piVar1 = (int *)((int)g_pGameStateManager + 0x3ad0dc);
    if (*piVar1 != 0) {
      FUN_00447810(param_1);
      _free((void *)*piVar1);
      *piVar1 = 0;
    }
    *(undefined4 *)(unaff_EBX + 0x9e80) = 0;
    if (*(void **)(unaff_EBX + 0x9ebc) != (void *)0x0) {
      _free(*(void **)(unaff_EBX + 0x9ebc));
      *(undefined4 *)(unaff_EBX + 0x9ebc) = 0;
    }
    *(undefined4 *)(unaff_EBX + 0x9ebc) = 0;
  }
  return;
}

