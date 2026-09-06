/* Raw Ghidra reference; not compilable reconstruction. Address: 0043DB60 */

undefined4 FUN_0043db60(void)

{
  int iVar1;
  int *unaff_EBX;
  uint uVar2;
  int *piVar3;
  ulonglong uVar4;
  
  unaff_EBX[0x188] = -1;
  unaff_EBX[0x189] = -1;
  unaff_EBX[0x18a] = -1;
  unaff_EBX[0x18b] = -1;
  unaff_EBX[0x18c] = -1;
  unaff_EBX[0x18d] = -1;
  unaff_EBX[0x18e] = -1;
  unaff_EBX[399] = -1;
  unaff_EBX[400] = -1;
  unaff_EBX[0x191] = -1;
  unaff_EBX[0x192] = -1;
  unaff_EBX[0x193] = -1;
  FUN_0043cc40();
  if (unaff_EBX[0x184] == 0) {
    return 0xffffffff;
  }
  if (*unaff_EBX != 0) {
    piVar3 = unaff_EBX + 0x82;
    uVar2 = 0;
    do {
      (**(code **)(*(int *)*unaff_EBX + 0x14))
                ((int *)*unaff_EBX,unaff_EBX[*(int *)((int)&DAT_004749c8 + uVar2) + 2],piVar3);
      (**(code **)(*(int *)*piVar3 + 0x34))((int *)*piVar3,0);
      (**(code **)(*(int *)*piVar3 + 0x3c))
                ((int *)*piVar3,(int)*(short *)((int)&DAT_004749cc + uVar2));
      uVar2 = uVar2 + 8;
      piVar3 = piVar3 + 1;
    } while (uVar2 < 0x178);
    unaff_EBX[0x14b1] = (int)DAT_00491d68;
    iVar1 = (int)DAT_00491d69;
    unaff_EBX[0x14b2] = iVar1;
    if (iVar1 != 0) {
      uVar4 = FUN_00463b2c();
      unaff_EBX[0x14b3] = -5000 - (int)uVar4;
      return 0;
    }
    unaff_EBX[0x14b3] = -10000;
  }
  return 0;
}

