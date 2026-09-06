/* Raw Ghidra reference; not compilable reconstruction. Address: 0045C377 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __fastcall FUN_0045c377(char *param_1)

{
  int iVar1;
  undefined4 uVar2;
  char local_10 [8];
  uint local_8;
  
  local_8 = DAT_00473660 ^ (uint)&stack0xfffffffc;
  if (((param_1 == (char *)0x0) || (*param_1 == '\0')) ||
     (iVar1 = _strcmp(param_1,"ACP"), iVar1 == 0)) {
    uVar2 = 0x1004;
  }
  else {
    iVar1 = _strcmp(param_1,"OCP");
    if (iVar1 != 0) goto LAB_0045c3dd;
    uVar2 = 0xb;
  }
  iVar1 = (*DAT_00477648)(DAT_00477630,uVar2,local_10,8);
  if (iVar1 == 0) {
    return;
  }
  param_1 = local_10;
LAB_0045c3dd:
  _atol(param_1);
  return;
}

