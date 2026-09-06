/* Raw Ghidra reference; not compilable reconstruction. Address: 0045A52B */

/* Library Function - Single Match
    __Gettnames
   
   Library: Visual Studio 2003 Release */

void * __cdecl __Gettnames(void)

{
  undefined *puVar1;
  size_t sVar2;
  size_t sVar3;
  size_t sVar4;
  size_t sVar5;
  size_t sVar6;
  void *_Dst;
  uint *puVar7;
  undefined4 *puVar8;
  int iVar9;
  uint *puVar10;
  int local_14;
  undefined4 *local_10;
  undefined4 *local_c;
  undefined4 *local_8;
  
  puVar1 = PTR_PTR_004739e0;
  iVar9 = 0;
  local_8 = (undefined4 *)0x0;
  do {
    sVar2 = _strlen(*(char **)(puVar1 + (int)local_8 * 4 + 0x1c));
    sVar3 = _strlen(*(char **)(puVar1 + (int)local_8 * 4));
    local_8 = (undefined4 *)((int)local_8 + 1);
    iVar9 = sVar3 + iVar9 + 2 + sVar2;
  } while (local_8 < 7);
  local_10 = (undefined4 *)(puVar1 + 0x38);
  local_c = (undefined4 *)0xc;
  do {
    sVar2 = _strlen((char *)local_10[0xc]);
    sVar3 = _strlen((char *)*local_10);
    local_10 = local_10 + 1;
    local_c = (undefined4 *)((int)local_c + -1);
    iVar9 = sVar3 + iVar9 + 2 + sVar2;
  } while (local_c != (undefined4 *)0x0);
  sVar2 = _strlen(*(char **)(puVar1 + 0x98));
  sVar3 = _strlen(*(char **)(puVar1 + 0x9c));
  sVar4 = _strlen(*(char **)(puVar1 + 0xa0));
  sVar5 = _strlen(*(char **)(puVar1 + 0xa4));
  sVar6 = _strlen(*(char **)(puVar1 + 0xa8));
  _Dst = _malloc(sVar3 + iVar9 + sVar2 + sVar4 + sVar5 + sVar6 + 0xbd);
  if (_Dst != (void *)0x0) {
    puVar10 = (uint *)((int)_Dst + 0xb8);
    _memcpy(_Dst,PTR_PTR_004739e0,0xb8);
    local_8 = (undefined4 *)0x0;
    local_c = (undefined4 *)(puVar1 + 0x1c);
    do {
      *(uint **)((int)_Dst + (int)local_8 * 4) = puVar10;
      puVar7 = FUN_0045bd80(puVar10,(uint *)local_c[-7]);
      sVar2 = _strlen((char *)puVar7);
      puVar10 = (uint *)((int)puVar10 + sVar2 + 1);
      *(uint **)(((int)_Dst - (int)puVar1) + (int)local_c) = puVar10;
      puVar7 = FUN_0045bd80(puVar10,(uint *)*local_c);
      sVar2 = _strlen((char *)puVar7);
      local_c = local_c + 1;
      local_8 = (undefined4 *)((int)local_8 + 1);
      puVar10 = (uint *)((int)puVar10 + sVar2 + 1);
    } while (local_8 < 7);
    local_8 = (undefined4 *)((int)_Dst + 0x68);
    puVar8 = (undefined4 *)(puVar1 + 0x38);
    local_14 = 0xc;
    do {
      *(uint **)((int)puVar8 + ((int)_Dst - (int)puVar1)) = puVar10;
      puVar7 = FUN_0045bd80(puVar10,(uint *)*puVar8);
      sVar2 = _strlen((char *)puVar7);
      puVar10 = (uint *)((int)puVar10 + sVar2 + 1);
      *local_8 = puVar10;
      puVar7 = FUN_0045bd80(puVar10,(uint *)puVar8[0xc]);
      sVar2 = _strlen((char *)puVar7);
      puVar8 = puVar8 + 1;
      local_8 = local_8 + 1;
      local_14 = local_14 + -1;
      puVar10 = (uint *)((int)puVar10 + sVar2 + 1);
    } while (local_14 != 0);
    *(uint **)((int)_Dst + 0x98) = puVar10;
    puVar7 = FUN_0045bd80(puVar10,*(uint **)(puVar1 + 0x98));
    sVar2 = _strlen((char *)puVar7);
    puVar10 = (uint *)((int)puVar10 + sVar2 + 1);
    *(uint **)((int)_Dst + 0x9c) = puVar10;
    puVar7 = FUN_0045bd80(puVar10,*(uint **)(puVar1 + 0x9c));
    sVar2 = _strlen((char *)puVar7);
    puVar10 = (uint *)((int)puVar10 + sVar2 + 1);
    *(uint **)((int)_Dst + 0xa0) = puVar10;
    puVar7 = FUN_0045bd80(puVar10,*(uint **)(puVar1 + 0xa0));
    sVar2 = _strlen((char *)puVar7);
    puVar10 = (uint *)((int)puVar10 + sVar2 + 1);
    *(uint **)((int)_Dst + 0xa4) = puVar10;
    puVar7 = FUN_0045bd80(puVar10,*(uint **)(puVar1 + 0xa4));
    sVar2 = _strlen((char *)puVar7);
    puVar10 = (uint *)((int)puVar10 + sVar2 + 1);
    *(uint **)((int)_Dst + 0xa8) = puVar10;
    FUN_0045bd80(puVar10,*(uint **)(puVar1 + 0xa8));
  }
  return _Dst;
}

