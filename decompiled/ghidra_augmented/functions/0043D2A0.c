/* Raw Ghidra reference; not compilable reconstruction. Address: 0043D2A0 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

int __thiscall FUN_0043d2a0(void *this,int param_1)

{
  char cVar1;
  byte bVar2;
  byte *pbVar3;
  char *pcVar4;
  byte *pbVar5;
  int iVar6;
  int iVar7;
  byte *pbVar8;
  bool bVar9;
  byte local_84 [128];
  uint local_4;
  
  local_4 = DAT_00473660 ^ (uint)local_84;
  iVar7 = 0;
  pcVar4 = _strrchr(this,0x2f);
  if ((pcVar4 == (char *)0x0) && (pcVar4 = _strrchr(this,0x5c), pcVar4 == (char *)0x0)) {
    iVar6 = -(int)this;
    do {
      cVar1 = *(char *)this;
      *(char *)((int)this + (int)(local_84 + iVar6)) = cVar1;
      this = (void *)((int)this + 1);
    } while (cVar1 != '\0');
  }
  else {
    pcVar4 = pcVar4 + 1;
    iVar6 = -(int)pcVar4;
    do {
      cVar1 = *pcVar4;
      pcVar4[(int)(local_84 + iVar6)] = cVar1;
      pcVar4 = pcVar4 + 1;
    } while (cVar1 != '\0');
  }
  pbVar3 = *(byte **)(param_1 + 0x1f84);
  bVar2 = *pbVar3;
  pbVar5 = pbVar3;
  while (bVar2 != 0) {
    pbVar8 = local_84;
    do {
      bVar2 = *pbVar5;
      bVar9 = bVar2 < *pbVar8;
      if (bVar2 != *pbVar8) {
LAB_0043d33f:
        iVar6 = (1 - (uint)bVar9) - (uint)(bVar9 != 0);
        goto LAB_0043d344;
      }
      if (bVar2 == 0) break;
      bVar2 = pbVar5[1];
      bVar9 = bVar2 < pbVar8[1];
      if (bVar2 != pbVar8[1]) goto LAB_0043d33f;
      pbVar5 = pbVar5 + 2;
      pbVar8 = pbVar8 + 2;
    } while (bVar2 != 0);
    iVar6 = 0;
LAB_0043d344:
    if (iVar6 == 0) break;
    iVar7 = iVar7 + 1;
    pbVar5 = pbVar3 + iVar7 * 0x34;
    bVar2 = pbVar3[iVar7 * 0x34];
  }
  if (pbVar3[iVar7 * 0x34] == 0) {
    iVar7 = 0;
  }
  return iVar7;
}

