/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x0042AF20
 * Tracking name: FUN_0042af20
 * Ghidra name: FUN_0042af20
 * Tracked span: 272 bytes
 */


void FUN_0042af20(void)

{
  void *pvVar1;
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_004655ab;
  local_c = ExceptionList;
  ExceptionList = &local_c;
  pvVar1 = operator_new(0x1dcb4);
  local_4 = 0;
  if (pvVar1 != (void *)0x0) {
    DAT_0047783c = FUN_0042ae60();
    ExceptionList = local_c;
    return;
  }
  DAT_0047783c = 0;
  ExceptionList = local_c;
  return;
}

