/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x0040AC90
 * Tracking name: FUN_0040ac90
 * Ghidra name: FUN_0040ac90
 * Tracked span: 80 bytes
 */


void FUN_0040ac90(undefined4 param_1)

{
  int in_EAX;
  
  if ((*(uint *)(in_EAX + 0x3cc) & 0x1000) == 0) {
    *(undefined4 *)(in_EAX + 0x390) = param_1;
    return;
  }
  *(undefined4 *)(in_EAX + 0x390) = 2;
  return;
}

