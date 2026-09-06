/* Raw Ghidra reference; not compilable reconstruction. Address: 00408660 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

float10 FUN_00408660(float param_1,float param_2)

{
  float10 fVar1;
  
  fVar1 = (float10)param_1 - (float10)param_2;
  if ((float10)_DAT_00470b18 < fVar1) {
    return (float10)param_1 - ((float10)param_2 + (float10)_DAT_00470b14);
  }
  if (_DAT_00470b18 < param_2 - param_1) {
    fVar1 = (float10)param_1 - ((float10)param_2 - (float10)_DAT_00470b14);
  }
  return fVar1;
}

