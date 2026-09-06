/* Raw Ghidra reference; not compilable reconstruction. Address: 00428B10 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 __fastcall FUN_00428b10(undefined4 param_1,int param_2)

{
  int iVar1;
  float fVar2;
  float10 fVar3;
  float10 extraout_ST1;
  
  if (*(int *)(param_2 + 0x40) != 2) {
    iVar1 = *(int *)(param_2 + 0x4c);
    if (iVar1 != 0) {
      if (((*(uint *)(iVar1 + 0x2480) & 0x11) == 0) && ((*(uint *)(iVar1 + 0x2480) & 0xc0000) == 0))
      {
        fVar3 = (float10)fpatan((float10)*(float *)(iVar1 + 0x106c) -
                                (float10)*(float *)(param_2 + 0x18),
                                (float10)*(float *)(iVar1 + 0x1068) -
                                (float10)*(float *)(param_2 + 0x14));
        fVar3 = FUN_00428ce0((float)fVar3,*(float *)(param_2 + 0x30));
        if (*(int *)(param_2 + 4) < 0x78) {
          fVar3 = (float10)NormalizeAngle((float)fVar3 * _DAT_00470c38 + *(float *)(param_2 + 0x30))
          ;
          *(float *)(param_2 + 0x30) = (float)fVar3;
          *(float *)(param_2 + 0x2c) = (float)extraout_ST1;
          return 0;
        }
        *(float *)(param_2 + 0x2c) = *(float *)(param_2 + 0x2c) + _DAT_00470c38;
        return 0;
      }
      *(undefined4 *)(param_2 + 0x4c) = 0;
    }
    fVar2 = *(float *)(param_2 + 0x2c) + _DAT_00470c18;
    if (_DAT_00470b48 < fVar2) {
      fVar2 = _DAT_00470b48;
    }
    *(float *)(param_2 + 0x2c) = fVar2;
  }
  return 0;
}

