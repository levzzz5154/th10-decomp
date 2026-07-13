/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x00421B90
 * Tracking name: FUN_00421b90
 * Ghidra name: FUN_00421b90
 * Tracked span: 192 bytes
 */


void __fastcall FUN_00421b90(float *param_1,float *param_2)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  float *in_EAX;
  
  fVar1 = param_2[2];
  fVar2 = *param_1;
  fVar3 = param_1[2];
  fVar4 = *param_2;
  fVar5 = *param_2;
  fVar6 = param_1[1];
  fVar7 = *param_1;
  fVar8 = param_2[1];
  *in_EAX = param_1[2] * param_2[1] - param_2[2] * param_1[1];
  in_EAX[1] = fVar1 * fVar2 - fVar3 * fVar4;
  in_EAX[2] = fVar5 * fVar6 - fVar7 * fVar8;
  return;
}

