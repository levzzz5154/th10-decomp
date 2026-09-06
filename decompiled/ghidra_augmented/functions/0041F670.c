/* Raw Ghidra reference; not compilable reconstruction. Address: 0041F670 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 __thiscall FUN_0041f670(void *this,float *param_1,float param_2)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float10 fVar4;
  float10 fVar5;
  
  fVar2 = *param_1 - *(float *)((int)this + 0x24);
  fVar3 = param_1[1] - *(float *)((int)this + 0x28);
  fVar4 = (float10)fsin(-(float10)*(float *)((int)this + 0x3c));
  fVar5 = (float10)fcos(-(float10)*(float *)((int)this + 0x3c));
  fVar1 = (float)((float10)fVar2 * fVar5 - fVar4 * (float10)fVar3);
  fVar4 = fVar4 * (float10)fVar2 + fVar5 * (float10)fVar3;
  if ((((fVar1 - param_2 <= *(float *)((int)this + 0x40)) &&
       ((float)(fVar4 - (float10)param_2) <= *(float *)((int)this + 0x44) * _DAT_00470b0c)) &&
      (_DAT_00470b04 <= fVar1 + param_2)) &&
     (*(float *)((int)this + 0x44) * _DAT_00470b78 <= (float)(fVar4 + (float10)param_2))) {
    return 2;
  }
  return 0;
}

