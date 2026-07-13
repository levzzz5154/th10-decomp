/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x004267F0
 * Tracking name: FUN_004267f0
 * Ghidra name: FUN_004267f0
 * Tracked span: 480 bytes
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 __thiscall FUN_004267f0(void *this,float param_1,float param_2,float param_3)

{
  float fVar1;
  float fVar2;
  int iVar3;
  float fVar4;
  float *in_EAX;
  float10 fVar5;
  float10 fVar6;
  
  fVar2 = *(float *)((int)this + 0x3c0) - *in_EAX;
  fVar4 = *(float *)((int)this + 0x3c4) - in_EAX[1];
  fVar5 = (float10)fsin(-(float10)param_1);
  fVar6 = (float10)fcos(-(float10)param_1);
  fVar1 = (float)((float10)fVar2 * fVar6 - fVar5 * (float10)fVar4);
  fVar5 = fVar5 * (float10)fVar2 + fVar6 * (float10)fVar4;
  fVar4 = fVar1 - *(float *)((int)this + 0x41c);
  fVar2 = (float)(fVar5 - (float10)*(float *)((int)this + 0x420));
  fVar1 = fVar1 + *(float *)((int)this + 0x41c);
  if (fVar4 <= param_3) {
    if (((param_2 * _DAT_00470b0c < fVar2) || (fVar1 < _DAT_00470b04)) ||
       ((float)(fVar5 + (float10)*(float *)((int)this + 0x420)) < param_2 * _DAT_00470b78)) {
      if (((fVar4 <= param_3) && (_DAT_00470b04 <= fVar1)) &&
         ((fVar2 <= param_2 * _DAT_00470ca8 && (param_2 * _DAT_00470ca4 <= fVar2)))) {
        return 2;
      }
    }
    else if (((DAT_0047770c == 0) || (*(int *)(DAT_0047770c + 0x9eb8) == 0)) &&
            ((iVar3 = *(int *)((int)this + 0x458), iVar3 != 2 &&
             (((iVar3 != 4 && (iVar3 != 3)) && (*(int *)((int)this + 0x4310) < 1)))))) {
      FUN_00426cf0((int)this);
      return 1;
    }
  }
  return 0;
}

