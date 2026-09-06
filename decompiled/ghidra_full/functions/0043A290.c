/* Raw Ghidra reference; not compilable reconstruction. Address: 0043A290 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

undefined4 FUN_0043a290(LPCSTR param_1)

{
  HRESULT HVar1;
  int iVar2;
  LPWSTR lpWideCharStr;
  int unaff_EBX;
  int *unaff_ESI;
  int unaff_EDI;
  int *piVar3;
  int *piVar4;
  int *piVar5;
  undefined4 *local_150;
  int local_14c;
  undefined4 local_148;
  uint local_4;
  
  local_4 = DAT_00473660 ^ (uint)&local_150;
  if (unaff_EBX == 0) {
    return 0;
  }
  local_148 = 0;
  CoInitialize((LPVOID)0x0);
  HVar1 = CoCreateInstance((IID *)&DAT_0046954c,(LPUNKNOWN)0x0,1,(IID *)&DAT_0046931c,&local_150);
  if (-1 < HVar1) {
    piVar5 = &local_14c;
    piVar4 = (int *)&DAT_0046997c;
    iVar2 = (**(code **)*local_150)(local_150);
    if (-1 < iVar2) {
      lpWideCharStr = operator_new(unaff_EDI * 2);
      MultiByteToWideChar(0,0,param_1,-1,lpWideCharStr,unaff_EDI);
      piVar3 = (int *)0x0;
      iVar2 = (**(code **)(*piVar5 + 0x14))(piVar5,lpWideCharStr);
      if (-1 < iVar2) {
        iVar2 = (**(code **)(*piVar3 + 0xc))(piVar3);
        if (-1 < iVar2) {
          local_150 = (undefined4 *)0x1;
        }
      }
      _free(lpWideCharStr);
      (**(code **)(*unaff_ESI + 8))(unaff_ESI);
    }
    (**(code **)(*piVar4 + 8))(piVar4,local_150);
  }
  CoUninitialize();
  return local_148;
}

