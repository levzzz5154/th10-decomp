/* Raw Ghidra reference; not compilable reconstruction. Address: 00404D40 */

void __fastcall FUN_00404d40(float *param_1)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  float fVar10;
  float *in_EAX;
  float *unaff_ESI;
  ulonglong uVar11;
  
  fVar1 = param_1[5];
  fVar2 = in_EAX[5];
  fVar3 = param_1[4];
  fVar4 = in_EAX[4];
  fVar5 = param_1[3];
  fVar6 = in_EAX[3];
  fVar7 = param_1[2];
  fVar8 = in_EAX[2];
  fVar9 = param_1[1];
  fVar10 = in_EAX[1];
  *unaff_ESI = *param_1 - *in_EAX;
  unaff_ESI[1] = fVar9 - fVar10;
  unaff_ESI[2] = fVar7 - fVar8;
  unaff_ESI[3] = fVar5 - fVar6;
  unaff_ESI[4] = fVar3 - fVar4;
  unaff_ESI[5] = fVar1 - fVar2;
  uVar11 = FUN_00463b2c();
  *(char *)(unaff_ESI + 6) = (char)uVar11;
  uVar11 = FUN_00463b2c();
  *(char *)((int)unaff_ESI + 0x19) = (char)uVar11;
  uVar11 = FUN_00463b2c();
  *(char *)((int)unaff_ESI + 0x1a) = (char)uVar11;
  uVar11 = FUN_00463b2c();
  *(char *)((int)unaff_ESI + 0x1b) = (char)uVar11;
  return;
}

