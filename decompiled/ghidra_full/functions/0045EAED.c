/* Raw Ghidra reference; not compilable reconstruction. Address: 0045EAED */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

float10 __cdecl
FUN_0045eaed(uint param_1,int param_2,undefined8 param_3,undefined8 param_4,double param_5,
            uint param_6)

{
  bool bVar1;
  undefined3 extraout_var;
  int _Value;
  float10 fVar2;
  uint local_90 [12];
  undefined8 local_60;
  uint local_50;
  uint local_14;
  
  local_14 = DAT_00473660 ^ (uint)&stack0xfffffffc;
  bVar1 = __handle_exc(param_1,&param_5,param_6);
  if (CONCAT31(extraout_var,bVar1) == 0) {
    local_60 = param_4;
    local_50 = local_50 & 0xffffffe3 | 3;
    __raise_exc(local_90,&param_6,param_1,param_2,&param_3,&param_5);
  }
  _Value = __errcode((byte)param_1);
  if ((DAT_00473c90 == 0) && (_Value != 0)) {
    fVar2 = __umatherr(_Value,param_2);
  }
  else {
    FID_conflict___set_errno_from_matherr(_Value);
    __ctrlfp();
    fVar2 = (float10)param_5;
  }
  return fVar2;
}

