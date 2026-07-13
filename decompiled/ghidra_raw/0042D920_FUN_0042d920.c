/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x0042D920
 * Tracking name: FUN_0042d920
 * Ghidra name: FUN_0042d920
 * Tracked span: 3200 bytes
 */


/* WARNING: Removing unreachable block (ram,0x0042d94d) */
/* WARNING: Removing unreachable block (ram,0x0042d95a) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_0042d920(int param_1)

{
  void *pvVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  int *piVar5;
  undefined4 extraout_ECX;
  undefined4 extraout_ECX_00;
  undefined4 extraout_ECX_01;
  undefined4 extraout_ECX_02;
  undefined4 extraout_ECX_03;
  undefined4 extraout_ECX_04;
  undefined4 extraout_ECX_05;
  undefined4 extraout_ECX_06;
  undefined4 extraout_ECX_07;
  undefined4 extraout_ECX_08;
  undefined4 extraout_ECX_09;
  undefined4 extraout_ECX_10;
  undefined4 extraout_ECX_11;
  undefined4 extraout_ECX_12;
  undefined4 extraout_ECX_13;
  undefined4 extraout_ECX_14;
  undefined4 extraout_ECX_15;
  undefined4 extraout_ECX_16;
  undefined4 extraout_ECX_17;
  
  switch(*(undefined4 *)(param_1 + 0x20)) {
  case 0:
    *(undefined4 *)(param_1 + 0x2c) = 6;
    *(undefined4 *)(param_1 + 0x24) = 0;
    FUN_0042c670(param_1);
    FUN_0042e5a0(extraout_ECX);
    FUN_0042c620(1);
  case 1:
    if (6 < *(int *)(param_1 + 0x2b4)) {
      FUN_0042c620(2);
      FUN_00449250(extraout_ECX_00,(int)g_pGameStateManager,*(int *)(param_1 + 0x2c8));
      pvVar1 = g_pGameStateManager;
      if (DAT_00491d6a == 0) {
        iVar2 = FUN_004491c0(*(undefined4 *)(param_1 + 0x2c8),(int)g_pGameStateManager,
                             *(undefined4 *)(param_1 + 0x2c8));
        if (iVar2 == 0) {
          *(undefined4 *)(param_1 + 0x2c8) = 0;
        }
        for (piVar5 = (int *)(iVar2 + 0x10);
            (piVar5 != (int *)0x0 && (*(short *)(*piVar5 + 0x38a) != 0x1f));
            piVar5 = (int *)piVar5[1]) {
        }
        FUN_00449670(0x2e);
        iVar2 = FUN_004491c0(extraout_ECX_02,(int)pvVar1,*(int *)(param_1 + 0x2c8));
        if (iVar2 == 0) {
          *(undefined4 *)(param_1 + 0x2c8) = 0;
        }
        for (piVar5 = (int *)(iVar2 + 0x10); piVar5 != (int *)0x0; piVar5 = (int *)piVar5[1]) {
          if (*(short *)(*piVar5 + 0x38a) == 0x20) {
            iVar2 = 0x2f;
            goto LAB_0042db8d;
          }
        }
        iVar2 = 0x2f;
      }
      else if (DAT_00491d6a == 1) {
        iVar2 = FUN_004491c0(extraout_ECX_01,(int)g_pGameStateManager,*(int *)(param_1 + 0x2c8));
        if (iVar2 == 0) {
          *(undefined4 *)(param_1 + 0x2c8) = 0;
        }
        for (piVar5 = (int *)(iVar2 + 0x10);
            (piVar5 != (int *)0x0 && (*(short *)(*piVar5 + 0x38a) != 0x1f));
            piVar5 = (int *)piVar5[1]) {
        }
        FUN_00449670(0x30);
        iVar2 = FUN_004491c0(extraout_ECX_03,(int)pvVar1,*(int *)(param_1 + 0x2c8));
        if (iVar2 == 0) {
          *(undefined4 *)(param_1 + 0x2c8) = 0;
        }
        for (piVar5 = (int *)(iVar2 + 0x10); piVar5 != (int *)0x0; piVar5 = (int *)piVar5[1]) {
          if (*(short *)(*piVar5 + 0x38a) == 0x20) {
            iVar2 = 0x31;
            goto LAB_0042db8d;
          }
        }
        iVar2 = 0x31;
      }
      else {
        iVar2 = FUN_004491c0(extraout_ECX_01,(int)g_pGameStateManager,*(int *)(param_1 + 0x2c8));
        if (iVar2 == 0) {
          *(undefined4 *)(param_1 + 0x2c8) = 0;
        }
        for (piVar5 = (int *)(iVar2 + 0x10);
            (piVar5 != (int *)0x0 && (*(short *)(*piVar5 + 0x38a) != 0x1f));
            piVar5 = (int *)piVar5[1]) {
        }
        FUN_00449670(0x2c);
        iVar2 = FUN_004491c0(extraout_ECX_04,(int)pvVar1,*(int *)(param_1 + 0x2c8));
        if (iVar2 == 0) {
          *(undefined4 *)(param_1 + 0x2c8) = 0;
        }
        for (piVar5 = (int *)(iVar2 + 0x10);
            (piVar5 != (int *)0x0 && (*(short *)(*piVar5 + 0x38a) != 0x20));
            piVar5 = (int *)piVar5[1]) {
        }
        iVar2 = 0x2d;
      }
LAB_0042db8d:
      FUN_00449670(iVar2);
      FUN_0042c770(1);
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
      FUN_00449250(*(undefined4 *)(param_1 + 0x2c8),(int)g_pGameStateManager,
                   *(undefined4 *)(param_1 + 0x2c8));
      FUN_0042c770(1);
    }
    if ((_DAT_00474e36 & 10) != 0) {
      if (*(int *)(param_1 + 0x24) != 5) {
        FUN_0043dc90(&DAT_00492590,0);
        iVar2 = *(int *)(param_1 + 0x2c);
        if (iVar2 == 0) {
          *(undefined4 *)(param_1 + 0x24) = 5;
        }
        else if (iVar2 < 6) {
          *(int *)(param_1 + 0x24) = iVar2 + -1;
        }
        else {
          *(undefined4 *)(param_1 + 0x24) = 5;
        }
        FUN_0042c750(1);
        FUN_0042c770(1);
        return 1;
      }
LAB_0042e27b:
      FUN_0042c770(1);
LAB_0042e291:
      FUN_0043dc90(&DAT_00492590,0);
      FUN_0042c620(4);
      return 1;
    }
    if ((*(int *)(param_1 + 0x24) == 2) &&
       (iVar2 = FUN_00427c70((void *)(param_1 + 0x2b0),0x3c), iVar2 != 0)) {
      FUN_0043dc90(&DAT_00492590,0);
    }
    uVar3 = FUN_0040ace0(0x474e30);
    pvVar1 = g_pGameStateManager;
    if ((short)uVar3 != 0) {
      iVar2 = *(int *)(param_1 + 0x24);
      if (iVar2 == 0) {
        if (DAT_00491d6a == 0) {
          DAT_00491d6a = 2;
LAB_0042de49:
          iVar2 = FUN_004491c0(extraout_ECX_05,(int)g_pGameStateManager,*(int *)(param_1 + 0x2c8));
          if (iVar2 == 0) {
            *(undefined4 *)(param_1 + 0x2c8) = 0;
          }
          for (piVar5 = (int *)(iVar2 + 0x10);
              (piVar5 != (int *)0x0 && (*(short *)(*piVar5 + 0x38a) != 0x1f));
              piVar5 = (int *)piVar5[1]) {
          }
          FUN_00449670(0x2c);
          iVar2 = FUN_004491c0(*(undefined4 *)(param_1 + 0x2c8),(int)pvVar1,
                               *(undefined4 *)(param_1 + 0x2c8));
          if (iVar2 == 0) {
            *(undefined4 *)(param_1 + 0x2c8) = 0;
          }
          for (piVar5 = (int *)(iVar2 + 0x10);
              (piVar5 != (int *)0x0 && (*(short *)(*piVar5 + 0x38a) != 0x20));
              piVar5 = (int *)piVar5[1]) {
          }
          iVar2 = 0x2d;
        }
        else {
          DAT_00491d6a = DAT_00491d6a - 1;
          if (DAT_00491d6a == 0) {
            iVar2 = FUN_004491c0(extraout_ECX_05,(int)g_pGameStateManager,*(int *)(param_1 + 0x2c8))
            ;
            if (iVar2 == 0) {
              *(undefined4 *)(param_1 + 0x2c8) = 0;
            }
            for (piVar5 = (int *)(iVar2 + 0x10);
                (piVar5 != (int *)0x0 && (*(short *)(*piVar5 + 0x38a) != 0x1f));
                piVar5 = (int *)piVar5[1]) {
            }
            FUN_00449670(0x2e);
            iVar2 = FUN_004491c0(*(undefined4 *)(param_1 + 0x2c8),(int)pvVar1,
                                 *(undefined4 *)(param_1 + 0x2c8));
            if (iVar2 == 0) {
              *(undefined4 *)(param_1 + 0x2c8) = 0;
            }
            for (piVar5 = (int *)(iVar2 + 0x10); piVar5 != (int *)0x0; piVar5 = (int *)piVar5[1]) {
              if (*(short *)(*piVar5 + 0x38a) == 0x20) {
                iVar2 = 0x2f;
                goto LAB_0042dedd;
              }
            }
            iVar2 = 0x2f;
          }
          else {
            if (DAT_00491d6a != 1) goto LAB_0042de49;
            iVar2 = FUN_004491c0(extraout_ECX_05,(int)g_pGameStateManager,*(int *)(param_1 + 0x2c8))
            ;
            if (iVar2 == 0) {
              *(undefined4 *)(param_1 + 0x2c8) = 0;
            }
            for (piVar5 = (int *)(iVar2 + 0x10);
                (piVar5 != (int *)0x0 && (*(short *)(*piVar5 + 0x38a) != 0x1f));
                piVar5 = (int *)piVar5[1]) {
            }
            FUN_00449670(0x30);
            iVar2 = FUN_004491c0(*(undefined4 *)(param_1 + 0x2c8),(int)pvVar1,
                                 *(undefined4 *)(param_1 + 0x2c8));
            if (iVar2 == 0) {
              *(undefined4 *)(param_1 + 0x2c8) = 0;
            }
            for (piVar5 = (int *)(iVar2 + 0x10); piVar5 != (int *)0x0; piVar5 = (int *)piVar5[1]) {
              if (*(short *)(*piVar5 + 0x38a) == 0x20) {
                iVar2 = 0x31;
                goto LAB_0042dedd;
              }
            }
            iVar2 = 0x31;
          }
        }
LAB_0042dedd:
        FUN_00449670(iVar2);
        FUN_0043dc90(&DAT_00492590,0);
      }
      else if (iVar2 == 1) {
        if (DAT_00491d68 < '\x05') {
          DAT_00491d68 = '\0';
          FUN_0042e5a0(extraout_ECX_05);
        }
        else {
          DAT_00491d68 = DAT_00491d68 + -5;
          FUN_0042e5a0(extraout_ECX_05);
        }
      }
      else if (iVar2 == 2) {
        if (DAT_00491d69 < '\x05') {
          DAT_00491d69 = '\0';
          FUN_0042e5a0(extraout_ECX_05);
        }
        else {
          DAT_00491d69 = DAT_00491d69 + -5;
          FUN_0042e5a0(extraout_ECX_05);
        }
      }
    }
    uVar4 = FUN_0040ace0(0x474e30);
    uVar3 = extraout_ECX_06;
    if ((short)uVar4 != 0) {
      iVar2 = *(int *)(param_1 + 0x24);
      if (iVar2 == 0) {
        if (DAT_00491d6a < 2) {
          DAT_00491d6a = DAT_00491d6a + 1;
        }
        else {
          DAT_00491d6a = 0;
        }
        FUN_0043dc90(&DAT_00492590,0);
        iVar2 = *(int *)(param_1 + 0x2c8);
        if (DAT_00491d6a == 0) {
          iVar2 = FUN_004491c0(extraout_ECX_09,(int)pvVar1,iVar2);
          if (iVar2 == 0) {
            *(undefined4 *)(param_1 + 0x2c8) = 0;
          }
          for (piVar5 = (int *)(iVar2 + 0x10);
              (piVar5 != (int *)0x0 && (*(short *)(*piVar5 + 0x38a) != 0x1f));
              piVar5 = (int *)piVar5[1]) {
          }
          FUN_00449670(0x2e);
          iVar2 = FUN_004491c0(extraout_ECX_10,(int)pvVar1,*(int *)(param_1 + 0x2c8));
          if (iVar2 == 0) {
            *(undefined4 *)(param_1 + 0x2c8) = 0;
          }
          for (piVar5 = (int *)(iVar2 + 0x10); piVar5 != (int *)0x0; piVar5 = (int *)piVar5[1]) {
            if (*(short *)(*piVar5 + 0x38a) == 0x20) {
              iVar2 = 0x2f;
              goto LAB_0042e24c;
            }
          }
          iVar2 = 0x2f;
        }
        else if (DAT_00491d6a == 1) {
          iVar2 = FUN_004491c0(extraout_ECX_09,(int)pvVar1,iVar2);
          if (iVar2 == 0) {
            *(undefined4 *)(param_1 + 0x2c8) = 0;
          }
          for (piVar5 = (int *)(iVar2 + 0x10);
              (piVar5 != (int *)0x0 && (*(short *)(*piVar5 + 0x38a) != 0x1f));
              piVar5 = (int *)piVar5[1]) {
          }
          FUN_00449670(0x30);
          iVar2 = FUN_004491c0(extraout_ECX_11,(int)pvVar1,*(int *)(param_1 + 0x2c8));
          if (iVar2 == 0) {
            *(undefined4 *)(param_1 + 0x2c8) = 0;
          }
          for (piVar5 = (int *)(iVar2 + 0x10); piVar5 != (int *)0x0; piVar5 = (int *)piVar5[1]) {
            if (*(short *)(*piVar5 + 0x38a) == 0x20) {
              iVar2 = 0x31;
              goto LAB_0042e24c;
            }
          }
          iVar2 = 0x31;
        }
        else {
          iVar2 = FUN_004491c0(extraout_ECX_09,(int)pvVar1,iVar2);
          if (iVar2 == 0) {
            *(undefined4 *)(param_1 + 0x2c8) = 0;
          }
          for (piVar5 = (int *)(iVar2 + 0x10);
              (piVar5 != (int *)0x0 && (*(short *)(*piVar5 + 0x38a) != 0x1f));
              piVar5 = (int *)piVar5[1]) {
          }
          FUN_00449670(0x2c);
          iVar2 = FUN_004491c0(extraout_ECX_12,(int)pvVar1,*(int *)(param_1 + 0x2c8));
          if (iVar2 == 0) {
            *(undefined4 *)(param_1 + 0x2c8) = 0;
          }
          for (piVar5 = (int *)(iVar2 + 0x10);
              (piVar5 != (int *)0x0 && (*(short *)(*piVar5 + 0x38a) != 0x20));
              piVar5 = (int *)piVar5[1]) {
          }
          iVar2 = 0x2d;
        }
LAB_0042e24c:
        FUN_00449670(iVar2);
        uVar3 = extraout_ECX_13;
      }
      else if (iVar2 == 1) {
        DAT_00491d68 = DAT_00491d68 + '\x05';
        if ('d' < DAT_00491d68) {
          DAT_00491d68 = 'd';
        }
        FUN_0042e5a0(extraout_ECX_06);
        uVar3 = extraout_ECX_08;
      }
      else if (iVar2 == 2) {
        DAT_00491d69 = DAT_00491d69 + '\x05';
        if ('d' < DAT_00491d69) {
          DAT_00491d69 = 'd';
        }
        FUN_0042e5a0(extraout_ECX_06);
        uVar3 = extraout_ECX_07;
      }
    }
    if ((_DAT_00474e36 & 0x1001) != 0) {
      iVar2 = *(int *)(param_1 + 0x24);
      if (iVar2 == 3) {
        FUN_0042c770(1);
        goto LAB_0042e291;
      }
      if (iVar2 == 4) {
        DAT_00491d68 = 100;
        DAT_00491d69 = 0x50;
        DAT_00491d6a = '\0';
        FUN_0042e5a0(uVar3);
        iVar2 = *(int *)(param_1 + 0x2c8);
        if (DAT_00491d6a == '\0') {
          iVar2 = FUN_004491c0(extraout_ECX_14,(int)pvVar1,iVar2);
          if (iVar2 == 0) {
            *(undefined4 *)(param_1 + 0x2c8) = 0;
          }
          for (piVar5 = (int *)(iVar2 + 0x10);
              (piVar5 != (int *)0x0 && (*(short *)(*piVar5 + 0x38a) != 0x1f));
              piVar5 = (int *)piVar5[1]) {
          }
          FUN_00449670(0x2e);
          iVar2 = FUN_004491c0(extraout_ECX_15,(int)pvVar1,*(int *)(param_1 + 0x2c8));
          if (iVar2 == 0) {
            *(undefined4 *)(param_1 + 0x2c8) = 0;
          }
          for (piVar5 = (int *)(iVar2 + 0x10); piVar5 != (int *)0x0; piVar5 = (int *)piVar5[1]) {
            if (*(short *)(*piVar5 + 0x38a) == 0x20) {
              iVar2 = 0x2f;
              goto LAB_0042e4bd;
            }
          }
          iVar2 = 0x2f;
        }
        else if (DAT_00491d6a == '\x01') {
          iVar2 = FUN_004491c0(extraout_ECX_14,(int)pvVar1,iVar2);
          if (iVar2 == 0) {
            *(undefined4 *)(param_1 + 0x2c8) = 0;
          }
          for (piVar5 = (int *)(iVar2 + 0x10);
              (piVar5 != (int *)0x0 && (*(short *)(*piVar5 + 0x38a) != 0x1f));
              piVar5 = (int *)piVar5[1]) {
          }
          FUN_00449670(0x30);
          iVar2 = FUN_004491c0(extraout_ECX_16,(int)pvVar1,*(int *)(param_1 + 0x2c8));
          if (iVar2 == 0) {
            *(undefined4 *)(param_1 + 0x2c8) = 0;
          }
          for (piVar5 = (int *)(iVar2 + 0x10); piVar5 != (int *)0x0; piVar5 = (int *)piVar5[1]) {
            if (*(short *)(*piVar5 + 0x38a) == 0x20) {
              iVar2 = 0x31;
              goto LAB_0042e4bd;
            }
          }
          iVar2 = 0x31;
        }
        else {
          iVar2 = FUN_004491c0(extraout_ECX_14,(int)pvVar1,iVar2);
          if (iVar2 == 0) {
            *(undefined4 *)(param_1 + 0x2c8) = 0;
          }
          for (piVar5 = (int *)(iVar2 + 0x10);
              (piVar5 != (int *)0x0 && (*(short *)(*piVar5 + 0x38a) != 0x1f));
              piVar5 = (int *)piVar5[1]) {
          }
          FUN_00449670(0x2c);
          iVar2 = FUN_004491c0(extraout_ECX_17,(int)pvVar1,*(int *)(param_1 + 0x2c8));
          if (iVar2 == 0) {
            *(undefined4 *)(param_1 + 0x2c8) = 0;
          }
          for (piVar5 = (int *)(iVar2 + 0x10);
              (piVar5 != (int *)0x0 && (*(short *)(*piVar5 + 0x38a) != 0x20));
              piVar5 = (int *)piVar5[1]) {
          }
          iVar2 = 0x2d;
        }
LAB_0042e4bd:
        FUN_00449670(iVar2);
        FUN_0043dc90(&DAT_00492590,0);
        return 1;
      }
      if (iVar2 == 5) goto LAB_0042e27b;
    }
    break;
  case 3:
    break;
  case 4:
    if (9 < *(int *)(param_1 + 0x2b4)) {
      if (*(int *)(param_1 + 0x24) == 3) {
        FUN_0042c5c0(5);
        FUN_0044be20();
      }
      else if (*(int *)(param_1 + 0x24) == 5) {
        FUN_0042c730(0x5a);
        FUN_0042c730(0x5b);
        FUN_0042c5c0(2);
        FUN_0044be70();
        return 1;
      }
    }
    break;
  default:
    goto switchD_0042d93b_default;
  }
switchD_0042d93b_default:
  return 1;
}

