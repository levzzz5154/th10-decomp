/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x004246C0
 * Tracking name: FUN_004246c0
 * Ghidra name: FUN_004246c0
 * Tracked span: 304 bytes
 */


void FUN_004246c0(void)

{
  uint *puVar1;
  int iVar2;
  undefined4 *unaff_ESI;
  undefined4 *puVar3;
  
  unaff_ESI[0x20] = unaff_ESI[0x20] & 0xfffffffe;
  unaff_ESI[0x31] = unaff_ESI[0x31] & 0xfffffffe;
  unaff_ESI[0x44] = unaff_ESI[0x44] & 0xfffffffe;
  unaff_ESI[0x4f] = unaff_ESI[0x4f] & 0xfffffffe;
  unaff_ESI[0x62] = unaff_ESI[0x62] & 0xfffffffe;
  unaff_ESI[0x71] = unaff_ESI[0x71] & 0xfffffffe;
  unaff_ESI[0x84] = unaff_ESI[0x84] & 0xfffffffe;
  unaff_ESI[0x8f] = unaff_ESI[0x8f] & 0xfffffffe;
  unaff_ESI[0xe3] = unaff_ESI[0xe3] & 0xfffffffe;
  puVar3 = unaff_ESI + 5;
  for (iVar2 = 0xeb; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar3 = 0;
    puVar3 = puVar3 + 1;
  }
  *(undefined2 *)(unaff_ESI + 0xe6) = 0xffff;
  unaff_ESI[0x11c] = unaff_ESI[0x11c] & 0xfffffffe;
  unaff_ESI[0x121] = unaff_ESI[0x121] & 0xfffffffe;
  unaff_ESI[0x126] = unaff_ESI[0x126] & 0xfffffffe;
  puVar1 = unaff_ESI + 299;
  iVar2 = 0x80;
  do {
    *puVar1 = *puVar1 & 0xfffffffe;
    puVar1 = puVar1 + 0x17;
    iVar2 = iVar2 + -1;
  } while (iVar2 != 0);
  unaff_ESI[0xcc8] = unaff_ESI[0xcc8] & 0xfffffffe;
  unaff_ESI[0xcee] = unaff_ESI[0xcee] & 0xfffffffe;
  unaff_ESI[0xd14] = unaff_ESI[0xd14] & 0xfffffffe;
  unaff_ESI[0xd3a] = unaff_ESI[0xd3a] & 0xfffffffe;
  puVar1 = unaff_ESI + 0xd58;
  iVar2 = 0x21;
  do {
    *puVar1 = *puVar1 & 0xfffffffe;
    puVar1 = puVar1 + 0x1b;
    iVar2 = iVar2 + -1;
  } while (iVar2 != 0);
  unaff_ESI[0x10c7] = unaff_ESI[0x10c7] & 0xfffffffe;
  puVar3 = unaff_ESI;
  for (iVar2 = 0x111e; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar3 = 0;
    puVar3 = puVar3 + 1;
  }
  DAT_00477834 = unaff_ESI;
  return;
}

