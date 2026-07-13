/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x00436CA0
 * Tracking name: FUN_00436ca0
 * Ghidra name: FUN_00436ca0
 * Tracked span: 256 bytes
 */


void __fastcall FUN_00436ca0(uint param_1)

{
  int iVar1;
  ushort *puVar2;
  int unaff_ESI;
  
  puVar2 = *(ushort **)(unaff_ESI + 0x120);
  iVar1 = 0;
  if (0 < *(int *)(unaff_ESI + 0x10c)) {
    do {
      *puVar2 = (ushort)(((param_1 >> 0x14 & 0xf) << 4 | param_1 >> 0xc & 0xf) << 4) |
                (ushort)(param_1 >> 4) & 0xf;
      iVar1 = iVar1 + 2;
      puVar2 = puVar2 + 1;
    } while (iVar1 < *(int *)(unaff_ESI + 0x10c));
  }
  return;
}

