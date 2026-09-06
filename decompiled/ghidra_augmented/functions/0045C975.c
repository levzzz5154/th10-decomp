/* Raw Ghidra reference; not compilable reconstruction. Address: 0045C975 */

/* Library Function - Single Match
    _GetLcidFromLangCountry
   
   Library: Visual Studio 2003 Release */

void _GetLcidFromLangCountry(void)

{
  size_t sVar1;
  char *pcVar2;
  
  pcVar2 = DAT_00477644;
  sVar1 = _strlen(DAT_00477644);
  DAT_00477634 = (uint)(sVar1 == 3);
  sVar1 = _strlen(DAT_0047763c);
  DAT_00477638 = (uint)(sVar1 == 3);
  DAT_0047762c = 0;
  if (DAT_00477634 == 0) {
    DAT_00477640 = _GetPrimaryLen(pcVar2,DAT_00477644);
  }
  else {
    DAT_00477640 = 2;
  }
  EnumSystemLocalesA(FUN_0045c651,1);
  if ((((DAT_00477628 & 0x100) == 0) || ((DAT_00477628 & 0x200) == 0)) || ((DAT_00477628 & 7) == 0))
  {
    DAT_00477628 = 0;
  }
  return;
}

