/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x004501B0
 * Tracking name: FUN_004501b0
 * Ghidra name: FUN_004501b0
 * Tracked span: 112 bytes
 */


void __thiscall FUN_004501b0(void *this,float param_1,float param_2)

{
  float10 fVar1;
  float10 fVar2;
  
  fVar1 = (float10)fcos((float10)param_1);
  fVar2 = (float10)fsin((float10)param_1);
  *(float *)this = (float)(fVar1 * (float10)param_2);
  *(float *)((int)this + 4) = (float)(fVar2 * (float10)param_2);
  return;
}

