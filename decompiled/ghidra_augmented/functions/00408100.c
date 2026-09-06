/* Raw Ghidra reference; not compilable reconstruction. Address: 00408100 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_00408100(float param_1,int param_2,int param_3)

{
  float fVar1;
  float fVar2;
  float fVar3;
  int in_EAX;
  int iVar4;
  void *this;
  float *unaff_EBX;
  int iVar5;
  int iVar6;
  
  iVar6 = in_EAX + 0x60;
  iVar5 = 2000;
  do {
    if (((*(short *)(iVar6 + 0x446) != 0) && (*(short *)(iVar6 + 0x446) != 3)) &&
       ((param_3 == 0 || (*(int *)(iVar6 + 4) == 0)))) {
      fVar1 = *(float *)(iVar6 + 0x3b4) - *unaff_EBX;
      fVar2 = *(float *)(iVar6 + 0x3b8) - unaff_EBX[1];
      fVar3 = *(float *)(iVar6 + 0x3f0) * _DAT_00470b0c + param_1;
      if (fVar1 * fVar1 + fVar2 * fVar2 <= fVar3 * fVar3) {
        FUN_00408030();
        iVar4 = FUN_004086b0((void *)(iVar6 + 0x3b4),2.0,2.0);
        if ((iVar4 == 0) && (param_2 != 0)) {
          FUN_0041bb00(this,8,0xffffffff,-1.5707964,0.6);
        }
      }
    }
    iVar6 = iVar6 + 0x7f0;
    iVar5 = iVar5 + -1;
  } while (iVar5 != 0);
  return 0;
}

