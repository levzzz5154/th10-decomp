/* Raw Ghidra reference; not compilable reconstruction. Address: 0045373D */

/* Library Function - Single Match
    __amsg_exit
   
   Library: Visual Studio 2003 Release */

void __cdecl __amsg_exit(int param_1)

{
  if (DAT_0047720c == 1) {
    __FF_MSGBANNER();
  }
  FUN_00458efd(param_1);
  (*(code *)PTR___exit_00473070)(0xff);
  return;
}

