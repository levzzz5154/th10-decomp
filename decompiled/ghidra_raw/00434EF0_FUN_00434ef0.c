/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x00434EF0
 * Tracking name: FUN_00434ef0
 * Ghidra name: FUN_00434ef0
 * Tracked span: 64 bytes
 */


undefined4 FUN_00434ef0(void)

{
  int *in_EAX;
  int iVar1;
  char *unaff_EBX;
  int iVar2;
  undefined4 *puVar3;
  
  puVar3 = (undefined4 *)*in_EAX;
  if (puVar3 != (undefined4 *)0x0) {
    for (iVar2 = in_EAX[1]; 0 < iVar2; iVar2 = iVar2 + -1) {
      iVar1 = __stricmp(unaff_EBX,(char *)*puVar3);
      if (iVar1 == 0) {
        return puVar3[2];
      }
      puVar3 = puVar3 + 4;
    }
  }
  return 0;
}

