/* Raw Ghidra reference; not compilable reconstruction. Address: 00430A60 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 __thiscall FUN_00430a60(void *this,int param_1)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 extraout_ECX;
  undefined4 extraout_ECX_00;
  undefined4 extraout_ECX_01;
  undefined4 extraout_ECX_02;
  undefined4 extraout_ECX_03;
  
  switch(*(undefined4 *)(param_1 + 0x20)) {
  case 0:
    *(undefined4 *)(param_1 + 0x2c) = 3;
    iVar1 = DAT_0047783c;
    if (DAT_00474c74 == 4) {
      if (*(char *)(DAT_00474c68 * 3 + 0x1d888 + DAT_0047783c) == '\0') {
        if (*(int *)(param_1 + 0x24) == 0) {
          iVar2 = *(int *)(param_1 + 0x2c);
          if (*(char *)(DAT_00474c68 * 3 + DAT_0047783c + 0x1d889) == '\0') {
            if (iVar2 == 0) {
              *(undefined4 *)(param_1 + 0x24) = 2;
            }
            else if (iVar2 < 3) {
              *(int *)(param_1 + 0x24) = iVar2 + -1;
            }
            else {
              *(undefined4 *)(param_1 + 0x24) = 2;
            }
          }
          else if (iVar2 == 0) {
            *(undefined4 *)(param_1 + 0x24) = 1;
          }
          else if (iVar2 < 2) {
            *(int *)(param_1 + 0x24) = iVar2 + -1;
          }
          else {
            *(undefined4 *)(param_1 + 0x24) = 1;
          }
        }
        *(undefined4 *)(param_1 + 0xb4 + *(int *)(param_1 + 0xf8) * 4) = 0;
        *(int *)(param_1 + 0xf8) = *(int *)(param_1 + 0xf8) + 1;
      }
      if (*(char *)(DAT_00474c68 * 3 + iVar1 + 0x1d889) == '\0') {
        if (*(int *)(param_1 + 0x24) == 1) {
          iVar2 = *(int *)(param_1 + 0x2c);
          if (*(char *)(DAT_00474c68 * 3 + 0x1d888 + iVar1) == '\0') {
            if (iVar2 == 0) {
              *(undefined4 *)(param_1 + 0x24) = 2;
            }
            else if (iVar2 < 3) {
              *(int *)(param_1 + 0x24) = iVar2 + -1;
            }
            else {
              *(undefined4 *)(param_1 + 0x24) = 2;
            }
          }
          else if (iVar2 == 0) {
            *(undefined4 *)(param_1 + 0x24) = 0;
          }
          else if (iVar2 < 1) {
            *(int *)(param_1 + 0x24) = iVar2 + -1;
          }
          else {
            *(undefined4 *)(param_1 + 0x24) = 0;
          }
        }
        *(undefined4 *)(param_1 + 0xb4 + *(int *)(param_1 + 0xf8) * 4) = 1;
        *(int *)(param_1 + 0xf8) = *(int *)(param_1 + 0xf8) + 1;
      }
      iVar1 = iVar1 + DAT_00474c68 * 3;
      if (*(char *)(iVar1 + 0x1d88a) == '\0') {
        if (*(int *)(param_1 + 0x24) == 2) {
          iVar2 = *(int *)(param_1 + 0x2c);
          if (*(char *)(iVar1 + 0x1d888) == '\0') {
            if (iVar2 == 0) {
              *(undefined4 *)(param_1 + 0x24) = 1;
            }
            else if (iVar2 < 2) {
              *(int *)(param_1 + 0x24) = iVar2 + -1;
            }
            else {
              *(undefined4 *)(param_1 + 0x24) = 1;
            }
          }
          else if (iVar2 == 0) {
            *(undefined4 *)(param_1 + 0x24) = 0;
          }
          else if (iVar2 < 1) {
            *(int *)(param_1 + 0x24) = iVar2 + -1;
          }
          else {
            *(undefined4 *)(param_1 + 0x24) = 0;
          }
        }
        *(undefined4 *)(param_1 + 0xb4 + *(int *)(param_1 + 0xf8) * 4) = 2;
        *(int *)(param_1 + 0xf8) = *(int *)(param_1 + 0xf8) + 1;
      }
    }
    FUN_0042c670(param_1);
    FUN_0042c6d0(extraout_ECX);
    FUN_0042c670(param_1);
    uVar3 = *(undefined4 *)(param_1 + 0x51c + DAT_00474c68 * 4);
    FUN_00449250(uVar3,(int)g_pGameStateManager,uVar3);
    FUN_0042c770(DAT_00474c68 + 0x96);
    FUN_0042c620(1);
    if (*(int *)(DAT_0047783c + 0x4d0 + (DAT_00474c68 * 0x329d + DAT_00474c74) * 4) == 0) {
      FUN_004497d0(DAT_0047783c);
      FUN_004495e0();
    }
    if (*(int *)(DAT_0047783c + 0x484c + (DAT_00474c68 * 0x329d + DAT_00474c74) * 4) == 0) {
      FUN_004497d0(DAT_0047783c);
      FUN_004495e0();
    }
    if (*(int *)(DAT_0047783c + 0x8bc8 + (DAT_00474c68 * 0x329d + DAT_00474c74) * 4) == 0) {
      FUN_004497d0(DAT_0047783c);
      FUN_004495e0();
    }
  case 1:
    if (6 < *(int *)(param_1 + 0x2b4)) {
      FUN_0042c620(2);
      return 1;
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
    if (*(int *)(param_1 + 0x28) != *(int *)(param_1 + 0x24)) {
      FUN_0043dc90(&DAT_00492590,0);
      FUN_0042c750(DAT_00474c68 + 0x96);
      FUN_0042c770(DAT_00474c68 + 0x96);
    }
    if ((_DAT_00474e36 & 10) != 0) {
      FUN_0042c620(4);
      FUN_0043dc90(&DAT_00492590,0);
      return 1;
    }
    if ((_DAT_00474e36 & 0x1001) != 0) {
      FUN_0042c620(3);
      FUN_0043dc90(&DAT_00492590,0);
      FUN_004497d0(DAT_00474c68 * 3 + 0x3f);
      FUN_00449470(extraout_ECX_00);
      return 1;
    }
    break;
  case 3:
    if (*(int *)(param_1 + 0x2b4) == 10) {
      if ((DAT_00474ca0 & 0x10) == 0) {
        FUN_0040c540();
        FUN_0043c8b0(5,0x20,0,0,0);
      }
      else {
        DAT_00474c6c = *(undefined4 *)(param_1 + 0x24);
        FUN_0044be20();
        FUN_0042c6d0(extraout_ECX_01);
        FUN_0042c5c0(9);
      }
    }
    if (0x27 < *(int *)(param_1 + 0x2b4)) {
      DAT_00474c6c = *(undefined4 *)(param_1 + 0x24);
      FUN_0044be20();
      if ((DAT_00474ca0 & 0x10) != 0) {
        FUN_0042c6d0(extraout_ECX_02);
        FUN_0042c5c0(9);
        return 1;
      }
      FUN_0042c5c0(3);
      if (DAT_00474c74 < 4) {
        DAT_00477848 = &DAT_004747b8;
        DAT_00474c7c = 1;
        DAT_00474c80 = 1;
      }
      else {
        DAT_00477848 = &DAT_004748d8;
        DAT_00474c7c = 7;
        DAT_00474c80 = 7;
      }
      DAT_00491fb8 = 7;
      FUN_00420c30();
      return 1;
    }
    break;
  case 4:
    if (5 < *(int *)(param_1 + 0x2b4)) {
      FUN_0042c6d0(this);
      FUN_0042c6d0(extraout_ECX_03);
      FUN_0042c5c0(7);
      FUN_0044be70();
    }
  }
  return 1;
}

