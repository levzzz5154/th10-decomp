/* Raw Ghidra reference; not compilable reconstruction. Address: 00452A84 */

/* Library Function - Single Match
    _atof
   
   Library: Visual Studio 2003 Release */

double __cdecl _atof(char *_String)

{
  int iVar1;
  uint *puVar2;
  uint local_1c [6];
  
  while( true ) {
    iVar1 = _isspace((uint)(byte)*_String);
    if (iVar1 == 0) break;
    _String = _String + 1;
  }
  _strlen(_String);
  puVar2 = FUN_00456674(local_1c,(byte *)_String);
  return *(double *)(puVar2 + 4);
}

