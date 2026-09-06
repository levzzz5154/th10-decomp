/* Raw Ghidra reference; not compilable reconstruction. Address: 00456AD4 */

/* Library Function - Single Match
    __fpmath
   
   Library: Visual Studio 2003 Release */

void __cdecl __fpmath(int param_1)

{
  FUN_00456a8c();
  DAT_00477388 = __ms_p5_mp_test_fdiv();
  if (param_1 != 0) {
    __setdefaultprecision();
  }
  return;
}

