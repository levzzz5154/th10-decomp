/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x00448BB0
 * Tracking name: FUN_00448bb0
 * Ghidra name: FUN_00448bb0
 * Tracked span: 336 bytes
 */


undefined4 FUN_00448bb0(void)

{
  undefined4 *puVar1;
  int iVar2;
  int extraout_ECX;
  undefined4 *unaff_ESI;
  int unaff_EDI;
  
  puVar1 = unaff_ESI + 1;
  if (puVar1 == *(undefined4 **)(unaff_EDI + 0x72dad8)) {
    *(undefined4 *)(unaff_EDI + 0x72dad8) = unaff_ESI[3];
  }
  if (puVar1 == *(undefined4 **)(unaff_EDI + 0x72dad4)) {
    *(undefined4 *)(unaff_EDI + 0x72dad4) = unaff_ESI[2];
  }
  if (puVar1 == *(undefined4 **)(unaff_EDI + 0x72dae0)) {
    *(undefined4 *)(unaff_EDI + 0x72dae0) = unaff_ESI[3];
  }
  if (puVar1 == *(undefined4 **)(unaff_EDI + 0x72dadc)) {
    *(undefined4 *)(unaff_EDI + 0x72dadc) = unaff_ESI[2];
  }
  if (unaff_ESI[2] != 0) {
    *(undefined4 *)(unaff_ESI[2] + 8) = unaff_ESI[3];
  }
  if (unaff_ESI[3] != 0) {
    *(undefined4 *)(unaff_ESI[3] + 4) = unaff_ESI[2];
  }
  unaff_ESI[2] = 0;
  unaff_ESI[3] = 0;
  if (unaff_ESI[5] != 0) {
    *(undefined4 *)(unaff_ESI[5] + 8) = unaff_ESI[6];
  }
  if (unaff_ESI[6] != 0) {
    *(undefined4 *)(unaff_ESI[6] + 4) = unaff_ESI[5];
  }
  unaff_ESI[5] = 0;
  unaff_ESI[6] = 0;
  if (((undefined4 *)(unaff_EDI + 0x68U) <= unaff_ESI) &&
     (unaff_ESI < (undefined4 *)(unaff_EDI + 0x3ac068U))) {
    iVar2 = (int)unaff_ESI + (-0x68 - unaff_EDI);
    *(undefined1 *)(iVar2 / 0x3ac + 0x3ac068 + unaff_EDI) = 0;
    if ((void *)unaff_ESI[0xd6] != (void *)0x0) {
      _free((void *)unaff_ESI[0xd6]);
      iVar2 = extraout_ECX;
    }
    unaff_ESI[0xd6] = 0;
    FUN_00401de0(iVar2,unaff_ESI);
    return 0;
  }
  if (unaff_ESI != (undefined4 *)0x0) {
    if ((void *)unaff_ESI[0xd6] != (void *)0x0) {
      _free((void *)unaff_ESI[0xd6]);
    }
    unaff_ESI[0xd6] = 0;
    _free(unaff_ESI);
  }
  return 0;
}

