/* Raw Ghidra reference; not compilable reconstruction. Address: 0042CDF0 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 __fastcall FUN_0042cdf0(void *param_1)

{
  size_t *psVar1;
  char cVar2;
  float *pfVar3;
  float fVar4;
  void *pvVar5;
  size_t *in_EAX;
  char *pcVar6;
  undefined4 *puVar7;
  int *piVar8;
  undefined4 extraout_ECX;
  undefined4 extraout_ECX_00;
  undefined4 extraout_ECX_01;
  undefined4 extraout_ECX_02;
  undefined4 extraout_ECX_03;
  void *this;
  void *extraout_ECX_04;
  void *extraout_ECX_05;
  int iVar9;
  size_t sVar10;
  void *pvVar11;
  ulonglong uVar12;
  
  if ((in_EAX[7] == 1) || (in_EAX[7] == 2)) {
    param_1 = (void *)((int)DAT_00474ca4 + 1);
    if ((DAT_00474e30 & 0x160b) == 0) {
      DAT_00474ca4 = param_1;
      if (899 < (int)param_1) {
        DAT_00474ca0 = (void *)((uint)DAT_00474ca0 & 0xffffffbf | 0x20);
        pcVar6 = (&PTR_s_demo_demo1_rpy_00476ff8)[DAT_00474ca8];
        iVar9 = (int)&DAT_00477710 - (int)pcVar6;
        do {
          cVar2 = *pcVar6;
          pcVar6[iVar9] = cVar2;
          pcVar6 = pcVar6 + 1;
        } while (cVar2 != '\0');
        puVar7 = FUN_004296f0(&DAT_00477710);
        DAT_00474ca8 = DAT_00474ca8 + 1 & 0x80000003;
        if ((int)DAT_00474ca8 < 0) {
          DAT_00474ca8 = (DAT_00474ca8 - 1 | 0xfffffffc) + 1;
        }
        DAT_00474c7c = 0;
        piVar8 = puVar7 + 0x2c;
        do {
          if (*piVar8 != 0) break;
          DAT_00474c7c = DAT_00474c7c + 1;
          piVar8 = piVar8 + 9;
        } while (DAT_00474c7c < 8);
        DAT_00491fb8 = 0xc;
        iVar9 = puVar7[6];
        DAT_00474c68 = *(undefined4 *)(iVar9 + 0x50);
        DAT_00477848 = &DAT_00474788 + DAT_00474c7c * 0x30;
        DAT_00474c6c = *(undefined4 *)(iVar9 + 0x54);
        DAT_00474c78 = DAT_00474c74;
        DAT_00474c74 = *(int *)(iVar9 + 0x58);
        DAT_00474c80 = DAT_00474c7c;
        FUN_004294a0((int)puVar7);
        _free(puVar7);
        param_1 = (void *)(uint)(in_EAX[7] != 1);
        DAT_00474ca4 = (void *)0x0;
        DAT_00491c00 = param_1;
      }
    }
    else {
      DAT_00474ca4 = (void *)0x0;
    }
  }
  pvVar5 = g_pGameStateManager;
  pvVar11 = DAT_00491c00;
  switch(in_EAX[7]) {
  case 0:
    FUN_004493e0(param_1,*(int *)((int)g_pGameStateManager + 0x3ad084));
    FUN_004493e0(extraout_ECX,*(int *)((int)pvVar5 + 0x3ad088));
    FUN_004493e0(extraout_ECX_00,*(int *)((int)pvVar5 + 0x3ad074));
    FUN_004493e0(extraout_ECX_01,*(int *)((int)pvVar5 + 0x3ad078));
    FUN_004493e0(extraout_ECX_02,*(int *)((int)pvVar5 + 0x3ad06c));
    puVar7 = (undefined4 *)((int)g_pGameThread + 0x89a4);
    FUN_00409e50(extraout_ECX_03);
    *puVar7 = 0;
    if (pvVar11 != (void *)0x3) {
      if (((uint)DAT_00474ca0 & 0x20) == 0) {
        FUN_00420a90(0,"bgm/th10_02.wav");
        FUN_00420b10(this,0,0);
        pvVar11 = DAT_00491c00;
      }
      else {
        DAT_00474c74 = DAT_00474c78;
      }
      param_1 = (void *)((uint)DAT_00474ca0 & 0xffffffdf);
      DAT_00474ca0 = param_1;
      if (pvVar11 == (void *)0x0) {
        FUN_0042c5c0(1);
        DAT_00491c00 = (void *)0x1;
        param_1 = extraout_ECX_04;
      }
      else {
        if (pvVar11 == (void *)0x1) {
          if (DAT_00474c74 == 4) {
            sVar10 = in_EAX[0xb];
            if (sVar10 == 0) {
              in_EAX[9] = 1;
            }
            else if ((int)sVar10 < 2) {
              in_EAX[9] = sVar10 - 1;
            }
            else {
              in_EAX[9] = 1;
            }
          }
          FUN_0042c5c0(2);
          FUN_0042c670((int)in_EAX);
          param_1 = extraout_ECX_05;
          goto switchD_0042ce37_caseD_2;
        }
        if (pvVar11 == (void *)0x2) {
          psVar1 = in_EAX + 9;
          in_EAX[0xb] = 10;
          sVar10 = in_EAX[0xb];
          if (sVar10 == 0) {
            *psVar1 = 3;
          }
          else if ((int)sVar10 < 4) {
            *psVar1 = sVar10 - 1;
          }
          else {
            *psVar1 = 3;
          }
          FUN_0044be20();
          FUN_0042c5c0(0xc);
          FUN_0042c670((int)in_EAX);
          FUN_0042c770(0x5b);
          DAT_00491c00 = (void *)0x1;
          *(uint *)(in_EAX[4] + 4) = *(uint *)(in_EAX[4] + 4) | 2;
          goto switchD_0042ce37_caseD_c;
        }
      }
      goto switchD_0042ce37_caseD_1;
    }
    psVar1 = in_EAX + 9;
    in_EAX[0xb] = 10;
    sVar10 = in_EAX[0xb];
    if (sVar10 == 0) {
      *psVar1 = 0;
    }
    else if ((int)sVar10 < 1) {
      *psVar1 = sVar10 - 1;
    }
    else {
      *psVar1 = 0;
    }
    FUN_0044be20();
    FUN_0042c5c0(0xf);
    FUN_0042c670((int)in_EAX);
    FUN_0042c770(0x5b);
    param_1 = (void *)(*(uint *)(in_EAX[4] + 4) | 2);
    DAT_00491c00 = (void *)0x1;
    *(void **)(in_EAX[4] + 4) = param_1;
  case 0xf:
    FUN_00432cb0(param_1,(int)in_EAX);
    break;
  case 1:
switchD_0042ce37_caseD_1:
    FUN_0042d300(param_1);
    break;
  case 2:
switchD_0042ce37_caseD_2:
    *(uint *)(in_EAX[4] + 4) = *(uint *)(in_EAX[4] + 4) | 2;
    FUN_0042d420(param_1);
    break;
  case 3:
    DAT_00491fb8 = ~(DAT_00491ff4 >> 0xc) & 1 | 2;
  case 10:
  case 0xd:
    FUN_00420c00(param_1);
    break;
  case 4:
    FUN_0042d920((int)in_EAX);
    break;
  case 5:
    FUN_0042f540();
    break;
  case 6:
    FUN_00430320(param_1,(int)in_EAX);
    break;
  case 7:
    FUN_004306a0(param_1,(int)in_EAX);
    break;
  case 8:
    FUN_00430a60(param_1,(int)in_EAX);
    break;
  case 9:
    FUN_00430ff0(param_1,(int)in_EAX);
    break;
  case 0xb:
    FUN_00431ee0(param_1,(int)in_EAX);
    break;
  case 0xc:
switchD_0042ce37_caseD_c:
    FUN_004315c0((int)in_EAX);
    break;
  case 0xe:
    FUN_00433ef0(param_1,in_EAX);
    break;
  case 0x10:
    FUN_00433570(param_1,(int)in_EAX);
  }
  pfVar3 = (float *)in_EAX[0xaf];
  in_EAX[0xac] = in_EAX[0xad];
  if ((_DAT_00470b68 < *pfVar3) && (*pfVar3 < _DAT_00470b64)) {
    fVar4 = (float)in_EAX[0xae] + _DAT_00470afc;
    sVar10 = in_EAX[0xad] + 1;
    in_EAX[0xad] = sVar10;
    in_EAX[0xae] = (size_t)fVar4;
    return CONCAT44(sVar10,1);
  }
  in_EAX[0xae] = (size_t)(*pfVar3 + (float)in_EAX[0xae]);
  uVar12 = FUN_00463b2c();
  in_EAX[0xad] = (size_t)uVar12;
  return CONCAT44((int)(uVar12 >> 0x20),1);
}

