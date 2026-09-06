/* Raw Ghidra reference; not compilable reconstruction. Address: 0040A1A0 */

void FUN_0040a1a0(int param_1)

{
  void *pvVar1;
  int iVar2;
  void *extraout_ECX;
  void *extraout_ECX_00;
  void *extraout_ECX_01;
  void *extraout_ECX_02;
  void *extraout_ECX_03;
  void *extraout_ECX_04;
  void *this;
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  puStack_8 = &LAB_004657e9;
  local_c = ExceptionList;
  local_4 = 1;
  ExceptionList = &local_c;
  FUN_00409eb0();
  iVar2 = DAT_00491be4;
  pvVar1 = *(void **)(param_1 + 8);
  this = extraout_ECX;
  if (pvVar1 != (void *)0x0) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_00492274);
    DAT_0049231c = DAT_0049231c + '\x01';
    FUN_00449f60(pvVar1,iVar2);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_00492274);
    DAT_0049231c = DAT_0049231c + -1;
    this = extraout_ECX_00;
  }
  iVar2 = DAT_00491be4;
  pvVar1 = *(void **)(param_1 + 0xc);
  if (pvVar1 != (void *)0x0) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_00492274);
    DAT_0049231c = DAT_0049231c + '\x01';
    FUN_00449f60(pvVar1,iVar2);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_00492274);
    DAT_0049231c = DAT_0049231c + -1;
    this = extraout_ECX_01;
  }
  pvVar1 = DAT_0047770c;
  if (DAT_0047770c != (void *)0x0) {
    FUN_004145f0(this,(int)DAT_0047770c);
    _free(pvVar1);
    this = extraout_ECX_02;
  }
  pvVar1 = DAT_00477834;
  if (DAT_00477834 != (void *)0x0) {
    FUN_00424ed0(this,(int)DAT_00477834);
    _free(pvVar1);
    this = extraout_ECX_03;
  }
  pvVar1 = DAT_004776f0;
  if (DAT_004776f0 != (void *)0x0) {
    FUN_00405f70((int)DAT_004776f0);
    _free(pvVar1);
    this = extraout_ECX_04;
  }
  pvVar1 = DAT_00477704;
  if (DAT_00477704 != (void *)0x0) {
    FUN_0040d530(this);
    _free(pvVar1);
  }
  pvVar1 = DAT_004776ec;
  if (DAT_004776ec != (void *)0x0) {
    FUN_00405620((int)DAT_004776ec);
    _free(pvVar1);
  }
  pvVar1 = DAT_00477818;
  if (DAT_00477818 != (void *)0x0) {
    FUN_0041adf0((int)DAT_00477818);
    _free(pvVar1);
  }
  pvVar1 = DAT_00477840;
  if (DAT_00477840 != (void *)0x0) {
    FUN_0042b570((int)DAT_00477840);
    _free(pvVar1);
  }
  DAT_004776f8 = 0;
  if (*(void **)(param_1 + 0x620) != (void *)0x0) {
    _free(*(void **)(param_1 + 0x620));
  }
  *(undefined4 *)(param_1 + 0x620) = 0;
  *(undefined ***)(param_1 + 0x10) = &PTR_FUN_004703e4;
  FUN_0044c150();
  ExceptionList = local_c;
  return;
}

