/* Raw Ghidra reference; not compilable reconstruction. Address: 00435800 */

byte * __thiscall FUN_00435800(void *this,byte *param_1)

{
  undefined *puVar1;
  byte *pbVar2;
  uint uVar3;
  undefined **local_18;
  HANDLE local_14;
  undefined4 local_10;
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_004653a8;
  local_c = ExceptionList;
  ExceptionList = &local_c;
  puVar1 = FUN_004356f0(this);
  if (puVar1 != (undefined *)0x0) {
    FUN_00452730(this,'/');
    pbVar2 = FUN_00434dd0((int)puVar1,param_1);
    ExceptionList = local_c;
    return pbVar2;
  }
  local_18 = &PTR_FUN_0046f230;
  local_14 = (HANDLE)0xffffffff;
  local_10 = 0;
  local_4 = 0;
  FUN_00435370(&local_18,this,PTR_DAT_00474908);
  if (local_14 == (HANDLE)0xffffffff) {
    uVar3 = 0;
  }
  else {
    uVar3 = GetFileSize(local_14,(LPDWORD)0x0);
  }
  pbVar2 = FUN_00435580(&local_18,uVar3);
  local_18 = &PTR_FUN_0046f230;
  if (local_14 != (HANDLE)0xffffffff) {
    CloseHandle(local_14);
  }
  ExceptionList = local_c;
  return pbVar2;
}

