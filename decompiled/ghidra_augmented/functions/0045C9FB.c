/* Raw Ghidra reference; not compilable reconstruction. Address: 0045C9FB */

/* Library Function - Single Match
    _GetLcidFromLanguage
   
   Library: Visual Studio 2003 Release */

void _GetLcidFromLanguage(void)

{
  size_t sVar1;
  char *pcVar2;
  
  pcVar2 = DAT_00477644;
  sVar1 = _strlen(DAT_00477644);
  DAT_00477634 = (uint)(sVar1 == 3);
  if (sVar1 == 3) {
    DAT_00477640 = 2;
  }
  else {
    DAT_00477640 = _GetPrimaryLen(pcVar2,DAT_00477644);
  }
  EnumSystemLocalesA(FUN_0045c86f,1);
  if ((DAT_00477628 & 4) == 0) {
    DAT_00477628 = 0;
  }
  return;
}

