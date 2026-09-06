/* Raw Ghidra reference; not compilable reconstruction. Address: 0042E5A0 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __fastcall FUN_0042e5a0(undefined4 param_1)

{
  void *pvVar1;
  int *piVar2;
  int extraout_ECX;
  int iVar3;
  undefined4 extraout_ECX_00;
  undefined4 uVar4;
  undefined4 extraout_ECX_01;
  undefined4 extraout_ECX_02;
  undefined4 extraout_ECX_03;
  undefined4 extraout_ECX_04;
  undefined4 extraout_ECX_05;
  undefined4 extraout_ECX_06;
  undefined4 extraout_ECX_07;
  undefined4 extraout_ECX_08;
  uint uVar5;
  undefined4 extraout_ECX_09;
  undefined4 extraout_ECX_10;
  undefined4 extraout_ECX_11;
  undefined4 extraout_ECX_12;
  undefined4 extraout_ECX_13;
  undefined4 extraout_ECX_14;
  undefined4 extraout_ECX_15;
  undefined4 extraout_ECX_16;
  undefined4 extraout_ECX_17;
  undefined4 extraout_ECX_18;
  undefined4 extraout_ECX_19;
  undefined4 extraout_ECX_20;
  undefined4 extraout_ECX_21;
  undefined4 extraout_ECX_22;
  undefined4 extraout_ECX_23;
  undefined4 extraout_ECX_24;
  undefined4 extraout_ECX_25;
  undefined4 extraout_ECX_26;
  undefined4 extraout_ECX_27;
  undefined4 extraout_ECX_28;
  int unaff_EDI;
  ulonglong uVar6;
  
  DAT_00497854 = (int)DAT_00491d68;
  FUN_0043e460(param_1,"SetVol",8,0);
  DAT_00497858 = (int)DAT_00491d69;
  if (DAT_00497858 == 0) {
    _DAT_0049785c = -10000;
    iVar3 = extraout_ECX;
  }
  else {
    uVar6 = FUN_00463b2c();
    iVar3 = -5000 - (int)uVar6;
    _DAT_0049785c = iVar3;
  }
  pvVar1 = g_pGameStateManager;
  iVar3 = FUN_004491c0(iVar3,(int)g_pGameStateManager,*(int *)(unaff_EDI + 0x2c8));
  if (iVar3 == 0) {
    *(undefined4 *)(unaff_EDI + 0x2c8) = 0;
  }
  for (piVar2 = (int *)(iVar3 + 0x10); piVar2 != (int *)0x0; piVar2 = (int *)piVar2[1]) {
    if (*(short *)(*piVar2 + 0x38a) == 0x25) {
      iVar3 = *(int *)*piVar2;
      goto LAB_0042e668;
    }
  }
  iVar3 = 0;
LAB_0042e668:
  iVar3 = FUN_004491c0(0x25,(int)pvVar1,iVar3);
  if (iVar3 != 0) {
    FUN_0043e5a0(*(int *)(iVar3 + 0x308),(int)DAT_00491d68 / 100 + 0x33);
  }
  iVar3 = FUN_004491c0(*(undefined4 *)(unaff_EDI + 0x2c8),(int)pvVar1,
                       *(undefined4 *)(unaff_EDI + 0x2c8));
  if (iVar3 == 0) {
    *(undefined4 *)(unaff_EDI + 0x2c8) = 0;
  }
  for (piVar2 = (int *)(iVar3 + 0x10); piVar2 != (int *)0x0; piVar2 = (int *)piVar2[1]) {
    if (*(short *)(*piVar2 + 0x38a) == 0x26) {
      iVar3 = *(int *)*piVar2;
      goto LAB_0042e6d9;
    }
  }
  iVar3 = 0;
LAB_0042e6d9:
  iVar3 = FUN_004491c0(0x26,(int)pvVar1,iVar3);
  if (iVar3 != 0) {
    FUN_0043e5a0(*(int *)(iVar3 + 0x308),((int)DAT_00491d68 / 10) % 10 + 0x33);
  }
  iVar3 = FUN_004491c0(*(undefined4 *)(unaff_EDI + 0x2c8),(int)pvVar1,
                       *(undefined4 *)(unaff_EDI + 0x2c8));
  if (iVar3 == 0) {
    *(undefined4 *)(unaff_EDI + 0x2c8) = 0;
  }
  piVar2 = (int *)(iVar3 + 0x10);
  uVar4 = extraout_ECX_00;
  if (piVar2 != (int *)0x0) {
    uVar4 = 0x27;
    do {
      if (*(short *)(*piVar2 + 0x38a) == 0x27) {
        iVar3 = *(int *)*piVar2;
        goto LAB_0042e758;
      }
      piVar2 = (int *)piVar2[1];
    } while (piVar2 != (int *)0x0);
  }
  iVar3 = 0;
LAB_0042e758:
  iVar3 = FUN_004491c0(uVar4,(int)pvVar1,iVar3);
  if (iVar3 != 0) {
    FUN_0043e5a0(*(int *)(iVar3 + 0x308),(int)DAT_00491d68 % 10 + 0x33);
  }
  iVar3 = FUN_004491c0(*(undefined4 *)(unaff_EDI + 0x2c8),(int)pvVar1,
                       *(undefined4 *)(unaff_EDI + 0x2c8));
  if (iVar3 == 0) {
    *(undefined4 *)(unaff_EDI + 0x2c8) = 0;
  }
  for (piVar2 = (int *)(iVar3 + 0x10); piVar2 != (int *)0x0; piVar2 = (int *)piVar2[1]) {
    if (*(short *)(*piVar2 + 0x38a) == 0x29) {
      iVar3 = *(int *)*piVar2;
      goto LAB_0042e7c8;
    }
  }
  iVar3 = 0;
LAB_0042e7c8:
  iVar3 = FUN_004491c0(extraout_ECX_01,(int)pvVar1,iVar3);
  if (iVar3 != 0) {
    FUN_0043e5a0(*(int *)(iVar3 + 0x308),(int)DAT_00491d68 / 100 + 0x3d);
  }
  iVar3 = FUN_004491c0(*(undefined4 *)(unaff_EDI + 0x2c8),(int)pvVar1,
                       *(undefined4 *)(unaff_EDI + 0x2c8));
  if (iVar3 == 0) {
    *(undefined4 *)(unaff_EDI + 0x2c8) = 0;
  }
  for (piVar2 = (int *)(iVar3 + 0x10); piVar2 != (int *)0x0; piVar2 = (int *)piVar2[1]) {
    if (*(short *)(*piVar2 + 0x38a) == 0x2a) {
      iVar3 = *(int *)*piVar2;
      goto LAB_0042e839;
    }
  }
  iVar3 = 0;
LAB_0042e839:
  iVar3 = FUN_004491c0(0x2a,(int)pvVar1,iVar3);
  if (iVar3 != 0) {
    FUN_0043e5a0(*(int *)(iVar3 + 0x308),((int)DAT_00491d68 / 10) % 10 + 0x3d);
  }
  iVar3 = FUN_004491c0(*(undefined4 *)(unaff_EDI + 0x2c8),(int)pvVar1,
                       *(undefined4 *)(unaff_EDI + 0x2c8));
  if (iVar3 == 0) {
    *(undefined4 *)(unaff_EDI + 0x2c8) = 0;
  }
  piVar2 = (int *)(iVar3 + 0x10);
  uVar4 = extraout_ECX_02;
  if (piVar2 != (int *)0x0) {
    uVar4 = 0x2b;
    do {
      if (*(short *)(*piVar2 + 0x38a) == 0x2b) {
        iVar3 = *(int *)*piVar2;
        goto LAB_0042e8b8;
      }
      piVar2 = (int *)piVar2[1];
    } while (piVar2 != (int *)0x0);
  }
  iVar3 = 0;
LAB_0042e8b8:
  iVar3 = FUN_004491c0(uVar4,(int)pvVar1,iVar3);
  if (iVar3 != 0) {
    FUN_0043e5a0(*(int *)(iVar3 + 0x308),(int)DAT_00491d68 % 10 + 0x3d);
  }
  iVar3 = FUN_004491c0(*(undefined4 *)(unaff_EDI + 0x2c8),(int)pvVar1,
                       *(undefined4 *)(unaff_EDI + 0x2c8));
  if (iVar3 == 0) {
    *(undefined4 *)(unaff_EDI + 0x2c8) = 0;
  }
  for (piVar2 = (int *)(iVar3 + 0x10); piVar2 != (int *)0x0; piVar2 = (int *)piVar2[1]) {
    if (*(short *)(*piVar2 + 0x38a) == 0x2d) {
      iVar3 = *(int *)*piVar2;
      goto LAB_0042e928;
    }
  }
  iVar3 = 0;
LAB_0042e928:
  iVar3 = FUN_004491c0(0x2d,(int)pvVar1,iVar3);
  if (iVar3 != 0) {
    FUN_0043e5a0(*(int *)(iVar3 + 0x308),(int)DAT_00491d69 / 100 + 0x33);
  }
  iVar3 = FUN_004491c0(*(undefined4 *)(unaff_EDI + 0x2c8),(int)pvVar1,
                       *(undefined4 *)(unaff_EDI + 0x2c8));
  if (iVar3 == 0) {
    *(undefined4 *)(unaff_EDI + 0x2c8) = 0;
  }
  for (piVar2 = (int *)(iVar3 + 0x10); piVar2 != (int *)0x0; piVar2 = (int *)piVar2[1]) {
    if (*(short *)(*piVar2 + 0x38a) == 0x2e) {
      iVar3 = *(int *)*piVar2;
      goto LAB_0042e999;
    }
  }
  iVar3 = 0;
LAB_0042e999:
  iVar3 = FUN_004491c0(0x2e,(int)pvVar1,iVar3);
  if (iVar3 != 0) {
    FUN_0043e5a0(*(int *)(iVar3 + 0x308),((int)DAT_00491d69 / 10) % 10 + 0x33);
  }
  iVar3 = FUN_004491c0(*(undefined4 *)(unaff_EDI + 0x2c8),(int)pvVar1,
                       *(undefined4 *)(unaff_EDI + 0x2c8));
  if (iVar3 == 0) {
    *(undefined4 *)(unaff_EDI + 0x2c8) = 0;
  }
  piVar2 = (int *)(iVar3 + 0x10);
  uVar4 = extraout_ECX_03;
  if (piVar2 != (int *)0x0) {
    uVar4 = 0x2f;
    do {
      if (*(short *)(*piVar2 + 0x38a) == 0x2f) {
        iVar3 = *(int *)*piVar2;
        goto LAB_0042ea18;
      }
      piVar2 = (int *)piVar2[1];
    } while (piVar2 != (int *)0x0);
  }
  iVar3 = 0;
LAB_0042ea18:
  iVar3 = FUN_004491c0(uVar4,(int)pvVar1,iVar3);
  if (iVar3 != 0) {
    FUN_0043e5a0(*(int *)(iVar3 + 0x308),(int)DAT_00491d69 % 10 + 0x33);
  }
  iVar3 = FUN_004491c0(*(undefined4 *)(unaff_EDI + 0x2c8),(int)pvVar1,
                       *(undefined4 *)(unaff_EDI + 0x2c8));
  if (iVar3 == 0) {
    *(undefined4 *)(unaff_EDI + 0x2c8) = 0;
  }
  for (piVar2 = (int *)(iVar3 + 0x10); piVar2 != (int *)0x0; piVar2 = (int *)piVar2[1]) {
    if (*(short *)(*piVar2 + 0x38a) == 0x31) {
      iVar3 = *(int *)*piVar2;
      goto LAB_0042ea88;
    }
  }
  iVar3 = 0;
LAB_0042ea88:
  iVar3 = FUN_004491c0(0x31,(int)pvVar1,iVar3);
  if (iVar3 != 0) {
    FUN_0043e5a0(*(int *)(iVar3 + 0x308),(int)DAT_00491d69 / 100 + 0x3d);
  }
  iVar3 = FUN_004491c0(*(undefined4 *)(unaff_EDI + 0x2c8),(int)pvVar1,
                       *(undefined4 *)(unaff_EDI + 0x2c8));
  if (iVar3 == 0) {
    *(undefined4 *)(unaff_EDI + 0x2c8) = 0;
  }
  for (piVar2 = (int *)(iVar3 + 0x10); piVar2 != (int *)0x0; piVar2 = (int *)piVar2[1]) {
    if (*(short *)(*piVar2 + 0x38a) == 0x32) {
      iVar3 = *(int *)*piVar2;
      goto LAB_0042eaf9;
    }
  }
  iVar3 = 0;
LAB_0042eaf9:
  iVar3 = FUN_004491c0(0x32,(int)pvVar1,iVar3);
  if (iVar3 != 0) {
    FUN_0043e5a0(*(int *)(iVar3 + 0x308),((int)DAT_00491d69 / 10) % 10 + 0x3d);
  }
  iVar3 = FUN_004491c0(*(undefined4 *)(unaff_EDI + 0x2c8),(int)pvVar1,
                       *(undefined4 *)(unaff_EDI + 0x2c8));
  if (iVar3 == 0) {
    *(undefined4 *)(unaff_EDI + 0x2c8) = 0;
  }
  piVar2 = (int *)(iVar3 + 0x10);
  uVar4 = extraout_ECX_04;
  if (piVar2 != (int *)0x0) {
    uVar4 = 0x33;
    do {
      if (*(short *)(*piVar2 + 0x38a) == 0x33) {
        iVar3 = *(int *)*piVar2;
        goto LAB_0042eb78;
      }
      piVar2 = (int *)piVar2[1];
    } while (piVar2 != (int *)0x0);
  }
  iVar3 = 0;
LAB_0042eb78:
  iVar3 = FUN_004491c0(uVar4,(int)pvVar1,iVar3);
  if (iVar3 != 0) {
    FUN_0043e5a0(*(int *)(iVar3 + 0x308),(int)DAT_00491d69 % 10 + 0x3d);
  }
  uVar4 = *(undefined4 *)(unaff_EDI + 0x2c8);
  if ('\t' < DAT_00491d68) {
    if (DAT_00491d68 < 'd') {
      iVar3 = FUN_004491c0(uVar4,(int)pvVar1,uVar4);
      if (iVar3 == 0) {
        *(undefined4 *)(unaff_EDI + 0x2c8) = 0;
      }
      piVar2 = (int *)(iVar3 + 0x10);
      uVar4 = extraout_ECX_09;
      if (piVar2 != (int *)0x0) {
        uVar4 = 0x25;
        do {
          if (*(short *)(*piVar2 + 0x38a) == 0x25) {
            iVar3 = *(int *)*piVar2;
            goto LAB_0042edf8;
          }
          piVar2 = (int *)piVar2[1];
        } while (piVar2 != (int *)0x0);
      }
      iVar3 = 0;
LAB_0042edf8:
      iVar3 = FUN_004491c0(uVar4,(int)pvVar1,iVar3);
      *(uint *)(iVar3 + 0x35c) = *(uint *)(iVar3 + 0x35c) & 0xfffffffd;
      iVar3 = FUN_004491c0(*(undefined4 *)(unaff_EDI + 0x2c8),(int)pvVar1,
                           *(undefined4 *)(unaff_EDI + 0x2c8));
      if (iVar3 == 0) {
        *(undefined4 *)(unaff_EDI + 0x2c8) = 0;
      }
      piVar2 = (int *)(iVar3 + 0x10);
      uVar4 = extraout_ECX_10;
      if (piVar2 != (int *)0x0) {
        uVar4 = 0x26;
        do {
          if (*(short *)(*piVar2 + 0x38a) == 0x26) {
            iVar3 = *(int *)*piVar2;
            goto LAB_0042ee58;
          }
          piVar2 = (int *)piVar2[1];
        } while (piVar2 != (int *)0x0);
      }
      iVar3 = 0;
LAB_0042ee58:
      iVar3 = FUN_004491c0(uVar4,(int)pvVar1,iVar3);
      *(uint *)(iVar3 + 0x35c) = *(uint *)(iVar3 + 0x35c) | 2;
      iVar3 = FUN_004491c0(*(undefined4 *)(unaff_EDI + 0x2c8),(int)pvVar1,
                           *(undefined4 *)(unaff_EDI + 0x2c8));
      if (iVar3 == 0) {
        *(undefined4 *)(unaff_EDI + 0x2c8) = 0;
      }
      for (piVar2 = (int *)(iVar3 + 0x10); piVar2 != (int *)0x0; piVar2 = (int *)piVar2[1]) {
        if (*(short *)(*piVar2 + 0x38a) == 0x29) {
          iVar3 = *(int *)*piVar2;
          goto LAB_0042eea4;
        }
      }
      iVar3 = 0;
LAB_0042eea4:
      iVar3 = FUN_004491c0(extraout_ECX_11,(int)pvVar1,iVar3);
      *(uint *)(iVar3 + 0x35c) = *(uint *)(iVar3 + 0x35c) & 0xfffffffd;
      iVar3 = FUN_004491c0(*(undefined4 *)(unaff_EDI + 0x2c8),(int)pvVar1,
                           *(undefined4 *)(unaff_EDI + 0x2c8));
      if (iVar3 == 0) {
        *(undefined4 *)(unaff_EDI + 0x2c8) = 0;
      }
      piVar2 = (int *)(iVar3 + 0x10);
      uVar4 = extraout_ECX_12;
      if (piVar2 != (int *)0x0) {
        uVar4 = 0x2a;
        do {
          if (*(short *)(*piVar2 + 0x38a) == 0x2a) goto LAB_0042ef13;
          piVar2 = (int *)piVar2[1];
        } while (piVar2 != (int *)0x0);
      }
    }
    else {
      iVar3 = FUN_004491c0(uVar4,(int)pvVar1,uVar4);
      if (iVar3 == 0) {
        *(undefined4 *)(unaff_EDI + 0x2c8) = 0;
      }
      piVar2 = (int *)(iVar3 + 0x10);
      uVar4 = extraout_ECX_13;
      if (piVar2 != (int *)0x0) {
        uVar4 = 0x25;
        do {
          if (*(short *)(*piVar2 + 0x38a) == 0x25) {
            iVar3 = *(int *)*piVar2;
            goto LAB_0042ef58;
          }
          piVar2 = (int *)piVar2[1];
        } while (piVar2 != (int *)0x0);
      }
      iVar3 = 0;
LAB_0042ef58:
      iVar3 = FUN_004491c0(uVar4,(int)pvVar1,iVar3);
      *(uint *)(iVar3 + 0x35c) = *(uint *)(iVar3 + 0x35c) | 2;
      iVar3 = FUN_004491c0(*(undefined4 *)(unaff_EDI + 0x2c8),(int)pvVar1,
                           *(undefined4 *)(unaff_EDI + 0x2c8));
      if (iVar3 == 0) {
        *(undefined4 *)(unaff_EDI + 0x2c8) = 0;
      }
      piVar2 = (int *)(iVar3 + 0x10);
      uVar4 = extraout_ECX_14;
      if (piVar2 != (int *)0x0) {
        uVar4 = 0x26;
        do {
          if (*(short *)(*piVar2 + 0x38a) == 0x26) {
            iVar3 = *(int *)*piVar2;
            goto LAB_0042efb8;
          }
          piVar2 = (int *)piVar2[1];
        } while (piVar2 != (int *)0x0);
      }
      iVar3 = 0;
LAB_0042efb8:
      iVar3 = FUN_004491c0(uVar4,(int)pvVar1,iVar3);
      *(uint *)(iVar3 + 0x35c) = *(uint *)(iVar3 + 0x35c) | 2;
      iVar3 = FUN_004491c0(*(undefined4 *)(unaff_EDI + 0x2c8),(int)pvVar1,
                           *(undefined4 *)(unaff_EDI + 0x2c8));
      if (iVar3 == 0) {
        *(undefined4 *)(unaff_EDI + 0x2c8) = 0;
      }
      for (piVar2 = (int *)(iVar3 + 0x10); piVar2 != (int *)0x0; piVar2 = (int *)piVar2[1]) {
        if (*(short *)(*piVar2 + 0x38a) == 0x29) {
          iVar3 = *(int *)*piVar2;
          goto LAB_0042f008;
        }
      }
      iVar3 = 0;
LAB_0042f008:
      iVar3 = FUN_004491c0(extraout_ECX_15,(int)pvVar1,iVar3);
      *(uint *)(iVar3 + 0x35c) = *(uint *)(iVar3 + 0x35c) | 2;
      iVar3 = FUN_004491c0(*(undefined4 *)(unaff_EDI + 0x2c8),(int)pvVar1,
                           *(undefined4 *)(unaff_EDI + 0x2c8));
      if (iVar3 == 0) {
        *(undefined4 *)(unaff_EDI + 0x2c8) = 0;
      }
      piVar2 = (int *)(iVar3 + 0x10);
      uVar4 = extraout_ECX_16;
      if (piVar2 != (int *)0x0) {
        uVar4 = 0x2a;
        do {
          if (*(short *)(*piVar2 + 0x38a) == 0x2a) goto LAB_0042ef13;
          piVar2 = (int *)piVar2[1];
        } while (piVar2 != (int *)0x0);
      }
    }
    iVar3 = 0;
    goto LAB_0042f068;
  }
  iVar3 = FUN_004491c0(uVar4,(int)pvVar1,uVar4);
  if (iVar3 == 0) {
    *(undefined4 *)(unaff_EDI + 0x2c8) = 0;
  }
  piVar2 = (int *)(iVar3 + 0x10);
  uVar4 = extraout_ECX_05;
  if (piVar2 != (int *)0x0) {
    uVar4 = 0x25;
    do {
      if (*(short *)(*piVar2 + 0x38a) == 0x25) {
        iVar3 = *(int *)*piVar2;
        goto LAB_0042ebf8;
      }
      piVar2 = (int *)piVar2[1];
    } while (piVar2 != (int *)0x0);
  }
  iVar3 = 0;
LAB_0042ebf8:
  iVar3 = FUN_004491c0(uVar4,(int)pvVar1,iVar3);
  *(uint *)(iVar3 + 0x35c) = *(uint *)(iVar3 + 0x35c) & 0xfffffffd;
  iVar3 = FUN_004491c0(*(undefined4 *)(unaff_EDI + 0x2c8),(int)pvVar1,
                       *(undefined4 *)(unaff_EDI + 0x2c8));
  if (iVar3 == 0) {
    *(undefined4 *)(unaff_EDI + 0x2c8) = 0;
  }
  piVar2 = (int *)(iVar3 + 0x10);
  uVar4 = extraout_ECX_06;
  if (piVar2 != (int *)0x0) {
    uVar4 = 0x26;
    do {
      if (*(short *)(*piVar2 + 0x38a) == 0x26) {
        iVar3 = *(int *)*piVar2;
        goto LAB_0042ec58;
      }
      piVar2 = (int *)piVar2[1];
    } while (piVar2 != (int *)0x0);
  }
  iVar3 = 0;
LAB_0042ec58:
  iVar3 = FUN_004491c0(uVar4,(int)pvVar1,iVar3);
  *(uint *)(iVar3 + 0x35c) = *(uint *)(iVar3 + 0x35c) & 0xfffffffd;
  iVar3 = FUN_004491c0(*(undefined4 *)(unaff_EDI + 0x2c8),(int)pvVar1,
                       *(undefined4 *)(unaff_EDI + 0x2c8));
  if (iVar3 == 0) {
    *(undefined4 *)(unaff_EDI + 0x2c8) = 0;
  }
  for (piVar2 = (int *)(iVar3 + 0x10); piVar2 != (int *)0x0; piVar2 = (int *)piVar2[1]) {
    if (*(short *)(*piVar2 + 0x38a) == 0x29) {
      iVar3 = *(int *)*piVar2;
      goto LAB_0042eca8;
    }
  }
  iVar3 = 0;
LAB_0042eca8:
  iVar3 = FUN_004491c0(extraout_ECX_07,(int)pvVar1,iVar3);
  *(uint *)(iVar3 + 0x35c) = *(uint *)(iVar3 + 0x35c) & 0xfffffffd;
  iVar3 = FUN_004491c0(*(undefined4 *)(unaff_EDI + 0x2c8),(int)pvVar1,
                       *(undefined4 *)(unaff_EDI + 0x2c8));
  if (iVar3 == 0) {
    *(undefined4 *)(unaff_EDI + 0x2c8) = 0;
  }
  piVar2 = (int *)(iVar3 + 0x10);
  uVar4 = extraout_ECX_08;
  if (piVar2 != (int *)0x0) {
    uVar4 = 0x2a;
    do {
      if (*(short *)(*piVar2 + 0x38a) == 0x2a) {
        iVar3 = *(int *)*piVar2;
        goto LAB_0042ed08;
      }
      piVar2 = (int *)piVar2[1];
    } while (piVar2 != (int *)0x0);
  }
  iVar3 = 0;
LAB_0042ed08:
  iVar3 = FUN_004491c0(uVar4,(int)pvVar1,iVar3);
  uVar5 = *(uint *)(iVar3 + 0x35c) & 0xfffffffd;
LAB_0042f07e:
  *(uint *)(iVar3 + 0x35c) = uVar5;
  uVar4 = *(undefined4 *)(unaff_EDI + 0x2c8);
  if (DAT_00491d69 < '\n') {
    iVar3 = FUN_004491c0(uVar4,(int)pvVar1,uVar4);
    if (iVar3 == 0) {
      *(undefined4 *)(unaff_EDI + 0x2c8) = 0;
    }
    piVar2 = (int *)(iVar3 + 0x10);
    uVar4 = extraout_ECX_17;
    if (piVar2 != (int *)0x0) {
      uVar4 = 0x2d;
      do {
        if (*(short *)(*piVar2 + 0x38a) == 0x2d) {
          iVar3 = *(int *)*piVar2;
          goto LAB_0042f0c9;
        }
        piVar2 = (int *)piVar2[1];
      } while (piVar2 != (int *)0x0);
    }
    iVar3 = 0;
LAB_0042f0c9:
    iVar3 = FUN_004491c0(uVar4,(int)pvVar1,iVar3);
    *(uint *)(iVar3 + 0x35c) = *(uint *)(iVar3 + 0x35c) & 0xfffffffd;
    iVar3 = FUN_004491c0(*(undefined4 *)(unaff_EDI + 0x2c8),(int)pvVar1,
                         *(undefined4 *)(unaff_EDI + 0x2c8));
    if (iVar3 == 0) {
      *(undefined4 *)(unaff_EDI + 0x2c8) = 0;
    }
    piVar2 = (int *)(iVar3 + 0x10);
    uVar4 = extraout_ECX_18;
    if (piVar2 != (int *)0x0) {
      uVar4 = 0x2e;
      do {
        if (*(short *)(*piVar2 + 0x38a) == 0x2e) {
          iVar3 = *(int *)*piVar2;
          goto LAB_0042f128;
        }
        piVar2 = (int *)piVar2[1];
      } while (piVar2 != (int *)0x0);
    }
    iVar3 = 0;
LAB_0042f128:
    iVar3 = FUN_004491c0(uVar4,(int)pvVar1,iVar3);
    *(uint *)(iVar3 + 0x35c) = *(uint *)(iVar3 + 0x35c) & 0xfffffffd;
    iVar3 = FUN_004491c0(*(undefined4 *)(unaff_EDI + 0x2c8),(int)pvVar1,
                         *(undefined4 *)(unaff_EDI + 0x2c8));
    if (iVar3 == 0) {
      *(undefined4 *)(unaff_EDI + 0x2c8) = 0;
    }
    piVar2 = (int *)(iVar3 + 0x10);
    uVar4 = extraout_ECX_19;
    if (piVar2 != (int *)0x0) {
      uVar4 = 0x31;
      do {
        if (*(short *)(*piVar2 + 0x38a) == 0x31) {
          iVar3 = *(int *)*piVar2;
          goto LAB_0042f188;
        }
        piVar2 = (int *)piVar2[1];
      } while (piVar2 != (int *)0x0);
    }
    iVar3 = 0;
LAB_0042f188:
    iVar3 = FUN_004491c0(uVar4,(int)pvVar1,iVar3);
    *(uint *)(iVar3 + 0x35c) = *(uint *)(iVar3 + 0x35c) & 0xfffffffd;
    iVar3 = FUN_004491c0(*(undefined4 *)(unaff_EDI + 0x2c8),(int)pvVar1,
                         *(undefined4 *)(unaff_EDI + 0x2c8));
    if (iVar3 == 0) {
      *(undefined4 *)(unaff_EDI + 0x2c8) = 0;
    }
    piVar2 = (int *)(iVar3 + 0x10);
    uVar4 = extraout_ECX_20;
    if (piVar2 != (int *)0x0) {
      uVar4 = 0x32;
      do {
        if (*(short *)(*piVar2 + 0x38a) == 0x32) {
          iVar3 = *(int *)*piVar2;
          goto LAB_0042f1d8;
        }
        piVar2 = (int *)piVar2[1];
      } while (piVar2 != (int *)0x0);
    }
    iVar3 = 0;
LAB_0042f1d8:
    iVar3 = FUN_004491c0(uVar4,(int)pvVar1,iVar3);
    *(uint *)(iVar3 + 0x35c) = *(uint *)(iVar3 + 0x35c) & 0xfffffffd;
    return;
  }
  if (DAT_00491d69 < 'd') {
    iVar3 = FUN_004491c0(uVar4,(int)pvVar1,uVar4);
    if (iVar3 == 0) {
      *(undefined4 *)(unaff_EDI + 0x2c8) = 0;
    }
    piVar2 = (int *)(iVar3 + 0x10);
    uVar4 = extraout_ECX_21;
    if (piVar2 != (int *)0x0) {
      uVar4 = 0x2d;
      do {
        if (*(short *)(*piVar2 + 0x38a) == 0x2d) {
          iVar3 = *(int *)*piVar2;
          goto LAB_0042f278;
        }
        piVar2 = (int *)piVar2[1];
      } while (piVar2 != (int *)0x0);
    }
    iVar3 = 0;
LAB_0042f278:
    iVar3 = FUN_004491c0(uVar4,(int)pvVar1,iVar3);
    *(uint *)(iVar3 + 0x35c) = *(uint *)(iVar3 + 0x35c) & 0xfffffffd;
    iVar3 = FUN_004491c0(*(undefined4 *)(unaff_EDI + 0x2c8),(int)pvVar1,
                         *(undefined4 *)(unaff_EDI + 0x2c8));
    if (iVar3 == 0) {
      *(undefined4 *)(unaff_EDI + 0x2c8) = 0;
    }
    piVar2 = (int *)(iVar3 + 0x10);
    uVar4 = extraout_ECX_22;
    if (piVar2 != (int *)0x0) {
      uVar4 = 0x2e;
      do {
        if (*(short *)(*piVar2 + 0x38a) == 0x2e) {
          iVar3 = *(int *)*piVar2;
          goto LAB_0042f2d8;
        }
        piVar2 = (int *)piVar2[1];
      } while (piVar2 != (int *)0x0);
    }
    iVar3 = 0;
LAB_0042f2d8:
    iVar3 = FUN_004491c0(uVar4,(int)pvVar1,iVar3);
    *(uint *)(iVar3 + 0x35c) = *(uint *)(iVar3 + 0x35c) | 2;
    iVar3 = FUN_004491c0(*(undefined4 *)(unaff_EDI + 0x2c8),(int)pvVar1,
                         *(undefined4 *)(unaff_EDI + 0x2c8));
    if (iVar3 == 0) {
      *(undefined4 *)(unaff_EDI + 0x2c8) = 0;
    }
    piVar2 = (int *)(iVar3 + 0x10);
    uVar4 = extraout_ECX_23;
    if (piVar2 != (int *)0x0) {
      uVar4 = 0x31;
      do {
        if (*(short *)(*piVar2 + 0x38a) == 0x31) {
          iVar3 = *(int *)*piVar2;
          goto LAB_0042f328;
        }
        piVar2 = (int *)piVar2[1];
      } while (piVar2 != (int *)0x0);
    }
    iVar3 = 0;
LAB_0042f328:
    iVar3 = FUN_004491c0(uVar4,(int)pvVar1,iVar3);
    *(uint *)(iVar3 + 0x35c) = *(uint *)(iVar3 + 0x35c) & 0xfffffffd;
    iVar3 = FUN_004491c0(*(undefined4 *)(unaff_EDI + 0x2c8),(int)pvVar1,
                         *(undefined4 *)(unaff_EDI + 0x2c8));
    if (iVar3 == 0) {
      *(undefined4 *)(unaff_EDI + 0x2c8) = 0;
    }
    piVar2 = (int *)(iVar3 + 0x10);
    uVar4 = extraout_ECX_24;
    if (piVar2 != (int *)0x0) {
      uVar4 = 0x32;
      do {
        if (*(short *)(*piVar2 + 0x38a) == 0x32) goto LAB_0042f39f;
        piVar2 = (int *)piVar2[1];
      } while (piVar2 != (int *)0x0);
    }
  }
  else {
    iVar3 = FUN_004491c0(uVar4,(int)pvVar1,uVar4);
    if (iVar3 == 0) {
      *(undefined4 *)(unaff_EDI + 0x2c8) = 0;
    }
    piVar2 = (int *)(iVar3 + 0x10);
    uVar4 = extraout_ECX_25;
    if (piVar2 != (int *)0x0) {
      uVar4 = 0x2d;
      do {
        if (*(short *)(*piVar2 + 0x38a) == 0x2d) {
          iVar3 = *(int *)*piVar2;
          goto LAB_0042f3e8;
        }
        piVar2 = (int *)piVar2[1];
      } while (piVar2 != (int *)0x0);
    }
    iVar3 = 0;
LAB_0042f3e8:
    iVar3 = FUN_004491c0(uVar4,(int)pvVar1,iVar3);
    *(uint *)(iVar3 + 0x35c) = *(uint *)(iVar3 + 0x35c) | 2;
    iVar3 = FUN_004491c0(*(undefined4 *)(unaff_EDI + 0x2c8),(int)pvVar1,
                         *(undefined4 *)(unaff_EDI + 0x2c8));
    if (iVar3 == 0) {
      *(undefined4 *)(unaff_EDI + 0x2c8) = 0;
    }
    piVar2 = (int *)(iVar3 + 0x10);
    uVar4 = extraout_ECX_26;
    if (piVar2 != (int *)0x0) {
      uVar4 = 0x2e;
      do {
        if (*(short *)(*piVar2 + 0x38a) == 0x2e) {
          iVar3 = *(int *)*piVar2;
          goto LAB_0042f448;
        }
        piVar2 = (int *)piVar2[1];
      } while (piVar2 != (int *)0x0);
    }
    iVar3 = 0;
LAB_0042f448:
    iVar3 = FUN_004491c0(uVar4,(int)pvVar1,iVar3);
    *(uint *)(iVar3 + 0x35c) = *(uint *)(iVar3 + 0x35c) | 2;
    iVar3 = FUN_004491c0(*(undefined4 *)(unaff_EDI + 0x2c8),(int)pvVar1,
                         *(undefined4 *)(unaff_EDI + 0x2c8));
    if (iVar3 == 0) {
      *(undefined4 *)(unaff_EDI + 0x2c8) = 0;
    }
    piVar2 = (int *)(iVar3 + 0x10);
    uVar4 = extraout_ECX_27;
    if (piVar2 != (int *)0x0) {
      uVar4 = 0x31;
      do {
        if (*(short *)(*piVar2 + 0x38a) == 0x31) {
          iVar3 = *(int *)*piVar2;
          goto LAB_0042f4a8;
        }
        piVar2 = (int *)piVar2[1];
      } while (piVar2 != (int *)0x0);
    }
    iVar3 = 0;
LAB_0042f4a8:
    iVar3 = FUN_004491c0(uVar4,(int)pvVar1,iVar3);
    *(uint *)(iVar3 + 0x35c) = *(uint *)(iVar3 + 0x35c) | 2;
    iVar3 = FUN_004491c0(*(undefined4 *)(unaff_EDI + 0x2c8),(int)pvVar1,
                         *(undefined4 *)(unaff_EDI + 0x2c8));
    if (iVar3 == 0) {
      *(undefined4 *)(unaff_EDI + 0x2c8) = 0;
    }
    piVar2 = (int *)(iVar3 + 0x10);
    uVar4 = extraout_ECX_28;
    if (piVar2 != (int *)0x0) {
      uVar4 = 0x32;
      do {
        if (*(short *)(*piVar2 + 0x38a) == 0x32) goto LAB_0042f39f;
        piVar2 = (int *)piVar2[1];
      } while (piVar2 != (int *)0x0);
    }
  }
  iVar3 = 0;
LAB_0042f508:
  iVar3 = FUN_004491c0(uVar4,(int)pvVar1,iVar3);
  *(uint *)(iVar3 + 0x35c) = *(uint *)(iVar3 + 0x35c) | 2;
  return;
LAB_0042ef13:
  uVar4 = 0x2a;
  iVar3 = *(int *)*piVar2;
LAB_0042f068:
  iVar3 = FUN_004491c0(uVar4,(int)pvVar1,iVar3);
  uVar5 = *(uint *)(iVar3 + 0x35c) | 2;
  goto LAB_0042f07e;
LAB_0042f39f:
  uVar4 = 0x32;
  iVar3 = *(int *)*piVar2;
  goto LAB_0042f508;
}

