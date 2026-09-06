/* Raw Ghidra reference; not compilable reconstruction. Address: 0045DF97 */

/* Library Function - Single Match
    __cfltcvt
   
   Library: Visual Studio 2003 Release */

errno_t __cdecl
__cfltcvt(double *arg,char *buffer,size_t sizeInBytes,int format,int precision,int caps)

{
  undefined1 *puVar1;
  errno_t eVar2;
  
  if ((sizeInBytes == 0x65) || (sizeInBytes == 0x45)) {
    eVar2 = FUN_0045dd85((undefined4 *)arg,(int)buffer,format,precision);
  }
  else {
    if (sizeInBytes == 0x66) {
      puVar1 = FUN_0045de91((undefined4 *)arg,buffer,format);
      return (errno_t)puVar1;
    }
    eVar2 = FUN_0045def8((undefined4 *)arg,buffer,format,precision);
  }
  return eVar2;
}

