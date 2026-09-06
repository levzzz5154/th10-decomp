/* Raw Ghidra reference; not compilable reconstruction. Address: 0045EA31 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

float10 __cdecl
FUN_0045ea31(uint param_1,int param_2,undefined8 param_3,double param_4,uint param_5)

{
  bool bVar1;
  undefined3 extraout_var;
  int _Value;
  float10 fVar2;
  uint local_90 [16];
  uint local_50;
  uint local_14;
  
  local_14 = DAT_00473660 ^ (uint)&stack0xfffffffc;
  bVar1 = __handle_exc(param_1,&param_4,param_5);
  if (CONCAT31(extraout_var,bVar1) == 0) {
    local_50 = local_50 & 0xfffffffe;
    __raise_exc(local_90,&param_5,param_1,param_2,&param_3,&param_4);
  }
  _Value = __errcode((byte)param_1);
  if ((DAT_00473c90 == 0) && (_Value != 0)) {
    fVar2 = __umatherr(_Value,param_2);
  }
  else {
    FID_conflict___set_errno_from_matherr(_Value);
    __ctrlfp();
    fVar2 = (float10)param_4;
  }
  return fVar2;
}

