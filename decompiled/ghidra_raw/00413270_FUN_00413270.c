/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x00413270
 * Tracking name: FUN_00413270
 * Ghidra name: FUN_00413270
 * Tracked span: 224 bytes
 */


void __thiscall FUN_00413270(void *this,float param_1,float param_2,float param_3)

{
  float10 fVar1;
  float10 fVar2;
  
  fVar1 = (float10)fcos((float10)param_1);
  fVar2 = (float10)fsin((float10)param_1);
  *(float *)this = (float)(fVar1 * (float10)param_2);
  *(float *)((int)this + 4) = (float)(fVar2 * (float10)param_3);
  return;
}

