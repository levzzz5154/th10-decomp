/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x00404DA0
 * Tracking name: FUN_00404da0
 * Ghidra name: FUN_00404da0
 * Tracked span: 112 bytes
 */


void FUN_00404da0(float param_1)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float *in_EAX;
  float *unaff_ESI;
  ulonglong uVar6;
  
  fVar1 = in_EAX[5];
  fVar2 = in_EAX[4];
  fVar3 = in_EAX[3];
  fVar4 = in_EAX[2];
  fVar5 = in_EAX[1];
  *unaff_ESI = param_1 * *in_EAX;
  unaff_ESI[1] = param_1 * fVar5;
  unaff_ESI[2] = param_1 * fVar4;
  unaff_ESI[3] = param_1 * fVar3;
  unaff_ESI[4] = param_1 * fVar2;
  unaff_ESI[5] = param_1 * fVar1;
  uVar6 = FUN_00463b2c();
  *(char *)(unaff_ESI + 6) = (char)uVar6;
  uVar6 = FUN_00463b2c();
  *(char *)((int)unaff_ESI + 0x19) = (char)uVar6;
  uVar6 = FUN_00463b2c();
  *(char *)((int)unaff_ESI + 0x1a) = (char)uVar6;
  uVar6 = FUN_00463b2c();
  *(char *)((int)unaff_ESI + 0x1b) = (char)uVar6;
  return;
}

