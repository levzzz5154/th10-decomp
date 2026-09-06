/* Raw Ghidra reference; not compilable reconstruction. Address: 00463AE6 */

/* Library Function - Multiple Matches With Different Base Names
    int __cdecl _ValidateRead(void const *,unsigned int)
    int __cdecl _ValidateWrite(void *,unsigned int)
   
   Library: Visual Studio 2003 Release */

int __cdecl _ValidateWrite(void *param_1,uint param_2)

{
  BOOL BVar1;
  
  BVar1 = IsBadWritePtr(param_1,param_2);
  return (uint)(BVar1 == 0);
}

