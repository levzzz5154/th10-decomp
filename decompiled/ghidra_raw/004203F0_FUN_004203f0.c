/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x004203F0
 * Tracking name: FUN_004203f0
 * Ghidra name: FUN_004203f0
 * Tracked span: 128 bytes
 */


void FUN_004203f0(void)

{
  void *pvVar1;
  undefined4 *_Memory;
  
  pvVar1 = DAT_00477810;
  if (DAT_00477810 != (void *)0x0) {
    FUN_00417c80((int)DAT_00477810);
    _free(pvVar1);
  }
  _Memory = DAT_0047784c;
  if (DAT_0047784c != (undefined4 *)0x0) {
    FUN_0042cb60(DAT_0047784c);
    _free(_Memory);
  }
  pvVar1 = DAT_00477820;
  if (DAT_00477820 != (void *)0x0) {
    FUN_0041fb50((int)DAT_00477820);
    _free(pvVar1);
  }
  pvVar1 = DAT_00477700;
  if (DAT_00477700 != (void *)0x0) {
    FUN_0040b7b0((int)DAT_00477700);
    _free(pvVar1);
  }
  pvVar1 = DAT_00477838;
  if (DAT_00477838 != (void *)0x0) {
    FUN_004294a0((int)DAT_00477838);
    _free(pvVar1);
  }
  return;
}

