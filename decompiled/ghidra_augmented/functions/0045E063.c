/* Raw Ghidra reference; not compilable reconstruction. Address: 0045E063 */

/* Library Function - Single Match
    __getenv_lk
   
   Library: Visual Studio 2003 Release */

int __cdecl __getenv_lk(uchar *param_1)

{
  int iVar1;
  size_t _MaxCount;
  size_t sVar2;
  int *piVar3;
  
  if (DAT_00499308 == 0) {
    return 0;
  }
  if (((DAT_00477490 != (int *)0x0) ||
      (((DAT_00477498 != 0 && (iVar1 = ___wtomb_environ(), iVar1 == 0)) &&
       (DAT_00477490 != (int *)0x0)))) && (piVar3 = DAT_00477490, param_1 != (uchar *)0x0)) {
    _MaxCount = _strlen((char *)param_1);
    for (; (char *)*piVar3 != (char *)0x0; piVar3 = piVar3 + 1) {
      sVar2 = _strlen((char *)*piVar3);
      if (((_MaxCount < sVar2) && (((uchar *)*piVar3)[_MaxCount] == '=')) &&
         (iVar1 = __mbsnbicoll((uchar *)*piVar3,param_1,_MaxCount), iVar1 == 0)) {
        return *piVar3 + 1 + _MaxCount;
      }
    }
  }
  return 0;
}

