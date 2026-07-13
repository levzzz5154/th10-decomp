/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x0044C5D0
 * Tracking name: FUN_0044c5d0
 * Ghidra name: FUN_0044c5d0
 * Tracked span: 528 bytes
 */


void __thiscall FUN_0044c5d0(void *this,float param_1,float param_2)

{
  float10 fVar1;
  float10 fVar2;
  
  fVar1 = (float10)fcos((float10)param_1);
  fVar2 = (float10)fsin((float10)param_1);
  *(float *)this = (float)(fVar1 * (float10)param_2);
  *(float *)((int)this + 4) = (float)(fVar2 * (float10)param_2);
  return;
}

