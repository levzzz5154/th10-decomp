/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x004088C0
 * Tracking name: FUN_004088c0
 * Ghidra name: FUN_004088c0
 * Tracked span: 80 bytes
 */


int __fastcall FUN_004088c0(undefined4 param_1,int param_2)

{
  int iVar1;
  int iVar2;
  
  iVar1 = 0;
  iVar2 = 0;
  do {
    if ((char)(&DAT_004743c0)[iVar2] == param_2) {
      iVar1 = iVar1 + 1;
    }
    if ((char)(&DAT_004743c1)[iVar2] == param_2) {
      iVar1 = iVar1 + 1;
    }
    if ((char)(&DAT_004743c2)[iVar2] == param_2) {
      iVar1 = iVar1 + 1;
    }
    if ((char)(&DAT_004743c3)[iVar2] == param_2) {
      iVar1 = iVar1 + 1;
    }
    if ((char)(&DAT_004743c4)[iVar2] == param_2) {
      iVar1 = iVar1 + 1;
    }
    iVar2 = iVar2 + 5;
  } while (iVar2 < 0x6e);
  return iVar1;
}

