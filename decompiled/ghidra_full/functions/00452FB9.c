/* Raw Ghidra reference; not compilable reconstruction. Address: 00452FB9 */

/* Library Function - Single Match
    _sscanf
   
   Library: Visual Studio 2003 Release */

int __cdecl _sscanf(char *_Src,char *_Format,...)

{
  int iVar1;
  FILE local_24;
  
  local_24._flag = 0x49;
  local_24._base = _Src;
  local_24._ptr = _Src;
  local_24._cnt = _strlen(_Src);
  iVar1 = FUN_00457a7c(&local_24,(byte *)_Format,(undefined4 *)&stack0x0000000c);
  return iVar1;
}

