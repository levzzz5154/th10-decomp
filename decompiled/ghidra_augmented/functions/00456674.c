/* Raw Ghidra reference; not compilable reconstruction. Address: 00456674 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

uint * __cdecl FUN_00456674(uint *param_1,byte *param_2)

{
  INTRNCVT_STATUS IVar1;
  uint uVar2;
  int local_28;
  byte *local_24;
  _CRT_DOUBLE local_20;
  uint local_18;
  _LDBL12 local_14;
  uint local_8;
  
  local_8 = DAT_00473660 ^ (uint)&stack0xfffffffc;
  local_24 = param_2;
  uVar2 = 0;
  local_18 = FUN_0045d746((undefined2 *)&local_14,&local_28,param_2,0,0,0,0);
  if ((local_18 & 4) == 0) {
    IVar1 = FID_conflict___ld12tod(&local_14,&local_20);
    if (((local_18 & 2) != 0) || (IVar1 == INTRNCVT_OVERFLOW)) {
      uVar2 = 0x80;
    }
    if (((local_18 & 1) != 0) || (IVar1 == INTRNCVT_UNDERFLOW)) {
      uVar2 = uVar2 | 0x100;
    }
  }
  else {
    uVar2 = 0x200;
    local_20.x._0_4_ = 0;
    local_20.x._4_4_ = 0;
  }
  param_1[1] = local_28 - (int)local_24;
  param_1[4] = local_20.x._0_4_;
  param_1[5] = local_20.x._4_4_;
  *param_1 = uVar2;
  return param_1;
}

