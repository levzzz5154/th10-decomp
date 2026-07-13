/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x004358E0
 * Tracking name: FUN_004358e0
 * Ghidra name: FUN_004358e0
 * Tracked span: 208 bytes
 */


DWORD __fastcall FUN_004358e0(uint *param_1)

{
  undefined *puVar1;
  DWORD DVar2;
  undefined **local_18;
  HANDLE local_14;
  undefined4 local_10;
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_00465388;
  local_c = ExceptionList;
  ExceptionList = &local_c;
  puVar1 = FUN_004356f0(param_1);
  DVar2 = 0;
  if (puVar1 != (undefined *)0x0) {
    FUN_00452730(param_1,'/');
    DVar2 = FUN_00434ef0();
    ExceptionList = local_c;
    return DVar2;
  }
  local_18 = &PTR_FUN_0046f230;
  local_14 = (HANDLE)0xffffffff;
  local_10 = 0;
  local_4 = 0;
  FUN_00435370(&local_18,(LPCSTR)param_1,PTR_DAT_00474908);
  if (local_14 != (HANDLE)0xffffffff) {
    DVar2 = GetFileSize(local_14,(LPDWORD)0x0);
  }
  local_18 = &PTR_FUN_0046f230;
  if (local_14 != (HANDLE)0xffffffff) {
    CloseHandle(local_14);
  }
  ExceptionList = local_c;
  return DVar2;
}

