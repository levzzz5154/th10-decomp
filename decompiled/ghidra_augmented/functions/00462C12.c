/* Raw Ghidra reference; not compilable reconstruction. Address: 00462C12 */

void * __thiscall FUN_00462c12(void *this,undefined4 *param_1)

{
  size_t sVar1;
  uint *puVar2;
  
  *(undefined ***)this = &PTR_FUN_0046ca68;
  if ((char *)*param_1 == (char *)0x0) {
    *(undefined4 *)((int)this + 4) = 0;
  }
  else {
    sVar1 = _strlen((char *)*param_1);
    puVar2 = _malloc(sVar1 + 1);
    *(uint **)((int)this + 4) = puVar2;
    if (puVar2 != (uint *)0x0) {
      FUN_0045bd80(puVar2,(uint *)*param_1);
    }
  }
  *(undefined4 *)((int)this + 8) = 1;
  return this;
}

