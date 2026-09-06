/* Raw Ghidra reference; not compilable reconstruction. Address: 0040B480 */

byte * FUN_0040b480(int param_1)

{
  char cVar1;
  char *in_EAX;
  char *pcVar2;
  byte *pbVar3;
  uint uVar4;
  char *pcVar5;
  char *pcVar6;
  
  DAT_00497c38._0_1_ = 0;
  pcVar2 = in_EAX;
  do {
    cVar1 = *pcVar2;
    pcVar2 = pcVar2 + 1;
  } while (cVar1 != '\0');
  pcVar6 = (char *)0x497c37;
  do {
    pcVar5 = pcVar6 + 1;
    pcVar6 = pcVar6 + 1;
  } while (*pcVar5 != '\0');
  pcVar5 = in_EAX;
  for (uVar4 = (uint)((int)pcVar2 - (int)in_EAX) >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
    *(undefined4 *)pcVar6 = *(undefined4 *)pcVar5;
    pcVar5 = pcVar5 + 4;
    pcVar6 = pcVar6 + 4;
  }
  for (uVar4 = (int)pcVar2 - (int)in_EAX & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
    *pcVar6 = *pcVar5;
    pcVar5 = pcVar5 + 1;
    pcVar6 = pcVar6 + 1;
  }
  pbVar3 = FUN_0044b360((size_t *)0x0,0);
  if (*(void **)(param_1 + 0x14) != (void *)0x0) {
    _free(*(void **)(param_1 + 0x14));
    *(undefined4 *)(param_1 + 0x14) = 0;
  }
  *(byte **)(param_1 + 0x14) = pbVar3;
  return pbVar3;
}

