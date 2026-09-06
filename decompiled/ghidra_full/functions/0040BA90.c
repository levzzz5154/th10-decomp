/* Raw Ghidra reference; not compilable reconstruction. Address: 0040BA90 */

undefined4 * FUN_0040ba90(undefined4 *param_1,undefined4 param_2)

{
  void *pvVar1;
  undefined4 *puVar2;
  int *piVar3;
  int iVar4;
  undefined4 extraout_ECX;
  uint local_18;
  int *local_14;
  int local_10;
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  puStack_8 = &LAB_004654ce;
  local_c = ExceptionList;
  ExceptionList = &local_c;
  param_1[5] = param_1[5] & 0xfffffffe;
  param_1[10] = param_1[10] & 0xfffffffe;
  param_1[0xf] = param_1[0xf] & 0xfffffffe;
  param_1[0x34] = &PTR_FUN_004703e4;
  param_1[0x35] = 0;
  param_1[0x36] = 0;
  param_1[0x37] = 0;
  param_1[0x38] = 0;
  local_4 = 0;
  puVar2 = param_1;
  for (iVar4 = 0x3b; iVar4 != 0; iVar4 = iVar4 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  local_14 = param_1 + 0x10;
  local_18 = 0;
LAB_0040bb10:
  puVar2 = FUN_00449950();
  puVar2[8] = 0xf;
  puVar2[0xd7] = puVar2[0xd7] | 0x40000000;
  FUN_00449870(puVar2,local_18 + 0x42);
  pvVar1 = g_pGameStateManager;
  FUN_004489d0(extraout_ECX,(int)g_pGameStateManager);
  *local_14 = local_10;
  if (local_10 == 0) {
LAB_0040bb6c:
    iVar4 = 0;
  }
  else {
    for (piVar3 = *(int **)((int)pvVar1 + 0x72dad4); piVar3 != (int *)0x0; piVar3 = (int *)piVar3[1]
        ) {
      if (*(int *)*piVar3 == local_10) goto LAB_0040bba6;
    }
    piVar3 = *(int **)((int)pvVar1 + 0x72dadc);
    if (piVar3 == (int *)0x0) goto LAB_0040bb6c;
    do {
      if (*(int *)*piVar3 == local_10) goto LAB_0040bba6;
      piVar3 = (int *)piVar3[1];
    } while (piVar3 != (int *)0x0);
    iVar4 = 0;
  }
  goto LAB_0040bbac;
LAB_0040bba6:
  iVar4 = *piVar3;
  if (iVar4 == 0) {
LAB_0040bbac:
    *local_14 = 0;
  }
  *(undefined1 *)(iVar4 + 0x3a0) = 0x10;
  iVar4 = *local_14;
  if (iVar4 != 0) {
    for (piVar3 = *(int **)((int)pvVar1 + 0x72dad4); piVar3 != (int *)0x0; piVar3 = (int *)piVar3[1]
        ) {
      if (*(int *)*piVar3 == iVar4) goto LAB_0040bbf6;
    }
    piVar3 = *(int **)((int)pvVar1 + 0x72dadc);
    if (piVar3 != (int *)0x0) {
      do {
        if (*(int *)*piVar3 == iVar4) goto LAB_0040bbf6;
        piVar3 = (int *)piVar3[1];
      } while (piVar3 != (int *)0x0);
      iVar4 = 0;
      goto LAB_0040bbfc;
    }
  }
  iVar4 = 0;
LAB_0040bbfc:
  *local_14 = 0;
LAB_0040bc02:
  *(undefined1 *)(iVar4 + 0x3a1) = 0x10;
  iVar4 = *local_14;
  if (iVar4 == 0) {
LAB_0040bc0e:
    iVar4 = 0;
  }
  else {
    for (piVar3 = *(int **)((int)pvVar1 + 0x72dad4); piVar3 != (int *)0x0; piVar3 = (int *)piVar3[1]
        ) {
      if (*(int *)*piVar3 == iVar4) goto LAB_0040bc46;
    }
    piVar3 = *(int **)((int)pvVar1 + 0x72dadc);
    if (piVar3 == (int *)0x0) goto LAB_0040bc0e;
    do {
      if (*(int *)*piVar3 == iVar4) goto LAB_0040bc46;
      piVar3 = (int *)piVar3[1];
    } while (piVar3 != (int *)0x0);
    iVar4 = 0;
  }
LAB_0040bc4c:
  *local_14 = 0;
LAB_0040bc52:
  *(uint *)(iVar4 + 0x360) = *(uint *)(iVar4 + 0x360) | 2;
  local_18 = local_18 + 1;
  local_14 = local_14 + 1;
  if (4 < local_18) {
    param_1[0x15] = param_2;
    if ((param_1[5] & 1) == 0) {
      param_1[2] = 0;
      param_1[1] = 0xfff0bdc1;
      param_1[3] = 0;
      param_1[4] = &DAT_00476f78;
      param_1[5] = param_1[5] | 1;
    }
    param_1[2] = 0;
    param_1[3] = 0;
    param_1[1] = 0xffffffff;
    if ((param_1[10] & 1) == 0) {
      param_1[7] = 0;
      param_1[6] = 0xfff0bdc1;
      param_1[8] = 0;
      param_1[9] = &DAT_00476f78;
      param_1[10] = param_1[10] | 1;
    }
    param_1[7] = 0;
    param_1[8] = 0;
    param_1[6] = 0xffffffff;
    if ((param_1[0xf] & 1) == 0) {
      param_1[0xc] = 0;
      param_1[0xb] = 0xfff0bdc1;
      param_1[0xd] = 0;
      param_1[0xe] = &DAT_00476f78;
      param_1[0xf] = param_1[0xf] | 1;
    }
    param_1[0xc] = 0;
    param_1[0xd] = 0;
    param_1[0xb] = 0xffffffff;
    param_1[0x1d] = param_1[0x1d] | 1;
    param_1[0x1f] = 0xffffff;
    ExceptionList = local_c;
    return param_1;
  }
  goto LAB_0040bb10;
LAB_0040bbf6:
  iVar4 = *piVar3;
  if (iVar4 == 0) goto LAB_0040bbfc;
  goto LAB_0040bc02;
LAB_0040bc46:
  iVar4 = *piVar3;
  if (iVar4 != 0) goto LAB_0040bc52;
  goto LAB_0040bc4c;
}

