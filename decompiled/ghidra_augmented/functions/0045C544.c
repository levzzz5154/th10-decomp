/* Raw Ghidra reference; not compilable reconstruction. Address: 0045C544 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

uint __thiscall FUN_0045c544(void *this,char *param_1)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  char local_80 [120];
  uint local_8;
  
  local_8 = DAT_00473660 ^ (uint)&stack0xfffffffc;
  iVar1 = _LcidFromHexString(this,param_1);
  iVar2 = (*DAT_00477648)(iVar1,(-(uint)(DAT_00477638 != 0) & 0xfffff005) + 0x1002,local_80,0x78);
  if (iVar2 == 0) {
    DAT_00477628 = 0;
    uVar3 = 1;
  }
  else {
    iVar2 = __stricmp(DAT_0047763c,local_80);
    if (iVar2 == 0) {
      iVar2 = FUN_0045c3f1((short)iVar1);
      if (iVar2 != 0) {
        DAT_00477628 = DAT_00477628 | 4;
        DAT_0047762c = iVar1;
        DAT_00477630 = iVar1;
      }
    }
    uVar3 = ~(DAT_00477628 >> 2) & 1;
  }
  return uVar3;
}

