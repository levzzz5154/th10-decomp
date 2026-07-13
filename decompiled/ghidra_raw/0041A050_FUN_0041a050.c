/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x0041A050
 * Tracking name: FUN_0041a050
 * Ghidra name: FUN_0041a050
 * Tracked span: 80 bytes
 */


void FUN_0041a050(void)

{
  char cVar1;
  char *in_EAX;
  uint *puVar2;
  char *pcVar3;
  int iVar4;
  int unaff_EBX;
  uint *unaff_EDI;
  
  iVar4 = (int)unaff_EDI - (int)in_EAX;
  do {
    cVar1 = *in_EAX;
    in_EAX[iVar4] = cVar1;
    in_EAX = in_EAX + 1;
  } while (cVar1 != '\0');
  puVar2 = FUN_00452730(unaff_EDI,':');
  if (puVar2 == (uint *)0x0) {
    FUN_0041a0a0();
    return;
  }
  pcVar3 = (char *)((int)puVar2 + 1);
  iVar4 = unaff_EBX - (int)pcVar3;
  do {
    cVar1 = *pcVar3;
    pcVar3[iVar4] = cVar1;
    pcVar3 = pcVar3 + 1;
  } while (cVar1 != '\0');
  *(undefined1 *)puVar2 = 0;
  FUN_0041a0a0();
  FUN_0041a0a0();
  return;
}

