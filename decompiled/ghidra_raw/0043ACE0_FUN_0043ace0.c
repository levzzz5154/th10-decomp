/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x0043ACE0
 * Tracking name: FUN_0043ace0
 * Ghidra name: FUN_0043ace0
 * Tracked span: 320 bytes
 */


void FUN_0043ace0(void)

{
  byte bVar1;
  undefined4 *puVar2;
  int iVar3;
  int iVar4;
  int unaff_EDI;
  
  puVar2 = *(undefined4 **)(unaff_EDI + 0x138);
  iVar3 = 0;
  *(undefined4 *)(unaff_EDI + 0x2c8) = 0x3f800000;
  *(undefined4 *)(unaff_EDI + 0x2dc) = 0;
  *(undefined4 *)(unaff_EDI + 0x2e0) = 0;
  *(undefined4 *)(unaff_EDI + 0x128) = 0;
  *(undefined4 *)(unaff_EDI + 300) = 0;
  *(undefined4 *)(unaff_EDI + 0x130) = 0;
  *(undefined4 *)(unaff_EDI + 0x134) = 0;
  if (0 < *(int *)(unaff_EDI + 0x118)) {
    do {
      puVar2[5] = puVar2[4];
      puVar2[6] = puVar2[4];
      *puVar2 = 1;
      iVar4 = 0;
      do {
        bVar1 = *(byte *)puVar2[5];
        puVar2[5] = (byte *)puVar2[5] + 1;
        iVar4 = iVar4 * 0x80 + (bVar1 & 0x7f);
      } while ((char)bVar1 < '\0');
      puVar2[1] = iVar4;
      iVar3 = iVar3 + 1;
      puVar2 = puVar2 + 8;
    } while (iVar3 < *(int *)(unaff_EDI + 0x118));
  }
  return;
}

