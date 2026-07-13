/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x00427AE0
 * Tracking name: FUN_00427ae0
 * Ghidra name: FUN_00427ae0
 * Tracked span: 112 bytes
 */


void __fastcall FUN_00427ae0(undefined4 param_1)

{
  int iVar1;
  int unaff_EDI;
  
  iVar1 = *(int *)(DAT_00477834 + 0x4474);
  if (iVar1 == 0) {
    if (*(int *)(unaff_EDI + 0x84) != 0) {
      FUN_00449470(param_1);
    }
    *(undefined4 *)(unaff_EDI + 0x4c) = *(undefined4 *)(unaff_EDI + 0x3c);
    *(undefined4 *)(unaff_EDI + 0x50) = *(undefined4 *)(unaff_EDI + 0x40);
    *(undefined4 *)(unaff_EDI + 0x84) = 0;
    return;
  }
  if (*(int *)(unaff_EDI + 0x84) == 0) {
    FUN_00449470(param_1);
  }
  *(undefined4 *)(unaff_EDI + 0x34) = *(undefined4 *)(unaff_EDI + 0x4c);
  *(undefined4 *)(unaff_EDI + 0x38) = *(undefined4 *)(unaff_EDI + 0x50);
  *(int *)(unaff_EDI + 0x84) = iVar1;
  return;
}

