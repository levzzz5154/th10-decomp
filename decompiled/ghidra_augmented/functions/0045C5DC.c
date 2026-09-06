/* Raw Ghidra reference; not compilable reconstruction. Address: 0045C5DC */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

undefined4 __cdecl FUN_0045c5dc(uint param_1,int param_2)

{
  int iVar1;
  uint uVar2;
  size_t sVar3;
  size_t sVar4;
  undefined4 uVar5;
  undefined4 extraout_ECX;
  char *pcVar6;
  char local_80 [120];
  uint local_8;
  
  local_8 = DAT_00473660 ^ (uint)&stack0xfffffffc;
  iVar1 = (*DAT_00477648)(param_1 & 0x3ff | 0x400,1,local_80,0x78);
  if (iVar1 == 0) {
LAB_0045c63e:
    uVar5 = 0;
  }
  else {
    uVar2 = _LcidFromHexString(extraout_ECX,local_80);
    if ((param_1 != uVar2) && (param_2 != 0)) {
      pcVar6 = DAT_00477644;
      sVar3 = _strlen(DAT_00477644);
      sVar4 = _GetPrimaryLen(pcVar6,DAT_00477644);
      if (sVar4 == sVar3) goto LAB_0045c63e;
    }
    uVar5 = 1;
  }
  return uVar5;
}

