/* Raw Ghidra reference; not compilable reconstruction. Address: 0044FE40 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

float10 __fastcall ResolveEclFloatOperand(float param_1)

{
  int iVar1;
  int in_EAX;
  float10 fVar2;
  ulonglong uVar3;
  undefined4 local_4;
  
  iVar1 = *(int *)(in_EAX + 4);
  if ((1 << (SUB41(param_1,0) & 0x1f) & (uint)*(ushort *)(iVar1 + 8)) == 0) {
    return (float10)*(float *)(iVar1 + 0x10 + (int)param_1 * 4);
  }
  if (_DAT_00470b04 <= *(float *)(iVar1 + 0x10 + (int)param_1 * 4)) {
    uVar3 = FUN_00463b2c();
    return (float10)*(float *)((int)uVar3 + *(int *)(in_EAX + 0x100c) + 8 + in_EAX);
  }
  if (*(float *)(iVar1 + 0x10 + (int)param_1 * 4) != _DAT_00470b60) {
    iVar1 = **(int **)(in_EAX + 0x1014);
    uVar3 = FUN_00463b2c();
    fVar2 = (float10)(**(code **)(iVar1 + 0xc))((int)uVar3);
    return fVar2;
  }
  iVar1 = *(int *)(in_EAX + 0x1008);
  local_4 = param_1;
  if (-1 < iVar1 + -4) {
    *(int *)(in_EAX + 0x1008) = iVar1 + -4;
    local_4 = *(float *)(iVar1 + 4 + in_EAX);
    *(int *)(in_EAX + 0x1008) = iVar1 + -8;
    if ((*(char *)(iVar1 + in_EAX) != 'f') && (*(char *)(iVar1 + in_EAX) == 'i')) {
      return (float10)(int)local_4;
    }
  }
  return (float10)local_4;
}

