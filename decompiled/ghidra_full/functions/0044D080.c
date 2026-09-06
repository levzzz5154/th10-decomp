/* Raw Ghidra reference; not compilable reconstruction. Address: 0044D080 */

void __fastcall ReleasePlatformOwnedArray(undefined4 *param_1)

{
  int *piVar1;
  void *_Memory;
  uint uVar2;
  
  uVar2 = 0;
  *param_1 = &PTR_DestroyPlatformCollection_004705d8;
  if (param_1[4] != 0) {
    do {
      piVar1 = *(int **)(param_1[1] + uVar2 * 4);
      if (piVar1 != (int *)0x0) {
        (**(code **)(*piVar1 + 8))(piVar1);
        *(undefined4 *)(param_1[1] + uVar2 * 4) = 0;
      }
      uVar2 = uVar2 + 1;
    } while (uVar2 < (uint)param_1[4]);
  }
  if ((void *)param_1[1] != (void *)0x0) {
    _free((void *)param_1[1]);
    param_1[1] = 0;
  }
  _Memory = (void *)param_1[3];
  if (_Memory != (void *)0x0) {
    if (*(int *)((int)_Memory + 0x78) == 1) {
      CloseHandle(*(HANDLE *)((int)_Memory + 0x8c));
      *(undefined4 *)((int)_Memory + 0x8c) = 0xffffffff;
    }
    _free(_Memory);
    param_1[3] = 0;
  }
  return;
}

