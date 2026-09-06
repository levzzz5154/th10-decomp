/* Raw Ghidra reference; not compilable reconstruction. Address: 00449E50 */

void FUN_00449e50(int param_1)

{
  undefined4 *puVar1;
  void *pvVar2;
  int in_EAX;
  
  puVar1 = *(undefined4 **)(in_EAX + 0x18);
  while (puVar1 != (undefined4 *)0x0) {
    pvVar2 = (void *)*puVar1;
    puVar1 = (undefined4 *)puVar1[1];
    if (pvVar2 != (void *)0x0) {
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_00492274);
      DAT_0049231c = DAT_0049231c + '\x01';
      FUN_00449f60(pvVar2,param_1);
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_00492274);
      DAT_0049231c = DAT_0049231c + -1;
    }
  }
  return;
}

