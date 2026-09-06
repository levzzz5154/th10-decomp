/* Raw Ghidra reference; not compilable reconstruction. Address: 0045C93E */

/* Library Function - Single Match
    _GetLcidFromCountry
   
   Library: Visual Studio 2003 Release */

void _GetLcidFromCountry(void)

{
  size_t sVar1;
  
  sVar1 = _strlen(DAT_0047763c);
  DAT_00477638 = (uint)(sVar1 == 3);
  EnumSystemLocalesA(FUN_0045c544,1);
  if ((DAT_00477628 & 4) == 0) {
    DAT_00477628 = 0;
  }
  return;
}

