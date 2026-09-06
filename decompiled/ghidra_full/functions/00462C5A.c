/* Raw Ghidra reference; not compilable reconstruction. Address: 00462C5A */

undefined4 * __thiscall FUN_00462c5a(void *this,int param_1)

{
  int iVar1;
  char *_Str;
  size_t sVar2;
  uint *puVar3;
  
  *(undefined ***)this = &PTR_FUN_0046ca68;
  iVar1 = *(int *)(param_1 + 8);
  *(int *)((int)this + 8) = iVar1;
  _Str = *(char **)(param_1 + 4);
  if (iVar1 == 0) {
    *(char **)((int)this + 4) = _Str;
  }
  else if (_Str == (char *)0x0) {
    *(undefined4 *)((int)this + 4) = 0;
  }
  else {
    sVar2 = _strlen(_Str);
    puVar3 = _malloc(sVar2 + 1);
    *(uint **)((int)this + 4) = puVar3;
    if (puVar3 != (uint *)0x0) {
      FUN_0045bd80(puVar3,*(uint **)(param_1 + 4));
    }
  }
  return this;
}

