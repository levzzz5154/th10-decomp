/* Raw Ghidra reference; not compilable reconstruction. Address: 00455BF3 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

uint * __cdecl FUN_00455bf3(char *param_1,uint *param_2,undefined2 *param_3,undefined4 *param_4)

{
  size_t sVar1;
  int iVar2;
  BOOL BVar3;
  uint local_98 [12];
  undefined1 local_68 [96];
  uint local_8;
  
  local_8 = DAT_00473660 ^ (uint)local_68;
  if (param_1 == (char *)0x0) {
    param_2 = (uint *)0x0;
  }
  else if ((*param_1 == 'C') && (param_1[1] == '\0')) {
    *(undefined1 *)param_2 = 0x43;
    *(undefined1 *)((int)param_2 + 1) = 0;
    if (param_3 != (undefined2 *)0x0) {
      *param_3 = 0;
      param_3[1] = 0;
      param_3[2] = 0;
    }
    if (param_4 != (undefined4 *)0x0) {
      *param_4 = 0;
    }
  }
  else {
    sVar1 = _strlen(param_1);
    if ((0x81 < sVar1) ||
       ((iVar2 = _strcmp(&DAT_004732c0,param_1), iVar2 != 0 &&
        (iVar2 = _strcmp(&DAT_00473238,param_1), iVar2 != 0)))) {
      iVar2 = ___lc_strtolc((char *)local_98,param_1);
      if ((iVar2 != 0) ||
         (BVar3 = ___get_qualified_locale
                            ((LPLC_STRINGS)local_98,(UINT *)&DAT_00477368,(LPLC_STRINGS)local_98),
         BVar3 == 0)) {
        return (uint *)0x0;
      }
      _DAT_00477370 = (uint)DAT_0047736c;
      ___lc_lctostr((uint *)&DAT_004732c0,local_98);
      if ((*param_1 == '\0') || (sVar1 = _strlen(param_1), 0x81 < sVar1)) {
        param_1 = "";
      }
      DAT_004732ba = 0;
      _strncpy(&DAT_00473238,param_1,0x82);
    }
    if (param_3 != (undefined2 *)0x0) {
      _memcpy(param_3,&DAT_00477368,6);
    }
    if (param_4 != (undefined4 *)0x0) {
      _memcpy(param_4,&DAT_00477370,4);
    }
    FUN_0045bd80(param_2,(uint *)&DAT_004732c0);
    param_2 = (uint *)&DAT_004732c0;
  }
  return param_2;
}

