/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x00444B10
 * Tracking name: FUN_00444b10
 * Ghidra name: FUN_00444b10
 * Tracked span: 208 bytes
 */


undefined4 __fastcall FUN_00444b10(int param_1)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  int in_EAX;
  float *pfVar6;
  int iVar7;
  int unaff_EBX;
  
  if (2 < in_EAX) {
    iVar7 = *(int *)(param_1 + 0x394);
    fVar3 = *(float *)(param_1 + 0x54) + *(float *)(iVar7 + 0x28);
    fVar1 = *(float *)(iVar7 + 0x24);
    fVar2 = *(float *)(param_1 + 0x58);
    fVar5 = (*(float *)(iVar7 + 0x28) - *(float *)(iVar7 + 0x20)) / (float)((in_EAX + 1) / 2 + -1);
    if (0 < in_EAX) {
      pfVar6 = (float *)(unaff_EBX + 0x18);
      iVar7 = (in_EAX - 1U >> 1) + 1;
      fVar4 = fVar3;
      do {
        pfVar6[-1] = fVar4;
        fVar4 = fVar4 - fVar5;
        *pfVar6 = fVar1 + fVar2;
        pfVar6[-2] = *(float *)(param_1 + 0x2fc);
        pfVar6[-3] = 1.0;
        pfVar6 = pfVar6 + 0xe;
        iVar7 = iVar7 + -1;
      } while (iVar7 != 0);
    }
    fVar1 = *(float *)(*(int *)(param_1 + 0x394) + 0x2c);
    fVar2 = *(float *)(param_1 + 0x58);
    if (1 < in_EAX) {
      pfVar6 = (float *)(unaff_EBX + 0x34);
      iVar7 = (in_EAX - 2U >> 1) + 1;
      do {
        pfVar6[-1] = fVar3;
        fVar3 = fVar3 - fVar5;
        *pfVar6 = fVar1 + fVar2;
        pfVar6[-2] = *(float *)(param_1 + 0x2fc);
        pfVar6[-3] = 1.0;
        pfVar6 = pfVar6 + 0xe;
        iVar7 = iVar7 + -1;
      } while (iVar7 != 0);
    }
    return 0;
  }
  return 0xffffffff;
}

