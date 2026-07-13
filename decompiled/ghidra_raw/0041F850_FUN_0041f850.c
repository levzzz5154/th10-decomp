/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x0041F850
 * Tracking name: FUN_0041f850
 * Ghidra name: FUN_0041f850
 * Tracked span: 128 bytes
 */


void FUN_0041f850(void)

{
  int iVar1;
  uint *unaff_ESI;
  uint *puVar2;
  
  unaff_ESI[4] = (uint)&PTR_FUN_004703e4;
  unaff_ESI[5] = 0;
  unaff_ESI[6] = 0;
  unaff_ESI[7] = 0;
  unaff_ESI[8] = 0;
  unaff_ESI[0x27] = unaff_ESI[0x27] & 0xfffffffe;
  unaff_ESI[0x38] = unaff_ESI[0x38] & 0xfffffffe;
  unaff_ESI[0x4b] = unaff_ESI[0x4b] & 0xfffffffe;
  unaff_ESI[0x56] = unaff_ESI[0x56] & 0xfffffffe;
  unaff_ESI[0x69] = unaff_ESI[0x69] & 0xfffffffe;
  unaff_ESI[0x78] = unaff_ESI[0x78] & 0xfffffffe;
  unaff_ESI[0x8b] = unaff_ESI[0x8b] & 0xfffffffe;
  unaff_ESI[0x96] = unaff_ESI[0x96] & 0xfffffffe;
  unaff_ESI[0xea] = unaff_ESI[0xea] & 0xfffffffe;
  puVar2 = unaff_ESI + 0xc;
  for (iVar1 = 0xeb; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  *(undefined2 *)(unaff_ESI + 0xed) = 0xffff;
  puVar2 = unaff_ESI;
  for (iVar1 = 0xfc; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  *unaff_ESI = *unaff_ESI | 2;
  DAT_00477820 = unaff_ESI;
  return;
}

