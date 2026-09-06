/* Raw Ghidra reference; not compilable reconstruction. Address: 0041EA40 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 __fastcall FUN_0041ea40(int param_1)

{
  void *pvVar1;
  float10 fVar2;
  
  *(float *)(param_1 + 0x950) = *(float *)(param_1 + 0x24) + _DAT_00470b4c;
  *(float *)(param_1 + 0x954) = *(float *)(param_1 + 0x28) + _DAT_00470b48;
  *(undefined4 *)(param_1 + 0x958) = *(undefined4 *)(param_1 + 0x2c);
  fVar2 = (float10)FUN_0044bc10(*(float *)(param_1 + 0x3c),1.5707964);
  *(float *)(param_1 + 0x648) = (float)fVar2;
  pvVar1 = g_pGameStateManager;
  *(uint *)(param_1 + 0x978) = *(uint *)(param_1 + 0x978) | 4;
  FUN_004451c0(pvVar1);
  pvVar1 = g_pGameStateManager;
  if (*(float *)(param_1 + 0x4c) == _DAT_00470b04) {
    *(float *)(param_1 + 0xcfc) = *(float *)(param_1 + 0x24) + _DAT_00470b4c;
    *(float *)(param_1 + 0xd00) = *(float *)(param_1 + 0x28) + _DAT_00470b48;
    *(undefined4 *)(param_1 + 0xd04) = *(undefined4 *)(param_1 + 0x2c);
    FUN_004451c0(pvVar1);
  }
  return 0;
}

