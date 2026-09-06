/* Raw Ghidra reference; not compilable reconstruction. Address: 00460872 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __cdecl FUN_00460872(char *param_1,int param_2,uint *param_3)

{
  short sVar1;
  uint uVar2;
  int local_20;
  char *local_1c;
  uint local_14;
  uint local_10;
  uint local_c;
  uint local_8;
  
  local_8 = DAT_00473660 ^ (uint)&stack0xfffffffc;
  local_1c = param_1;
  sVar1 = 0x404e;
  *param_3 = 0;
  param_3[1] = 0;
  param_3[2] = 0;
  if (param_2 != 0) {
    local_20 = param_2;
    do {
      local_14 = *param_3;
      local_10 = param_3[1];
      local_c = param_3[2];
      ___shl_12(param_3);
      ___shl_12(param_3);
      ___add_12(param_3,&local_14);
      ___shl_12(param_3);
      local_14 = (uint)*local_1c;
      local_10 = 0;
      local_c = 0;
      ___add_12(param_3,&local_14);
      local_1c = local_1c + 1;
      local_20 = local_20 + -1;
    } while (local_20 != 0);
  }
  if (param_3[2] == 0) {
    do {
      sVar1 = sVar1 + -0x10;
      uVar2 = param_3[1] >> 0x10;
      param_3[1] = *param_3 >> 0x10 | param_3[1] << 0x10;
      *param_3 = *param_3 << 0x10;
    } while (uVar2 == 0);
    param_3[2] = uVar2;
  }
  while ((param_3[2] & 0x8000) == 0) {
    ___shl_12(param_3);
    sVar1 = sVar1 + -1;
  }
  *(short *)((int)param_3 + 10) = sVar1;
  return;
}

