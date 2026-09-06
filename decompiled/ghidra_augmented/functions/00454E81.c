/* Raw Ghidra reference; not compilable reconstruction. Address: 00454E81 */

/* Library Function - Single Match
    _write_string
   
   Library: Visual Studio 2003 Release */

void __cdecl write_string(int param_1)

{
  int *in_EAX;
  int unaff_EDI;
  
  if (((*(byte *)(unaff_EDI + 0xc) & 0x40) == 0) || (*(int *)(unaff_EDI + 8) != 0)) {
    do {
      if (param_1 < 1) {
        return;
      }
      param_1 = param_1 + -1;
      write_char();
    } while (*in_EAX != -1);
  }
  else {
    *in_EAX = *in_EAX + param_1;
  }
  return;
}

