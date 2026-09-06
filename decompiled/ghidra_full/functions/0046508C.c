/* Raw Ghidra reference; not compilable reconstruction. Address: 0046508C */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __cdecl FUN_0046508c(int param_1,int *param_2,ushort *param_3)

{
  bool bVar1;
  undefined3 extraout_var;
  int iVar2;
  uint uVar3;
  uint local_94;
  uint local_90 [12];
  undefined8 local_60;
  uint local_50;
  uint local_14;
  
  local_14 = DAT_00473660 ^ (uint)&stack0xfffffffc;
  local_94 = (uint)*param_3;
  iVar2 = *param_2;
  if (iVar2 == 1) {
LAB_004650e6:
    uVar3 = 8;
  }
  else if (iVar2 == 2) {
    uVar3 = 4;
  }
  else if (iVar2 == 3) {
    uVar3 = 0x11;
  }
  else if (iVar2 == 4) {
    uVar3 = 0x12;
  }
  else {
    if (iVar2 == 5) goto LAB_004650e6;
    if (iVar2 == 7) {
      *param_2 = 1;
      goto LAB_00465142;
    }
    if (iVar2 != 8) goto LAB_00465142;
    uVar3 = 0x10;
  }
  bVar1 = __handle_exc(uVar3,(double *)(param_2 + 6),local_94);
  if (CONCAT31(extraout_var,bVar1) == 0) {
    if (((param_1 == 0x10) || (param_1 == 0x16)) || (param_1 == 0x1d)) {
      local_60 = *(undefined8 *)(param_2 + 4);
      local_50 = local_50 & 0xffffffe3 | 3;
    }
    else {
      local_50 = local_50 & 0xfffffffe;
    }
    __raise_exc(local_90,&local_94,uVar3,param_1,(undefined8 *)(param_2 + 2),
                (undefined8 *)(param_2 + 6));
  }
LAB_00465142:
  __ctrlfp();
  if (((*param_2 != 8) && (DAT_00473c90 == 0)) && (iVar2 = FUN_0045e3a0(), iVar2 != 0)) {
    return;
  }
  FID_conflict___set_errno_from_matherr(*param_2);
  return;
}

