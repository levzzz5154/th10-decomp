/* Raw Ghidra reference; not compilable reconstruction. Address: 0041D7C0 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 __fastcall FUN_0041d7c0(int param_1)

{
  void *pvVar1;
  float10 fVar2;
  
  *(float *)(param_1 + 0x934) = *(float *)(param_1 + 0x24) + _DAT_00470b4c;
  *(float *)(param_1 + 0x938) = *(float *)(param_1 + 0x28) + _DAT_00470b48;
  *(undefined4 *)(param_1 + 0x93c) = *(undefined4 *)(param_1 + 0x2c);
  fVar2 = (float10)FUN_0044bc10(*(float *)(param_1 + 0x3c),1.5707964);
  *(float *)(param_1 + 0x62c) = (float)fVar2;
  pvVar1 = g_pGameStateManager;
  *(uint *)(param_1 + 0x95c) = *(uint *)(param_1 + 0x95c) | 4;
  FUN_004451c0(pvVar1);
  pvVar1 = g_pGameStateManager;
  if (*(float *)(param_1 + 0x4c) == _DAT_00470b04) {
    *(float *)(param_1 + 0xce0) = *(float *)(param_1 + 0x24) + _DAT_00470b4c;
    *(float *)(param_1 + 0xce4) = *(float *)(param_1 + 0x28) + _DAT_00470b48;
    *(undefined4 *)(param_1 + 0xce8) = *(undefined4 *)(param_1 + 0x2c);
    FUN_004451c0(pvVar1);
  }
  return 0;
}

