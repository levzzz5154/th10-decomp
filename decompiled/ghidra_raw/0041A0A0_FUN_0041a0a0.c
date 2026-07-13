/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x0041A0A0
 * Tracking name: FUN_0041a0a0
 * Ghidra name: FUN_0041a0a0
 * Tracked span: 128 bytes
 */


void FUN_0041a0a0(void)

{
  char cVar1;
  char *in_EAX;
  char *pcVar2;
  int iVar3;
  char *pcVar4;
  
  while ((((cVar1 = *in_EAX, cVar1 == ' ' || (cVar1 == '\t')) || (cVar1 == '\n')) || (cVar1 == '\r')
         )) {
    pcVar2 = in_EAX;
    do {
      cVar1 = *pcVar2;
      pcVar2 = pcVar2 + 1;
    } while (cVar1 != '\0');
    iVar3 = (int)pcVar2 - (int)(in_EAX + 1);
    pcVar4 = in_EAX;
    pcVar2 = in_EAX;
    if (0 < iVar3) {
      for (; iVar3 != 0; iVar3 = iVar3 + -1) {
        *pcVar4 = pcVar2[1];
        pcVar4 = pcVar4 + 1;
        pcVar2 = pcVar2 + 1;
      }
    }
  }
  pcVar2 = in_EAX;
  do {
    cVar1 = *pcVar2;
    pcVar2 = pcVar2 + 1;
  } while (cVar1 != '\0');
  iVar3 = (int)pcVar2 - (int)(in_EAX + 1);
  while ((iVar3 = iVar3 + -1, -1 < iVar3 &&
         (((cVar1 = in_EAX[iVar3], cVar1 == ' ' || (cVar1 == '\t')) ||
          ((cVar1 == '\n' || (cVar1 == '\r'))))))) {
    in_EAX[iVar3] = '\0';
  }
  return;
}

