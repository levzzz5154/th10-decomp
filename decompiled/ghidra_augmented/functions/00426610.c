/* Raw Ghidra reference; not compilable reconstruction. Address: 00426610 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

float10 __fastcall FUN_00426610(int param_1)

{
  float *in_EAX;
  float10 fVar1;
  float10 fVar2;
  
  fVar1 = (float10)*in_EAX - (float10)*(float *)(param_1 + 0x3c0);
  fVar2 = (float10)in_EAX[1] - (float10)*(float *)(param_1 + 0x3c4);
  if ((fVar2 == (float10)_DAT_00470b04) && (fVar1 == (float10)_DAT_00470b04)) {
    return (float10)_DAT_00470b94;
  }
  fVar1 = (float10)fpatan(fVar2,fVar1);
  return fVar1;
}

