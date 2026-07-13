/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x004203C0
 * Tracking name: FUN_004203c0
 * Ghidra name: FUN_004203c0
 * Tracked span: 48 bytes
 */


void FUN_004203c0(void)

{
  undefined4 *unaff_ESI;
  
  *unaff_ESI = &PTR_LAB_0046f810;
  if (unaff_ESI[1] != 0) {
    timeKillEvent(unaff_ESI[1]);
  }
  timeEndPeriod(unaff_ESI[2]);
  unaff_ESI[1] = 0;
  timeEndPeriod(unaff_ESI[2]);
  return;
}

