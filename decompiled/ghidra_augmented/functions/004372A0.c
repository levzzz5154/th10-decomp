/* Raw Ghidra reference; not compilable reconstruction. Address: 004372A0 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

uint FUN_004372a0(int param_1,int param_2,int param_3,COLORREF param_4,COLORREF param_5)

{
  LPCSTR **pszFaceName;
  undefined4 uVar1;
  BOOL BVar2;
  BOOL extraout_EAX;
  HFONT local_30;
  int local_2c;
  int local_28;
  LPCSTR *local_20 [5];
  uint local_c;
  int local_8;
  uint local_4;
  
  local_4 = DAT_00473660 ^ (uint)&local_30;
  FUN_00436890(&local_30);
  local_2c = 0;
  local_28 = param_3;
  if (local_30 != (HFONT)0x0) {
    DeleteObject(local_30);
    local_30 = (HFONT)0x0;
  }
  pszFaceName = (LPCSTR **)local_20[0];
  if (local_c < 0x10) {
    pszFaceName = local_20;
  }
  local_30 = CreateFontA(local_28,local_2c,0,0,local_8,0,0,0,1,0,0,0,0x30,(LPCSTR)pszFaceName);
  uVar1 = FUN_00437380(param_1,param_2,local_30,param_4,param_5);
  BVar2 = 0;
  if (local_30 != (HFONT)0x0) {
    BVar2 = DeleteObject(local_30);
    local_30 = (HFONT)0x0;
  }
  if (0xf < local_c) {
    _free(local_20[0]);
    BVar2 = extraout_EAX;
  }
  return CONCAT31((int3)((uint)BVar2 >> 8),(char)uVar1);
}

