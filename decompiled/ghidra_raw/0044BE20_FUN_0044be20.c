/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x0044BE20
 * Tracking name: FUN_0044be20
 * Ghidra name: FUN_0044be20
 * Tracked span: 80 bytes
 */


void FUN_0044be20(void)

{
  int iVar1;
  undefined4 *in_EAX;
  
  in_EAX[in_EAX[0x23] + 3] = *in_EAX;
  in_EAX[in_EAX[0x23] + 0x13] = in_EAX[2];
  iVar1 = in_EAX[0x23];
  in_EAX[0x23] = iVar1 + 1;
  in_EAX[0x35] = 0;
  if (0xf < iVar1 + 1) {
    in_EAX[0x23] = 0xf;
  }
  return;
}

