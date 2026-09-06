/* Raw Ghidra reference; not compilable reconstruction. Address: 00417040 */

/* WARNING: Removing unreachable block (ram,0x0041711f) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int FUN_00417040(void)

{
  int iVar1;
  undefined4 extraout_ECX;
  undefined4 extraout_ECX_00;
  undefined4 uVar2;
  undefined4 extraout_ECX_01;
  undefined4 extraout_ECX_02;
  undefined4 extraout_ECX_03;
  uint extraout_EDX;
  uint extraout_EDX_00;
  uint uVar3;
  uint extraout_EDX_01;
  int unaff_ESI;
  int iVar4;
  bool bVar5;
  ulonglong uVar6;
  int local_c;
  int local_8;
  int local_4;
  
  iVar4 = *(int *)(unaff_ESI + 0x9e78);
  iVar1 = iVar4;
  if (DAT_00474c44 != iVar4) {
    iVar1 = (int)((DAT_00474c44 - iVar4) + (DAT_00474c44 - iVar4 >> 0x1f & 0x1fU)) >> 5;
    if (iVar1 < 0x8d55e) {
      if (iVar1 == 0) {
        iVar1 = 1;
      }
    }
    else {
      iVar1 = 0x8d55e;
    }
    if (*(int *)(unaff_ESI + 0x9e7c) < iVar1) {
      *(int *)(unaff_ESI + 0x9e7c) = iVar1;
    }
    iVar1 = DAT_00474c44 - *(int *)(unaff_ESI + 0x9e78);
    if (iVar1 < *(int *)(unaff_ESI + 0x9e7c)) {
      *(int *)(unaff_ESI + 0x9e7c) = iVar1;
    }
    iVar1 = *(int *)(unaff_ESI + 0x9e78) + *(int *)(unaff_ESI + 0x9e7c);
    *(int *)(unaff_ESI + 0x9e78) = iVar1;
    if (DAT_00474c44 <= iVar1) {
      *(undefined4 *)(unaff_ESI + 0x9e7c) = 0;
    }
    iVar1 = *(int *)(unaff_ESI + 0x9e78);
    if ((99999999 < iVar1) && (iVar4 < 100000000)) {
      *(undefined2 *)(unaff_ESI + 0x48d8) = 4;
    }
  }
  if (DAT_00474c40 < iVar1) {
    _DAT_00474ca0 = _DAT_00474ca0 | 4;
    DAT_00474c94 = DAT_00474c90;
    DAT_00474c40 = iVar1;
  }
  if (0x13 < *(int *)(unaff_ESI + 0x9e64)) {
    if ((99999999 < DAT_00474c40) && (*(int *)(unaff_ESI + 0x9e74) < 100000000)) {
      *(undefined2 *)(unaff_ESI + 0x2420) = 4;
    }
    *(int *)(unaff_ESI + 0x9e74) = DAT_00474c40;
  }
  local_8 = *(int *)(unaff_ESI + 0x9e78);
  local_c = DAT_00474c40;
  iVar4 = unaff_ESI + 0x2874;
  local_4 = 9;
  do {
    if (local_c == 0) {
      FUN_0043e5a0(*(int *)(unaff_ESI + 0x9ec8),8);
    }
    else {
      FUN_0043e5a0(*(int *)(unaff_ESI + 0x9ec8),local_c % 10 + 8);
      local_c = local_c / 10;
    }
    if (local_8 == 0) {
      FUN_0043e5a0(*(int *)(unaff_ESI + 0x9ec8),8);
      uVar2 = extraout_ECX_00;
      uVar3 = extraout_EDX_00;
    }
    else {
      FUN_0043e5a0(*(int *)(unaff_ESI + 0x9ec8),local_8 % 10 + 8);
      uVar2 = extraout_ECX;
      uVar3 = extraout_EDX;
      local_8 = local_8 / 10;
    }
    uVar6 = FUN_0043ee30(uVar2,uVar3,iVar4 + -0x24b8);
    FUN_0043ee30(extraout_ECX_01,(uint)(uVar6 >> 0x20),iVar4);
    iVar4 = iVar4 + 0x3ac;
    local_4 = local_4 + -1;
  } while (local_4 != 0);
  FUN_0043e5a0(*(int *)(unaff_ESI + 0x9ec8),DAT_00474c94 + 8);
  FUN_0043e5a0(*(int *)(unaff_ESI + 0x9ec8),DAT_00474c90 + 8);
  uVar6 = FUN_0043ee30(extraout_ECX_02,extraout_EDX_01,unaff_ESI + 0x10);
  uVar6 = FUN_0043ee30(extraout_ECX_03,(uint)(uVar6 >> 0x20),unaff_ESI + 0x24c8);
  iVar4 = (int)uVar6;
  if ((*(byte *)(unaff_ESI + 0x9eb4) & 0x20) == 0) {
    if (DAT_00474c74 == 4) {
      bVar5 = SBORROW4(*(int *)(unaff_ESI + 0x9e78),*(int *)(&DAT_00474488 + DAT_00474c9c * 4));
      iVar1 = *(int *)(unaff_ESI + 0x9e78) - *(int *)(&DAT_00474488 + DAT_00474c9c * 4);
    }
    else {
      bVar5 = SBORROW4(*(int *)(unaff_ESI + 0x9e78),*(int *)(&DAT_00474474 + DAT_00474c9c * 4));
      iVar1 = *(int *)(unaff_ESI + 0x9e78) - *(int *)(&DAT_00474474 + DAT_00474c9c * 4);
      iVar4 = DAT_00474c9c;
    }
    if (bVar5 == iVar1 < 0) {
      iVar4 = FUN_004188a0(1);
      DAT_00474c9c = DAT_00474c9c + 1;
    }
  }
  return iVar4;
}

