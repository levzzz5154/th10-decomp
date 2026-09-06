/* Raw Ghidra reference; not compilable reconstruction. Address: 00452422 */

/* WARNING: Function: __SEH_prolog replaced with injection: SEH_prolog */
/* WARNING: Function: __SEH_epilog replaced with injection: EH_epilog3 */
/* Library Function - Single Match
    _free
   
   Library: Visual Studio 2003 Release */

void __cdecl _free(void *_Memory)

{
  uint *puVar1;
  
  if (_Memory != (void *)0x0) {
    if (DAT_00499344 == 3) {
      __lock(4);
      puVar1 = (uint *)___sbh_find_block((int)_Memory);
      if (puVar1 != (uint *)0x0) {
        ___sbh_free_block(puVar1,(int)_Memory);
      }
      FUN_00452475();
      if (puVar1 != (uint *)0x0) {
        return;
      }
    }
    HeapFree(DAT_00499340,0,_Memory);
  }
  return;
}

