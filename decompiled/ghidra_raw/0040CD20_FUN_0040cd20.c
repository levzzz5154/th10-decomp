/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x0040CD20
 * Tracking name: FUN_0040cd20
 * Ghidra name: FUN_0040cd20
 * Tracked span: 384 bytes
 */


int __thiscall FUN_0040cd20(void *this,char *param_1)

{
  char cVar1;
  char *pcVar2;
  byte *pbVar3;
  int iVar4;
  uint uVar5;
  char *pcVar6;
  char *pcVar7;
  
  DAT_00497c38._0_1_ = 0;
  pcVar2 = param_1;
  do {
    cVar1 = *pcVar2;
    pcVar2 = pcVar2 + 1;
  } while (cVar1 != '\0');
  pcVar7 = (char *)0x497c37;
  do {
    pcVar6 = pcVar7 + 1;
    pcVar7 = pcVar7 + 1;
  } while (*pcVar6 != '\0');
  pcVar6 = param_1;
  for (uVar5 = (uint)((int)pcVar2 - (int)param_1) >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
    *(undefined4 *)pcVar7 = *(undefined4 *)pcVar6;
    pcVar6 = pcVar6 + 4;
    pcVar7 = pcVar7 + 4;
  }
  for (uVar5 = (int)pcVar2 - (int)param_1 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
    *pcVar7 = *pcVar6;
    pcVar6 = pcVar6 + 1;
    pcVar7 = pcVar7 + 1;
  }
  pbVar3 = FUN_0044b360((size_t *)0x0,0);
  iVar4 = FUN_00450220(this,(int *)pbVar3);
  return (-1 < iVar4) - 1;
}

