/* Raw Ghidra reference; not compilable reconstruction. Address: 0045728E */

/* Library Function - Single Match
    _gmtime
   
   Library: Visual Studio 2003 Release */

tm * __cdecl _gmtime(time_t *_Time)

{
  bool bVar1;
  _ptiddata p_Var2;
  void *pvVar3;
  tm *ptVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  undefined4 *puVar9;
  
  iVar8 = (int)*_Time;
  bVar1 = false;
  p_Var2 = __getptd();
  if (iVar8 < 0) {
    return (tm *)0x0;
  }
  if (p_Var2->_gmtimebuf == (void *)0x0) {
    pvVar3 = _malloc(0x24);
    p_Var2->_gmtimebuf = pvVar3;
    ptVar4 = (tm *)&DAT_00477448;
    if (pvVar3 == (void *)0x0) goto LAB_004572c8;
  }
  ptVar4 = p_Var2->_gmtimebuf;
LAB_004572c8:
  iVar6 = iVar8 % 0x7861f80;
  iVar8 = (iVar8 / 0x7861f80) * 4;
  iVar5 = iVar8 + 0x46;
  iVar7 = iVar6;
  if (0x1e1337f < iVar6) {
    iVar7 = iVar6 + -0x1e13380;
    iVar5 = iVar8 + 0x47;
    if (0x1e1337f < iVar7) {
      iVar7 = iVar6 + -0x3c26700;
      iVar5 = iVar8 + 0x48;
      if (iVar7 < 0x1e28500) {
        bVar1 = true;
      }
      else {
        iVar5 = iVar8 + 0x49;
        iVar7 = iVar6 + -0x5a4ec00;
      }
    }
  }
  ptVar4->tm_year = iVar5;
  puVar9 = (undefined4 *)&DAT_00473c28;
  ptVar4->tm_yday = iVar7 / 0x15180;
  if (!bVar1) {
    puVar9 = &DAT_00473c5c;
  }
  iVar5 = 1;
  iVar8 = puVar9[1];
  while (iVar8 < ptVar4->tm_yday) {
    iVar5 = iVar5 + 1;
    iVar8 = puVar9[iVar5];
  }
  ptVar4->tm_mon = iVar5 + -1;
  ptVar4->tm_mday = ptVar4->tm_yday - puVar9[iVar5 + -1];
  ptVar4->tm_wday = ((int)*_Time / 0x15180 + 4) % 7;
  ptVar4->tm_hour = (iVar7 % 0x15180) / 0xe10;
  iVar8 = (iVar7 % 0x15180) % 0xe10;
  ptVar4->tm_min = iVar8 / 0x3c;
  ptVar4->tm_isdst = 0;
  ptVar4->tm_sec = iVar8 % 0x3c;
  return ptVar4;
}

