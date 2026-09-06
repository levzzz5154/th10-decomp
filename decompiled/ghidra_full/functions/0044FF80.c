/* Raw Ghidra reference; not compilable reconstruction. Address: 0044FF80 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

float10 __thiscall ResolveEclFloatValue(byte param_1,float param_2)

{
  int iVar1;
  int in_EAX;
  float10 fVar2;
  ulonglong uVar3;
  
  if ((1 << (param_1 & 0x1f) & (uint)*(ushort *)(*(int *)(in_EAX + 4) + 8)) != 0) {
    if (_DAT_00470b04 <= param_2) {
      uVar3 = FUN_00463b2c();
      return (float10)*(float *)((int)uVar3 + *(int *)(in_EAX + 0x100c) + 8 + in_EAX);
    }
    if (param_2 != _DAT_00470b60) {
      iVar1 = **(int **)(in_EAX + 0x1014);
      uVar3 = FUN_00463b2c();
      fVar2 = (float10)(**(code **)(iVar1 + 0xc))((int)uVar3);
      return fVar2;
    }
    iVar1 = *(int *)(in_EAX + 0x1008);
    if (-1 < iVar1 + -4) {
      *(int *)(in_EAX + 0x1008) = iVar1 + -4;
      param_2 = *(float *)(iVar1 + 4 + in_EAX);
      *(int *)(in_EAX + 0x1008) = iVar1 + -8;
      if ((*(char *)(iVar1 + in_EAX) != 'f') && (*(char *)(iVar1 + in_EAX) == 'i')) {
        param_2 = (float)(int)param_2;
      }
    }
  }
  return (float10)param_2;
}

