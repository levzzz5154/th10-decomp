/* Raw Ghidra reference; not compilable reconstruction. Address: 00453C52 */

/* Library Function - Single Match
    ___sbh_heap_init
   
   Library: Visual Studio 2003 Release */

undefined4 __cdecl ___sbh_heap_init(undefined4 param_1)

{
  DAT_0049932c = HeapAlloc(DAT_00499340,0,0x140);
  if (DAT_0049932c == (LPVOID)0x0) {
    return 0;
  }
  DAT_00499324 = 0;
  DAT_00499328 = 0;
  DAT_00499334 = DAT_0049932c;
  DAT_00499330 = param_1;
  DAT_00499338 = 0x10;
  return 1;
}

