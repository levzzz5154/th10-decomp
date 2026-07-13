/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x0043E5A0
 * Tracking name: FUN_0043e5a0
 * Ghidra name: FUN_0043e5a0
 * Tracked span: 368 bytes
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 __fastcall FUN_0043e5a0(int param_1,int param_2)

{
  float fVar1;
  float fVar2;
  int in_EAX;
  int iVar3;
  float *pfVar4;
  float *pfVar5;
  
  if ((*(int *)(param_1 + 0x108) != 0) && (*(int *)(param_1 + 0x124) == 0)) {
    *(short *)(in_EAX + 900) = (short)param_2;
    *(int *)(in_EAX + 0x308) = param_1;
    iVar3 = param_2 * 0x44 + *(int *)(param_1 + 0x118);
    *(int *)(in_EAX + 0x394) = iVar3;
    *(undefined4 *)(in_EAX + 0x4c) = *(undefined4 *)(iVar3 + 0x34);
    *(undefined4 *)(in_EAX + 0x50) = *(undefined4 *)(*(int *)(in_EAX + 0x394) + 0x30);
    *(undefined4 *)(in_EAX + 0x274) = 0;
    *(undefined4 *)(in_EAX + 0x270) = 0;
    *(undefined4 *)(in_EAX + 0x26c) = 0;
    *(undefined4 *)(in_EAX + 0x268) = 0;
    *(undefined4 *)(in_EAX + 0x260) = 0;
    *(undefined4 *)(in_EAX + 0x25c) = 0;
    *(undefined4 *)(in_EAX + 600) = 0;
    *(undefined4 *)(in_EAX + 0x254) = 0;
    *(undefined4 *)(in_EAX + 0x24c) = 0;
    *(undefined4 *)(in_EAX + 0x248) = 0;
    *(undefined4 *)(in_EAX + 0x244) = 0;
    *(undefined4 *)(in_EAX + 0x240) = 0;
    pfVar4 = (float *)(in_EAX + 0x23c);
    *(undefined4 *)(in_EAX + 0x278) = 0x3f800000;
    *(undefined4 *)(in_EAX + 0x264) = 0x3f800000;
    *(undefined4 *)(in_EAX + 0x250) = 0x3f800000;
    *pfVar4 = 1.0;
    *(undefined4 *)(in_EAX + 0x2f4) = 0;
    *(undefined4 *)(in_EAX + 0x2f0) = 0;
    *(undefined4 *)(in_EAX + 0x2ec) = 0;
    *(undefined4 *)(in_EAX + 0x2e8) = 0;
    *(undefined4 *)(in_EAX + 0x2e0) = 0;
    *(undefined4 *)(in_EAX + 0x2dc) = 0;
    *(undefined4 *)(in_EAX + 0x2d8) = 0;
    *(undefined4 *)(in_EAX + 0x2d4) = 0;
    *(undefined4 *)(in_EAX + 0x2cc) = 0;
    *(undefined4 *)(in_EAX + 0x2c8) = 0;
    *(undefined4 *)(in_EAX + 0x2c4) = 0;
    *(undefined4 *)(in_EAX + 0x2c0) = 0;
    *(undefined4 *)(in_EAX + 0x2f8) = 0x3f800000;
    *(undefined4 *)(in_EAX + 0x2e4) = 0x3f800000;
    *(undefined4 *)(in_EAX + 0x2d0) = 0x3f800000;
    *(undefined4 *)(in_EAX + 700) = 0x3f800000;
    iVar3 = *(int *)(in_EAX + 0x394);
    *pfVar4 = *(float *)(in_EAX + 0x4c) * _DAT_00470b7c;
    *(float *)(in_EAX + 0x250) = *(float *)(in_EAX + 0x50) * _DAT_00470b7c;
    *(float *)(in_EAX + 700) =
         (*(float *)(iVar3 + 0x38) / *(float *)(iVar3 + 0x1c)) * *(float *)(in_EAX + 0x4c);
    fVar1 = *(float *)(iVar3 + 0x3c);
    fVar2 = *(float *)(iVar3 + 0x18);
    pfVar5 = (float *)(in_EAX + 0x27c);
    for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
      *pfVar5 = *pfVar4;
      pfVar4 = pfVar4 + 1;
      pfVar5 = pfVar5 + 1;
    }
    *(float *)(in_EAX + 0x2d0) = (fVar1 / fVar2) * *(float *)(in_EAX + 0x50);
    return 0;
  }
  return 0xffffffff;
}

