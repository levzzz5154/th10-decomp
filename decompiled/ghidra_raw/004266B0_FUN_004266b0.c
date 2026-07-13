/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x004266B0
 * Tracking name: FUN_004266b0
 * Ghidra name: FUN_004266b0
 * Tracked span: 320 bytes
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 __fastcall FUN_004266b0(float *param_1,int param_2)

{
  int iVar1;
  float *in_EAX;
  
  if ((((*in_EAX * _DAT_00470b0c + *param_1 < *(float *)(param_2 + 0x404)) ||
       (in_EAX[1] * _DAT_00470b0c + param_1[1] < *(float *)(param_2 + 0x408))) ||
      (*(float *)(param_2 + 0x410) < *param_1 - *in_EAX * _DAT_00470b0c)) ||
     (*(float *)(param_2 + 0x414) < param_1[1] - in_EAX[1] * _DAT_00470b0c)) {
    if ((((*(float *)(param_2 + 0x404) <= *param_1 + _DAT_00470be8) &&
         (*(float *)(param_2 + 0x408) <= param_1[1] + _DAT_00470be8)) &&
        (*param_1 - _DAT_00470be8 <= *(float *)(param_2 + 0x410))) &&
       (param_1[1] - _DAT_00470be8 <= *(float *)(param_2 + 0x414))) {
      return 2;
    }
  }
  else if (((DAT_0047770c == 0) || (*(int *)(DAT_0047770c + 0x9eb8) == 0)) &&
          ((iVar1 = *(int *)(param_2 + 0x458), iVar1 != 2 && ((iVar1 != 4 && (iVar1 != 3)))))) {
    if (*(int *)(param_2 + 0x4310) < 1) {
      FUN_00426cf0(param_2);
    }
    return 1;
  }
  return 0;
}

