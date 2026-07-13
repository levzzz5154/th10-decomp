/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x0042B430
 * Tracking name: FUN_0042b430
 * Ghidra name: FUN_0042b430
 * Tracked span: 160 bytes
 */


void FUN_0042b430(void)

{
  uint *puVar1;
  int iVar2;
  uint *unaff_EBX;
  
  unaff_EBX[0x21] = unaff_EBX[0x21] & 0xfffffffe;
  unaff_EBX[0x32] = unaff_EBX[0x32] & 0xfffffffe;
  unaff_EBX[0x45] = unaff_EBX[0x45] & 0xfffffffe;
  unaff_EBX[0x50] = unaff_EBX[0x50] & 0xfffffffe;
  unaff_EBX[99] = unaff_EBX[99] & 0xfffffffe;
  unaff_EBX[0x72] = unaff_EBX[0x72] & 0xfffffffe;
  unaff_EBX[0x85] = unaff_EBX[0x85] & 0xfffffffe;
  unaff_EBX[0x90] = unaff_EBX[0x90] & 0xfffffffe;
  unaff_EBX[0xe4] = unaff_EBX[0xe4] & 0xfffffffe;
  puVar1 = unaff_EBX + 6;
  for (iVar2 = 0xeb; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar1 = 0;
    puVar1 = puVar1 + 1;
  }
  *(undefined2 *)(unaff_EBX + 0xe7) = 0xffff;
  puVar1 = unaff_EBX + 0xfc;
  iVar2 = 0x2d3;
  do {
    *puVar1 = *puVar1 & 0xfffffffe;
    puVar1 = puVar1 + 0x10;
    iVar2 = iVar2 + -1;
  } while (iVar2 != 0);
  puVar1 = unaff_EBX;
  for (iVar2 = 0x2e21; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar1 = 0;
    puVar1 = puVar1 + 1;
  }
  *unaff_EBX = *unaff_EBX | 2;
  DAT_00477840 = unaff_EBX;
  return;
}

