/* Raw Ghidra reference; not compilable reconstruction. Address: 0045F655 */

/* Library Function - Single Match
    __free_osfhnd
   
   Library: Visual Studio 2003 Release */

int __cdecl __free_osfhnd(int param_1)

{
  int *piVar1;
  ulong *puVar2;
  int iVar3;
  DWORD nStdHandle;
  
  if ((uint)param_1 < DAT_004991e4) {
    iVar3 = (param_1 & 0x1fU) * 0x24;
    piVar1 = (int *)((&DAT_00499200)[param_1 >> 5] + iVar3);
    if (((*(byte *)(piVar1 + 1) & 1) != 0) && (*piVar1 != -1)) {
      if (DAT_00473074 == 1) {
        if (param_1 == 0) {
          nStdHandle = 0xfffffff6;
        }
        else if (param_1 == 1) {
          nStdHandle = 0xfffffff5;
        }
        else {
          if (param_1 != 2) goto LAB_0045f6b1;
          nStdHandle = 0xfffffff4;
        }
        SetStdHandle(nStdHandle,(HANDLE)0x0);
      }
LAB_0045f6b1:
      *(undefined4 *)(iVar3 + (&DAT_00499200)[param_1 >> 5]) = 0xffffffff;
      return 0;
    }
  }
  piVar1 = FUN_00456af2();
  *piVar1 = 9;
  puVar2 = FUN_00456afb();
  *puVar2 = 0;
  return -1;
}

