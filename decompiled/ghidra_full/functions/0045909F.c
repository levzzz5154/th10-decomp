/* Raw Ghidra reference; not compilable reconstruction. Address: 0045909F */

/* Library Function - Single Match
    __FF_MSGBANNER
   
   Library: Visual Studio 2003 Release */

void __cdecl __FF_MSGBANNER(void)

{
  if ((DAT_0047720c == 1) || ((DAT_0047720c == 0 && (DAT_00473074 == 1)))) {
    FUN_00458efd(0xfc);
    if (DAT_004774b4 != (code *)0x0) {
      (*DAT_004774b4)();
    }
    FUN_00458efd(0xff);
  }
  return;
}

