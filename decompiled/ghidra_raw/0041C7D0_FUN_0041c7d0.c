/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x0041C7D0
 * Tracking name: FUN_0041c7d0
 * Ghidra name: FUN_0041c7d0
 * Tracked span: 48 bytes
 */


undefined4 FUN_0041c7d0(void)

{
  int iVar1;
  int iVar2;
  int in_EAX;
  
  iVar1 = *(int *)(in_EAX + 0x18);
  while (iVar2 = iVar1, iVar2 != 0) {
    iVar1 = *(int *)(iVar2 + 8);
    if ((*(int *)(iVar2 + 0xc) != 1) && (*(char *)(iVar2 + 0x50) == '\0')) {
      *(undefined1 *)(iVar2 + 0x50) = 1;
    }
  }
  return 0;
}

