/* Raw Ghidra reference; not compilable reconstruction. Address: 00460E41 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

int * __cdecl FUN_00460e41(undefined4 param_1,undefined4 param_2,int *param_3,uint *param_4)

{
  int *piVar1;
  uint *puVar2;
  int iVar3;
  short local_30;
  char local_2e;
  uint local_2c [6];
  uint local_14;
  uint uStack_10;
  ushort uStack_c;
  uint local_8;
  
  puVar2 = param_4;
  piVar1 = param_3;
  local_8 = DAT_00473660 ^ (uint)&stack0xfffffffc;
  ___dtold(&local_14,&param_1);
  iVar3 = FUN_00461841(local_14,uStack_10,uStack_c,0x11,0,&local_30);
  piVar1[2] = iVar3;
  *piVar1 = (int)local_2e;
  piVar1[1] = (int)local_30;
  FUN_0045bd80(puVar2,local_2c);
  piVar1[3] = (int)puVar2;
  return piVar1;
}

