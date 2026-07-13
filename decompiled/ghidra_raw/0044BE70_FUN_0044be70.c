/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x0044BE70
 * Tracking name: FUN_0044be70
 * Ghidra name: FUN_0044be70
 * Tracked span: 48 bytes
 */


void FUN_0044be70(void)

{
  int *piVar1;
  undefined4 *in_EAX;
  
  piVar1 = in_EAX + 0x23;
  *piVar1 = *piVar1 + -1;
  if (*piVar1 < 0) {
    in_EAX[0x23] = 0;
  }
  *in_EAX = in_EAX[in_EAX[0x23] + 3];
  in_EAX[2] = in_EAX[in_EAX[0x23] + 0x13];
  in_EAX[0x35] = 0;
  return;
}

