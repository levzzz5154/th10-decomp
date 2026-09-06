/* Raw Ghidra reference; not compilable reconstruction. Address: 00455A90 */

/* Library Function - Single Match
    ___lc_lctostr
   
   Library: Visual Studio 2003 Release */

void __cdecl ___lc_lctostr(uint *param_1,uint *param_2)

{
  FUN_0045bd80(param_1,param_2);
  if ((char)param_2[0x10] != '\0') {
    __strcats(param_1,2);
  }
  if ((char)param_2[0x20] != '\0') {
    __strcats(param_1,2);
  }
  return;
}

