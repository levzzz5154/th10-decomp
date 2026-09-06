/* Raw Ghidra reference; not compilable reconstruction. Address: 00443FB0 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_00443fb0(void)

{
  float fVar1;
  float fVar2;
  float fVar3;
  byte bVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  undefined4 uVar9;
  void *unaff_ESI;
  int unaff_EDI;
  ulonglong uVar10;
  undefined4 local_20;
  
  iVar5 = FUN_00443b60();
  if (iVar5 != 0) {
    return 0xffffffff;
  }
  if ((char)((uint)*(undefined4 *)(unaff_EDI + 0x35c) >> 8) < '\0') {
    local_20 = *(uint *)(unaff_EDI + 0x300);
  }
  else {
    local_20 = *(uint *)(unaff_EDI + 0x2fc);
  }
  fVar3 = (*(float *)(unaff_EDI + 0x340) + *(float *)(unaff_EDI + 0x334) +
          *(float *)(unaff_EDI + 0x34c)) - DAT_00491d7c;
  fVar1 = (*(float *)(unaff_EDI + 0x344) + *(float *)(unaff_EDI + 0x338) +
          *(float *)(unaff_EDI + 0x350)) - DAT_00491d80;
  fVar2 = (*(float *)(unaff_EDI + 0x348) + *(float *)(unaff_EDI + 0x33c) +
          *(float *)(unaff_EDI + 0x354)) - _DAT_00491d84;
  fVar1 = SQRT(fVar3 * fVar3 + fVar1 * fVar1 + fVar2 * fVar2);
  uVar6 = local_20;
  if (*(int *)((int)unaff_ESI + 0x73245c) != 0) {
    uVar6 = (uint)*(byte *)((int)unaff_ESI + 0x73245a) * (local_20 >> 0x10 & 0xff) >> 7;
    if (0xff < uVar6) {
      uVar6 = 0xff;
    }
    uVar7 = local_20 >> 8;
    bVar4 = local_20._3_1_;
    local_20._0_3_ = CONCAT12((char)uVar6,(undefined2)local_20);
    uVar7 = (uint)*(byte *)((int)unaff_ESI + 0x732459) * (uVar7 & 0xff) >> 7;
    if (0xff < uVar7) {
      uVar7 = 0xff;
    }
    uVar6 = (uint)(uint3)local_20;
    uVar6 = (uint)*(byte *)((int)unaff_ESI + 0x732458) * (uVar6 & 0xff) >> 7;
    if (0xff < uVar6) {
      uVar6 = 0xff;
    }
    uVar8 = (uint)*(byte *)((int)unaff_ESI + 0x73245b) * (uint)bVar4 >> 7;
    local_20 = CONCAT31(CONCAT21(local_20._2_2_,(char)uVar7),(char)uVar6);
    if (0xff < uVar8) {
      uVar8 = 0xff;
    }
    local_20 = CONCAT13((char)uVar8,(uint3)local_20);
  }
  if (fVar1 <= _DAT_00491e78) {
    DAT_004978d0 = local_20;
  }
  else {
    if (_DAT_00470afc <= (_DAT_00491e78 - fVar1) / (_DAT_00491e78 - _DAT_00491e7c)) {
      return 0xffffffff;
    }
    FUN_00463b2c();
    uVar10 = FUN_00463b2c();
    DAT_004978d0 = CONCAT31(DAT_004978d0._1_3_,(char)uVar6 - (char)uVar10);
    FUN_00463b2c();
    uVar10 = FUN_00463b2c();
    DAT_004978d0._0_2_ = CONCAT11(local_20._1_1_ - (char)uVar10,(undefined1)DAT_004978d0);
    FUN_00463b2c();
    uVar10 = FUN_00463b2c();
    DAT_004978d0._0_3_ = CONCAT12(local_20._2_1_ - (char)uVar10,(undefined2)DAT_004978d0);
    uVar10 = FUN_00463b2c();
    DAT_004978d0 = CONCAT13((char)uVar10,(undefined3)DAT_004978d0);
  }
  _DAT_004978ec = DAT_004978d0;
  _DAT_00497908 = DAT_004978d0;
  _DAT_00497924 = DAT_004978d0;
  uVar9 = FUN_00442670(unaff_ESI,2);
  return uVar9;
}

