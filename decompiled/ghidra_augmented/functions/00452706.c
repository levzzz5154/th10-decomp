/* Raw Ghidra reference; not compilable reconstruction. Address: 00452706 */

/* Library Function - Single Match
    _malloc
   
   Library: Visual Studio 2003 Release */

void * __cdecl _malloc(size_t _Size)

{
  void *pvVar1;
  
  pvVar1 = __nh_malloc(_Size,DAT_00477364);
  return pvVar1;
}

