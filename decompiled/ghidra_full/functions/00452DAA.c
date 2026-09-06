/* Raw Ghidra reference; not compilable reconstruction. Address: 00452DAA */

/* Library Function - Single Match
    ___onexitinit
   
   Library: Visual Studio 2003 Release */

undefined4 ___onexitinit(void)

{
  DAT_00499310 = _malloc(0x80);
  if (DAT_00499310 == (undefined4 *)0x0) {
    return 0x18;
  }
  *DAT_00499310 = 0;
  DAT_0049930c = DAT_00499310;
  return 0;
}

