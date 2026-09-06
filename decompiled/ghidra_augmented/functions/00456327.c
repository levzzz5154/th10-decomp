/* Raw Ghidra reference; not compilable reconstruction. Address: 00456327 */

/* Library Function - Single Match
    __mtterm
   
   Library: Visual Studio 2003 Release */

void __cdecl __mtterm(void)

{
  if (DAT_00473390 != -1) {
    (*DAT_00477380)(DAT_00473390);
    DAT_00473390 = -1;
  }
  __mtdeletelocks();
  return;
}

