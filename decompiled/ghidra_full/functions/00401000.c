/* Raw Ghidra reference; not compilable reconstruction. Address: 00401000 */

void ConstructGameThread(void)

{
  int iVar1;
  undefined4 *unaff_ESI;
  undefined4 *puVar2;
  
  *unaff_ESI = &PTR_LAB_0046cb14;
  unaff_ESI[0x20] = unaff_ESI[0x20] & 0xfffffffe;
  unaff_ESI[0x31] = unaff_ESI[0x31] & 0xfffffffe;
  unaff_ESI[0x44] = unaff_ESI[0x44] & 0xfffffffe;
  unaff_ESI[0x4f] = unaff_ESI[0x4f] & 0xfffffffe;
  unaff_ESI[0x62] = unaff_ESI[0x62] & 0xfffffffe;
  unaff_ESI[0x71] = unaff_ESI[0x71] & 0xfffffffe;
  unaff_ESI[0x84] = unaff_ESI[0x84] & 0xfffffffe;
  unaff_ESI[0x8f] = unaff_ESI[0x8f] & 0xfffffffe;
  unaff_ESI[0xe3] = unaff_ESI[0xe3] & 0xfffffffe;
  puVar2 = unaff_ESI + 5;
  for (iVar1 = 0xeb; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  *(undefined2 *)(unaff_ESI + 0xe6) = 0xffff;
  unaff_ESI[0x10b] = unaff_ESI[0x10b] & 0xfffffffe;
  unaff_ESI[0x11c] = unaff_ESI[0x11c] & 0xfffffffe;
  unaff_ESI[0x12f] = unaff_ESI[0x12f] & 0xfffffffe;
  unaff_ESI[0x13a] = unaff_ESI[0x13a] & 0xfffffffe;
  unaff_ESI[0x14d] = unaff_ESI[0x14d] & 0xfffffffe;
  unaff_ESI[0x15c] = unaff_ESI[0x15c] & 0xfffffffe;
  unaff_ESI[0x16f] = unaff_ESI[0x16f] & 0xfffffffe;
  unaff_ESI[0x17a] = unaff_ESI[0x17a] & 0xfffffffe;
  unaff_ESI[0x1ce] = unaff_ESI[0x1ce] & 0xfffffffe;
  puVar2 = unaff_ESI + 0xf0;
  for (iVar1 = 0xeb; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  *(undefined2 *)(unaff_ESI + 0x1d1) = 0xffff;
  puVar2 = unaff_ESI;
  for (iVar1 = 0x226b; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  unaff_ESI[1] = unaff_ESI[1] | 2;
  g_pGameThread = unaff_ESI;
  unaff_ESI[0x225d] = 0xffffffff;
  unaff_ESI[0x225e] = 0x3f800000;
  unaff_ESI[0x225f] = 0x3f800000;
  unaff_ESI[0x2261] = 0;
  unaff_ESI[0x2263] = 9;
  return;
}

