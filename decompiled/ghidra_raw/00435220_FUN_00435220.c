/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x00435220
 * Tracking name: FUN_00435220
 * Ghidra name: FUN_00435220
 * Tracked span: 48 bytes
 */


void FUN_00435220(void)

{
  char cVar1;
  char *pcVar2;
  void *pvVar3;
  int iVar4;
  char *unaff_EDI;
  
  pcVar2 = unaff_EDI;
  do {
    cVar1 = *pcVar2;
    pcVar2 = pcVar2 + 1;
  } while (cVar1 != '\0');
  pvVar3 = _malloc((size_t)(pcVar2 + (1 - (int)(unaff_EDI + 1))));
  if (pvVar3 != (void *)0x0) {
    iVar4 = (int)pvVar3 - (int)unaff_EDI;
    do {
      cVar1 = *unaff_EDI;
      unaff_EDI[iVar4] = cVar1;
      unaff_EDI = unaff_EDI + 1;
    } while (cVar1 != '\0');
  }
  return;
}

