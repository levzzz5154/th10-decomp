/* Raw Ghidra reference; not compilable reconstruction. Address: 004477D0 */

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

