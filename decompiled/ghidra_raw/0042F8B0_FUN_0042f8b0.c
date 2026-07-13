/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x0042F8B0
 * Tracking name: FUN_0042f8b0
 * Ghidra name: FUN_0042f8b0
 * Tracked span: 2464 bytes
 */


void __fastcall FUN_0042f8b0(undefined4 param_1)

{
  void *pvVar1;
  int in_EAX;
  int iVar2;
  int *piVar3;
  undefined4 extraout_ECX;
  undefined4 uVar4;
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
  undefined4 extraout_ECX_18;
  
  pvVar1 = g_pGameStateManager;
  iVar2 = FUN_004491c0(param_1,(int)g_pGameStateManager,*(int *)(in_EAX + 0x2cc));
  if (iVar2 == 0) {
    *(undefined4 *)(in_EAX + 0x2cc) = 0;
  }
  piVar3 = (int *)(iVar2 + 0x10);
  uVar4 = extraout_ECX;
  if (piVar3 != (int *)0x0) {
    uVar4 = 0x43;
    do {
      if (*(short *)(*piVar3 + 0x38a) == 0x43) {
        iVar2 = *(int *)*piVar3;
        goto LAB_0042f8f9;
      }
      piVar3 = (int *)piVar3[1];
    } while (piVar3 != (int *)0x0);
  }
  iVar2 = 0;
LAB_0042f8f9:
  iVar2 = FUN_004491c0(uVar4,(int)pvVar1,iVar2);
  if (iVar2 != 0) {
    FUN_0043e5a0(*(int *)(iVar2 + 0x308),(int)*(short *)(in_EAX + 0x59cc) / 10 + 0x33);
  }
  iVar2 = FUN_004491c0(*(undefined4 *)(in_EAX + 0x2cc),(int)pvVar1,*(undefined4 *)(in_EAX + 0x2cc));
  if (iVar2 == 0) {
    *(undefined4 *)(in_EAX + 0x2cc) = 0;
  }
  piVar3 = (int *)(iVar2 + 0x10);
  uVar4 = extraout_ECX_00;
  if (piVar3 != (int *)0x0) {
    uVar4 = 0x44;
    do {
      if (*(short *)(*piVar3 + 0x38a) == 0x44) {
        iVar2 = *(int *)*piVar3;
        goto LAB_0042f978;
      }
      piVar3 = (int *)piVar3[1];
    } while (piVar3 != (int *)0x0);
  }
  iVar2 = 0;
LAB_0042f978:
  iVar2 = FUN_004491c0(uVar4,(int)pvVar1,iVar2);
  if (iVar2 != 0) {
    FUN_0043e5a0(*(int *)(iVar2 + 0x308),(int)*(short *)(in_EAX + 0x59cc) % 10 + 0x33);
  }
  iVar2 = FUN_004491c0(*(undefined4 *)(in_EAX + 0x2cc),(int)pvVar1,*(undefined4 *)(in_EAX + 0x2cc));
  if (iVar2 == 0) {
    *(undefined4 *)(in_EAX + 0x2cc) = 0;
  }
  piVar3 = (int *)(iVar2 + 0x10);
  uVar4 = extraout_ECX_01;
  if (piVar3 != (int *)0x0) {
    uVar4 = 0x4d;
    do {
      if (*(short *)(*piVar3 + 0x38a) == 0x4d) {
        iVar2 = *(int *)*piVar3;
        goto LAB_0042f9e8;
      }
      piVar3 = (int *)piVar3[1];
    } while (piVar3 != (int *)0x0);
  }
  iVar2 = 0;
LAB_0042f9e8:
  iVar2 = FUN_004491c0(uVar4,(int)pvVar1,iVar2);
  if (iVar2 != 0) {
    FUN_0043e5a0(*(int *)(iVar2 + 0x308),(int)*(short *)(in_EAX + 0x59cc) / 10 + 0x33);
  }
  iVar2 = FUN_004491c0(*(undefined4 *)(in_EAX + 0x2cc),(int)pvVar1,*(undefined4 *)(in_EAX + 0x2cc));
  if (iVar2 == 0) {
    *(undefined4 *)(in_EAX + 0x2cc) = 0;
  }
  piVar3 = (int *)(iVar2 + 0x10);
  uVar4 = extraout_ECX_02;
  if (piVar3 != (int *)0x0) {
    uVar4 = 0x4e;
    do {
      if (*(short *)(*piVar3 + 0x38a) == 0x4e) {
        iVar2 = *(int *)*piVar3;
        goto LAB_0042fa59;
      }
      piVar3 = (int *)piVar3[1];
    } while (piVar3 != (int *)0x0);
  }
  iVar2 = 0;
LAB_0042fa59:
  iVar2 = FUN_004491c0(uVar4,(int)pvVar1,iVar2);
  if (iVar2 != 0) {
    FUN_0043e5a0(*(int *)(iVar2 + 0x308),(int)*(short *)(in_EAX + 0x59cc) % 10 + 0x33);
  }
  iVar2 = FUN_004491c0(*(undefined4 *)(in_EAX + 0x2cc),(int)pvVar1,*(undefined4 *)(in_EAX + 0x2cc));
  if (iVar2 == 0) {
    *(undefined4 *)(in_EAX + 0x2cc) = 0;
  }
  piVar3 = (int *)(iVar2 + 0x10);
  uVar4 = extraout_ECX_03;
  if (piVar3 != (int *)0x0) {
    uVar4 = 0x45;
    do {
      if (*(short *)(*piVar3 + 0x38a) == 0x45) {
        iVar2 = *(int *)*piVar3;
        goto LAB_0042fac8;
      }
      piVar3 = (int *)piVar3[1];
    } while (piVar3 != (int *)0x0);
  }
  iVar2 = 0;
LAB_0042fac8:
  iVar2 = FUN_004491c0(uVar4,(int)pvVar1,iVar2);
  if (iVar2 != 0) {
    FUN_0043e5a0(*(int *)(iVar2 + 0x308),(int)*(short *)(in_EAX + 0x59ce) / 10 + 0x33);
  }
  iVar2 = FUN_004491c0(*(undefined4 *)(in_EAX + 0x2cc),(int)pvVar1,*(undefined4 *)(in_EAX + 0x2cc));
  if (iVar2 == 0) {
    *(undefined4 *)(in_EAX + 0x2cc) = 0;
  }
  piVar3 = (int *)(iVar2 + 0x10);
  uVar4 = extraout_ECX_04;
  if (piVar3 != (int *)0x0) {
    uVar4 = 0x46;
    do {
      if (*(short *)(*piVar3 + 0x38a) == 0x46) {
        iVar2 = *(int *)*piVar3;
        goto LAB_0042fb39;
      }
      piVar3 = (int *)piVar3[1];
    } while (piVar3 != (int *)0x0);
  }
  iVar2 = 0;
LAB_0042fb39:
  iVar2 = FUN_004491c0(uVar4,(int)pvVar1,iVar2);
  if (iVar2 != 0) {
    FUN_0043e5a0(*(int *)(iVar2 + 0x308),(int)*(short *)(in_EAX + 0x59ce) % 10 + 0x33);
  }
  iVar2 = FUN_004491c0(*(undefined4 *)(in_EAX + 0x2cc),(int)pvVar1,*(undefined4 *)(in_EAX + 0x2cc));
  if (iVar2 == 0) {
    *(undefined4 *)(in_EAX + 0x2cc) = 0;
  }
  piVar3 = (int *)(iVar2 + 0x10);
  uVar4 = extraout_ECX_05;
  if (piVar3 != (int *)0x0) {
    uVar4 = 0x4f;
    do {
      if (*(short *)(*piVar3 + 0x38a) == 0x4f) {
        iVar2 = *(int *)*piVar3;
        goto LAB_0042fba8;
      }
      piVar3 = (int *)piVar3[1];
    } while (piVar3 != (int *)0x0);
  }
  iVar2 = 0;
LAB_0042fba8:
  iVar2 = FUN_004491c0(uVar4,(int)pvVar1,iVar2);
  if (iVar2 != 0) {
    FUN_0043e5a0(*(int *)(iVar2 + 0x308),(int)*(short *)(in_EAX + 0x59ce) / 10 + 0x33);
  }
  iVar2 = FUN_004491c0(*(undefined4 *)(in_EAX + 0x2cc),(int)pvVar1,*(undefined4 *)(in_EAX + 0x2cc));
  if (iVar2 == 0) {
    *(undefined4 *)(in_EAX + 0x2cc) = 0;
  }
  piVar3 = (int *)(iVar2 + 0x10);
  uVar4 = extraout_ECX_06;
  if (piVar3 != (int *)0x0) {
    uVar4 = 0x50;
    do {
      if (*(short *)(*piVar3 + 0x38a) == 0x50) {
        iVar2 = *(int *)*piVar3;
        goto LAB_0042fc19;
      }
      piVar3 = (int *)piVar3[1];
    } while (piVar3 != (int *)0x0);
  }
  iVar2 = 0;
LAB_0042fc19:
  iVar2 = FUN_004491c0(uVar4,(int)pvVar1,iVar2);
  if (iVar2 != 0) {
    FUN_0043e5a0(*(int *)(iVar2 + 0x308),(int)*(short *)(in_EAX + 0x59ce) % 10 + 0x33);
  }
  iVar2 = FUN_004491c0(*(undefined4 *)(in_EAX + 0x2cc),(int)pvVar1,*(undefined4 *)(in_EAX + 0x2cc));
  if (iVar2 == 0) {
    *(undefined4 *)(in_EAX + 0x2cc) = 0;
  }
  piVar3 = (int *)(iVar2 + 0x10);
  uVar4 = extraout_ECX_07;
  if (piVar3 != (int *)0x0) {
    uVar4 = 0x47;
    do {
      if (*(short *)(*piVar3 + 0x38a) == 0x47) {
        iVar2 = *(int *)*piVar3;
        goto LAB_0042fc88;
      }
      piVar3 = (int *)piVar3[1];
    } while (piVar3 != (int *)0x0);
  }
  iVar2 = 0;
LAB_0042fc88:
  iVar2 = FUN_004491c0(uVar4,(int)pvVar1,iVar2);
  if (iVar2 != 0) {
    FUN_0043e5a0(*(int *)(iVar2 + 0x308),(int)*(short *)(in_EAX + 0x59d0) / 10 + 0x33);
  }
  iVar2 = FUN_004491c0(*(undefined4 *)(in_EAX + 0x2cc),(int)pvVar1,*(undefined4 *)(in_EAX + 0x2cc));
  if (iVar2 == 0) {
    *(undefined4 *)(in_EAX + 0x2cc) = 0;
  }
  piVar3 = (int *)(iVar2 + 0x10);
  uVar4 = extraout_ECX_08;
  if (piVar3 != (int *)0x0) {
    uVar4 = 0x48;
    do {
      if (*(short *)(*piVar3 + 0x38a) == 0x48) {
        iVar2 = *(int *)*piVar3;
        goto LAB_0042fcf9;
      }
      piVar3 = (int *)piVar3[1];
    } while (piVar3 != (int *)0x0);
  }
  iVar2 = 0;
LAB_0042fcf9:
  iVar2 = FUN_004491c0(uVar4,(int)pvVar1,iVar2);
  if (iVar2 != 0) {
    FUN_0043e5a0(*(int *)(iVar2 + 0x308),(int)*(short *)(in_EAX + 0x59d0) % 10 + 0x33);
  }
  iVar2 = FUN_004491c0(*(undefined4 *)(in_EAX + 0x2cc),(int)pvVar1,*(undefined4 *)(in_EAX + 0x2cc));
  if (iVar2 == 0) {
    *(undefined4 *)(in_EAX + 0x2cc) = 0;
  }
  piVar3 = (int *)(iVar2 + 0x10);
  uVar4 = extraout_ECX_09;
  if (piVar3 != (int *)0x0) {
    uVar4 = 0x51;
    do {
      if (*(short *)(*piVar3 + 0x38a) == 0x51) {
        iVar2 = *(int *)*piVar3;
        goto LAB_0042fd68;
      }
      piVar3 = (int *)piVar3[1];
    } while (piVar3 != (int *)0x0);
  }
  iVar2 = 0;
LAB_0042fd68:
  iVar2 = FUN_004491c0(uVar4,(int)pvVar1,iVar2);
  if (iVar2 != 0) {
    FUN_0043e5a0(*(int *)(iVar2 + 0x308),(int)*(short *)(in_EAX + 0x59d0) / 10 + 0x33);
  }
  iVar2 = FUN_004491c0(*(undefined4 *)(in_EAX + 0x2cc),(int)pvVar1,*(undefined4 *)(in_EAX + 0x2cc));
  if (iVar2 == 0) {
    *(undefined4 *)(in_EAX + 0x2cc) = 0;
  }
  piVar3 = (int *)(iVar2 + 0x10);
  uVar4 = extraout_ECX_10;
  if (piVar3 != (int *)0x0) {
    uVar4 = 0x52;
    do {
      if (*(short *)(*piVar3 + 0x38a) == 0x52) {
        iVar2 = *(int *)*piVar3;
        goto LAB_0042fdd9;
      }
      piVar3 = (int *)piVar3[1];
    } while (piVar3 != (int *)0x0);
  }
  iVar2 = 0;
LAB_0042fdd9:
  iVar2 = FUN_004491c0(uVar4,(int)pvVar1,iVar2);
  if (iVar2 != 0) {
    FUN_0043e5a0(*(int *)(iVar2 + 0x308),(int)*(short *)(in_EAX + 0x59d0) % 10 + 0x33);
  }
  iVar2 = FUN_004491c0(*(undefined4 *)(in_EAX + 0x2cc),(int)pvVar1,*(undefined4 *)(in_EAX + 0x2cc));
  if (iVar2 == 0) {
    *(undefined4 *)(in_EAX + 0x2cc) = 0;
  }
  piVar3 = (int *)(iVar2 + 0x10);
  uVar4 = extraout_ECX_11;
  if (piVar3 != (int *)0x0) {
    uVar4 = 0x49;
    do {
      if (*(short *)(*piVar3 + 0x38a) == 0x49) {
        iVar2 = *(int *)*piVar3;
        goto LAB_0042fe48;
      }
      piVar3 = (int *)piVar3[1];
    } while (piVar3 != (int *)0x0);
  }
  iVar2 = 0;
LAB_0042fe48:
  iVar2 = FUN_004491c0(uVar4,(int)pvVar1,iVar2);
  if (iVar2 != 0) {
    FUN_0043e5a0(*(int *)(iVar2 + 0x308),(int)*(short *)(in_EAX + 0x59d2) / 10 + 0x33);
  }
  iVar2 = FUN_004491c0(*(undefined4 *)(in_EAX + 0x2cc),(int)pvVar1,*(undefined4 *)(in_EAX + 0x2cc));
  if (iVar2 == 0) {
    *(undefined4 *)(in_EAX + 0x2cc) = 0;
  }
  piVar3 = (int *)(iVar2 + 0x10);
  uVar4 = extraout_ECX_12;
  if (piVar3 != (int *)0x0) {
    uVar4 = 0x4a;
    do {
      if (*(short *)(*piVar3 + 0x38a) == 0x4a) {
        iVar2 = *(int *)*piVar3;
        goto LAB_0042feb9;
      }
      piVar3 = (int *)piVar3[1];
    } while (piVar3 != (int *)0x0);
  }
  iVar2 = 0;
LAB_0042feb9:
  iVar2 = FUN_004491c0(uVar4,(int)pvVar1,iVar2);
  if (iVar2 != 0) {
    FUN_0043e5a0(*(int *)(iVar2 + 0x308),(int)*(short *)(in_EAX + 0x59d2) % 10 + 0x33);
  }
  iVar2 = FUN_004491c0(*(undefined4 *)(in_EAX + 0x2cc),(int)pvVar1,*(undefined4 *)(in_EAX + 0x2cc));
  if (iVar2 == 0) {
    *(undefined4 *)(in_EAX + 0x2cc) = 0;
  }
  piVar3 = (int *)(iVar2 + 0x10);
  uVar4 = extraout_ECX_13;
  if (piVar3 != (int *)0x0) {
    uVar4 = 0x53;
    do {
      if (*(short *)(*piVar3 + 0x38a) == 0x53) {
        iVar2 = *(int *)*piVar3;
        goto LAB_0042ff28;
      }
      piVar3 = (int *)piVar3[1];
    } while (piVar3 != (int *)0x0);
  }
  iVar2 = 0;
LAB_0042ff28:
  iVar2 = FUN_004491c0(uVar4,(int)pvVar1,iVar2);
  if (iVar2 != 0) {
    FUN_0043e5a0(*(int *)(iVar2 + 0x308),(int)*(short *)(in_EAX + 0x59d2) / 10 + 0x33);
  }
  iVar2 = FUN_004491c0(*(undefined4 *)(in_EAX + 0x2cc),(int)pvVar1,*(undefined4 *)(in_EAX + 0x2cc));
  if (iVar2 == 0) {
    *(undefined4 *)(in_EAX + 0x2cc) = 0;
  }
  piVar3 = (int *)(iVar2 + 0x10);
  uVar4 = extraout_ECX_14;
  if (piVar3 != (int *)0x0) {
    uVar4 = 0x54;
    do {
      if (*(short *)(*piVar3 + 0x38a) == 0x54) {
        iVar2 = *(int *)*piVar3;
        goto LAB_0042ff99;
      }
      piVar3 = (int *)piVar3[1];
    } while (piVar3 != (int *)0x0);
  }
  iVar2 = 0;
LAB_0042ff99:
  iVar2 = FUN_004491c0(uVar4,(int)pvVar1,iVar2);
  if (iVar2 != 0) {
    FUN_0043e5a0(*(int *)(iVar2 + 0x308),(int)*(short *)(in_EAX + 0x59d2) % 10 + 0x33);
  }
  iVar2 = FUN_004491c0(*(undefined4 *)(in_EAX + 0x2cc),(int)pvVar1,*(undefined4 *)(in_EAX + 0x2cc));
  if (iVar2 == 0) {
    *(undefined4 *)(in_EAX + 0x2cc) = 0;
  }
  piVar3 = (int *)(iVar2 + 0x10);
  uVar4 = extraout_ECX_15;
  if (piVar3 != (int *)0x0) {
    uVar4 = 0x4b;
    do {
      if (*(short *)(*piVar3 + 0x38a) == 0x4b) {
        iVar2 = *(int *)*piVar3;
        goto LAB_00430008;
      }
      piVar3 = (int *)piVar3[1];
    } while (piVar3 != (int *)0x0);
  }
  iVar2 = 0;
LAB_00430008:
  iVar2 = FUN_004491c0(uVar4,(int)pvVar1,iVar2);
  if (iVar2 != 0) {
    FUN_0043e5a0(*(int *)(iVar2 + 0x308),(int)*(short *)(in_EAX + 0x59d4) / 10 + 0x33);
  }
  iVar2 = FUN_004491c0(*(undefined4 *)(in_EAX + 0x2cc),(int)pvVar1,*(undefined4 *)(in_EAX + 0x2cc));
  if (iVar2 == 0) {
    *(undefined4 *)(in_EAX + 0x2cc) = 0;
  }
  piVar3 = (int *)(iVar2 + 0x10);
  uVar4 = extraout_ECX_16;
  if (piVar3 != (int *)0x0) {
    uVar4 = 0x4c;
    do {
      if (*(short *)(*piVar3 + 0x38a) == 0x4c) {
        iVar2 = *(int *)*piVar3;
        goto LAB_00430079;
      }
      piVar3 = (int *)piVar3[1];
    } while (piVar3 != (int *)0x0);
  }
  iVar2 = 0;
LAB_00430079:
  iVar2 = FUN_004491c0(uVar4,(int)pvVar1,iVar2);
  if (iVar2 != 0) {
    FUN_0043e5a0(*(int *)(iVar2 + 0x308),(int)*(short *)(in_EAX + 0x59d4) % 10 + 0x33);
  }
  iVar2 = FUN_004491c0(*(undefined4 *)(in_EAX + 0x2cc),(int)pvVar1,*(undefined4 *)(in_EAX + 0x2cc));
  if (iVar2 == 0) {
    *(undefined4 *)(in_EAX + 0x2cc) = 0;
  }
  piVar3 = (int *)(iVar2 + 0x10);
  uVar4 = extraout_ECX_17;
  if (piVar3 != (int *)0x0) {
    uVar4 = 0x55;
    do {
      if (*(short *)(*piVar3 + 0x38a) == 0x55) {
        iVar2 = *(int *)*piVar3;
        goto LAB_004300e8;
      }
      piVar3 = (int *)piVar3[1];
    } while (piVar3 != (int *)0x0);
  }
  iVar2 = 0;
LAB_004300e8:
  iVar2 = FUN_004491c0(uVar4,(int)pvVar1,iVar2);
  if (iVar2 != 0) {
    FUN_0043e5a0(*(int *)(iVar2 + 0x308),(int)*(short *)(in_EAX + 0x59d4) / 10 + 0x33);
  }
  iVar2 = FUN_004491c0(*(undefined4 *)(in_EAX + 0x2cc),(int)pvVar1,*(undefined4 *)(in_EAX + 0x2cc));
  if (iVar2 == 0) {
    *(undefined4 *)(in_EAX + 0x2cc) = 0;
  }
  piVar3 = (int *)(iVar2 + 0x10);
  uVar4 = extraout_ECX_18;
  if (piVar3 != (int *)0x0) {
    uVar4 = 0x56;
    do {
      if (*(short *)(*piVar3 + 0x38a) == 0x56) {
        iVar2 = *(int *)*piVar3;
        goto LAB_00430159;
      }
      piVar3 = (int *)piVar3[1];
    } while (piVar3 != (int *)0x0);
  }
  iVar2 = 0;
LAB_00430159:
  iVar2 = FUN_004491c0(uVar4,(int)pvVar1,iVar2);
  if (iVar2 != 0) {
    FUN_0043e5a0(*(int *)(iVar2 + 0x308),(int)*(short *)(in_EAX + 0x59d4) % 10 + 0x33);
    return;
  }
  return;
}

