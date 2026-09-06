/* Raw Ghidra reference; not compilable reconstruction. Address: 004250B0 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 __fastcall FUN_004250b0(undefined4 param_1)

{
  void *pvVar1;
  undefined4 *puVar2;
  int iVar3;
  uint uVar4;
  undefined4 extraout_ECX;
  undefined4 extraout_ECX_00;
  int extraout_ECX_01;
  int *piVar5;
  undefined4 extraout_ECX_02;
  int *piVar6;
  int iVar7;
  int iVar8;
  int *piVar9;
  int unaff_EDI;
  bool bVar10;
  ulonglong uVar11;
  int local_18;
  int local_14;
  undefined4 local_10;
  
  iVar7 = 0;
  uVar4 = CONCAT31((int3)((uint)param_1 >> 8),(byte)DAT_00474e5c) & 0xffffff50;
  local_18 = 0;
  if ((char)uVar4 == 'P') {
    *(undefined4 *)(unaff_EDI + 0x454) = 5;
  }
  else if (((byte)DAT_00474e5c & 0x60) == 0x60) {
    *(undefined4 *)(unaff_EDI + 0x454) = 7;
  }
  else {
    uVar4 = CONCAT31((int3)(uVar4 >> 8),(byte)DAT_00474e5c) & 0xffffff90;
    if ((char)uVar4 == -0x70) {
      *(undefined4 *)(unaff_EDI + 0x454) = 6;
    }
    else if (((byte)DAT_00474e5c & 0xa0) == 0xa0) {
      *(undefined4 *)(unaff_EDI + 0x454) = 8;
    }
    else if ((DAT_00474e5c & 0x20) == 0) {
      if ((DAT_00474e5c & 0x10) == 0) {
        if ((DAT_00474e5c & 0x40) == 0) {
          if ((char)(byte)DAT_00474e5c < '\0') {
            *(undefined4 *)(unaff_EDI + 0x454) = 4;
          }
          else {
            *(undefined4 *)(unaff_EDI + 0x454) = 0;
          }
        }
        else {
          *(undefined4 *)(unaff_EDI + 0x454) = 3;
        }
      }
      else {
        *(undefined4 *)(unaff_EDI + 0x454) = 1;
      }
    }
    else {
      *(undefined4 *)(unaff_EDI + 0x454) = 2;
    }
  }
  if (((DAT_00477704 == 0) || (*(int *)(DAT_00477704 + 0x60) == 0)) ||
     (*(int *)(unaff_EDI + 0x48c) < 4)) {
    *(undefined4 *)(unaff_EDI + 0x4474) = 0;
    *(undefined4 *)(unaff_EDI + 0x4308) = 0x1e;
  }
  else {
    *(uint *)(unaff_EDI + 0x4474) = DAT_00474e5c >> 2 & 1;
    uVar4 = DAT_00474c6c;
    if (DAT_00474c6c + DAT_00474c68 * 3 == 5) {
      if ((DAT_00474e5c & 4) == 0) {
        if (*(int *)(unaff_EDI + 0x4308) < 0x1e) {
          *(int *)(unaff_EDI + 0x4308) = *(int *)(unaff_EDI + 0x4308) + 1;
        }
      }
      else {
        *(undefined4 *)(unaff_EDI + 0x4308) = 0;
      }
    }
  }
  if (*(int *)(unaff_EDI + 0x4474) == 0) {
    iVar3 = FUN_004491c0(uVar4,(int)g_pGameStateManager,*(int *)(unaff_EDI + 0x329c));
    if (iVar3 != 0) {
      FUN_00449210(extraout_ECX_00,(int)g_pGameStateManager,*(int *)(unaff_EDI + 0x329c));
    }
    *(undefined4 *)(unaff_EDI + 0x329c) = 0;
    switch(*(undefined4 *)(unaff_EDI + 0x454)) {
    case 1:
      local_18 = -*(int *)(unaff_EDI + 0x3d4);
      goto switchD_0042525b_default;
    case 2:
      local_18 = *(int *)(unaff_EDI + 0x3d4);
      goto switchD_0042525b_default;
    case 3:
      iVar7 = -*(int *)(unaff_EDI + 0x3d4);
      break;
    case 4:
      iVar7 = *(int *)(unaff_EDI + 0x3d4);
      break;
    case 5:
      iVar7 = -*(int *)(unaff_EDI + 0x3dc);
      local_18 = iVar7;
      break;
    case 6:
      iVar7 = *(int *)(unaff_EDI + 0x3dc);
      local_18 = -iVar7;
      break;
    case 7:
      iVar7 = -*(int *)(unaff_EDI + 0x3dc);
      local_18 = *(int *)(unaff_EDI + 0x3dc);
      break;
    case 8:
      iVar7 = *(int *)(unaff_EDI + 0x3dc);
      local_18 = iVar7;
      break;
    default:
      goto switchD_0042525b_default;
    }
    goto LAB_00425373;
  }
  if (*(int *)(unaff_EDI + 0x329c) == 0) {
    puVar2 = FUN_00449950();
    puVar2[8] = 9;
    puVar2[0xd7] = puVar2[0xd7] | 0x40000000;
    FUN_00449870(puVar2,0x160);
    FUN_004489d0(extraout_ECX,(int)g_pGameStateManager);
    *(undefined4 *)(unaff_EDI + 0x329c) = local_10;
  }
  switch(*(undefined4 *)(unaff_EDI + 0x454)) {
  case 1:
    local_18 = -*(int *)(unaff_EDI + 0x3d8);
    goto switchD_0042525b_default;
  case 2:
    local_18 = *(int *)(unaff_EDI + 0x3d8);
    goto switchD_0042525b_default;
  case 3:
    iVar7 = -*(int *)(unaff_EDI + 0x3d8);
    break;
  case 4:
    iVar7 = *(int *)(unaff_EDI + 0x3d8);
    break;
  case 5:
    iVar7 = -*(int *)(unaff_EDI + 0x3e0);
    local_18 = iVar7;
    break;
  case 6:
    iVar7 = *(int *)(unaff_EDI + 0x3e0);
    local_18 = -iVar7;
    break;
  case 7:
    iVar7 = -*(int *)(unaff_EDI + 0x3e0);
    local_18 = *(int *)(unaff_EDI + 0x3e0);
    break;
  case 8:
    iVar7 = *(int *)(unaff_EDI + 0x3e0);
    local_18 = iVar7;
    break;
  default:
    goto switchD_0042525b_default;
  }
LAB_00425373:
  if ((iVar7 < 0) && (-1 < *(int *)(unaff_EDI + 0x44c))) {
    FUN_0043e710(*(undefined2 **)(unaff_EDI + 0x10));
LAB_00425399:
    if ((0 < iVar7) && (*(int *)(unaff_EDI + 0x44c) < 1)) goto LAB_004253e5;
    if (iVar7 == 0) goto LAB_004253d6;
  }
  else {
    if (iVar7 != 0) goto LAB_00425399;
switchD_0042525b_default:
    iVar3 = *(int *)(unaff_EDI + 0x44c);
    bVar10 = false;
    if (iVar3 < 0) {
      FUN_0043e710(*(undefined2 **)(unaff_EDI + 0x10));
LAB_004253d6:
      iVar3 = *(int *)(unaff_EDI + 0x44c);
      bVar10 = iVar3 < 0;
    }
    if (iVar3 != 0 && !bVar10) {
LAB_004253e5:
      FUN_0043e710(*(undefined2 **)(unaff_EDI + 0x10));
    }
  }
  *(int *)(unaff_EDI + 0x44c) = iVar7;
  *(int *)(unaff_EDI + 0x450) = local_18;
  uVar11 = FUN_00463b2c();
  *(int *)(unaff_EDI + 0x3f0) = (int)uVar11;
  uVar11 = FUN_00463b2c();
  *(int *)(unaff_EDI + 0x3f4) = (int)uVar11;
  iVar3 = *(int *)(unaff_EDI + 0x3cc) + *(int *)(unaff_EDI + 0x3f0);
  iVar8 = *(int *)(unaff_EDI + 0x3d0) + *(int *)(unaff_EDI + 0x3f4);
  *(int *)(unaff_EDI + 0x3cc) = iVar3;
  *(int *)(unaff_EDI + 0x3d0) = iVar8;
  if (iVar3 < -0x47e0) {
    *(undefined4 *)(unaff_EDI + 0x3cc) = 0xffffb820;
  }
  else if (0x47e0 < iVar3) {
    *(undefined4 *)(unaff_EDI + 0x3cc) = 0x47e0;
  }
  if (iVar8 < 0xc80) {
    *(undefined4 *)(unaff_EDI + 0x3d0) = 0xc80;
  }
  else if (0xa8c0 < iVar8) {
    *(undefined4 *)(unaff_EDI + 0x3d0) = 0xa8c0;
  }
  pvVar1 = g_pGameStateManager;
  *(float *)(unaff_EDI + 0x3c0) = (float)*(int *)(unaff_EDI + 0x3cc) * _DAT_00470b00;
  *(float *)(unaff_EDI + 0x3c4) = (float)*(int *)(unaff_EDI + 0x3d0) * _DAT_00470b00;
  iVar3 = FUN_004491c0(iVar8,(int)pvVar1,*(int *)(unaff_EDI + 0x329c));
  if (iVar3 == 0) {
    *(undefined4 *)(unaff_EDI + 0x329c) = 0;
  }
  else {
    FUN_004492f0(*(undefined4 *)(unaff_EDI + 0x3c8),(int)g_pGameStateManager,
                 *(int *)(unaff_EDI + 0x329c));
  }
  if ((*(int *)(unaff_EDI + 0x4474) == 0) && ((local_18 != 0 || (iVar7 != 0)))) {
    iVar7 = 0x20;
    if (*(int *)(unaff_EDI + 0x3500) * 8 < 0x20) {
      puVar2 = (undefined4 *)(unaff_EDI + 0x446c);
      do {
        iVar3 = *(int *)(unaff_EDI + 0x3500) * 0x40;
        *puVar2 = *(undefined4 *)(iVar3 + 0x436c + unaff_EDI);
        puVar2[1] = *(undefined4 *)(iVar3 + unaff_EDI + 0x4370);
        iVar7 = iVar7 + -1;
        puVar2 = puVar2 + -2;
      } while (*(int *)(unaff_EDI + 0x3500) * 8 < iVar7);
      if (iVar7 < 1) goto LAB_004255a1;
    }
    puVar2 = (undefined4 *)(unaff_EDI + 0x4370 + iVar7 * 8);
    do {
      puVar2[-1] = puVar2[-3];
      *puVar2 = puVar2[-2];
      puVar2 = puVar2 + -2;
      iVar7 = iVar7 + -1;
    } while (iVar7 != 0);
  }
LAB_004255a1:
  *(undefined4 *)(unaff_EDI + 0x436c) = *(undefined4 *)(unaff_EDI + 0x3cc);
  *(undefined4 *)(unaff_EDI + 0x4370) = *(undefined4 *)(unaff_EDI + 0x3d0);
  piVar6 = (int *)(unaff_EDI + 0x32e0);
  local_14 = 4;
  do {
    piVar5 = piVar6 + -0x10;
    if (piVar6[-0x10] != 0) {
      piVar9 = piVar6 + 3;
      if (*(int *)(unaff_EDI + 0x4474) == 0) {
        piVar9 = piVar6 + 1;
      }
      iVar7 = piVar9[1];
      iVar3 = *(int *)(unaff_EDI + 0x3d0);
      piVar6[-3] = *piVar9 + *(int *)(unaff_EDI + 0x3cc);
      piVar6[-2] = iVar3 + iVar7;
      if ((code *)piVar6[0x14] != (code *)0x0) {
        (*(code *)piVar6[0x14])();
        piVar5 = (int *)extraout_ECX_01;
      }
      if (piVar6[0x13] == 0) {
        iVar7 = *(int *)(unaff_EDI + 0x4308);
        if (0x1d < iVar7) {
          piVar5 = (int *)((piVar6[-2] - *piVar6) * iVar7);
          iVar7 = ((piVar6[-3] - piVar6[-1]) * iVar7) / 100;
          if ((iVar7 != 0) || ((int)piVar5 / 100 != 0)) {
            piVar6[-1] = piVar6[-1] + iVar7;
            piVar5 = (int *)(*piVar6 + (int)piVar5 / 100);
            goto LAB_00425686;
          }
          piVar6[-1] = piVar6[-3];
          *piVar6 = piVar6[-2];
        }
      }
      else {
        piVar6[0x13] = 0;
        piVar6[-1] = piVar6[-3];
        piVar5 = (int *)piVar6[-2];
LAB_00425686:
        *piVar6 = (int)piVar5;
      }
      pvVar1 = g_pGameStateManager;
      FUN_00449350(piVar5,(int)g_pGameStateManager,piVar6[10]);
      FUN_00449350(extraout_ECX_02,(int)pvVar1,piVar6[0xb]);
    }
    piVar6 = piVar6 + 0x26;
    local_14 = local_14 + -1;
    if (local_14 == 0) {
      return 0;
    }
  } while( true );
}

