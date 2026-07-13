/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x00412FF0
 * Tracking name: FUN_00412ff0
 * Ghidra name: FUN_00412ff0
 * Tracked span: 384 bytes
 */


void FUN_00412ff0(int param_1)

{
  int unaff_EDI;
  
  if (*(int *)(unaff_EDI + 0x18) < 0x82) {
    FUN_0044bf40((float)param_1);
    if (0x82 < *(int *)(unaff_EDI + 0x18)) {
      if ((*(uint *)(unaff_EDI + 0x24) & 1) == 0) {
        *(undefined4 *)(unaff_EDI + 0x18) = 0;
        *(undefined4 *)(unaff_EDI + 0x14) = 0xfff0bdc1;
        *(undefined4 *)(unaff_EDI + 0x1c) = 0;
        *(undefined4 **)(unaff_EDI + 0x20) = &DAT_00476f78;
        *(uint *)(unaff_EDI + 0x24) = *(uint *)(unaff_EDI + 0x24) | 1;
      }
      *(undefined4 *)(unaff_EDI + 0x18) = 0x82;
      *(undefined4 *)(unaff_EDI + 0x1c) = 0x43020000;
      *(undefined4 *)(unaff_EDI + 0x14) = 0x81;
    }
  }
  return;
}

