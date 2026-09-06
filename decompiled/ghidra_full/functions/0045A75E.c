/* Raw Ghidra reference; not compilable reconstruction. Address: 0045A75E */

/* Library Function - Single Match
    __store_str
   
   Library: Visual Studio 2003 Release */

void __fastcall __store_str(int *param_1,char *param_2)

{
  int iVar1;
  int *in_EAX;
  
  iVar1 = *in_EAX;
  for (; (iVar1 != 0 && (*param_2 != '\0')); param_2 = param_2 + 1) {
    *(char *)*param_1 = *param_2;
    *param_1 = *param_1 + 1;
    *in_EAX = *in_EAX + -1;
    iVar1 = *in_EAX;
  }
  return;
}

