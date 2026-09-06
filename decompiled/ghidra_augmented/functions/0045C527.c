/* Raw Ghidra reference; not compilable reconstruction. Address: 0045C527 */

/* Library Function - Single Match
    _GetPrimaryLen
   
   Library: Visual Studio 2003 Release */

int __fastcall _GetPrimaryLen(undefined4 param_1,char *param_2)

{
  char cVar1;
  int iVar2;
  
  iVar2 = 0;
  while( true ) {
    cVar1 = *param_2;
    param_2 = param_2 + 1;
    if (((cVar1 < 'A') || ('Z' < cVar1)) && ((cVar1 < 'a' || ('z' < cVar1)))) break;
    iVar2 = iVar2 + 1;
  }
  return iVar2;
}

