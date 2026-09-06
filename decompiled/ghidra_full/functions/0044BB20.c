/* Raw Ghidra reference; not compilable reconstruction. Address: 0044BB20 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

float10 __fastcall NextRandomFloat(ushort *param_1)

{
  ushort uVar1;
  ushort uVar2;
  uint uVar3;
  int iVar4;
  float10 fVar5;
  
  uVar3 = (*param_1 ^ 0x9630) - 0x6553;
  iVar4 = (uVar3 >> 0xe & 3) + uVar3 * 4;
  uVar1 = (ushort)iVar4;
  uVar2 = (uVar1 ^ 0x9630) + 0x9aad;
  *param_1 = uVar1;
  uVar2 = uVar2 * 4 + (uVar2 >> 0xe);
  *param_1 = uVar2;
  *(int *)(param_1 + 2) = *(int *)(param_1 + 2) + 2;
  uVar3 = iVar4 * 0x10000 | (uint)uVar2;
  fVar5 = (float10)(int)uVar3;
  if ((int)uVar3 < 0) {
    fVar5 = fVar5 + (float10)_DAT_00470b98;
  }
  return fVar5 * (float10)_DAT_00470bf0;
}

