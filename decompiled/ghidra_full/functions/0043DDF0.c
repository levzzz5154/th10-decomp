/* Raw Ghidra reference; not compilable reconstruction. Address: 0043DDF0 */

int FUN_0043ddf0(int *param_1)

{
  int *piVar1;
  bool bVar2;
  int *piVar3;
  int iVar4;
  DWORD DVar5;
  int iVar6;
  int *piVar7;
  int iVar8;
  void *this;
  int iVar9;
  int *piVar10;
  int *piVar11;
  int *piVar12;
  ulonglong uVar13;
  int local_c;
  
  piVar3 = param_1;
  if (param_1[0x184] == 0) {
    return 0;
  }
  piVar1 = param_1 + 0x7e2;
  piVar11 = piVar1;
LAB_0043de18:
  iVar4 = DAT_00497798;
  bVar2 = false;
  switch(*piVar11) {
  case 1:
    if (((byte)DAT_00491d78 & 0x10) == 0) {
      FUN_0043d7d0(piVar11[1]);
      bVar2 = true;
    }
    else {
      if (piVar11[2] != 0) goto LAB_0043e20f;
      FUN_0043dab0();
      FUN_0043d7d0(piVar11[1]);
      bVar2 = true;
    }
    break;
  case 2:
    if ((((byte)DAT_00491d78 & 0x10) == 0) || (piVar11[1] < 0)) {
      this = (void *)param_1[0x1482];
      if (this != (void *)0x0) {
        iVar4 = piVar11[2];
        if (iVar4 == 0) goto LAB_0043e204;
        if (iVar4 != 1) {
          if (iVar4 == 2) {
            if (piVar11[1] < 0) {
              piVar7 = piVar11 + 3;
            }
            else {
              piVar7 = param_1 + piVar11[1] * 0x40 + 0x1042;
            }
            iVar4 = FUN_0043d2a0(piVar7,(int)param_1);
            SelectStreamRecord(iVar4 * 0x34 + param_1[0x7e1]);
          }
          else {
            if (iVar4 == 3) {
              if (*(undefined4 **)((int)this + 4) == (undefined4 *)0x0) {
                piVar7 = (int *)0x0;
              }
              else if (*(int *)((int)this + 0x10) == 0) {
                piVar7 = (int *)0x0;
              }
              else {
                piVar7 = (int *)**(undefined4 **)((int)this + 4);
              }
              FUN_0044dad0((int)this);
              iVar4 = *(int *)(*(int *)(*(int *)(param_1[0x1482] + 0xc) + 0x90) + 0x1c);
              goto LAB_0043df39;
            }
            if (iVar4 == 4) goto LAB_0043e17a;
            if (6 < iVar4) break;
          }
          goto LAB_0043e20f;
        }
        if (*(int *)(param_1[0x1482] + 0x74) != 0) goto switchD_0043de3e_default;
        FUN_0044cf20();
        goto LAB_0043e20f;
      }
    }
    else {
      this = (void *)piVar11[2];
      if (this != (void *)0x0) {
        if (this == (void *)0x2) {
          if (param_1[0x1482] != 0) {
            iVar4 = FUN_0044dad0(2);
joined_r0x0043df49:
            if (iVar4 < 0) break;
          }
        }
        else {
          if (this == (void *)0x5) {
            iVar4 = param_1[0x1482];
            piVar7 = (int *)0x0;
            if (*(undefined4 **)(iVar4 + 4) != (undefined4 *)0x0) {
              if (*(int *)(iVar4 + 0x10) == 0) {
                piVar7 = (int *)0x0;
              }
              else {
                piVar7 = (int *)**(undefined4 **)(iVar4 + 4);
              }
            }
            iVar4 = *(int *)(*(int *)(*(int *)(iVar4 + 0xc) + 0x90) + 0x1c);
LAB_0043df39:
            piVar11[1] = (uint)(iVar4 != 0);
            iVar4 = FUN_0044d110(piVar7);
            goto joined_r0x0043df49;
          }
          if (this == (void *)0x7) {
LAB_0043e17a:
            FUN_0044d440(this,0,1);
          }
          else if (0x13 < (int)this) break;
        }
LAB_0043e20f:
        piVar11[2] = piVar11[2] + 1;
        goto switchD_0043de3e_default;
      }
      iVar4 = FUN_0043d950();
      if (iVar4 == 0) goto LAB_0043e20f;
    }
    break;
  case 3:
    if (param_1[0x1482] != 0) {
      if (piVar11[2] == 0) {
LAB_0043e204:
        AggregatePlatformInterfaces();
        goto LAB_0043e20f;
      }
      if (piVar11[2] != 1) goto LAB_0043e20f;
    }
    break;
  case 4:
    if (param_1[0x1482] != 0) {
      iVar4 = piVar11[2];
      if (iVar4 == 0) goto LAB_0043e204;
      if (iVar4 == 1) {
        if (param_1[0x186] == 0) break;
        PostThreadMessageA(param_1[0x185],0x12,0,0);
      }
      else if (iVar4 == 2) {
        DVar5 = WaitForSingleObject((HANDLE)param_1[0x186],0x100);
        if (DVar5 == 0) {
          param_1[0x186] = 0;
        }
        else {
          PostThreadMessageA(param_1[0x185],0x12,0,0);
          piVar11[2] = piVar11[2] + -1;
        }
      }
      else if (iVar4 == 3) {
        CloseHandle((HANDLE)param_1[0x186]);
        CloseHandle((HANDLE)param_1[0x1483]);
        param_1[0x186] = 0;
        if ((undefined4 *)param_1[0x1482] != (undefined4 *)0x0) {
          (*(code *)**(undefined4 **)param_1[0x1482])(1);
          param_1[0x1482] = 0;
        }
        param_1[0x1482] = 0;
      }
      else if (iVar4 == 10) break;
      goto LAB_0043e20f;
    }
    break;
  case 5:
    if (DAT_00497798 != 0) {
      *(undefined4 *)(DAT_00497798 + 0x1c) = 1;
      uVar13 = FUN_00463b2c();
      *(int *)(iVar4 + 0x14) = (int)uVar13;
      *(int *)(iVar4 + 0x18) = (int)uVar13;
    }
    break;
  case 6:
    if (DAT_00491d63 == '\x01') {
      iVar4 = param_1[0x1482];
      if (*(int *)(iVar4 + 0x74) != 0) goto switchD_0043de3e_default;
      if (iVar4 != 0) {
        FUN_0044d5b0(iVar4);
      }
    }
    break;
  case 7:
    if (DAT_00491d63 == '\x01') {
      if (*(int *)(param_1[0x1482] + 0x74) != 0) goto switchD_0043de3e_default;
      if (param_1[0x1482] != 0) {
        InvokeConfiguredPlatform();
      }
    }
    break;
  case 8:
    if (param_1[0x1482] != 0) {
      SetOperationDeadline();
    }
    break;
  default:
    goto switchD_0043de3e_default;
  }
  iVar4 = 0;
  piVar10 = piVar11;
  piVar7 = piVar11;
  do {
    piVar7 = piVar7 + 0x43;
    piVar11 = piVar10;
    if (*piVar10 == 0) break;
    iVar4 = iVar4 + 1;
    piVar11 = piVar10 + 0x43;
    piVar12 = piVar7;
    for (iVar8 = 0x43; iVar8 != 0; iVar8 = iVar8 + -1) {
      *piVar10 = *piVar12;
      piVar12 = piVar12 + 1;
      piVar10 = piVar10 + 1;
    }
    piVar10 = piVar11;
  } while (iVar4 < 0x1f);
  if (!bVar2) goto switchD_0043de3e_default;
  goto LAB_0043de18;
switchD_0043de3e_default:
  if (DAT_00491d64 == '\0') {
    return *piVar1;
  }
  local_c = 0;
  piVar11 = param_1 + 0x194;
  param_1 = param_1 + 0x1a0;
  do {
    iVar4 = piVar11[-0xc];
    if (iVar4 < 0) break;
    iVar8 = *piVar11;
    piVar11[-0xc] = -1;
    if (iVar8 < 0) {
      piVar7 = (int *)piVar3[iVar4 + 0x82];
      if (piVar7 != (int *)0x0) {
        (**(code **)(*piVar7 + 0x48))(piVar7);
      }
      *piVar11 = 0;
    }
    else {
      iVar6 = 0;
      if (0 < iVar8) {
        iVar9 = *piVar11;
        piVar7 = param_1;
        do {
          iVar6 = iVar6 + *piVar7;
          piVar7 = piVar7 + 1;
          iVar9 = iVar9 + -1;
        } while (iVar9 != 0);
      }
      *piVar11 = 0;
      piVar7 = (int *)piVar3[iVar4 + 0x82];
      if (piVar7 != (int *)0x0) {
        (**(code **)(*piVar7 + 0x48))(piVar7);
        (**(code **)(*(int *)piVar3[iVar4 + 0x82] + 0x34))((int *)piVar3[iVar4 + 0x82],0);
        (**(code **)(*(int *)piVar3[iVar4 + 0x82] + 0x40))
                  ((int *)piVar3[iVar4 + 0x82],iVar6 / iVar8);
        piVar7 = (int *)piVar3[iVar4 + 0x82];
        if (DAT_00497858 == 0) {
          (**(code **)(*piVar7 + 0x3c))(piVar7,0xffffd8f0);
        }
        else {
          iVar8 = *piVar7;
          uVar13 = FUN_00463b2c();
          (**(code **)(iVar8 + 0x3c))(piVar3[iVar4 + 0x82],(int)uVar13 + -5000);
        }
        (**(code **)(*(int *)piVar3[iVar4 + 0x82] + 0x30))((int *)piVar3[iVar4 + 0x82],0,0,0);
      }
    }
    local_c = local_c + 1;
    param_1 = param_1 + 0x80;
    piVar11 = piVar11 + 1;
  } while (local_c < 0xc);
  return *piVar1;
}

