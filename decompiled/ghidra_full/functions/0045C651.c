/* Raw Ghidra reference; not compilable reconstruction. Address: 0045C651 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

uint __thiscall FUN_0045c651(void *this,char *param_1)

{
  uint uVar1;
  int iVar2;
  size_t sVar3;
  char local_80 [120];
  uint local_8;
  
  local_8 = DAT_00473660 ^ (uint)&stack0xfffffffc;
  uVar1 = _LcidFromHexString(this,param_1);
  iVar2 = (*DAT_00477648)(uVar1,(-(uint)(DAT_00477638 != 0) & 0xfffff005) + 0x1002,local_80,0x78);
  if (iVar2 == 0) {
    DAT_00477628 = 0;
    return 1;
  }
  iVar2 = __stricmp(DAT_0047763c,local_80);
  if (iVar2 == 0) {
    iVar2 = (*DAT_00477648)(uVar1,(-(uint)(DAT_00477634 != 0) & 0xfffff002) + 0x1001,local_80,0x78);
    if (iVar2 == 0) {
      DAT_00477628 = 0;
      return 1;
    }
    iVar2 = __stricmp(DAT_00477644,local_80);
    if (iVar2 == 0) {
      DAT_00477628 = DAT_00477628 | 0x304;
      DAT_0047762c = uVar1;
      DAT_00477630 = uVar1;
    }
    else if ((DAT_00477628 & 2) == 0) {
      if ((DAT_00477640 == 0) ||
         (iVar2 = __strnicmp(DAT_00477644,local_80,DAT_00477640), iVar2 != 0)) {
        if (((DAT_00477628 & 1) == 0) && (iVar2 = FUN_0045c3f1((short)uVar1), iVar2 != 0)) {
          DAT_00477628 = DAT_00477628 | 1;
          DAT_00477630 = uVar1;
        }
      }
      else {
        DAT_00477628 = DAT_00477628 | 2;
        DAT_00477630 = uVar1;
        sVar3 = _strlen(DAT_00477644);
        if (sVar3 == DAT_00477640) {
          DAT_0047762c = uVar1;
        }
      }
    }
  }
  if ((DAT_00477628 & 0x300) == 0x300) goto LAB_0045c851;
  iVar2 = (*DAT_00477648)(uVar1,(-(uint)(DAT_00477634 != 0) & 0xfffff002) + 0x1001,local_80,0x78);
  if (iVar2 == 0) {
    DAT_00477628 = 0;
    return 1;
  }
  iVar2 = __stricmp(DAT_00477644,local_80);
  if (iVar2 == 0) {
    DAT_00477628 = DAT_00477628 | 0x200;
    if (((DAT_00477634 == 0) && (DAT_00477640 != 0)) &&
       (sVar3 = _strlen(DAT_00477644), sVar3 == DAT_00477640)) {
      iVar2 = 1;
      goto LAB_0045c830;
    }
  }
  else {
    if (((DAT_00477634 != 0) || (DAT_00477640 == 0)) ||
       (iVar2 = __strnicmp(DAT_00477644,local_80,DAT_00477640), iVar2 != 0)) goto LAB_0045c851;
    iVar2 = 0;
LAB_0045c830:
    iVar2 = FUN_0045c5dc(uVar1,iVar2);
    if (iVar2 == 0) goto LAB_0045c851;
  }
  DAT_00477628 = DAT_00477628 | 0x100;
  if (DAT_0047762c == 0) {
    DAT_0047762c = uVar1;
  }
LAB_0045c851:
  return ~(DAT_00477628 >> 2) & 1;
}

