/* Raw Ghidra reference; not compilable reconstruction. Address: 0045DBDB */

void __cdecl FUN_0045dbdb(char *param_1)

{
  char cVar1;
  char cVar2;
  int iVar3;
  bool bVar4;
  
  iVar3 = _tolower((int)*param_1);
  bVar4 = iVar3 == 0x65;
  while (!bVar4) {
    param_1 = param_1 + 1;
    iVar3 = _isdigit((int)*param_1);
    bVar4 = iVar3 == 0;
  }
  cVar2 = *param_1;
  *param_1 = DAT_00473af4;
  do {
    param_1 = param_1 + 1;
    cVar1 = *param_1;
    *param_1 = cVar2;
    cVar2 = cVar1;
  } while (*param_1 != '\0');
  return;
}

