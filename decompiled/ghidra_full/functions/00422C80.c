/* Raw Ghidra reference; not compilable reconstruction. Address: 00422C80 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __thiscall FUN_00422c80(void *this,int param_1)

{
  int *piVar1;
  undefined4 uVar2;
  int iVar3;
  int extraout_ECX;
  undefined4 extraout_ECX_00;
  undefined4 extraout_ECX_01;
  undefined4 extraout_ECX_02;
  undefined4 extraout_ECX_03;
  undefined4 extraout_ECX_04;
  int extraout_ECX_05;
  undefined4 extraout_ECX_06;
  undefined4 extraout_ECX_07;
  undefined4 extraout_ECX_08;
  int extraout_ECX_09;
  undefined4 extraout_ECX_10;
  undefined4 extraout_ECX_11;
  int extraout_ECX_12;
  int iVar4;
  void *extraout_ECX_13;
  int extraout_ECX_14;
  undefined4 extraout_ECX_15;
  undefined4 extraout_ECX_16;
  int extraout_ECX_17;
  undefined4 extraout_ECX_18;
  undefined4 extraout_ECX_19;
  undefined4 extraout_ECX_20;
  undefined4 extraout_ECX_21;
  undefined4 extraout_ECX_22;
  
  iVar4 = DAT_00477810;
  switch(*(undefined4 *)(param_1 + 4)) {
  case 1:
    if (9 < *(int *)(param_1 + 0x14)) {
      *(undefined4 *)(param_1 + 4) = 2;
      iVar4 = -(uint)(*(int *)(iVar4 + 0x5c) != 0);
      iVar3 = iVar4 + 3;
      *(int *)(param_1 + 0x2c) = iVar3;
      *(undefined4 *)(param_1 + 0xf4) = 1;
      if (iVar3 == 0) {
        *(undefined4 *)(param_1 + 0x24) = 0;
      }
      else if (iVar3 < 1) {
        *(int *)(param_1 + 0x24) = iVar4 + 2;
      }
      else {
        *(undefined4 *)(param_1 + 0x24) = 0;
      }
      FUN_00449470(iVar3);
      return;
    }
    break;
  case 2:
    *(undefined4 *)(param_1 + 0x28) = *(undefined4 *)(param_1 + 0x24);
    if (((_DAT_00474e36 & 0x10) != 0) || ((DAT_00474e34 & 0x10) != 0)) {
      FUN_0044bea0(-1);
    }
    if (((_DAT_00474e36 & 0x20) != 0) || ((DAT_00474e34 & 0x20) != 0)) {
      FUN_0044bea0(1);
    }
    iVar4 = *(int *)(param_1 + 0x24);
    if (*(int *)(param_1 + 0x28) != iVar4) {
      FUN_00449470(iVar4);
      FUN_0043dc90(&DAT_00492590,0);
      iVar4 = extraout_ECX;
    }
    if ((_DAT_00474e36 & 0x1001) != 0) {
      FUN_0043dc90(&DAT_00492590,0);
      iVar4 = *(int *)(param_1 + 0x24);
      if (iVar4 == 0) {
        FUN_00409e50(extraout_ECX_00);
        FUN_00409e50(extraout_ECX_03);
        FUN_00409e50(extraout_ECX_04);
        *(undefined4 *)(param_1 + 4) = 3;
      }
      else if (iVar4 == 1) {
        FUN_004497d0(extraout_ECX_00);
        FUN_004243f0(extraout_ECX_02);
        *(uint *)(param_1 + 4) = 4 - (uint)(*(int *)(DAT_00477810 + 0x5c) != 0);
      }
      else if (iVar4 == 2) {
        FUN_004497d0(extraout_ECX_00);
        FUN_004243f0(extraout_ECX_01);
        *(undefined4 *)(param_1 + 4) = 4;
      }
      FUN_00405410(0);
      iVar4 = extraout_ECX_05;
    }
    if ((_DAT_00474e36 & 0x4000) != 0) {
      FUN_0043dc90(&DAT_00492590,0);
      FUN_004497d0(extraout_ECX_06);
      FUN_004243f0(extraout_ECX_07);
      *(undefined4 *)(param_1 + 4) = 3;
      FUN_00405410(0);
      iVar4 = *(int *)(param_1 + 0x2c);
      if (iVar4 == 0) {
        *(undefined4 *)(param_1 + 0x24) = 2;
      }
      else if (iVar4 < 3) {
        *(int *)(param_1 + 0x24) = iVar4 + -1;
      }
      else {
        *(undefined4 *)(param_1 + 0x24) = 2;
      }
      FUN_00409e50(extraout_ECX_08);
      iVar4 = extraout_ECX_09;
    }
    if ((_DAT_00474e36 & 0x200) != 0) {
      FUN_0043dc90(&DAT_00492590,0);
      FUN_004497d0(extraout_ECX_10);
      FUN_004243f0(extraout_ECX_11);
      *(undefined4 *)(param_1 + 4) = 3;
      FUN_00405410(0);
      iVar3 = *(int *)(param_1 + 0x2c);
      iVar4 = extraout_ECX_12;
      if (iVar3 == 0) {
        *(undefined4 *)(param_1 + 0x24) = 1;
      }
      else if (iVar3 < 2) {
        *(int *)(param_1 + 0x24) = iVar3 + -1;
      }
      else {
        *(undefined4 *)(param_1 + 0x24) = 1;
      }
    }
    goto LAB_00423059;
  case 3:
    if (0xb < *(int *)(param_1 + 0x14)) {
      iVar4 = *(int *)(param_1 + 0x24);
      *(undefined4 *)(param_1 + 4) = 0;
      if (iVar4 == 0) {
        FUN_00422c30();
      }
      else {
        if (iVar4 == 1) {
          FUN_00409e50(this);
          FUN_00409e50(extraout_ECX_22);
          FUN_0040ac90(4);
          return;
        }
        if (iVar4 == 2) {
          FUN_00409e50(this);
          DAT_00491fb8 = 10;
          return;
        }
      }
    }
    break;
  case 4:
    if (*(int *)(param_1 + 0x14) < 0x14) {
      return;
    }
    if (*(int *)(param_1 + 0x14) == 0x14) {
      piVar1 = (int *)FUN_0044be20();
      *(undefined4 *)(param_1 + 0x2c) = 2;
      *(undefined4 *)(param_1 + 0xf4) = 1;
      iVar4 = piVar1[2];
      if (iVar4 == 0) {
        *piVar1 = 1;
        iVar4 = 0;
      }
      else if (iVar4 < 2) {
        iVar4 = iVar4 + -1;
        *piVar1 = iVar4;
      }
      else {
        iVar4 = 1;
        *piVar1 = 1;
      }
      FUN_00449470(iVar4);
      this = extraout_ECX_13;
    }
    if (*(int *)(param_1 + 0x14) < 0x1e) {
      return;
    }
    if (*(int *)(param_1 + 0x14) == 0x1e) {
      FUN_00449470(this);
    }
    *(undefined4 *)(param_1 + 0x28) = *(undefined4 *)(param_1 + 0x24);
    uVar2 = FUN_0040ace0(0x474e30);
    if ((short)uVar2 != 0) {
      FUN_0044bea0(-1);
    }
    uVar2 = FUN_0040ace0(0x474e30);
    if ((short)uVar2 != 0) {
      FUN_0044bea0(1);
    }
    iVar4 = *(int *)(param_1 + 0x28);
    if (iVar4 != *(int *)(param_1 + 0x24)) {
      FUN_00449470(iVar4);
      FUN_0043dc90(&DAT_00492590,0);
      iVar4 = extraout_ECX_14;
    }
    if ((_DAT_00474e36 & 0x1001) != 0) {
      FUN_0043dc90(&DAT_00492590,0);
      iVar4 = *(int *)(param_1 + 0x24);
      if ((iVar4 == 0) || (iVar4 == 1)) {
        FUN_004497d0(extraout_ECX_15);
        FUN_004243f0(extraout_ECX_16);
        *(undefined4 *)(param_1 + 4) = 5;
      }
      FUN_00405410(0);
      iVar4 = extraout_ECX_17;
    }
LAB_00423059:
    if ((_DAT_00474e36 & 8) != 0) {
      iVar3 = *(int *)(param_1 + 0x2c);
      if (iVar3 == 0) {
        *(undefined4 *)(param_1 + 0x24) = 0;
      }
      else if (iVar3 < 1) {
        *(int *)(param_1 + 0x24) = iVar3 + -1;
      }
      else {
        *(undefined4 *)(param_1 + 0x24) = 0;
      }
      FUN_00409e50(iVar4);
      FUN_00409e50(extraout_ECX_18);
      FUN_00409e50(extraout_ECX_19);
      *(undefined4 *)(param_1 + 4) = 3;
      FUN_00405410(0);
      return;
    }
    break;
  case 5:
    if (0x13 < *(int *)(param_1 + 0x14)) {
      if (*(int *)(param_1 + 0x24) == 0) {
        FUN_00409e50(this);
        FUN_00409e50(extraout_ECX_21);
        *(undefined4 *)(param_1 + 4) = 3;
        FUN_0044be70();
      }
      else if (*(int *)(param_1 + 0x24) == 1) {
        FUN_0044be70();
        FUN_00449470(extraout_ECX_20);
        *(undefined4 *)(param_1 + 4) = 2;
        FUN_00405410(0);
        return;
      }
      FUN_00405410(0);
      return;
    }
  }
  return;
}

