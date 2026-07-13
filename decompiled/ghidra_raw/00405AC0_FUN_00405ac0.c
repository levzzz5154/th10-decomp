/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x00405AC0
 * Tracking name: FUN_00405ac0
 * Ghidra name: FUN_00405ac0
 * Tracked span: 160 bytes
 */


undefined4 FUN_00405ac0(void)

{
  int unaff_ESI;
  float fVar1;
  int iVar2;
  
  if (*(int *)(unaff_ESI + 0x28) != 0) {
    if (((((*(uint *)(DAT_004776f4 + 0x378c) & 1) == 0) || (*(int *)(DAT_004776f4 + 0x3788) < 0x5d))
        || (0x60 < *(int *)(DAT_004776f4 + 0x3788))) && (*(int *)(DAT_004776f4 + 0x3788) != 0x6d)) {
      fVar1 = *(float *)(unaff_ESI + 0x3c);
      iVar2 = 1;
    }
    else {
      iVar2 = 0;
      fVar1 = *(float *)(unaff_ESI + 0x3c);
    }
    FUN_00408100(fVar1,~*(uint *)(DAT_004776f4 + 0x378c) & 1,iVar2);
    FUN_0041c800();
  }
  return 0;
}

