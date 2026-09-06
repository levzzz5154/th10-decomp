/* Raw Ghidra reference; not compilable reconstruction. Address: 00462FC1 */

/* Library Function - Single Match
    void * __cdecl AdjustPointer(void *,struct PMD const &)
   
   Library: Visual Studio 2003 Release */

void * __cdecl AdjustPointer(void *param_1,PMD *param_2)

{
  int in_EAX;
  void *pvVar1;
  int *in_ECX;
  
  pvVar1 = (void *)(*in_ECX + in_EAX);
  if (-1 < in_ECX[1]) {
    pvVar1 = (void *)((int)pvVar1 + *(int *)(*(int *)(in_ECX[1] + in_EAX) + in_ECX[2]) + in_ECX[1]);
  }
  return pvVar1;
}

