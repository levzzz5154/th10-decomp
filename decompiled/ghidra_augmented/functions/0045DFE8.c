/* Raw Ghidra reference; not compilable reconstruction. Address: 0045DFE8 */

/* Library Function - Single Match
    __setdefaultprecision
   
   Library: Visual Studio 2003 Release */

void __setdefaultprecision(void)

{
  __controlfp(0x10000,0x30000);
  return;
}

