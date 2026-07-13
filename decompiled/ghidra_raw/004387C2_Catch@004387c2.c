/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x004387C2
 * Tracking name: Catch@004387c2
 * Ghidra name: Catch@004387c2
 * Tracked span: 190 bytes
 */


void Catch_004387c2(void)

{
  int iVar1;
  int unaff_EBP;
  
  iVar1 = *(int *)(unaff_EBP + -0x14);
  if (0xf < *(uint *)(iVar1 + 0x18)) {
    _free(*(void **)(iVar1 + 4));
  }
  *(undefined4 *)(iVar1 + 0x18) = 0xf;
  *(undefined4 *)(iVar1 + 0x14) = 0;
  *(undefined1 *)(iVar1 + 4) = 0;
                    /* WARNING: Subroutine does not return */
  __CxxThrowException_8(0,0);
}

