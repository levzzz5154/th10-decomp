/* Raw Ghidra reference; not compilable reconstruction. Address: 004575BF */

/* Library Function - Single Match
    __cinit
   
   Library: Visual Studio 2003 Release */

int __cdecl __cinit(int param_1)

{
  int iVar1;
  undefined4 *puVar2;
  
  if (PTR___fpmath_004733a8 != (undefined *)0x0) {
    (*(code *)PTR___fpmath_004733a8)(param_1);
  }
  iVar1 = 0;
  puVar2 = &DAT_00473034;
  do {
    if (iVar1 != 0) {
      return iVar1;
    }
    if ((code *)*puVar2 != (code *)0x0) {
      iVar1 = (*(code *)*puVar2)();
    }
    puVar2 = puVar2 + 1;
  } while (puVar2 < &DAT_0047304c);
  if (iVar1 == 0) {
    _atexit((_func_4879 *)&LAB_004597ba);
    puVar2 = &DAT_00473000;
    do {
      if ((code *)*puVar2 != (code *)0x0) {
        (*(code *)*puVar2)();
      }
      puVar2 = puVar2 + 1;
    } while (puVar2 < &DAT_00473030);
    iVar1 = 0;
  }
  return iVar1;
}

