/* Raw Ghidra reference; not compilable reconstruction. Address: 0045A496 */

/* Library Function - Single Match
    __Getmonths
   
   Library: Visual Studio 2003 Release */

char * __cdecl __Getmonths(void)

{
  undefined *puVar1;
  size_t sVar2;
  size_t sVar3;
  char *pcVar4;
  uint *puVar5;
  int iVar6;
  undefined1 *puVar7;
  uint *puVar8;
  char *pcVar9;
  undefined4 *puVar10;
  int local_c;
  int local_8;
  
  puVar1 = PTR_PTR_004739e0;
  local_8 = 0;
  puVar10 = (undefined4 *)(PTR_PTR_004739e0 + 0x38);
  local_c = 0xc;
  do {
    sVar2 = _strlen((char *)puVar10[0xc]);
    sVar3 = _strlen((char *)*puVar10);
    local_8 = sVar3 + local_8 + 2 + sVar2;
    puVar10 = puVar10 + 1;
    local_c = local_c + -1;
  } while (local_c != 0);
  pcVar4 = _malloc(local_8 + 1);
  if (pcVar4 != (char *)0x0) {
    puVar10 = (undefined4 *)(puVar1 + 0x68);
    iVar6 = 0xc;
    pcVar9 = pcVar4;
    do {
      *pcVar9 = ':';
      puVar5 = FUN_0045bd80((uint *)(pcVar9 + 1),(uint *)puVar10[-0xc]);
      sVar2 = _strlen((char *)puVar5);
      puVar7 = (undefined1 *)((int)(pcVar9 + 1) + sVar2);
      *puVar7 = 0x3a;
      puVar8 = (uint *)(puVar7 + 1);
      puVar5 = FUN_0045bd80(puVar8,(uint *)*puVar10);
      sVar2 = _strlen((char *)puVar5);
      pcVar9 = (char *)((int)puVar8 + sVar2);
      puVar10 = puVar10 + 1;
      iVar6 = iVar6 + -1;
    } while (iVar6 != 0);
    *pcVar9 = '\0';
  }
  return pcVar4;
}

