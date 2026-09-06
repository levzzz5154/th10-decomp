/* Raw Ghidra reference; not compilable reconstruction. Address: 00462107 */

/* Library Function - Single Match
    __close_lk
   
   Library: Visual Studio 2003 Release */

undefined4 __cdecl __close_lk(uint param_1)

{
  intptr_t iVar1;
  intptr_t iVar2;
  HANDLE hObject;
  BOOL BVar3;
  DWORD DVar4;
  undefined4 uVar5;
  
  iVar1 = __get_osfhandle(param_1);
  if (iVar1 != -1) {
    if ((param_1 == 1) || (param_1 == 2)) {
      iVar1 = __get_osfhandle(2);
      iVar2 = __get_osfhandle(1);
      if (iVar2 == iVar1) goto LAB_00462155;
    }
    hObject = (HANDLE)__get_osfhandle(param_1);
    BVar3 = CloseHandle(hObject);
    if (BVar3 == 0) {
      DVar4 = GetLastError();
      goto LAB_00462157;
    }
  }
LAB_00462155:
  DVar4 = 0;
LAB_00462157:
  __free_osfhnd(param_1);
  *(undefined1 *)((&DAT_00499200)[(int)param_1 >> 5] + 4 + (param_1 & 0x1f) * 0x24) = 0;
  if (DVar4 == 0) {
    uVar5 = 0;
  }
  else {
    __dosmaperr(DVar4);
    uVar5 = 0xffffffff;
  }
  return uVar5;
}

