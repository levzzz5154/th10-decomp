/* Raw Ghidra reference; not compilable reconstruction. Address: 004539CB */

/* Library Function - Single Match
    __heap_init
   
   Library: Visual Studio 2003 Release */

int __cdecl __heap_init(void)

{
  int iVar1;
  int in_stack_00000004;
  
  DAT_00499340 = HeapCreate((uint)(in_stack_00000004 == 0),0x1000,0);
  if (DAT_00499340 == (HANDLE)0x0) {
    return 0;
  }
  DAT_00499344 = ___heap_select();
  if ((DAT_00499344 == 3) && (iVar1 = ___sbh_heap_init(0x3f8), iVar1 == 0)) {
    HeapDestroy(DAT_00499340);
    return 0;
  }
  return 1;
}

