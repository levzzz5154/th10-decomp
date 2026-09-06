/* Raw Ghidra reference; not compilable reconstruction. Address: 00428280 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_00428280(int param_1)

{
  char *pcVar1;
  float *pfVar2;
  code *pcVar3;
  float fVar4;
  int *piVar5;
  int iVar6;
  undefined4 extraout_ECX;
  undefined4 extraout_ECX_00;
  int iVar7;
  void *extraout_EDX;
  void *pvVar8;
  void *this;
  float10 fVar9;
  ulonglong uVar10;
  int *local_8;
  int local_4;
  
  local_8 = (int *)(param_1 + 0x49c);
  this = (void *)(param_1 + 0x4bc);
  local_4 = 0x80;
LAB_004282b0:
  if (*(int *)((int)this + 0x20) != 0) {
    iVar7 = *(int *)((int)this + 0x38);
    if (((*(char *)(iVar7 + 0x1d) == '\x03') && (*(int *)((int)this + 0x20) == 1)) &&
       ((*(int *)(param_1 + 0x464) < 0 ||
        (pcVar1 = (char *)(iVar7 + 0x1c), iVar7 = *(int *)(param_1 + 0x3500), iVar7 <= *pcVar1 + -1)
        ))) {
      FUN_00409e50(iVar7);
      FUN_00409e50(extraout_ECX);
      iVar7 = *(int *)((int)this + 0x38);
      *(undefined4 *)((int)this + 0x20) = 2;
      *(undefined4 *)(param_1 + 0x42f4 + *(char *)(iVar7 + 0x1c) * 4) = 0;
    }
    if (((*(char *)(*(int *)((int)this + 0x38) + 0x1d) == '\x03') &&
        (*(int *)((int)this + 0x20) == 1)) &&
       (((DAT_0047770c != 0 && (*(int *)(DAT_0047770c + 0x9eb8) != 0)) || (DAT_00477704 == 0)))) {
      *(undefined4 *)((int)this + 0x20) = 2;
      FUN_00409e50(iVar7);
      FUN_00409e50(extraout_ECX_00);
      iVar7 = *(int *)((int)this + 0x38);
      *(undefined4 *)(param_1 + 0x42f4 + *(char *)(iVar7 + 0x1c) * 4) = 0;
    }
    if ((((*(char *)(*(int *)((int)this + 0x38) + 0x1d) == '\x03') &&
         (*(int *)((int)this + 0x30) == 0)) && (*(int *)((int)this + 0x20) == 1)) &&
       (*(int *)((int)this + 0x34) == 1)) {
      FUN_0040c4d0(iVar7);
      *(undefined4 *)((int)this + 0x34) = 0;
    }
    *(undefined4 *)((int)this + 0x30) = 0;
    pcVar3 = *(code **)(*(int *)((int)this + 0x38) + 0x28);
    if (pcVar3 != (code *)0x0) {
      (*pcVar3)();
    }
    if ((*(byte *)((int)this + 0x1c) & 1) == 0) {
      FUN_0044c5d0(this,*(float *)((int)this + 0x10),*(float *)((int)this + 0xc));
      *(undefined4 *)((int)this + 8) = 0;
    }
    else {
      *(float *)((int)this + 0x14) = *(float *)((int)this + 0x18) + *(float *)((int)this + 0x14);
      fVar9 = (float10)NormalizeAngle(*(float *)((int)this + 0xc) + *(float *)((int)this + 0x10));
      *(float *)((int)this + 0x10) = (float)fVar9;
    }
    pfVar2 = (float *)((int)this + -0xc);
    FUN_0044c2a0();
    pvVar8 = g_pGameStateManager;
    iVar7 = *(int *)((int)this + 0x24);
    if (iVar7 != 0) {
      for (piVar5 = *(int **)((int)g_pGameStateManager + 0x72dad4); piVar5 != (int *)0x0;
          piVar5 = (int *)piVar5[1]) {
        if (*(int *)*piVar5 == iVar7) goto LAB_00428410;
      }
      for (piVar5 = *(int **)((int)g_pGameStateManager + 0x72dadc); piVar5 != (int *)0x0;
          piVar5 = (int *)piVar5[1]) {
        if (*(int *)*piVar5 == iVar7) goto LAB_00428410;
      }
    }
    goto LAB_0042841a;
  }
  goto LAB_004285c3;
LAB_00428410:
  iVar7 = *piVar5;
  if (iVar7 != 0) {
    if (((*(char *)(*(int *)((int)this + 0x38) + 0x1d) == '\x03') ||
        (*(int *)((int)this + -0x1c) < 10)) ||
       (iVar6 = FUN_00428d70(pfVar2,*(float *)(*(int *)(iVar7 + 0x394) + 0x34) *
                                    *(float *)(iVar7 + 0x3c),
                             *(float *)(*(int *)(iVar7 + 0x394) + 0x30) * *(float *)(iVar7 + 0x40)),
       pvVar8 = extraout_EDX, iVar6 == 0)) {
      *(float *)(iVar7 + 0x340) = *pfVar2 + _DAT_00470b4c;
      *(float *)(iVar7 + 0x344) = *(float *)((int)this + -8) + _DAT_00470b48;
      *(undefined4 *)(iVar7 + 0x348) = *(undefined4 *)((int)this + -4);
      iVar6 = *(int *)((int)this + 0x28);
      if (iVar6 != 0) {
        iVar6 = FUN_004491c0(iVar6,(int)pvVar8,iVar6);
        if (iVar6 == 0) {
          *(undefined4 *)((int)this + 0x28) = 0;
        }
        else {
          *(float *)(iVar6 + 0x340) = *pfVar2 + _DAT_00470b4c;
          *(float *)(iVar6 + 0x344) = *(float *)((int)this + -8) + _DAT_00470b48;
          *(undefined4 *)(iVar6 + 0x348) = *(undefined4 *)((int)this + -4);
        }
      }
      if ((*(uint *)(iVar7 + 0x35c) & 0x8000000) != 0) {
        *(undefined4 *)(iVar7 + 0x2c) = *(undefined4 *)((int)this + 0x10);
        *(uint *)(iVar7 + 0x35c) = *(uint *)(iVar7 + 0x35c) | 4;
      }
      iVar7 = *(int *)((int)this + -0x1c);
      pfVar2 = *(float **)((int)this + -0x14);
      *local_8 = iVar7;
      if ((*pfVar2 <= _DAT_00470b68) || (_DAT_00470b64 <= *pfVar2)) {
        *(float *)((int)this + -0x18) = *(float *)((int)this + -0x18) + *pfVar2;
        uVar10 = FUN_00463b2c();
        *(int *)((int)this + -0x1c) = (int)uVar10;
      }
      else {
        fVar4 = *(float *)((int)this + -0x18) + _DAT_00470afc;
        *(int *)((int)this + -0x1c) = iVar7 + 1;
        *(float *)((int)this + -0x18) = fVar4;
      }
    }
    else {
      FUN_004492a0(*(undefined4 *)((int)this + 0x24),(int)extraout_EDX,
                   *(undefined4 *)((int)this + 0x24));
      *(undefined4 *)((int)this + 0x24) = 0;
      *(undefined4 *)((int)this + 0x20) = 0;
    }
    goto LAB_004285c3;
  }
LAB_0042841a:
  *(undefined4 *)((int)this + 0x20) = 0;
  iVar7 = *(int *)((int)this + 0x28);
  if (iVar7 != 0) {
    for (piVar5 = *(int **)((int)pvVar8 + 0x72dad4); piVar5 != (int *)0x0; piVar5 = (int *)piVar5[1]
        ) {
      if (*(int *)*piVar5 == iVar7) goto LAB_00428462;
    }
    piVar5 = *(int **)((int)pvVar8 + 0x72dadc);
    if (piVar5 != (int *)0x0) {
      do {
        if (*(int *)*piVar5 == iVar7) goto LAB_00428462;
        piVar5 = (int *)piVar5[1];
      } while (piVar5 != (int *)0x0);
      *(undefined4 *)((int)this + 0x28) = 0;
      *(undefined4 *)((int)this + 0x24) = 0;
      *(undefined4 *)((int)this + 0x28) = 0;
      goto LAB_004285c3;
    }
  }
  goto LAB_0042849f;
LAB_00428462:
  iVar7 = *piVar5;
  if ((iVar7 != 0) &&
     (*(uint *)(iVar7 + 0x35c) = *(uint *)(iVar7 + 0x35c) | 0x4000000, *(int *)(iVar7 + 0x18) == 0))
  {
    for (piVar5 = *(int **)(iVar7 + 0x14); piVar5 != (int *)0x0; piVar5 = (int *)piVar5[1]) {
      *(uint *)(*piVar5 + 0x35c) = *(uint *)(*piVar5 + 0x35c) | 0x4000000;
    }
  }
LAB_0042849f:
  *(undefined4 *)((int)this + 0x28) = 0;
  *(undefined4 *)((int)this + 0x24) = 0;
  *(undefined4 *)((int)this + 0x28) = 0;
LAB_004285c3:
  local_8 = local_8 + 0x17;
  this = (void *)((int)this + 0x5c);
  local_4 = local_4 + -1;
  if (local_4 == 0) {
    return 0;
  }
  goto LAB_004282b0;
}

