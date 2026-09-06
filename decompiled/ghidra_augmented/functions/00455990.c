/* Raw Ghidra reference; not compilable reconstruction. Address: 00455990 */

/* Library Function - Single Match
    __strcats
   
   Library: Visual Studio 2003 Release */

void __cdecl __strcats(uint *param_1,int param_2)

{
  int *piVar1;
  int iVar2;
  
  if (0 < param_2) {
    piVar1 = &param_2;
    iVar2 = param_2;
    do {
      piVar1 = piVar1 + 1;
      FUN_0045bd90(param_1,(uint *)*piVar1);
      iVar2 = iVar2 + -1;
    } while (iVar2 != 0);
  }
  return;
}

