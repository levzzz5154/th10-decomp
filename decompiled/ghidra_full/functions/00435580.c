/* Raw Ghidra reference; not compilable reconstruction. Address: 00435580 */

void * __thiscall FUN_00435580(void *this,uint param_1)

{
  char cVar1;
  uint _Size;
  void *_Memory;
  undefined4 uVar2;
  int iVar3;
  
  if (*(int *)((int)this + 8) != -0x80000000) {
    return (void *)0x0;
  }
  _Size = (**(code **)(*(int *)this + 0x14))();
  if (param_1 < _Size) {
    return (void *)0x0;
  }
  _Memory = _malloc(_Size);
  if (_Memory == (void *)0x0) {
    return (void *)0x0;
  }
  uVar2 = (**(code **)(*(int *)this + 0x10))();
  cVar1 = (**(code **)(*(int *)this + 0x18))(uVar2,0);
  if (cVar1 != '\0') {
    iVar3 = (**(code **)(*(int *)this + 8))(_Memory,_Size);
    if (iVar3 != 0) {
      (**(code **)(*(int *)this + 0x18))(uVar2,0);
      return _Memory;
    }
    _free(_Memory);
  }
  return (void *)0x0;
}

