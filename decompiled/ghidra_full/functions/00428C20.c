/* Raw Ghidra reference; not compilable reconstruction. Address: 00428C20 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 __fastcall FUN_00428c20(int param_1,int param_2)

{
  float *pfVar1;
  float fVar2;
  int iVar3;
  
  iVar3 = *(char *)(*(int *)(param_2 + 0x58) + 0x1c) * 0x98;
  fVar2 = (float)*(int *)(iVar3 + 0x3248 + param_1) * _DAT_00470b00;
  pfVar1 = (float *)(param_2 + 0x14);
  *pfVar1 = (float)*(int *)(iVar3 + 0x3244 + param_1) * _DAT_00470b00;
  *(float *)(param_2 + 0x18) = fVar2;
  *(undefined4 *)(param_2 + 0x1c) = 0;
  *pfVar1 = (*(float *)(*(int *)(param_2 + 0x58) + 4) - *(float *)(param_2 + 0x20)) + *pfVar1;
  *(float *)(param_2 + 0x18) =
       (*(float *)(*(int *)(param_2 + 0x58) + 8) - *(float *)(param_2 + 0x24)) +
       *(float *)(param_2 + 0x18);
  return 0;
}

