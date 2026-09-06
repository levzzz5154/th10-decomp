/* Raw Ghidra reference; not compilable reconstruction. Address: 004073E0 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 __fastcall FUN_004073e0(int param_1,int param_2,uint param_3)

{
  int in_EAX;
  uint uVar1;
  int iVar2;
  float10 fVar3;
  float10 fVar4;
  ulonglong uVar5;
  undefined4 local_4;
  
  fVar3 = (float10)*(float *)(DAT_00477834 + 0x3c0) - (float10)*(float *)(in_EAX + 4);
  fVar4 = (float10)*(float *)(DAT_00477834 + 0x3c4) - (float10)*(float *)(in_EAX + 8);
  if ((fVar4 == (float10)_DAT_00470b04) && (fVar3 == (float10)_DAT_00470b04)) {
    local_4 = 1.5707964;
  }
  else {
    fVar3 = (float10)fpatan(fVar4,fVar3);
    local_4 = (float)fVar3;
  }
  iVar2 = 0;
  if (0 < *(short *)(in_EAX + 0x1f6)) {
    do {
      uVar1 = 0;
      if (0 < *(short *)(in_EAX + 500)) {
        do {
          uVar5 = FUN_004067d0(param_1,param_2,param_3,uVar1,iVar2,local_4);
          param_2 = (int)(uVar5 >> 0x20);
          if ((int)uVar5 != 0) goto LAB_0040747a;
          param_1 = (int)*(short *)(in_EAX + 500);
          uVar1 = uVar1 + 1;
        } while ((int)uVar1 < param_1);
      }
      param_2 = (int)*(short *)(in_EAX + 0x1f6);
      iVar2 = iVar2 + 1;
    } while (iVar2 < param_2);
  }
LAB_0040747a:
  if ((*(uint *)(in_EAX + 0x1fc) & 0x200) != 0) {
    FUN_0043dd10();
  }
  return 0;
}

