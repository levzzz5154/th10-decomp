/* Raw Ghidra reference; not compilable reconstruction. Address: 0045DC7C */

/* Library Function - Single Match
    __fassign
   
   Library: Visual Studio 2003 Release */

void __cdecl __fassign(int flag,char *argument,char *number)

{
  _CRT_DOUBLE local_c;
  
  if (flag != 0) {
    FUN_0045d676(&local_c,(byte *)number);
    *(undefined4 *)argument = local_c.x._0_4_;
    *(undefined4 *)(argument + 4) = local_c.x._4_4_;
    return;
  }
  FUN_0045d701((_CRT_DOUBLE *)&flag,(byte *)number);
  *(int *)argument = flag;
  return;
}

