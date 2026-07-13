/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x0040C540
 * Tracking name: FUN_0040c540
 * Ghidra name: FUN_0040c540
 * Tracked span: 416 bytes
 */


void FUN_0040c540(void)

{
  undefined4 *puVar1;
  int unaff_ESI;
  
  if (*(int *)(unaff_ESI + 0x89a4) == 0) {
    puVar1 = (undefined4 *)FUN_00448d50(*(undefined2 **)(unaff_ESI + 0x8994));
    *(undefined4 *)(unaff_ESI + 0x89a4) = *puVar1;
  }
  return;
}

