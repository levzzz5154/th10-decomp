/* Raw Ghidra reference; not compilable reconstruction. Address: 00452E5A */

/* WARNING: Function: __SEH_prolog replaced with injection: SEH_prolog */

void __cdecl FUN_00452e5a(void *param_1)

{
  void *pvVar1;
  int iVar2;
  _EXCEPTION_POINTERS *local_18;
  
  pvVar1 = (void *)(*DAT_00477378)(DAT_00473390);
  if (pvVar1 == (void *)0x0) {
    iVar2 = (*DAT_0047737c)(DAT_00473390,param_1);
    pvVar1 = param_1;
    if (iVar2 == 0) {
      __amsg_exit(0x10);
    }
  }
  else {
    *(undefined4 *)((int)pvVar1 + 0x4c) = *(undefined4 *)((int)param_1 + 0x4c);
    *(undefined4 *)((int)pvVar1 + 0x50) = *(undefined4 *)((int)param_1 + 0x50);
    *(undefined4 *)((int)pvVar1 + 4) = *(undefined4 *)((int)param_1 + 4);
    _free(param_1);
  }
  if (PTR_FUN_004733ac != (undefined *)0x0) {
    (*(code *)PTR_FUN_004733ac)();
  }
  (**(code **)((int)pvVar1 + 0x4c))(*(undefined4 *)((int)pvVar1 + 0x50));
  __endthread();
  __XcptFilter(local_18->ExceptionRecord->ExceptionCode,local_18);
  return;
}

