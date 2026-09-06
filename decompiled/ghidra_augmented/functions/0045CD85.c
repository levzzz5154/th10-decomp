/* Raw Ghidra reference; not compilable reconstruction. Address: 0045CD85 */

/* Library Function - Single Match
    _setSBCS
   
   Library: Visual Studio 2003 Release */

void __cdecl setSBCS(void)

{
  int iVar1;
  undefined4 *puVar2;
  
  puVar2 = &DAT_00497fa0;
  for (iVar1 = 0x40; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  *(undefined1 *)puVar2 = 0;
  DAT_004980a4 = 0;
  DAT_00497f98 = 0;
  DAT_00497f90 = 0;
  DAT_004980b0 = 0;
  DAT_004980b4 = 0;
  DAT_004980b8 = 0;
  return;
}

