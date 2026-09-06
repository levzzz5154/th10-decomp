/* Raw Ghidra reference; not compilable reconstruction. Address: 0045C35D */

/* Library Function - Single Match
    _GetLcidFromDefault
   
   Library: Visual Studio 2003 Release */

void _GetLcidFromDefault(void)

{
  DAT_00477628._0_2_ = (ushort)DAT_00477628 | 0x104;
  DAT_00477630 = GetUserDefaultLCID();
  DAT_0047762c = DAT_00477630;
  return;
}

