/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x00413170
 * Tracking name: FUN_00413170
 * Ghidra name: FUN_00413170
 * Tracked span: 144 bytes
 */


void FUN_00413170(int param_1,float param_2)

{
  float10 fVar1;
  
  fVar1 = (float10)FUN_0044bc70(param_2);
  *(float *)(param_1 + 0x1c) = (float)fVar1;
  return;
}

