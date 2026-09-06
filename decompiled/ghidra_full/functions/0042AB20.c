/* Raw Ghidra reference; not compilable reconstruction. Address: 0042AB20 */

void __fastcall FUN_0042ab20(int param_1)

{
  undefined4 *puVar1;
  void *_Memory;
  undefined4 *puVar2;
  int in_EAX;
  
  puVar2 = *(undefined4 **)(param_1 + 0x40 + in_EAX * 0xc);
  while (puVar2 != (undefined4 *)0x0) {
    puVar1 = (undefined4 *)puVar2[1];
    _Memory = (void *)*puVar2;
    puVar2 = puVar1;
    if (_Memory != (void *)0x0) {
      if (*(int *)((int)_Memory + 0x627c) != 0) {
        *(undefined4 *)(*(int *)((int)_Memory + 0x627c) + 8) =
             *(undefined4 *)((int)_Memory + 0x6280);
      }
      if (*(int *)((int)_Memory + 0x6280) != 0) {
        *(undefined4 *)(*(int *)((int)_Memory + 0x6280) + 4) =
             *(undefined4 *)((int)_Memory + 0x627c);
      }
      *(undefined4 *)((int)_Memory + 0x627c) = 0;
      *(undefined4 *)((int)_Memory + 0x6280) = 0;
      _free(_Memory);
    }
  }
  return;
}

