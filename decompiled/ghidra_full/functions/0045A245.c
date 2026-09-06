/* Raw Ghidra reference; not compilable reconstruction. Address: 0045A245 */

/* Library Function - Single Match
    _abort
   
   Library: Visual Studio 2003 Release */

void __cdecl _abort(void)

{
  code *pcVar1;
  
  FUN_00458efd(10);
  _raise(0x16);
  __exit(3);
  pcVar1 = (code *)swi(3);
  (*pcVar1)();
  return;
}

