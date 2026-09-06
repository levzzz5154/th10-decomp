/* Raw Ghidra reference; not compilable reconstruction. Address: 00459368 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Library Function - Single Match
    __setargv
   
   Library: Visual Studio 2003 Release */

int __cdecl __setargv(void)

{
  undefined4 *puVar1;
  int iVar2;
  int in_ECX;
  int local_8;
  
  local_8 = in_ECX;
  if (DAT_00499314 == 0) {
    ___initmbctable();
  }
  DAT_004775bc = 0;
  GetModuleFileNameA((HMODULE)0x0,&DAT_004774b8,0x104);
  _DAT_004774a0 = &DAT_004774b8;
  parse_cmdline((undefined4 *)0x0,&local_8);
  puVar1 = _malloc(in_ECX + local_8 * 4);
  if (puVar1 == (undefined4 *)0x0) {
    iVar2 = -1;
  }
  else {
    parse_cmdline(puVar1,&local_8);
    _DAT_00477484 = local_8 + -1;
    iVar2 = 0;
    _DAT_00477488 = puVar1;
  }
  return iVar2;
}

