/* Raw Ghidra reference; not compilable reconstruction. Address: 00461ADD */

/* Library Function - Single Match
    _strncnt
   
   Library: Visual Studio 2003 Release */

size_t __cdecl _strncnt(char *_String,size_t _Cnt)

{
  char *pcVar1;
  char *in_EAX;
  
  pcVar1 = _String;
  for (; (pcVar1 != (char *)0x0 && (*in_EAX != '\0')); in_EAX = in_EAX + 1) {
    pcVar1 = pcVar1 + -1;
  }
  return (size_t)(_String + (-1 - (int)(pcVar1 + -1)));
}

