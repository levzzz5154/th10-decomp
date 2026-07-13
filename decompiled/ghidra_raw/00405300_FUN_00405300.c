/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x00405300
 * Tracking name: FUN_00405300
 * Ghidra name: FUN_00405300
 * Tracked span: 272 bytes
 */


void FUN_00405300(void)

{
  int unaff_EBX;
  int unaff_ESI;
  
  *(int *)(unaff_ESI + 900) = unaff_EBX * 0x118 + 0x154 + unaff_ESI;
  FUN_00421480();
  (**(code **)(**(int **)(unaff_ESI + 8) + 0xbc))
            (*(int **)(unaff_ESI + 8),*(int *)(unaff_ESI + 900) + 0xcc);
  *(int *)(unaff_ESI + 0x388) = unaff_EBX;
  return;
}

