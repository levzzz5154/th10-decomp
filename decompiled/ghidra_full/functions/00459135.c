/* Raw Ghidra reference; not compilable reconstruction. Address: 00459135 */

/* Library Function - Single Match
    __setenvp
   
   Library: Visual Studio 2003 Release */

int __cdecl __setenvp(void)

{
  undefined4 *puVar1;
  size_t sVar2;
  uint *puVar3;
  uint *puVar4;
  int iVar5;
  
  if (DAT_00499314 == 0) {
    ___initmbctable();
  }
  iVar5 = 0;
  puVar4 = DAT_00477204;
  if (DAT_00477204 != (uint *)0x0) {
    for (; (char)*puVar4 != '\0'; puVar4 = (uint *)((int)puVar4 + sVar2 + 1)) {
      if ((char)*puVar4 != '=') {
        iVar5 = iVar5 + 1;
      }
      sVar2 = _strlen((char *)puVar4);
    }
    puVar1 = _malloc(iVar5 * 4 + 4);
    puVar4 = DAT_00477204;
    DAT_00477490 = puVar1;
    if (puVar1 != (undefined4 *)0x0) {
      do {
        if ((char)*puVar4 == '\0') {
          _free(DAT_00477204);
          DAT_00477204 = (uint *)0x0;
          *puVar1 = 0;
          DAT_00499308 = 1;
          return 0;
        }
        sVar2 = _strlen((char *)puVar4);
        if ((char)*puVar4 != '=') {
          puVar3 = _malloc(sVar2 + 1);
          *puVar1 = puVar3;
          if (puVar3 == (uint *)0x0) {
            _free(DAT_00477490);
            DAT_00477490 = (undefined4 *)0x0;
            return -1;
          }
          FUN_0045bd80(puVar3,puVar4);
          puVar1 = puVar1 + 1;
        }
        puVar4 = (uint *)((int)puVar4 + sVar2 + 1);
      } while( true );
    }
  }
  return -1;
}

