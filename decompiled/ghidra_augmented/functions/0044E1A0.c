/* Raw Ghidra reference; not compilable reconstruction. Address: 0044E1A0 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_0044e1a0(float param_1)

{
  char cVar1;
  short sVar2;
  int iVar3;
  float *in_EAX;
  float fVar4;
  int *piVar5;
  undefined4 *puVar6;
  float *pfVar7;
  uint *puVar8;
  int iVar9;
  uint uVar10;
  undefined4 extraout_ECX;
  undefined4 extraout_ECX_00;
  undefined4 extraout_ECX_01;
  uint extraout_ECX_02;
  uint extraout_ECX_03;
  undefined4 extraout_ECX_04;
  undefined4 extraout_ECX_05;
  undefined4 extraout_ECX_06;
  uint extraout_ECX_07;
  uint extraout_ECX_08;
  uint extraout_ECX_09;
  uint extraout_ECX_10;
  uint extraout_ECX_11;
  uint extraout_ECX_12;
  float fVar11;
  undefined4 extraout_ECX_13;
  undefined4 extraout_ECX_14;
  byte bVar12;
  uint *puVar13;
  float10 fVar14;
  ulonglong uVar15;
  uint *local_108;
  undefined1 *local_104;
  float local_100;
  float local_fc;
  uint local_f8;
  int local_f4;
  int local_f0;
  float local_ec;
  float local_e8;
  int local_e4;
  float local_e0;
  int local_dc;
  float local_d8;
  int local_d4;
  int local_d0;
  float local_cc;
  int local_c8;
  float local_c4;
  int local_c0;
  float local_bc;
  float local_b8;
  float local_b4;
  float local_b0;
  float local_ac;
  int local_a8;
  float local_a4;
  int local_a0;
  float local_9c;
  int local_98;
  float local_94;
  int local_90;
  float local_8c;
  int local_88;
  float local_84;
  int local_80;
  int local_7c;
  int local_78;
  uint local_74;
  float local_70;
  int local_6c;
  int local_68;
  uint local_64;
  float local_60;
  uint local_5c;
  int local_58;
  uint local_54;
  int local_50;
  uint local_4c;
  int local_48;
  uint local_44;
  float local_40;
  uint local_3c;
  int local_38;
  uint local_34;
  int local_30;
  float local_2c;
  int local_28;
  float local_24;
  float local_20;
  int local_1c;
  float local_18;
  int local_14;
  int local_10;
  undefined4 local_c;
  undefined4 local_8;
  
  if ((int *)in_EAX[1] == (int *)0x0) {
    return 0xffffffff;
  }
  fVar11 = (float)*(int *)in_EAX[1];
  if (fVar11 < *in_EAX != (fVar11 == *in_EAX)) {
    do {
      pfVar7 = in_EAX + 1;
      fVar11 = *pfVar7;
      if ((*(byte *)(in_EAX + 0x407) & *(byte *)((int)fVar11 + 10)) == 0)
      goto switchD_0044e205_caseD_0;
      sVar2 = *(short *)((int)fVar11 + 4);
      if (0x57 < (uint)(int)sVar2) {
switchD_0044e205_caseD_2:
        iVar9 = (*(code *)**(undefined4 **)in_EAX[0x405])();
        if (iVar9 == -1) {
          return 0;
        }
        goto switchD_0044e205_caseD_0;
      }
      uVar10 = (uint)(&switchD_0044e205::switchdataD_0044fcb4)[sVar2];
      switch(sVar2) {
      case 0:
        break;
      case 1:
switchD_0044e205_caseD_1:
        *pfVar7 = 0.0;
        return 0xffffffff;
      default:
        goto switchD_0044e205_caseD_2;
      case 10:
        PopEclScratchValue();
        if (in_EAX[0x402] == 0.0) goto switchD_0044e205_caseD_1;
        fVar11 = in_EAX[0x402];
        fVar4 = (float)((int)fVar11 + -4);
        if (-1 < (int)fVar4) {
          in_EAX[0x402] = fVar4;
          *pfVar7 = *(float *)((int)in_EAX + (int)fVar11 + 4);
        }
        fVar11 = in_EAX[0x402];
        fVar4 = (float)((int)fVar11 + -4);
        if (-1 < (int)fVar4) {
          in_EAX[0x402] = fVar4;
          *in_EAX = *(float *)((int)in_EAX + (int)fVar11 + 4);
        }
        if (*pfVar7 == 0.0) {
          return 0xffffffff;
        }
        break;
      case 0xb:
        iVar9 = FUN_0044df70(in_EAX,(float *)0x0);
        if (iVar9 != 0) {
          return 0xffffffff;
        }
        goto LAB_0044fb85;
      case 0xc:
switchD_0044e205_caseD_c:
        fVar11 = *pfVar7;
        *in_EAX = (float)*(int *)((int)fVar11 + 0x14);
        uVar10 = *(uint *)((int)fVar11 + 0x10);
        goto LAB_0044fb81;
      case 0xd:
        fVar11 = in_EAX[0x402];
        if (-1 < (int)fVar11 + -4) {
          in_EAX[0x402] = (float)((int)fVar11 + -4);
          local_1c = *(int *)((int)in_EAX + (int)fVar11 + 4);
          in_EAX[0x402] = (float)((int)fVar11 + -8);
          if (*(char *)((int)in_EAX + (int)fVar11) == 'f') {
            uVar15 = FUN_00463b2c();
            local_1c = (int)uVar15;
          }
        }
        if (local_1c == 0) goto switchD_0044e205_caseD_c;
        break;
      case 0xe:
        fVar11 = in_EAX[0x402];
        if (-1 < (int)fVar11 + -4) {
          in_EAX[0x402] = (float)((int)fVar11 + -4);
          local_88 = *(int *)((int)in_EAX + (int)fVar11 + 4);
          in_EAX[0x402] = (float)((int)fVar11 + -8);
          if (*(char *)((int)in_EAX + (int)fVar11) == 'f') {
            uVar15 = FUN_00463b2c();
            local_88 = (int)uVar15;
          }
        }
        if (local_88 != 0) goto switchD_0044e205_caseD_c;
        break;
      case 0xf:
        FUN_004500d0(0xffffffff,(float *)0x0);
        break;
      case 0x10:
        uVar10 = *(int *)((int)fVar11 + 0x10) + 4U >> 2;
        pfVar7 = (float *)0x1;
        uVar15 = ResolveEclIntValue(uVar10,(int)in_EAX,1,*(int *)((int)fVar11 + 0x10 + uVar10 * 4));
        FUN_004500d0((int)uVar15,pfVar7);
        break;
      case 0x11:
        uVar15 = ResolveEclIntOperand(uVar10,(int)in_EAX,0);
        piVar5 = FindEclVariable((int)uVar15);
        if (piVar5 != (int *)0x0) {
          *(undefined4 *)(*piVar5 + 4) = 0;
        }
        break;
      case 0x12:
        uVar15 = ResolveEclIntOperand(uVar10,(int)in_EAX,0);
        piVar5 = FindEclVariable((int)uVar15);
        if (piVar5 != (int *)0x0) {
          *(uint *)(*piVar5 + 0x1020) = *(uint *)(*piVar5 + 0x1020) | 1;
        }
        break;
      case 0x13:
        uVar15 = ResolveEclIntOperand(uVar10,(int)in_EAX,0);
        piVar5 = FindEclVariable((int)uVar15);
        if (piVar5 != (int *)0x0) {
          *(uint *)(*piVar5 + 0x1020) = *(uint *)(*piVar5 + 0x1020) & 0xfffffffe;
        }
        break;
      case 0x14:
        uVar15 = ResolveEclIntOperand(uVar10,(int)in_EAX,0);
        piVar5 = FindEclVariable((int)uVar15);
        if (piVar5 != (int *)0x0) {
          iVar9 = *piVar5;
          uVar15 = ResolveEclIntOperand(extraout_ECX,(int)in_EAX,1);
          *(int *)(iVar9 + 0x1018) = (int)uVar15;
        }
        break;
      case 0x15:
        ResetEclVariableBindings();
        break;
      case 0x1e:
        puVar13 = (uint *)((int)fVar11 + 0x14);
        local_104 = _malloc(0x400);
        *local_104 = 0;
        if (puVar13 != (uint *)0x0) {
          bVar12 = 1;
          local_100 = 0.0;
          iVar9 = 6;
          do {
            local_108 = FUN_00452730(puVar13,'%');
            if (local_108 == (uint *)0x0) break;
            puVar8 = puVar13;
            do {
              uVar10 = *puVar8;
              *(char *)((int)puVar8 + ((int)local_104 - (int)puVar13)) = (char)uVar10;
              puVar8 = (uint *)((int)puVar8 + 1);
            } while ((char)uVar10 != '\0');
            local_104[(int)local_108 - (int)puVar13] = 0;
            cVar1 = *(char *)((int)local_108 + 1);
            if ((cVar1 != '%') && ((cVar1 == 'd' || (cVar1 == 'f')))) {
              fVar11 = in_EAX[1];
              iVar3 = *(int *)((int)fVar11 + 0x10);
              cVar1 = *(char *)((int)local_100 + iVar3 + 0x14 + (int)fVar11);
              if ((cVar1 == 'f') || (cVar1 == 'g')) {
                ResolveEclFloatValue
                          (bVar12,*(float *)((int)fVar11 +
                                            (((int)(iVar3 + (iVar3 >> 0x1f & 3U)) >> 2) + iVar9) * 4
                                            ));
              }
              else {
                ResolveEclIntValue(fVar11,(int)in_EAX,bVar12,
                                   *(int *)((int)fVar11 +
                                           (((int)(iVar3 + (iVar3 >> 0x1f & 3U)) >> 2) + iVar9) * 4)
                                  );
              }
              local_100 = (float)((int)local_100 + 8);
              iVar9 = iVar9 + 2;
              bVar12 = bVar12 + 1;
            }
            puVar13 = (uint *)((int)local_108 + 2);
          } while (puVar13 != (uint *)0x0);
        }
        _free(local_104);
        break;
      case 0x28:
        uVar15 = ResolveEclIntOperand(uVar10,(int)in_EAX,0);
        PushEclScratchValue((int)uVar15);
        break;
      case 0x29:
        PopEclScratchValue();
        break;
      case 0x2a:
        uVar15 = ResolveEclIntOperand(uVar10,(int)in_EAX,0);
        local_108 = (uint *)uVar15;
        FUN_004505b0(extraout_ECX_00,'i',4,&local_108);
        break;
      case 0x2b:
        puVar6 = (undefined4 *)ResolveEclVariableValue(0);
        fVar11 = in_EAX[0x402];
        fVar4 = (float)((int)fVar11 + -4);
        if (-1 < (int)fVar4) {
          in_EAX[0x402] = fVar4;
          *puVar6 = *(undefined4 *)((int)in_EAX + (int)fVar11 + 4);
          fVar11 = in_EAX[0x402];
          in_EAX[0x402] = (float)((int)fVar11 + -4);
          if (*(char *)((int)in_EAX + (int)fVar11 + 4) == 'f') {
            uVar15 = FUN_00463b2c();
            *puVar6 = (int)uVar15;
          }
        }
        break;
      case 0x2c:
        fVar14 = ResolveEclFloatOperand(0.0);
        local_108 = (uint *)(float)fVar14;
        FUN_004505b0(extraout_ECX_01,'f',4,&local_108);
        break;
      case 0x2d:
        pfVar7 = (float *)ResolveEclFloatDestination(0);
        fVar11 = in_EAX[0x402];
        fVar4 = (float)((int)fVar11 + -4);
        if (-1 < (int)fVar4) {
          in_EAX[0x402] = fVar4;
          *pfVar7 = *(float *)((int)in_EAX + (int)fVar11 + 4);
          fVar11 = in_EAX[0x402];
          in_EAX[0x402] = (float)((int)fVar11 + -4);
          cVar1 = *(char *)((int)in_EAX + (int)fVar11 + 4);
          if ((cVar1 != 'f') && (cVar1 == 'i')) {
            *pfVar7 = (float)(int)*pfVar7;
          }
        }
        break;
      case 0x32:
        fVar11 = in_EAX[0x402];
        if (-1 < (int)fVar11 + -4) {
          in_EAX[0x402] = (float)((int)fVar11 + -4);
          local_14 = *(int *)((int)in_EAX + (int)fVar11 + 4);
          in_EAX[0x402] = (float)((int)fVar11 + -8);
          if (*(char *)((int)in_EAX + (int)fVar11) == 'f') {
            uVar15 = FUN_00463b2c();
            local_14 = (int)uVar15;
            uVar10 = extraout_ECX_02;
          }
        }
        fVar11 = in_EAX[0x402];
        if (-1 < (int)fVar11 + -4) {
          in_EAX[0x402] = (float)((int)fVar11 + -4);
          uVar10 = *(uint *)((int)in_EAX + (int)fVar11 + 4);
          in_EAX[0x402] = (float)((int)fVar11 + -8);
          local_f8 = uVar10;
          if (*(char *)((int)in_EAX + (int)fVar11) == 'f') {
            uVar15 = FUN_00463b2c();
            local_f8 = (uint)uVar15;
            uVar10 = extraout_ECX_03;
          }
        }
        local_f8 = local_f8 + local_14;
        FUN_004505b0(uVar10,'i',4,&local_f8);
        break;
      case 0x33:
        fVar11 = in_EAX[0x402];
        if (-1 < (int)fVar11 + -4) {
          in_EAX[0x402] = (float)((int)fVar11 + -4);
          local_b8 = *(float *)((int)in_EAX + (int)fVar11 + 4);
          in_EAX[0x402] = (float)((int)fVar11 + -8);
          if ((*(char *)((int)in_EAX + (int)fVar11) != 'f') &&
             (*(char *)((int)in_EAX + (int)fVar11) == 'i')) {
            local_b8 = (float)(int)local_b8;
          }
        }
        fVar11 = in_EAX[0x402];
        if (-1 < (int)fVar11 + -4) {
          in_EAX[0x402] = (float)((int)fVar11 + -4);
          local_e8 = *(float *)((int)in_EAX + (int)fVar11 + 4);
          in_EAX[0x402] = (float)((int)fVar11 + -8);
          if ((*(char *)((int)in_EAX + (int)fVar11) != 'f') &&
             (*(char *)((int)in_EAX + (int)fVar11) == 'i')) {
            local_e8 = (float)(int)local_e8 + local_b8;
            FUN_004505b0(&local_e8,'f',4,&local_e8);
            break;
          }
        }
        local_e8 = local_e8 + local_b8;
        FUN_004505b0(&local_e8,'f',4,&local_e8);
        break;
      case 0x34:
        fVar11 = in_EAX[0x402];
        if (-1 < (int)fVar11 + -4) {
          in_EAX[0x402] = (float)((int)fVar11 + -4);
          local_c8 = *(int *)((int)in_EAX + (int)fVar11 + 4);
          in_EAX[0x402] = (float)((int)fVar11 + -8);
          if (*(char *)((int)in_EAX + (int)fVar11) == 'f') {
            uVar15 = FUN_00463b2c();
            local_c8 = (int)uVar15;
          }
        }
        fVar11 = in_EAX[0x402];
        if (-1 < (int)fVar11 + -4) {
          in_EAX[0x402] = (float)((int)fVar11 + -4);
          local_f4 = *(int *)((int)in_EAX + (int)fVar11 + 4);
          in_EAX[0x402] = (float)((int)fVar11 + -8);
          if (*(char *)((int)in_EAX + (int)fVar11) == 'f') {
            uVar15 = FUN_00463b2c();
            local_f4 = (int)uVar15;
          }
        }
        local_f4 = local_f4 - local_c8;
        FUN_004505b0(&local_f4,'i',4,&local_f4);
        break;
      case 0x35:
        fVar11 = in_EAX[0x402];
        if (-1 < (int)fVar11 + -4) {
          in_EAX[0x402] = (float)((int)fVar11 + -4);
          local_60 = *(float *)((int)in_EAX + (int)fVar11 + 4);
          in_EAX[0x402] = (float)((int)fVar11 + -8);
          if ((*(char *)((int)in_EAX + (int)fVar11) != 'f') &&
             (*(char *)((int)in_EAX + (int)fVar11) == 'i')) {
            local_60 = (float)(int)local_60;
          }
        }
        fVar11 = in_EAX[0x402];
        if (-1 < (int)fVar11 + -4) {
          in_EAX[0x402] = (float)((int)fVar11 + -4);
          local_d8 = *(float *)((int)in_EAX + (int)fVar11 + 4);
          in_EAX[0x402] = (float)((int)fVar11 + -8);
          if ((*(char *)((int)in_EAX + (int)fVar11) != 'f') &&
             (*(char *)((int)in_EAX + (int)fVar11) == 'i')) {
            local_d8 = (float)(int)local_d8 - local_60;
            FUN_004505b0(&local_d8,'f',4,&local_d8);
            break;
          }
        }
        local_d8 = local_d8 - local_60;
        FUN_004505b0(&local_d8,'f',4,&local_d8);
        break;
      case 0x36:
        fVar11 = in_EAX[0x402];
        if (-1 < (int)fVar11 + -4) {
          in_EAX[0x402] = (float)((int)fVar11 + -4);
          local_68 = *(int *)((int)in_EAX + (int)fVar11 + 4);
          in_EAX[0x402] = (float)((int)fVar11 + -8);
          if (*(char *)((int)in_EAX + (int)fVar11) == 'f') {
            uVar15 = FUN_00463b2c();
            local_68 = (int)uVar15;
          }
        }
        fVar4 = in_EAX[0x402];
        fVar11 = (float)((int)fVar4 + -4);
        if (-1 < (int)fVar11) {
          in_EAX[0x402] = fVar11;
          local_d4 = *(int *)((int)in_EAX + (int)fVar4 + 4);
          fVar11 = (float)((int)fVar4 + -8);
          in_EAX[0x402] = fVar11;
          if (*(char *)((int)in_EAX + (int)fVar4) == 'f') {
            uVar15 = FUN_00463b2c();
            local_d4 = (int)uVar15 * local_68;
            FUN_004505b0(extraout_ECX_04,'i',4,&local_d4);
            break;
          }
        }
        local_d4 = local_d4 * local_68;
        FUN_004505b0(fVar11,'i',4,&local_d4);
        break;
      case 0x37:
        fVar11 = in_EAX[0x402];
        if (-1 < (int)fVar11 + -4) {
          in_EAX[0x402] = (float)((int)fVar11 + -4);
          local_b0 = *(float *)((int)in_EAX + (int)fVar11 + 4);
          in_EAX[0x402] = (float)((int)fVar11 + -8);
          if ((*(char *)((int)in_EAX + (int)fVar11) != 'f') &&
             (*(char *)((int)in_EAX + (int)fVar11) == 'i')) {
            local_b0 = (float)(int)local_b0;
          }
        }
        fVar11 = in_EAX[0x402];
        if (-1 < (int)fVar11 + -4) {
          in_EAX[0x402] = (float)((int)fVar11 + -4);
          local_e0 = *(float *)((int)in_EAX + (int)fVar11 + 4);
          in_EAX[0x402] = (float)((int)fVar11 + -8);
          if ((*(char *)((int)in_EAX + (int)fVar11) != 'f') &&
             (*(char *)((int)in_EAX + (int)fVar11) == 'i')) {
            local_e0 = (float)(int)local_e0 * local_b0;
            FUN_004505b0(&local_e0,'f',4,&local_e0);
            break;
          }
        }
        local_e0 = local_e0 * local_b0;
        FUN_004505b0(&local_e0,'f',4,&local_e0);
        break;
      case 0x38:
        fVar11 = in_EAX[0x402];
        if (-1 < (int)fVar11 + -4) {
          in_EAX[0x402] = (float)((int)fVar11 + -4);
          local_c0 = *(int *)((int)in_EAX + (int)fVar11 + 4);
          in_EAX[0x402] = (float)((int)fVar11 + -8);
          if (*(char *)((int)in_EAX + (int)fVar11) == 'f') {
            uVar15 = FUN_00463b2c();
            local_c0 = (int)uVar15;
          }
        }
        fVar4 = in_EAX[0x402];
        fVar11 = (float)((int)fVar4 + -4);
        if (-1 < (int)fVar11) {
          in_EAX[0x402] = fVar11;
          local_dc = *(int *)((int)in_EAX + (int)fVar4 + 4);
          fVar11 = (float)((int)fVar4 + -8);
          in_EAX[0x402] = fVar11;
          if (*(char *)((int)in_EAX + (int)fVar4) == 'f') {
            uVar15 = FUN_00463b2c();
            local_dc = (int)((longlong)
                             ((ulonglong)(uint)((int)uVar15 >> 0x1f) << 0x20 | uVar15 & 0xffffffff)
                            / (longlong)local_c0);
            FUN_004505b0(extraout_ECX_05,'i',4,&local_dc);
            break;
          }
        }
        local_dc = local_dc / local_c0;
        FUN_004505b0(fVar11,'i',4,&local_dc);
        break;
      case 0x39:
        fVar11 = in_EAX[0x402];
        if (-1 < (int)fVar11 + -4) {
          in_EAX[0x402] = (float)((int)fVar11 + -4);
          local_20 = *(float *)((int)in_EAX + (int)fVar11 + 4);
          in_EAX[0x402] = (float)((int)fVar11 + -8);
          if ((*(char *)((int)in_EAX + (int)fVar11) != 'f') &&
             (*(char *)((int)in_EAX + (int)fVar11) == 'i')) {
            local_20 = (float)(int)local_20;
          }
        }
        fVar11 = in_EAX[0x402];
        if (-1 < (int)fVar11 + -4) {
          in_EAX[0x402] = (float)((int)fVar11 + -4);
          local_ec = *(float *)((int)in_EAX + (int)fVar11 + 4);
          in_EAX[0x402] = (float)((int)fVar11 + -8);
          if ((*(char *)((int)in_EAX + (int)fVar11) != 'f') &&
             (*(char *)((int)in_EAX + (int)fVar11) == 'i')) {
            local_ec = (float)(int)local_ec / local_20;
            FUN_004505b0(&local_ec,'f',4,&local_ec);
            break;
          }
        }
        local_ec = local_ec / local_20;
        FUN_004505b0(&local_ec,'f',4,&local_ec);
        break;
      case 0x3a:
        fVar11 = in_EAX[0x402];
        if (-1 < (int)fVar11 + -4) {
          in_EAX[0x402] = (float)((int)fVar11 + -4);
          local_38 = *(int *)((int)in_EAX + (int)fVar11 + 4);
          in_EAX[0x402] = (float)((int)fVar11 + -8);
          if (*(char *)((int)in_EAX + (int)fVar11) == 'f') {
            uVar15 = FUN_00463b2c();
            local_38 = (int)uVar15;
          }
        }
        fVar4 = in_EAX[0x402];
        fVar11 = (float)((int)fVar4 + -4);
        if (-1 < (int)fVar11) {
          in_EAX[0x402] = fVar11;
          local_f0 = *(int *)((int)in_EAX + (int)fVar4 + 4);
          fVar11 = (float)((int)fVar4 + -8);
          in_EAX[0x402] = fVar11;
          if (*(char *)((int)in_EAX + (int)fVar4) == 'f') {
            uVar15 = FUN_00463b2c();
            local_f0 = (int)((longlong)
                             ((ulonglong)(uint)((int)uVar15 >> 0x1f) << 0x20 | uVar15 & 0xffffffff)
                            % (longlong)local_38);
            FUN_004505b0(extraout_ECX_06,'i',4,&local_f0);
            break;
          }
        }
        local_f0 = local_f0 % local_38;
        FUN_004505b0(fVar11,'i',4,&local_f0);
        break;
      case 0x3b:
        fVar11 = in_EAX[0x402];
        if (-1 < (int)fVar11 + -4) {
          in_EAX[0x402] = (float)((int)fVar11 + -4);
          local_a8 = *(int *)((int)in_EAX + (int)fVar11 + 4);
          in_EAX[0x402] = (float)((int)fVar11 + -8);
          if (*(char *)((int)in_EAX + (int)fVar11) == 'f') {
            uVar15 = FUN_00463b2c();
            local_a8 = (int)uVar15;
          }
        }
        fVar11 = in_EAX[0x402];
        if (-1 < (int)fVar11 + -4) {
          in_EAX[0x402] = (float)((int)fVar11 + -4);
          local_58 = *(int *)((int)in_EAX + (int)fVar11 + 4);
          in_EAX[0x402] = (float)((int)fVar11 + -8);
          if (*(char *)((int)in_EAX + (int)fVar11) == 'f') {
            uVar15 = FUN_00463b2c();
            local_58 = (int)uVar15;
          }
        }
        local_108 = (uint *)(uint)(local_58 == local_a8);
        FUN_004505b0(&local_108,'i',4,&local_108);
        break;
      case 0x3c:
        fVar11 = in_EAX[0x402];
        if (-1 < (int)fVar11 + -4) {
          in_EAX[0x402] = (float)((int)fVar11 + -4);
          local_40 = *(float *)((int)in_EAX + (int)fVar11 + 4);
          in_EAX[0x402] = (float)((int)fVar11 + -8);
          if ((*(char *)((int)in_EAX + (int)fVar11) != 'f') &&
             (*(char *)((int)in_EAX + (int)fVar11) == 'i')) {
            local_40 = (float)(int)local_40;
          }
        }
        fVar11 = in_EAX[0x402];
        if (-1 < (int)fVar11 + -4) {
          in_EAX[0x402] = (float)((int)fVar11 + -4);
          local_70 = *(float *)((int)in_EAX + (int)fVar11 + 4);
          in_EAX[0x402] = (float)((int)fVar11 + -8);
          if ((*(char *)((int)in_EAX + (int)fVar11) != 'f') &&
             (*(char *)((int)in_EAX + (int)fVar11) == 'i')) {
            local_70 = (float)(int)local_70;
          }
        }
        local_104 = (undefined1 *)0x1;
        if (local_70 != local_40) {
          local_104 = (undefined1 *)0x0;
        }
LAB_0044f05c:
        FUN_004505b0(in_EAX + 2,'i',4,&local_104);
        break;
      case 0x3d:
        fVar11 = in_EAX[0x402];
        if (-1 < (int)fVar11 + -4) {
          in_EAX[0x402] = (float)((int)fVar11 + -4);
          local_a0 = *(int *)((int)in_EAX + (int)fVar11 + 4);
          in_EAX[0x402] = (float)((int)fVar11 + -8);
          if (*(char *)((int)in_EAX + (int)fVar11) == 'f') {
            uVar15 = FUN_00463b2c();
            local_a0 = (int)uVar15;
          }
        }
        fVar11 = in_EAX[0x402];
        if (-1 < (int)fVar11 + -4) {
          in_EAX[0x402] = (float)((int)fVar11 + -4);
          local_30 = *(int *)((int)in_EAX + (int)fVar11 + 4);
          in_EAX[0x402] = (float)((int)fVar11 + -8);
          if (*(char *)((int)in_EAX + (int)fVar11) == 'f') {
            uVar15 = FUN_00463b2c();
            local_30 = (int)uVar15;
          }
        }
        local_108 = (uint *)(uint)(local_30 != local_a0);
        FUN_004505b0(&local_108,'i',4,&local_108);
        break;
      case 0x3e:
        fVar11 = in_EAX[0x402];
        pfVar7 = in_EAX + 2;
        fVar4 = (float)((int)fVar11 + -4);
        if (-1 < (int)fVar4) {
          in_EAX[0x402] = fVar4;
          local_18 = *(float *)((int)pfVar7 + (int)fVar4);
          fVar11 = (float)((int)fVar11 + -8);
          in_EAX[0x402] = fVar11;
          cVar1 = *(char *)((int)pfVar7 + (int)fVar11);
          if ((cVar1 != 'f') && (cVar1 == 'i')) {
            local_18 = (float)(int)local_18;
          }
        }
        fVar11 = in_EAX[0x402];
        fVar4 = (float)((int)fVar11 + -4);
        if (-1 < (int)fVar4) {
          in_EAX[0x402] = fVar4;
          local_cc = *(float *)((int)fVar4 + (int)pfVar7);
          fVar11 = (float)((int)fVar11 + -8);
          in_EAX[0x402] = fVar11;
          cVar1 = *(char *)((int)fVar11 + (int)pfVar7);
          if ((cVar1 != 'f') && (cVar1 == 'i')) {
            local_cc = (float)(int)local_cc;
          }
        }
        local_104 = (undefined1 *)0x1;
        if (local_cc != local_18) goto LAB_0044f05c;
        local_104 = (undefined1 *)0x0;
        FUN_004505b0(pfVar7,'i',4,&local_104);
        break;
      case 0x3f:
        fVar11 = in_EAX[0x402];
        if (-1 < (int)fVar11 + -4) {
          in_EAX[0x402] = (float)((int)fVar11 + -4);
          local_98 = *(int *)((int)in_EAX + (int)fVar11 + 4);
          in_EAX[0x402] = (float)((int)fVar11 + -8);
          if (*(char *)((int)in_EAX + (int)fVar11) == 'f') {
            uVar15 = FUN_00463b2c();
            local_98 = (int)uVar15;
          }
        }
        fVar11 = in_EAX[0x402];
        if (-1 < (int)fVar11 + -4) {
          in_EAX[0x402] = (float)((int)fVar11 + -4);
          local_50 = *(int *)((int)in_EAX + (int)fVar11 + 4);
          in_EAX[0x402] = (float)((int)fVar11 + -8);
          if (*(char *)((int)in_EAX + (int)fVar11) == 'f') {
            uVar15 = FUN_00463b2c();
            local_50 = (int)uVar15;
          }
        }
        local_108 = (uint *)(uint)(local_50 < local_98);
        FUN_004505b0(&local_108,'i',4,&local_108);
        break;
      case 0x40:
        fVar11 = in_EAX[0x402];
        pfVar7 = in_EAX + 2;
        fVar4 = (float)((int)fVar11 + -4);
        if (-1 < (int)fVar4) {
          in_EAX[0x402] = fVar4;
          local_bc = *(float *)((int)fVar4 + (int)pfVar7);
          fVar11 = (float)((int)fVar11 + -8);
          in_EAX[0x402] = fVar11;
          cVar1 = *(char *)((int)fVar11 + (int)pfVar7);
          if ((cVar1 != 'f') && (cVar1 == 'i')) {
            local_bc = (float)(int)local_bc;
          }
        }
        fVar11 = in_EAX[0x402];
        fVar4 = (float)((int)fVar11 + -4);
        if (-1 < (int)fVar4) {
          in_EAX[0x402] = fVar4;
          local_c4 = *(float *)((int)fVar4 + (int)pfVar7);
          fVar11 = (float)((int)fVar11 + -8);
          in_EAX[0x402] = fVar11;
          cVar1 = *(char *)((int)fVar11 + (int)pfVar7);
          if ((cVar1 != 'f') && (cVar1 == 'i')) {
            local_c4 = (float)(int)local_c4;
          }
        }
        local_104 = (undefined1 *)0x1;
        if (local_c4 < local_bc) goto LAB_0044f05c;
        local_104 = (undefined1 *)0x0;
        FUN_004505b0(pfVar7,'i',4,&local_104);
        break;
      case 0x41:
        fVar11 = in_EAX[0x402];
        if (-1 < (int)fVar11 + -4) {
          in_EAX[0x402] = (float)((int)fVar11 + -4);
          local_90 = *(int *)((int)in_EAX + (int)fVar11 + 4);
          in_EAX[0x402] = (float)((int)fVar11 + -8);
          if (*(char *)((int)in_EAX + (int)fVar11) == 'f') {
            uVar15 = FUN_00463b2c();
            local_90 = (int)uVar15;
          }
        }
        fVar11 = in_EAX[0x402];
        if (-1 < (int)fVar11 + -4) {
          in_EAX[0x402] = (float)((int)fVar11 + -4);
          local_10 = *(int *)((int)in_EAX + (int)fVar11 + 4);
          in_EAX[0x402] = (float)((int)fVar11 + -8);
          if (*(char *)((int)in_EAX + (int)fVar11) == 'f') {
            uVar15 = FUN_00463b2c();
            local_10 = (int)uVar15;
          }
        }
        local_108 = (uint *)(uint)(local_10 <= local_90);
        FUN_004505b0(&local_108,'i',4,&local_108);
        break;
      case 0x42:
        fVar11 = in_EAX[0x402];
        pfVar7 = in_EAX + 2;
        fVar4 = (float)((int)fVar11 + -4);
        if (-1 < (int)fVar4) {
          in_EAX[0x402] = fVar4;
          local_ac = *(float *)((int)fVar4 + (int)pfVar7);
          fVar11 = (float)((int)fVar11 + -8);
          in_EAX[0x402] = fVar11;
          cVar1 = *(char *)((int)fVar11 + (int)pfVar7);
          if ((cVar1 != 'f') && (cVar1 == 'i')) {
            local_ac = (float)(int)local_ac;
          }
        }
        fVar11 = in_EAX[0x402];
        fVar4 = (float)((int)fVar11 + -4);
        if (-1 < (int)fVar4) {
          in_EAX[0x402] = fVar4;
          local_b4 = *(float *)((int)fVar4 + (int)pfVar7);
          fVar11 = (float)((int)fVar11 + -8);
          in_EAX[0x402] = fVar11;
          cVar1 = *(char *)((int)fVar11 + (int)pfVar7);
          if ((cVar1 != 'f') && (cVar1 == 'i')) {
            local_b4 = (float)(int)local_b4;
          }
        }
        local_104 = (undefined1 *)0x1;
        if (local_b4 < local_ac != (local_b4 == local_ac)) goto LAB_0044f05c;
        local_104 = (undefined1 *)0x0;
        FUN_004505b0(pfVar7,'i',4,&local_104);
        break;
      case 0x43:
        fVar11 = in_EAX[0x402];
        if (-1 < (int)fVar11 + -4) {
          in_EAX[0x402] = (float)((int)fVar11 + -4);
          local_d0 = *(int *)((int)in_EAX + (int)fVar11 + 4);
          in_EAX[0x402] = (float)((int)fVar11 + -8);
          if (*(char *)((int)in_EAX + (int)fVar11) == 'f') {
            uVar15 = FUN_00463b2c();
            local_d0 = (int)uVar15;
          }
        }
        fVar11 = in_EAX[0x402];
        if (-1 < (int)fVar11 + -4) {
          in_EAX[0x402] = (float)((int)fVar11 + -4);
          local_48 = *(int *)((int)in_EAX + (int)fVar11 + 4);
          in_EAX[0x402] = (float)((int)fVar11 + -8);
          if (*(char *)((int)in_EAX + (int)fVar11) == 'f') {
            uVar15 = FUN_00463b2c();
            local_48 = (int)uVar15;
          }
        }
        local_108 = (uint *)(uint)(local_d0 < local_48);
        FUN_004505b0(&local_108,'i',4,&local_108);
        break;
      case 0x44:
        fVar11 = in_EAX[0x402];
        pfVar7 = in_EAX + 2;
        fVar4 = (float)((int)fVar11 + -4);
        if (-1 < (int)fVar4) {
          in_EAX[0x402] = fVar4;
          local_9c = *(float *)((int)fVar4 + (int)pfVar7);
          fVar11 = (float)((int)fVar11 + -8);
          in_EAX[0x402] = fVar11;
          cVar1 = *(char *)((int)fVar11 + (int)pfVar7);
          if ((cVar1 != 'f') && (cVar1 == 'i')) {
            local_9c = (float)(int)local_9c;
          }
        }
        fVar11 = in_EAX[0x402];
        fVar4 = (float)((int)fVar11 + -4);
        if (-1 < (int)fVar4) {
          in_EAX[0x402] = fVar4;
          local_a4 = *(float *)((int)fVar4 + (int)pfVar7);
          fVar11 = (float)((int)fVar11 + -8);
          in_EAX[0x402] = fVar11;
          cVar1 = *(char *)((int)fVar11 + (int)pfVar7);
          if ((cVar1 != 'f') && (cVar1 == 'i')) {
            local_a4 = (float)(int)local_a4;
          }
        }
        local_104 = (undefined1 *)0x1;
        if (local_9c < local_a4) goto LAB_0044f05c;
        local_104 = (undefined1 *)0x0;
        FUN_004505b0(pfVar7,'i',4,&local_104);
        break;
      case 0x45:
        fVar11 = in_EAX[0x402];
        if (-1 < (int)fVar11 + -4) {
          in_EAX[0x402] = (float)((int)fVar11 + -4);
          local_80 = *(int *)((int)in_EAX + (int)fVar11 + 4);
          in_EAX[0x402] = (float)((int)fVar11 + -8);
          if (*(char *)((int)in_EAX + (int)fVar11) == 'f') {
            uVar15 = FUN_00463b2c();
            local_80 = (int)uVar15;
          }
        }
        fVar11 = in_EAX[0x402];
        if (-1 < (int)fVar11 + -4) {
          in_EAX[0x402] = (float)((int)fVar11 + -4);
          local_28 = *(int *)((int)in_EAX + (int)fVar11 + 4);
          in_EAX[0x402] = (float)((int)fVar11 + -8);
          if (*(char *)((int)in_EAX + (int)fVar11) == 'f') {
            uVar15 = FUN_00463b2c();
            local_28 = (int)uVar15;
          }
        }
        local_108 = (uint *)(uint)(local_80 <= local_28);
        FUN_004505b0(&local_108,'i',4,&local_108);
        break;
      case 0x46:
        fVar11 = in_EAX[0x402];
        pfVar7 = in_EAX + 2;
        fVar4 = (float)((int)fVar11 + -4);
        if (-1 < (int)fVar4) {
          in_EAX[0x402] = fVar4;
          local_8c = *(float *)((int)fVar4 + (int)pfVar7);
          fVar11 = (float)((int)fVar11 + -8);
          in_EAX[0x402] = fVar11;
          cVar1 = *(char *)((int)fVar11 + (int)pfVar7);
          if ((cVar1 != 'f') && (cVar1 == 'i')) {
            local_8c = (float)(int)local_8c;
          }
        }
        fVar11 = in_EAX[0x402];
        fVar4 = (float)((int)fVar11 + -4);
        if (-1 < (int)fVar4) {
          in_EAX[0x402] = fVar4;
          local_94 = *(float *)((int)fVar4 + (int)pfVar7);
          fVar11 = (float)((int)fVar11 + -8);
          in_EAX[0x402] = fVar11;
          cVar1 = *(char *)((int)fVar11 + (int)pfVar7);
          if ((cVar1 != 'f') && (cVar1 == 'i')) {
            local_94 = (float)(int)local_94;
          }
        }
        local_104 = (undefined1 *)0x1;
        if (local_8c <= local_94) goto LAB_0044f05c;
        local_104 = (undefined1 *)0x0;
        FUN_004505b0(pfVar7,'i',4,&local_104);
        break;
      case 0x47:
        fVar11 = in_EAX[0x402];
        if (-1 < (int)fVar11 + -4) {
          in_EAX[0x402] = (float)((int)fVar11 + -4);
          local_78 = *(int *)((int)in_EAX + (int)fVar11 + 4);
          in_EAX[0x402] = (float)((int)fVar11 + -8);
          if (*(char *)((int)in_EAX + (int)fVar11) == 'f') {
            uVar15 = FUN_00463b2c();
            local_78 = (int)uVar15;
          }
        }
        local_108 = (uint *)(uint)(local_78 == 0);
        FUN_004505b0(&local_108,'i',4,&local_108);
        break;
      case 0x48:
        fVar11 = in_EAX[0x402];
        pfVar7 = in_EAX + 2;
        fVar4 = (float)((int)fVar11 + -4);
        if (-1 < (int)fVar4) {
          in_EAX[0x402] = fVar4;
          local_84 = *(float *)((int)fVar4 + (int)pfVar7);
          fVar11 = (float)((int)fVar11 + -8);
          in_EAX[0x402] = fVar11;
          cVar1 = *(char *)((int)fVar11 + (int)pfVar7);
          if ((cVar1 != 'f') && (cVar1 == 'i')) {
            local_84 = (float)(int)local_84;
          }
        }
        local_104 = (undefined1 *)0x1;
        if (local_84 == _DAT_00470b04) goto LAB_0044f05c;
        local_104 = (undefined1 *)0x0;
        FUN_004505b0(pfVar7,'i',4,&local_104);
        break;
      case 0x49:
        fVar11 = in_EAX[0x402];
        if (-1 < (int)fVar11 + -4) {
          in_EAX[0x402] = (float)((int)fVar11 + -4);
          uVar10 = *(uint *)((int)in_EAX + (int)fVar11 + 4);
          in_EAX[0x402] = (float)((int)fVar11 + -8);
          local_74 = uVar10;
          if (*(char *)((int)in_EAX + (int)fVar11) == 'f') {
            uVar15 = FUN_00463b2c();
            local_74 = (uint)uVar15;
            uVar10 = extraout_ECX_07;
          }
        }
        fVar11 = in_EAX[0x402];
        if (-1 < (int)fVar11 + -4) {
          in_EAX[0x402] = (float)((int)fVar11 + -4);
          local_7c = *(int *)((int)in_EAX + (int)fVar11 + 4);
          in_EAX[0x402] = (float)((int)fVar11 + -8);
          if (*(char *)((int)in_EAX + (int)fVar11) == 'f') {
            uVar15 = FUN_00463b2c();
            local_7c = (int)uVar15;
            uVar10 = extraout_ECX_08;
          }
        }
        if ((local_7c != 0) || (local_104 = (undefined1 *)0x0, local_74 != 0)) {
          local_104 = (undefined1 *)0x1;
        }
        FUN_004505b0(uVar10,'i',4,&local_104);
        break;
      case 0x4a:
        fVar11 = in_EAX[0x402];
        if (-1 < (int)fVar11 + -4) {
          in_EAX[0x402] = (float)((int)fVar11 + -4);
          uVar10 = *(uint *)((int)in_EAX + (int)fVar11 + 4);
          in_EAX[0x402] = (float)((int)fVar11 + -8);
          local_64 = uVar10;
          if (*(char *)((int)in_EAX + (int)fVar11) == 'f') {
            uVar15 = FUN_00463b2c();
            local_64 = (uint)uVar15;
            uVar10 = extraout_ECX_09;
          }
        }
        fVar11 = in_EAX[0x402];
        if (-1 < (int)fVar11 + -4) {
          in_EAX[0x402] = (float)((int)fVar11 + -4);
          local_6c = *(int *)((int)in_EAX + (int)fVar11 + 4);
          in_EAX[0x402] = (float)((int)fVar11 + -8);
          if (*(char *)((int)in_EAX + (int)fVar11) == 'f') {
            uVar15 = FUN_00463b2c();
            local_6c = (int)uVar15;
            uVar10 = extraout_ECX_10;
          }
        }
        if ((local_6c == 0) || (local_104 = (undefined1 *)0x1, local_64 == 0)) {
          local_104 = (undefined1 *)0x0;
        }
        FUN_004505b0(uVar10,'i',4,&local_104);
        break;
      case 0x4b:
        fVar11 = in_EAX[0x402];
        if (-1 < (int)fVar11 + -4) {
          in_EAX[0x402] = (float)((int)fVar11 + -4);
          local_54 = *(uint *)((int)in_EAX + (int)fVar11 + 4);
          in_EAX[0x402] = (float)((int)fVar11 + -8);
          if (*(char *)((int)in_EAX + (int)fVar11) == 'f') {
            uVar15 = FUN_00463b2c();
            local_54 = (uint)uVar15;
          }
        }
        fVar11 = in_EAX[0x402];
        if (-1 < (int)fVar11 + -4) {
          in_EAX[0x402] = (float)((int)fVar11 + -4);
          local_5c = *(uint *)((int)in_EAX + (int)fVar11 + 4);
          in_EAX[0x402] = (float)((int)fVar11 + -8);
          if (*(char *)((int)in_EAX + (int)fVar11) == 'f') {
            uVar15 = FUN_00463b2c();
            local_5c = (uint)uVar15;
          }
        }
        local_108 = (uint *)(local_5c ^ local_54);
        FUN_004505b0(&local_108,'i',4,&local_108);
        break;
      case 0x4c:
        fVar11 = in_EAX[0x402];
        if (-1 < (int)fVar11 + -4) {
          in_EAX[0x402] = (float)((int)fVar11 + -4);
          local_44 = *(uint *)((int)in_EAX + (int)fVar11 + 4);
          in_EAX[0x402] = (float)((int)fVar11 + -8);
          if (*(char *)((int)in_EAX + (int)fVar11) == 'f') {
            uVar15 = FUN_00463b2c();
            local_44 = (uint)uVar15;
            uVar10 = extraout_ECX_11;
          }
        }
        fVar11 = in_EAX[0x402];
        if (-1 < (int)fVar11 + -4) {
          in_EAX[0x402] = (float)((int)fVar11 + -4);
          uVar10 = *(uint *)((int)in_EAX + (int)fVar11 + 4);
          in_EAX[0x402] = (float)((int)fVar11 + -8);
          local_4c = uVar10;
          if (*(char *)((int)in_EAX + (int)fVar11) == 'f') {
            uVar15 = FUN_00463b2c();
            local_4c = (uint)uVar15;
            uVar10 = extraout_ECX_12;
          }
        }
        local_108 = (uint *)(local_4c | local_44);
        FUN_004505b0(uVar10,'i',4,&local_108);
        break;
      case 0x4d:
        fVar11 = in_EAX[0x402];
        if (-1 < (int)fVar11 + -4) {
          in_EAX[0x402] = (float)((int)fVar11 + -4);
          local_34 = *(uint *)((int)in_EAX + (int)fVar11 + 4);
          in_EAX[0x402] = (float)((int)fVar11 + -8);
          if (*(char *)((int)in_EAX + (int)fVar11) == 'f') {
            uVar15 = FUN_00463b2c();
            local_34 = (uint)uVar15;
          }
        }
        fVar11 = in_EAX[0x402];
        if (-1 < (int)fVar11 + -4) {
          in_EAX[0x402] = (float)((int)fVar11 + -4);
          local_3c = *(uint *)((int)in_EAX + (int)fVar11 + 4);
          in_EAX[0x402] = (float)((int)fVar11 + -8);
          if (*(char *)((int)in_EAX + (int)fVar11) == 'f') {
            uVar15 = FUN_00463b2c();
            local_3c = (uint)uVar15;
          }
        }
        local_108 = (uint *)(local_3c & local_34);
        FUN_004505b0(&local_108,'i',4,&local_108);
        break;
      case 0x4e:
        uVar15 = ResolveEclIntOperand(uVar10,(int)in_EAX,0);
        local_108 = (uint *)uVar15;
        piVar5 = (int *)ResolveEclVariableValue(0);
        *piVar5 = (int)(uint *)uVar15 + -1;
        FUN_004505b0(extraout_ECX_14,'i',4,&local_108);
        break;
      case 0x4f:
        fVar11 = in_EAX[0x402];
        if (-1 < (int)fVar11 + -4) {
          in_EAX[0x402] = (float)((int)fVar11 + -4);
          local_2c = *(float *)((int)in_EAX + (int)fVar11 + 4);
          in_EAX[0x402] = (float)((int)fVar11 + -8);
          if ((*(char *)((int)in_EAX + (int)fVar11) != 'f') &&
             (*(char *)((int)in_EAX + (int)fVar11) == 'i')) {
            local_2c = (float)(int)local_2c;
          }
        }
        fVar14 = (float10)fsin((float10)local_2c);
        goto LAB_0044f934;
      case 0x50:
        fVar11 = in_EAX[0x402];
        if (-1 < (int)fVar11 + -4) {
          in_EAX[0x402] = (float)((int)fVar11 + -4);
          local_24 = *(float *)((int)in_EAX + (int)fVar11 + 4);
          in_EAX[0x402] = (float)((int)fVar11 + -8);
          if ((*(char *)((int)in_EAX + (int)fVar11) != 'f') &&
             (*(char *)((int)in_EAX + (int)fVar11) == 'i')) {
            local_24 = (float)(int)local_24;
          }
        }
        fVar14 = (float10)fcos((float10)local_24);
LAB_0044f934:
        local_108 = (uint *)(float)fVar14;
        FUN_004505b0(&local_108,'f',4,&local_108);
        break;
      case 0x51:
        fVar14 = ResolveEclFloatOperand(4.2039e-45);
        fVar11 = (float)fVar14;
        fVar14 = ResolveEclFloatOperand(2.8026e-45);
        fVar14 = (float10)NormalizeAngle((float)fVar14);
        FUN_004501b0(&local_c,(float)fVar14,fVar11);
        puVar6 = (undefined4 *)ResolveEclFloatDestination(0);
        *puVar6 = local_c;
        puVar6 = (undefined4 *)ResolveEclFloatDestination(1);
        *puVar6 = local_8;
        break;
      case 0x52:
        pfVar7 = (float *)ResolveEclFloatDestination(0);
        fVar14 = ResolveEclFloatOperand(0.0);
        fVar14 = (float10)NormalizeAngle((float)fVar14);
        *pfVar7 = (float)fVar14;
        break;
      case 0x53:
        uVar15 = ResolveEclIntOperand(uVar10,(int)in_EAX,0);
        local_108 = (uint *)uVar15;
        *in_EAX = *in_EAX - (float)(int)local_108;
        break;
      case 0x54:
        fVar4 = in_EAX[0x402];
        fVar11 = (float)((int)fVar4 + -4);
        if (-1 < (int)fVar11) {
          in_EAX[0x402] = fVar11;
          local_e4 = *(int *)((int)in_EAX + (int)fVar4 + 4);
          fVar11 = (float)((int)fVar4 + -8);
          in_EAX[0x402] = fVar11;
          if (*(char *)((int)in_EAX + (int)fVar4) == 'f') {
            uVar15 = FUN_00463b2c();
            local_e4 = -(int)uVar15;
            FUN_004505b0(extraout_ECX_13,'i',4,&local_e4);
            break;
          }
        }
        local_e4 = -local_e4;
        FUN_004505b0(fVar11,'i',4,&local_e4);
        break;
      case 0x55:
        fVar11 = in_EAX[0x402];
        if (-1 < (int)fVar11 + -4) {
          in_EAX[0x402] = (float)((int)fVar11 + -4);
          local_fc = *(float *)((int)in_EAX + (int)fVar11 + 4);
          in_EAX[0x402] = (float)((int)fVar11 + -8);
          if ((*(char *)((int)in_EAX + (int)fVar11) != 'f') &&
             (*(char *)((int)in_EAX + (int)fVar11) == 'i')) {
            local_fc = (float)(int)local_fc;
          }
        }
        local_fc = (float)-(int)local_fc;
        FUN_004505b0(&local_fc,'f',4,&local_fc);
        break;
      case 0x56:
        fVar14 = ResolveEclFloatOperand(1.4013e-45);
        local_100 = (float)fVar14;
        fVar14 = ResolveEclFloatOperand(2.8026e-45);
        local_104 = (undefined1 *)(float)fVar14;
        pfVar7 = (float *)ResolveEclFloatDestination(0);
        *pfVar7 = local_100 * local_100 + (float)local_104 * (float)local_104;
        break;
      case 0x57:
        fVar14 = ResolveEclFloatOperand(2.8026e-45);
        local_108 = (uint *)(float)fVar14;
        fVar14 = ResolveEclFloatOperand(0.0);
        local_104 = (undefined1 *)(float)((float10)(float)local_108 - fVar14);
        fVar14 = ResolveEclFloatOperand(4.2039e-45);
        local_108 = (uint *)(float)fVar14;
        fVar14 = ResolveEclFloatOperand(1.4013e-45);
        fVar14 = (float10)fpatan((float10)(float)local_108 - fVar14,(float10)(float)local_104);
        local_108 = (uint *)(float)fVar14;
        pfVar7 = (float *)ResolveEclFloatDestination(0);
        *pfVar7 = (float)local_108;
      }
switchD_0044e205_caseD_0:
      fVar11 = in_EAX[1];
      uVar10 = (uint)*(ushort *)((int)fVar11 + 6);
LAB_0044fb81:
      in_EAX[1] = (float)(uVar10 + (int)fVar11);
LAB_0044fb85:
    } while ((float)*(int *)in_EAX[1] < *in_EAX != ((float)*(int *)in_EAX[1] == *in_EAX));
  }
  *in_EAX = param_1 + *in_EAX;
  return 0;
}

