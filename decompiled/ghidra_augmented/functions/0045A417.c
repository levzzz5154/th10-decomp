/* Raw Ghidra reference; not compilable reconstruction. Address: 0045A417 */

/* Library Function - Single Match
    __Getdays
   
   Library: Visual Studio 2003 Release */

char * __cdecl __Getdays(void)

{
  undefined *puVar1;
  size_t sVar2;
  size_t sVar3;
  char *pcVar4;
  uint *puVar5;
  uint uVar6;
  int iVar7;
  undefined1 *puVar8;
  uint *puVar9;
  char *pcVar10;
  
  puVar1 = PTR_PTR_004739e0;
  iVar7 = 0;
  uVar6 = 0;
  do {
    sVar2 = _strlen(*(char **)(puVar1 + uVar6 * 4 + 0x1c));
    sVar3 = _strlen(*(char **)(puVar1 + uVar6 * 4));
    uVar6 = uVar6 + 1;
    iVar7 = sVar3 + iVar7 + 2 + sVar2;
  } while (uVar6 < 7);
  pcVar4 = _malloc(iVar7 + 1);
  if (pcVar4 != (char *)0x0) {
    uVar6 = 0;
    pcVar10 = pcVar4;
    do {
      *pcVar10 = ':';
      puVar5 = FUN_0045bd80((uint *)(pcVar10 + 1),*(uint **)(puVar1 + uVar6 * 4));
      sVar2 = _strlen((char *)puVar5);
      puVar8 = (undefined1 *)((int)(pcVar10 + 1) + sVar2);
      *puVar8 = 0x3a;
      puVar9 = (uint *)(puVar8 + 1);
      puVar5 = FUN_0045bd80(puVar9,*(uint **)(puVar1 + uVar6 * 4 + 0x1c));
      sVar2 = _strlen((char *)puVar5);
      pcVar10 = (char *)((int)puVar9 + sVar2);
      uVar6 = uVar6 + 1;
    } while (uVar6 < 7);
    *pcVar10 = '\0';
  }
  return pcVar4;
}

