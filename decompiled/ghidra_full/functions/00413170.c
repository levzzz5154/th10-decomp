/* Raw Ghidra reference; not compilable reconstruction. Address: 00413170 */

void SetNormalizedScoreAngle(int param_1,float param_2)

{
  float10 fVar1;
  
  fVar1 = (float10)NormalizeAngle(param_2);
  *(float *)(param_1 + 0x1c) = (float)fVar1;
  return;
}

