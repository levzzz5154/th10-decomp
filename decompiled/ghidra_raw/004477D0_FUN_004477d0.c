/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x004477D0
 * Tracking name: FUN_004477d0
 * Ghidra name: FUN_004477d0
 * Tracked span: 64 bytes
 */


void __fastcall FUN_004477d0(undefined4 param_1)

{
  int unaff_EBX;
  uint unaff_ESI;
  
  if (((-1 < (int)unaff_ESI) && (unaff_ESI < 0x21)) &&
     (*(int *)(unaff_EBX + 0x3ad06c + unaff_ESI * 4) != 0)) {
    FUN_00447810(param_1);
    _free(*(void **)(unaff_EBX + 0x3ad06c + unaff_ESI * 4));
    *(undefined4 *)(unaff_EBX + 0x3ad06c + unaff_ESI * 4) = 0;
  }
  return;
}

