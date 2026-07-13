/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x00434F30
 * Tracking name: FUN_00434f30
 * Ghidra name: FUN_00434f30
 * Tracked span: 64 bytes
 */


undefined4 * FUN_00434f30(void)

{
  int *in_EAX;
  int iVar1;
  char *unaff_EBX;
  int iVar2;
  undefined4 *puVar3;
  
  puVar3 = (undefined4 *)*in_EAX;
  if (puVar3 == (undefined4 *)0x0) {
    return (undefined4 *)0x0;
  }
  iVar2 = in_EAX[1];
  while( true ) {
    if (iVar2 < 1) {
      return (undefined4 *)0x0;
    }
    iVar1 = __stricmp(unaff_EBX,(char *)*puVar3);
    if (iVar1 == 0) break;
    iVar2 = iVar2 + -1;
    puVar3 = puVar3 + 4;
  }
  return puVar3;
}

