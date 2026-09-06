/* Raw Ghidra reference; not compilable reconstruction. Address: 00415E90 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_00415e90(int *param_1)

{
  uint *puVar1;
  undefined4 *puVar2;
  ushort *puVar3;
  void *pvVar4;
  int iVar5;
  char *pcVar6;
  int *piVar7;
  undefined4 *puVar8;
  uint uVar9;
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
  int iVar10;
  
  if (0 < param_1[0x1e]) {
    param_1[0x1e] = param_1[0x1e] + -1;
  }
  if (((*(byte *)(param_1 + 0x1f) & 1) != 0) && ((DAT_00474e5c & 0x100) != 0)) {
    uVar9 = (uint)*(ushort *)param_1[0x17];
    if ((param_1[10] & 1U) == 0) {
      param_1[7] = 0;
      param_1[6] = -999999;
      param_1[8] = 0;
      param_1[9] = (int)&DAT_00476f78;
      param_1[10] = param_1[10] | 1;
    }
    param_1[7] = uVar9;
    param_1[6] = uVar9 - 1;
    param_1[8] = (int)(float)uVar9;
  }
  if ((int)(uint)*(ushort *)param_1[0x17] <= param_1[7]) {
    do {
      pvVar4 = g_pGameStateManager;
      iVar10 = DAT_0047783c;
      iVar5 = param_1[0x17];
      uVar9 = (uint)*(byte *)(iVar5 + 2);
      switch(uVar9) {
      case 0:
        if (DAT_00474c84 != 0) {
          DAT_00474c8c = 0;
        }
        DAT_00474c84 = 0;
        return 0xffffffff;
      case 1:
        if (DAT_00474c68 == 0) {
          piVar7 = (int *)FUN_00448d00(*(undefined4 *)(DAT_00477834 + 0x10),0x1d,0xf);
          param_1[0x10] = *piVar7;
        }
        else if (DAT_00474c68 == 1) {
          piVar7 = (int *)FUN_00448d00(*(undefined4 *)(DAT_00477834 + 0x10),0x1d,0xf);
          param_1[0x10] = *piVar7;
        }
        break;
      case 2:
        if (DAT_00474c7c == 6) {
          if (DAT_00474c68 == 0) {
            piVar7 = (int *)FUN_00448d00(*(undefined4 *)(DAT_00477704 + 0x38),0x20,0xf);
            param_1[0x11] = *piVar7;
          }
          else if (DAT_00474c68 == 1) {
            piVar7 = (int *)FUN_00448d00(*(undefined4 *)(DAT_00477704 + 0x38),0x20,0xf);
            param_1[0x11] = *piVar7;
          }
        }
        else if ((DAT_00474c7c == 7) && (*param_1 < 1)) {
          if (DAT_00474c68 == 0) {
            piVar7 = (int *)FUN_00448d00(*(undefined4 *)(DAT_00477704 + 0x38),0x25,0xf);
            param_1[0x11] = *piVar7;
          }
          else if (DAT_00474c68 == 1) {
            piVar7 = (int *)FUN_00448d00(*(undefined4 *)(DAT_00477704 + 0x38),0x25,0xf);
            param_1[0x11] = *piVar7;
          }
        }
        else if (DAT_00474c68 == 0) {
          piVar7 = (int *)FUN_00448d00(*(undefined4 *)(DAT_00477834 + 0x10),0x1e,0xf);
          param_1[0x11] = *piVar7;
        }
        else if (DAT_00474c68 == 1) {
          piVar7 = (int *)FUN_00448d00(*(undefined4 *)(DAT_00477834 + 0x10),0x1e,0xf);
          param_1[0x11] = *piVar7;
        }
        break;
      case 3:
        piVar7 = (int *)FUN_00448d00(*(undefined4 *)(DAT_0047770c + 0x9ec8),0x5a,0xf);
        param_1[0x12] = *piVar7;
        break;
      case 4:
        FUN_00409e50(uVar9);
        param_1[0x10] = 0;
        break;
      case 5:
        FUN_00409e50(uVar9);
        param_1[0x11] = 0;
        FUN_00409e50(extraout_ECX_06);
        break;
      case 6:
        FUN_00409e50(uVar9);
        FUN_00409e50(extraout_ECX_07);
        FUN_00409e50(extraout_ECX_08);
        break;
      case 7:
        FUN_0040c4d0(uVar9);
        FUN_0040c480(extraout_ECX_09);
        pvVar4 = g_pGameStateManager;
        param_1[0x21] = 0;
        FUN_004492f0(param_1[0x13],(int)pvVar4,param_1[0x13]);
        FUN_004492f0(extraout_ECX_10,(int)pvVar4,param_1[0x14]);
        param_1[0x20] = 0;
        break;
      case 8:
        FUN_0040c4d0(uVar9);
        FUN_0040c480(extraout_ECX_11);
        pvVar4 = g_pGameStateManager;
        param_1[0x21] = 1;
        FUN_004492f0(param_1[0x13],(int)pvVar4,param_1[0x13]);
        FUN_004492f0(extraout_ECX_12,(int)pvVar4,param_1[0x14]);
        param_1[0x20] = 0;
        break;
      case 9:
        param_1[0x1f] = param_1[0x1f] ^ ((uint)*(byte *)(iVar5 + 4) ^ param_1[0x1f]) & 1;
        break;
      case 10:
        if (param_1[0xc] < 1) {
          FUN_00405410(*(int *)(iVar5 + 4));
        }
        FUN_0044bf40(-1.0);
        if (((_DAT_00474e62 & 0x1001) == 0) && (0 < param_1[0xc])) {
          if ((*(byte *)(param_1 + 0x1f) & 1) == 0) {
            return 0;
          }
          if ((DAT_00474e5c & 0x100) == 0) {
            return 0;
          }
          FUN_00405410(0);
          param_1[0x20] = 0;
        }
        else {
          FUN_0043dc90(&DAT_00492590,0);
          FUN_00405410(0);
          param_1[0x20] = 0;
        }
        break;
      case 0xb:
        param_1[0x1e] = 1;
        break;
      case 0xc:
        if (DAT_00474c68 == 0) {
          iVar5 = *(int *)(iVar5 + 4) + 0x34;
          FUN_004497d0(0);
          FUN_00449670(iVar5);
          iVar5 = *(int *)(param_1[0x17] + 4) + 0x3c;
          FUN_004497d0(iVar5);
          FUN_00449670(iVar5);
        }
        else if (DAT_00474c68 == 1) {
          iVar5 = *(int *)(iVar5 + 4) + 0x2d;
          FUN_004497d0(0);
          FUN_00449670(iVar5);
          iVar5 = *(int *)(param_1[0x17] + 4) + 0x35;
          FUN_004497d0(iVar5);
          FUN_00449670(iVar5);
        }
        break;
      case 0xd:
        switch(DAT_00474c7c) {
        case 1:
          if (DAT_00474c68 == 0) {
            iVar10 = *(int *)(DAT_00477704 + 0x38);
            iVar5 = *(int *)(iVar5 + 4) + 0xf;
            FUN_004497d0(iVar10);
            FUN_004496a0(iVar10,iVar5);
            iVar5 = *(int *)(DAT_00477704 + 0x38);
            iVar10 = *(int *)(param_1[0x17] + 4) + 0x17;
            FUN_004497d0(iVar10);
            FUN_004496a0(iVar5,iVar10);
          }
          else if (DAT_00474c68 == 1) {
            iVar10 = *(int *)(DAT_00477704 + 0x38);
            iVar5 = *(int *)(iVar5 + 4) + 0xf;
            FUN_004497d0(iVar10);
            FUN_004496a0(iVar10,iVar5);
            iVar5 = *(int *)(DAT_00477704 + 0x38);
            iVar10 = *(int *)(param_1[0x17] + 4) + 0x17;
            FUN_004497d0(iVar10);
            FUN_004496a0(iVar5,iVar10);
          }
          break;
        case 2:
          if (DAT_00474c68 == 0) {
            iVar10 = *(int *)(DAT_00477704 + 0x38);
            iVar5 = *(int *)(iVar5 + 4) + 0x15;
            FUN_004497d0(iVar10);
            FUN_004496a0(iVar10,iVar5);
            iVar5 = *(int *)(DAT_00477704 + 0x38);
            iVar10 = *(int *)(param_1[0x17] + 4) + 0x1e;
            FUN_004497d0(iVar10);
            FUN_004496a0(iVar5,iVar10);
          }
          else if (DAT_00474c68 == 1) {
            iVar10 = *(int *)(DAT_00477704 + 0x38);
            iVar5 = *(int *)(iVar5 + 4) + 0x15;
            FUN_004497d0(iVar10);
            FUN_004496a0(iVar10,iVar5);
            iVar5 = *(int *)(DAT_00477704 + 0x38);
            iVar10 = *(int *)(param_1[0x17] + 4) + 0x1e;
            FUN_004497d0(iVar10);
            FUN_004496a0(iVar5,iVar10);
          }
          break;
        case 3:
          if (DAT_00474c68 == 0) {
            iVar10 = *(int *)(DAT_00477704 + 0x38);
            iVar5 = *(int *)(iVar5 + 4) + 0x22;
            FUN_004497d0(iVar10);
            FUN_004496a0(iVar10,iVar5);
            iVar5 = *(int *)(DAT_00477704 + 0x38);
            iVar10 = *(int *)(param_1[0x17] + 4) + 0x2b;
            FUN_004497d0(iVar10);
            FUN_004496a0(iVar5,iVar10);
          }
          else if (DAT_00474c68 == 1) {
            iVar10 = *(int *)(DAT_00477704 + 0x38);
            iVar5 = *(int *)(iVar5 + 4) + 0x22;
            FUN_004497d0(iVar10);
            FUN_004496a0(iVar10,iVar5);
            iVar5 = *(int *)(DAT_00477704 + 0x38);
            iVar10 = *(int *)(param_1[0x17] + 4) + 0x2b;
            FUN_004497d0(iVar10);
            FUN_004496a0(iVar5,iVar10);
          }
          break;
        case 4:
          if (DAT_00474c68 == 0) {
            iVar10 = *(int *)(DAT_00477704 + 0x38);
            iVar5 = *(int *)(iVar5 + 4) + 0x25;
            FUN_004497d0(iVar10);
            FUN_004496a0(iVar10,iVar5);
            iVar5 = *(int *)(DAT_00477704 + 0x38);
            iVar10 = *(int *)(param_1[0x17] + 4) + 0x2e;
            FUN_004497d0(iVar10);
            FUN_004496a0(iVar5,iVar10);
          }
          else if (DAT_00474c68 == 1) {
            iVar10 = *(int *)(DAT_00477704 + 0x38);
            iVar5 = *(int *)(iVar5 + 4) + 0x25;
            FUN_004497d0(iVar10);
            FUN_004496a0(iVar10,iVar5);
            iVar5 = *(int *)(DAT_00477704 + 0x38);
            iVar10 = *(int *)(param_1[0x17] + 4) + 0x2e;
            FUN_004497d0(iVar10);
            FUN_004496a0(iVar5,iVar10);
          }
          break;
        case 5:
          if (DAT_00474c68 == 0) {
            iVar10 = *(int *)(DAT_00477704 + 0x38);
            iVar5 = *(int *)(iVar5 + 4) + 0x16;
            FUN_004497d0(iVar10);
            FUN_004496a0(iVar10,iVar5);
            iVar5 = *(int *)(DAT_00477704 + 0x38);
            iVar10 = *(int *)(param_1[0x17] + 4) + 0x1f;
            FUN_004497d0(iVar10);
            FUN_004496a0(iVar5,iVar10);
          }
          else if (DAT_00474c68 == 1) {
            iVar10 = *(int *)(DAT_00477704 + 0x38);
            iVar5 = *(int *)(iVar5 + 4) + 0x16;
            FUN_004497d0(iVar10);
            FUN_004496a0(iVar10,iVar5);
            iVar5 = *(int *)(DAT_00477704 + 0x38);
            iVar10 = *(int *)(param_1[0x17] + 4) + 0x1f;
            FUN_004497d0(iVar10);
            FUN_004496a0(iVar5,iVar10);
          }
          break;
        case 6:
          if (DAT_00474c68 == 0) {
            iVar10 = *(int *)(DAT_00477704 + 0x38);
            iVar5 = *(int *)(iVar5 + 4) + 0x30;
            FUN_004497d0(iVar10);
            FUN_004496a0(iVar10,iVar5);
            iVar5 = *(int *)(DAT_00477704 + 0x38);
            iVar10 = *(int *)(param_1[0x17] + 4) + 0x39;
            FUN_004497d0(iVar10);
            FUN_004496a0(iVar5,iVar10);
          }
          else if (DAT_00474c68 == 1) {
            iVar10 = *(int *)(DAT_00477704 + 0x38);
            iVar5 = *(int *)(iVar5 + 4) + 0x30;
            FUN_004497d0(iVar10);
            FUN_004496a0(iVar10,iVar5);
            iVar5 = *(int *)(DAT_00477704 + 0x38);
            iVar10 = *(int *)(param_1[0x17] + 4) + 0x39;
            FUN_004497d0(iVar10);
            FUN_004496a0(iVar5,iVar10);
          }
          break;
        case 7:
          if (*param_1 < 1) {
            if (DAT_00474c68 == 0) {
              iVar10 = *(int *)(DAT_00477704 + 0x38);
              iVar5 = *(int *)(iVar5 + 4) + 0x44;
              FUN_004497d0(iVar10);
              FUN_004496a0(iVar10,iVar5);
              iVar5 = *(int *)(DAT_00477704 + 0x38);
              iVar10 = *(int *)(param_1[0x17] + 4) + 0x4d;
              FUN_004497d0(iVar10);
              FUN_004496a0(iVar5,iVar10);
            }
            else if (DAT_00474c68 == 1) {
              iVar10 = *(int *)(DAT_00477704 + 0x38);
              iVar5 = *(int *)(iVar5 + 4) + 0x44;
              FUN_004497d0(iVar10);
              FUN_004496a0(iVar10,iVar5);
              iVar5 = *(int *)(DAT_00477704 + 0x38);
              iVar10 = *(int *)(param_1[0x17] + 4) + 0x4d;
              FUN_004497d0(iVar10);
              FUN_004496a0(iVar5,iVar10);
            }
          }
          else if (DAT_00474c68 == 0) {
            iVar10 = *(int *)(DAT_00477704 + 0x38);
            iVar5 = *(int *)(iVar5 + 4) + 0x2e;
            FUN_004497d0(iVar10);
            FUN_004496a0(iVar10,iVar5);
            iVar5 = *(int *)(DAT_00477704 + 0x38);
            iVar10 = *(int *)(param_1[0x17] + 4) + 0x37;
            FUN_004497d0(iVar10);
            FUN_004496a0(iVar5,iVar10);
          }
          else if (DAT_00474c68 == 1) {
            iVar10 = *(int *)(DAT_00477704 + 0x38);
            iVar5 = *(int *)(iVar5 + 4) + 0x2e;
            FUN_004497d0(iVar10);
            FUN_004496a0(iVar10,iVar5);
            iVar5 = *(int *)(DAT_00477704 + 0x38);
            iVar10 = *(int *)(param_1[0x17] + 4) + 0x37;
            FUN_004497d0(iVar10);
            FUN_004496a0(iVar5,iVar10);
          }
        }
        break;
      case 0xe:
        piVar7 = param_1 + 0x13;
        goto LAB_00415f25;
      case 0xf:
        piVar7 = param_1 + 0x14;
LAB_00415f25:
        iVar5 = FUN_004491c0(uVar9,(int)g_pGameStateManager,*piVar7);
        if (iVar5 == 0) {
          *piVar7 = 0;
        }
        pcVar6 = FUN_00417010();
        FUN_00447a50(pvVar4,param_1[param_1[0x21] + 0x22],pcVar6);
        FUN_0040c480(extraout_ECX);
        break;
      case 0x10:
        if (param_1[0x20] == 0) {
          piVar7 = param_1 + 0x13;
          iVar5 = FUN_004491c0(uVar9,(int)g_pGameStateManager,param_1[0x13]);
          if (iVar5 == 0) {
            *piVar7 = 0;
          }
          FUN_00447a50(pvVar4,param_1[param_1[0x21] + 0x22]," ");
          pvVar4 = g_pGameStateManager;
          iVar5 = FUN_004491c0(extraout_ECX_00,(int)g_pGameStateManager,param_1[0x14]);
          if (iVar5 == 0) {
            param_1[0x14] = 0;
          }
          FUN_00447a50(pvVar4,param_1[param_1[0x21] + 0x22]," ");
          iVar5 = FUN_004491c0(extraout_ECX_01,(int)g_pGameStateManager,*piVar7);
          if (iVar5 == 0) {
            *piVar7 = 0;
          }
          pcVar6 = FUN_00417010();
          FUN_00447a50(g_pGameStateManager,param_1[param_1[0x21] + 0x22],pcVar6);
          FUN_0040c480(extraout_ECX_02);
          FUN_0040c4d0(extraout_ECX_03);
          param_1[0x20] = param_1[0x20] + 1;
        }
        else {
          iVar5 = FUN_004491c0(param_1[0x14],(int)g_pGameStateManager,param_1[0x14]);
          if (iVar5 == 0) {
            param_1[0x14] = 0;
          }
          pcVar6 = FUN_00417010();
          FUN_00447a50(pvVar4,param_1[param_1[0x21] + 0x22],pcVar6);
          FUN_0040c480(extraout_ECX_04);
          param_1[0x20] = 0;
        }
        break;
      case 0x11:
        FUN_0040c4d0(uVar9);
        FUN_0040c4d0(extraout_ECX_05);
        break;
      case 0x12:
        FUN_00420b10(*(void **)(DAT_00477848 + 0x28),1,(int)*(void **)(DAT_00477848 + 0x28));
        FUN_00448d00(*(undefined4 *)(DAT_0047770c + 0x9e80),2,0xf);
        break;
      case 0x13:
        switch(DAT_00474c7c) {
        case 1:
          piVar7 = (int *)FUN_00448d00(*(undefined4 *)(DAT_00477704 + 0x38),0xd,0xf);
          param_1[0x15] = *piVar7;
          break;
        case 2:
          piVar7 = (int *)FUN_00448d00(*(undefined4 *)(DAT_00477704 + 0x38),0x10,0xf);
          param_1[0x15] = *piVar7;
          break;
        case 3:
          piVar7 = (int *)FUN_00448d00(*(undefined4 *)(DAT_00477704 + 0x38),0x14,0xf);
          param_1[0x15] = *piVar7;
          break;
        case 4:
          piVar7 = (int *)FUN_00448d00(*(undefined4 *)(DAT_00477704 + 0x38),0x15,0xf);
          param_1[0x15] = *piVar7;
          break;
        case 5:
          piVar7 = (int *)FUN_00448d00(*(undefined4 *)(DAT_00477704 + 0x38),0xe,0xf);
          param_1[0x15] = *piVar7;
          break;
        case 6:
          piVar7 = (int *)FUN_00448d00(*(undefined4 *)(DAT_00477704 + 0x38),0x23,0xf);
          param_1[0x15] = *piVar7;
          break;
        case 7:
          piVar7 = (int *)FUN_00448d00(*(undefined4 *)(DAT_00477704 + 0x38),0x1d,0xf);
          param_1[0x15] = *piVar7;
        }
        break;
      case 0x14:
        iVar5 = DAT_00474c74;
        if (DAT_00474c74 != 4) {
          *(undefined1 *)
           ((DAT_00474c6c + DAT_00474c68 * 3) * 0x437c + DAT_0047783c + 0x4e1 +
           (DAT_00474c7c + DAT_00474c74 * 6) * 8) = 1;
          *(undefined1 *)
           ((DAT_00474c6c + DAT_00474c68 * 3) * 0x437c + iVar10 +
           (DAT_00474c7c + (DAT_00474c74 * 3 + 0x4e) * 2) * 8) = 1;
          iVar5 = iVar10;
        }
        iVar10 = DAT_0047770c;
        if (((byte)DAT_00474ca0 & 0x10) != 0) {
          FUN_00423370(iVar5);
          break;
        }
        if (DAT_00474c7c == 6) {
          *(uint *)(DAT_0047770c + 0x9eb4) = *(uint *)(DAT_0047770c + 0x9eb4) | 0x20;
          FUN_00409d90(&DAT_00474c40,DAT_00474c4c * 1000);
          switch(DAT_00474c74) {
          case 0:
            FUN_00409d90(&DAT_00474c40,DAT_00474c70 * 20000000);
            iVar5 = DAT_00474c48 * 100000;
            break;
          case 1:
            FUN_00409d90(&DAT_00474c40,DAT_00474c70 * 25000000);
            iVar5 = DAT_00474c48 * 100000;
            break;
          case 2:
            FUN_00409d90(&DAT_00474c40,DAT_00474c70 * 35000000);
            iVar5 = DAT_00474c48 * 200000;
            break;
          case 3:
            FUN_00409d90(&DAT_00474c40,DAT_00474c70 * 40000000);
            iVar5 = DAT_00474c48 * 300000;
            break;
          case 4:
            FUN_00409d90(&DAT_00474c40,DAT_00474c70 * 40000000);
            iVar5 = DAT_00474c48 * 400000;
            break;
          default:
            goto switchD_00416c94_default;
          }
          FUN_00409d90(&DAT_00474c40,iVar5);
switchD_00416c94_default:
          if (*(int *)(DAT_00477838 + 0x10) == 1) {
LAB_00416e8a:
            FUN_0040ac90(4);
            break;
          }
          FUN_0043c8b0(5,0x78,0,0,0);
          iVar5 = DAT_0047770c;
          puVar1 = (uint *)(DAT_0047770c + 0x9eb4);
          *(undefined4 *)(DAT_0047770c + 0x9ecc) = 0;
          *(uint *)(iVar5 + 0x9eb4) = *puVar1 | 0x10;
          piVar7 = (int *)(DAT_0047783c + 0x4d0 +
                          ((DAT_00474c6c + DAT_00474c68 * 3) * 0x10df + DAT_00474c74) * 4);
        }
        else {
          if (DAT_00474c7c != 7) {
            puVar2 = (undefined4 *)(DAT_0047770c + 0x9e14);
            FUN_004492a0(iVar5,(int)g_pGameStateManager,*(int *)(DAT_0047770c + 0x9e14));
            *puVar2 = 0;
            puVar8 = (undefined4 *)FUN_00448d00(*(undefined4 *)(iVar10 + 0x9ec8),0x4c,0xf);
            *puVar2 = *puVar8;
            FUN_0040ac90(0xb);
            FUN_004175e0();
            break;
          }
          *(uint *)(DAT_0047770c + 0x9eb4) = *(uint *)(DAT_0047770c + 0x9eb4) | 0x20;
          FUN_00409d90(&DAT_00474c40,DAT_00474c4c * 1000);
          FUN_00409d90(&DAT_00474c40,DAT_00474c70 * 40000000);
          FUN_00409d90(&DAT_00474c40,DAT_00474c48 * 400000);
          if (*(int *)(DAT_00477838 + 0x10) == 1) goto LAB_00416e8a;
          FUN_00423370(DAT_00477838);
          piVar7 = (int *)(DAT_0047783c + 0x4d0 +
                          ((DAT_00474c6c + DAT_00474c68 * 3) * 0x10df + DAT_00474c74) * 4);
        }
        if (*piVar7 < 99999) {
          *piVar7 = *piVar7 + 1;
        }
        break;
      case 0x15:
        FUN_00420c30();
        break;
      case 0x16:
        FUN_00449470(uVar9);
        break;
      case 0x17:
        FUN_00449470(uVar9);
      }
      puVar3 = (ushort *)(*(byte *)(param_1[0x17] + 3) + 4 + param_1[0x17]);
      param_1[0x17] = (int)puVar3;
    } while ((int)(uint)*puVar3 <= param_1[7]);
  }
  FUN_00404ed0();
  return 0;
}

