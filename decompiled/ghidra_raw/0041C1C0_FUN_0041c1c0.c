/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x0041C1C0
 * Tracking name: FUN_0041c1c0
 * Ghidra name: FUN_0041c1c0
 * Tracked span: 208 bytes
 */


void FUN_0041c1c0(int param_1)

{
  void *pvVar1;
  int *piVar2;
  int *_Memory;
  int iVar3;
  
  iVar3 = DAT_00491be4;
  pvVar1 = *(void **)(param_1 + 8);
  if (pvVar1 != (void *)0x0) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_00492274);
    DAT_0049231c = DAT_0049231c + '\x01';
    FUN_00449f60(pvVar1,iVar3);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_00492274);
    DAT_0049231c = DAT_0049231c + -1;
  }
  iVar3 = DAT_00491be4;
  pvVar1 = *(void **)(param_1 + 0xc);
  if (pvVar1 != (void *)0x0) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_00492274);
    DAT_0049231c = DAT_0049231c + '\x01';
    FUN_00449f60(pvVar1,iVar3);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_00492274);
    DAT_0049231c = DAT_0049231c + -1;
  }
  _Memory = *(int **)(param_1 + 0x18);
  while (_Memory != (int *)0x0) {
    piVar2 = (int *)_Memory[2];
    (**(code **)(*_Memory + 0x10))();
    *(int *)(_Memory[1] + 8) = _Memory[2];
    if (_Memory[2] != 0) {
      *(int *)(_Memory[2] + 4) = _Memory[1];
    }
    _free(_Memory);
    _Memory = piVar2;
  }
  DAT_0047781c = 0;
  return;
}

