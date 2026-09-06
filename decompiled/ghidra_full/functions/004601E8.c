/* Raw Ghidra reference; not compilable reconstruction. Address: 004601E8 */

/* WARNING: Function: __SEH_prolog replaced with injection: SEH_prolog */
/* WARNING: Function: __chkstk replaced with injection: alloca_probe */
/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* WARNING: Function: __SEH_epilog replaced with injection: EH_epilog3 */

int * __cdecl
FUN_004601e8(UINT param_1,UINT param_2,char *param_3,uint *param_4,int *param_5,int param_6)

{
  uint cbMultiByte;
  bool bVar1;
  bool bVar2;
  BOOL BVar3;
  size_t sVar4;
  int iVar5;
  uint uVar6;
  LPCWSTR local_58;
  uint local_40;
  int *lpMultiByteStr;
  _cpinfo local_34;
  uint local_20;
  undefined1 *local_1c;
  undefined4 uStack_c;
  undefined *local_8;
  
  local_8 = &DAT_0046c940;
  uStack_c = 0x4601f4;
  local_20 = DAT_00473660 ^ (uint)&stack0xfffffffc;
  lpMultiByteStr = (int *)0x0;
  bVar2 = false;
  cbMultiByte = *param_4;
  bVar1 = false;
  if (param_1 != param_2) {
    BVar3 = GetCPInfo(param_1,&local_34);
    if ((((BVar3 != 0) && (local_34.MaxCharSize == 1)) &&
        (BVar3 = GetCPInfo(param_2,&local_34), BVar3 != 0)) && (local_34.MaxCharSize == 1)) {
      bVar1 = true;
    }
    if ((bVar1) && (local_40 = cbMultiByte, cbMultiByte == 0xffffffff)) {
      sVar4 = _strlen(param_3);
      local_40 = sVar4 + 1;
    }
    if ((!bVar1) &&
       (local_40 = MultiByteToWideChar(param_1,1,param_3,cbMultiByte,(LPWSTR)0x0,0), local_40 == 0))
    {
      return (int *)0x0;
    }
    local_8 = (undefined *)0x0;
    local_1c = &stack0xffffff9c;
    local_58 = (LPCWSTR)&stack0xffffff9c;
    _memset(&stack0xffffff9c,0,local_40 * 2);
    local_8 = (undefined *)0xffffffff;
    if (&stack0x00000000 == (undefined1 *)0x64) {
      local_58 = (LPCWSTR)FUN_0045794d(2,local_40);
      if (local_58 == (LPCWSTR)0x0) {
        return (int *)0x0;
      }
      bVar2 = true;
    }
    iVar5 = MultiByteToWideChar(param_1,1,param_3,cbMultiByte,local_58,local_40);
    if (iVar5 != 0) {
      if (param_5 == (int *)0x0) {
        if (((bVar1) ||
            (local_40 = WideCharToMultiByte(param_2,0,local_58,local_40,(LPSTR)0x0,0,(LPCSTR)0x0,
                                            (LPBOOL)0x0), local_40 != 0)) &&
           (lpMultiByteStr = FUN_0045794d(1,local_40), lpMultiByteStr != (int *)0x0)) {
          uVar6 = WideCharToMultiByte(param_2,0,local_58,local_40,(LPSTR)lpMultiByteStr,local_40,
                                      (LPCSTR)0x0,(LPBOOL)0x0);
          if (uVar6 == 0) {
            _free(lpMultiByteStr);
            lpMultiByteStr = (int *)0x0;
          }
          else if (cbMultiByte != 0xffffffff) {
            *param_4 = uVar6;
          }
        }
      }
      else {
        iVar5 = WideCharToMultiByte(param_2,0,local_58,local_40,(LPSTR)param_5,param_6,(LPCSTR)0x0,
                                    (LPBOOL)0x0);
        if (iVar5 != 0) {
          lpMultiByteStr = param_5;
        }
      }
    }
  }
  if (bVar2) {
    _free(local_58);
  }
  return lpMultiByteStr;
}

