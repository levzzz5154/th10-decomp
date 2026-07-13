/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x00413450
 * Tracking name: FUN_00413450
 * Ghidra name: FUN_00413450
 * Tracked span: 96 bytes
 */


void FUN_00413450(void)

{
  void *pvVar1;
  int iVar2;
  void *unaff_EBX;
  
  iVar2 = DAT_00491be4;
  if (unaff_EBX != (void *)0x0) {
    pvVar1 = *(void **)((int)unaff_EBX + 0xc);
    if (pvVar1 != (void *)0x0) {
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_00492274);
      DAT_0049231c = DAT_0049231c + '\x01';
      FUN_00449f60(pvVar1,iVar2);
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_00492274);
      DAT_0049231c = DAT_0049231c + -1;
    }
    DAT_00477708 = 0;
    _free(unaff_EBX);
  }
  return;
}

