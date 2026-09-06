/* Raw Ghidra reference; not compilable reconstruction. Address: 004066E0 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 __fastcall FUN_004066e0(int param_1)

{
  int iVar1;
  int in_EAX;
  float10 fVar2;
  
  for (iVar1 = *(int *)(in_EAX + 0x14 + param_1 * 4); iVar1 != 0; iVar1 = *(int *)(iVar1 + 0x44c)) {
    *(float *)(iVar1 + 0x33c) = *(float *)(iVar1 + 0x3b4) + _DAT_00470b4c;
    *(float *)(iVar1 + 0x340) = *(float *)(iVar1 + 0x3b8) + _DAT_00470b48;
    *(undefined4 *)(iVar1 + 0x344) = *(undefined4 *)(iVar1 + 0x3bc);
    if ((*(uint *)(iVar1 + 0x364) & 0x8000000) != 0) {
      fVar2 = (float10)FUN_0044bc10(*(float *)(iVar1 + 0x3e4),1.5707964);
      *(float *)(iVar1 + 0x34) = (float)fVar2;
      *(uint *)(iVar1 + 0x364) = *(uint *)(iVar1 + 0x364) | 4;
    }
    FUN_004451c0(g_pGameStateManager);
  }
  return 1;
}

