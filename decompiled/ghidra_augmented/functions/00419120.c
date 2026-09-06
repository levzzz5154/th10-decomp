/* Raw Ghidra reference; not compilable reconstruction. Address: 00419120 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_00419120(int param_1,int param_2)

{
  void *_Memory;
  int iVar1;
  undefined4 uVar2;
  undefined4 *in_EAX;
  undefined4 *puVar3;
  int iVar4;
  int *piVar5;
  float *pfVar6;
  float *pfVar7;
  void *pvVar8;
  ulonglong uVar9;
  float local_30;
  float local_2c;
  float local_28;
  undefined4 local_24;
  float local_20;
  float local_1c;
  float local_18;
  undefined4 local_14;
  float local_10;
  float local_c;
  float local_8;
  undefined4 local_4;
  
  pvVar8 = g_pGameStateManager;
joined_r0x0041912a:
  do {
    if (in_EAX == (undefined4 *)0x0) {
      return 0;
    }
    puVar3 = (undefined4 *)in_EAX[1];
    _Memory = (void *)*in_EAX;
    if ((*(int *)((int)_Memory + 0x68) == 0) || (*(int *)((int)_Memory + 0x68) == DAT_00474c84)) {
      *(int *)((int)_Memory + 0x60) = *(int *)((int)_Memory + 0x60) + -1;
    }
    in_EAX = puVar3;
  } while (0 < *(int *)((int)_Memory + 0x60));
  iVar4 = *(int *)(param_1 + 0x1a4);
  iVar1 = *(int *)(param_1 + 0xdc + iVar4 * 4);
  if (iVar1 != 0) {
    for (piVar5 = *(int **)((int)pvVar8 + 0x72dad4); piVar5 != (int *)0x0; piVar5 = (int *)piVar5[1]
        ) {
      if (*(int *)*piVar5 == iVar1) goto LAB_004191af;
    }
    for (piVar5 = *(int **)((int)pvVar8 + 0x72dadc); piVar5 != (int *)0x0; piVar5 = (int *)piVar5[1]
        ) {
      if (*(int *)*piVar5 == iVar1) goto LAB_004191af;
    }
  }
  goto LAB_004191ef;
LAB_004191af:
  iVar1 = *piVar5;
  if ((iVar1 != 0) &&
     (*(uint *)(iVar1 + 0x35c) = *(uint *)(iVar1 + 0x35c) | 0x4000000, *(int *)(iVar1 + 0x18) == 0))
  {
    for (piVar5 = *(int **)(iVar1 + 0x14); piVar5 != (int *)0x0; piVar5 = (int *)piVar5[1]) {
      *(uint *)(*piVar5 + 0x35c) = *(uint *)(*piVar5 + 0x35c) | 0x4000000;
    }
  }
LAB_004191ef:
  *(undefined4 *)(param_1 + 0xdc + iVar4 * 4) = 0;
  *(float *)((int)_Memory + 4) =
       *(float *)((int)_Memory + 0x7c) * _DAT_00470bd0 + *(float *)((int)_Memory + 4);
  if (*(float *)((int)_Memory + 0x7c) < _DAT_00470afc !=
      (*(float *)((int)_Memory + 0x7c) == _DAT_00470afc)) {
    puVar3 = (undefined4 *)FUN_00448db0(*(undefined2 **)((int)g_pGameThread + 0x899c));
    pvVar8 = g_pGameStateManager;
    *(undefined4 *)(param_1 + 0xdc + *(int *)(param_1 + 0x1a4) * 4) = *puVar3;
    iVar4 = *(int *)(param_1 + 0xdc + *(int *)(param_1 + 0x1a4) * 4);
    if (iVar4 != 0) {
      for (piVar5 = *(int **)((int)pvVar8 + 0x72dad4); piVar5 != (int *)0x0;
          piVar5 = (int *)piVar5[1]) {
        if (*(int *)*piVar5 == iVar4) goto LAB_0041929f;
      }
      piVar5 = *(int **)((int)pvVar8 + 0x72dadc);
      if (piVar5 != (int *)0x0) {
        do {
          if (*(int *)*piVar5 == iVar4) goto LAB_0041929f;
          piVar5 = (int *)piVar5[1];
        } while (piVar5 != (int *)0x0);
        iVar4 = 0;
        goto LAB_004192a5;
      }
    }
    iVar4 = 0;
    goto LAB_004192a5;
  }
  if (*(float *)((int)_Memory + 0x7c) < _DAT_00470b08 !=
      (*(float *)((int)_Memory + 0x7c) == _DAT_00470b08)) {
    puVar3 = (undefined4 *)FUN_00448db0(*(undefined2 **)((int)g_pGameThread + 0x899c));
    *(undefined4 *)(param_1 + 0xdc + *(int *)(param_1 + 0x1a4) * 4) = *puVar3;
    iVar1 = *(int *)(param_1 + 0x1a4);
    uVar2 = *(undefined4 *)(param_1 + 0xdc + iVar1 * 4);
    iVar4 = FUN_004491c0(uVar2,(int)g_pGameStateManager,uVar2);
    if (iVar4 == 0) {
      *(undefined4 *)(param_1 + 0xdc + iVar1 * 4) = 0;
    }
    uVar9 = FUN_00463b2c();
    *(char *)(iVar4 + 0x3a1) = (char)uVar9;
    *(char *)(iVar4 + 0x3a0) = (char)uVar9;
    local_18 = *(float *)((int)_Memory + 0x7c) * _DAT_00470ce4;
    local_20 = *(float *)((int)_Memory + 0x7c) * _DAT_00470b0c;
    local_14 = 0;
    local_1c = local_20;
    FUN_0041ab70(&local_20,&local_18,8,4);
    pvVar8 = g_pGameStateManager;
    goto LAB_00419440;
  }
  puVar3 = (undefined4 *)FUN_00448db0(*(undefined2 **)((int)g_pGameThread + 0x899c));
  pvVar8 = g_pGameStateManager;
  *(undefined4 *)(param_1 + 0xdc + *(int *)(param_1 + 0x1a4) * 4) = *puVar3;
  iVar1 = *(int *)(param_1 + 0x1a4);
  uVar2 = *(undefined4 *)(param_1 + 0xdc + iVar1 * 4);
  iVar4 = FUN_004491c0(uVar2,(int)pvVar8,uVar2);
  if (iVar4 == 0) {
    *(undefined4 *)(param_1 + 0xdc + iVar1 * 4) = 0;
  }
  *(undefined1 *)(iVar4 + 0x3a1) = 0x1e;
  *(undefined1 *)(iVar4 + 0x3a0) = 0x1e;
  local_8 = *(float *)((int)_Memory + 0x7c) * _DAT_00470ce4;
  local_4 = 0;
  pfVar6 = &local_10;
  pfVar7 = &local_8;
  local_10 = *(float *)((int)_Memory + 0x7c) * _DAT_00470b0c;
  local_c = local_10;
LAB_00419435:
  FUN_0041ab70(pfVar6,pfVar7,8,4);
LAB_00419440:
  iVar1 = *(int *)((int)_Memory + 100);
  if (iVar1 == 0) {
    puVar3 = (undefined4 *)(param_1 + 0x104 + *(int *)(param_1 + 0x1a4) * 0xc);
    *puVar3 = *(undefined4 *)(iVar4 + 0x340);
    puVar3[1] = *(undefined4 *)(iVar4 + 0x344);
    puVar3[2] = *(undefined4 *)(iVar4 + 0x348);
    *(undefined4 *)(param_1 + 0x17c + *(int *)(param_1 + 0x1a4) * 4) =
         *(undefined4 *)((int)_Memory + 0x80);
    FUN_00447bb0(pvVar8,0xffffff,(char *)((int)_Memory + 0x1c));
    pvVar8 = g_pGameStateManager;
  }
  else if (iVar1 == 1) {
    puVar3 = (undefined4 *)(param_1 + 0x104 + *(int *)(param_1 + 0x1a4) * 0xc);
    *puVar3 = *(undefined4 *)(iVar4 + 0x340);
    puVar3[1] = *(undefined4 *)(iVar4 + 0x344);
    puVar3[2] = *(undefined4 *)(iVar4 + 0x348);
    pfVar6 = (float *)(param_1 + 0x104 + *(int *)(param_1 + 0x1a4) * 0xc);
    *pfVar6 = *(float *)((int)_Memory + 0x80) * _DAT_00470b0c + *pfVar6;
    *(undefined4 *)(param_1 + 0x17c + *(int *)(param_1 + 0x1a4) * 4) =
         *(undefined4 *)((int)_Memory + 0x80);
    FUN_00447a50(pvVar8,0xffffff,(char *)((int)_Memory + 0x1c));
    *(uint *)(iVar4 + 0x35c) = *(uint *)(iVar4 + 0x35c) & 0xfff7ffff | 0x40000;
    pvVar8 = g_pGameStateManager;
  }
  else if (iVar1 == 2) {
    puVar3 = (undefined4 *)(param_1 + 0x104 + *(int *)(param_1 + 0x1a4) * 0xc);
    *puVar3 = *(undefined4 *)(iVar4 + 0x340);
    puVar3[1] = *(undefined4 *)(iVar4 + 0x344);
    puVar3[2] = *(undefined4 *)(iVar4 + 0x348);
    pfVar6 = (float *)(param_1 + 0x104 + *(int *)(param_1 + 0x1a4) * 0xc);
    *pfVar6 = *pfVar6 - *(float *)((int)_Memory + 0x80) * _DAT_00470b0c;
    *(undefined4 *)(param_1 + 0x17c + *(int *)(param_1 + 0x1a4) * 4) =
         *(undefined4 *)((int)_Memory + 0x80);
    FUN_00447ae0(pvVar8,0xffffff,(char *)((int)_Memory + 0x1c));
    *(uint *)(iVar4 + 0x35c) = *(uint *)(iVar4 + 0x35c) & 0xfffbffff | 0x80000;
    pvVar8 = g_pGameStateManager;
  }
  *(undefined4 *)(iVar4 + 0x2fc) = *(undefined4 *)((int)_Memory + 0x84);
  *(undefined1 *)(iVar4 + 0x2ff) = 0;
  *(undefined4 *)(iVar4 + 0x30c) = *(undefined4 *)((int)_Memory + 0x6c);
  *(uint *)(iVar4 + 0x310) = (uint)*(byte *)((int)_Memory + 0x87);
  *(int *)(param_1 + 0x1a4) = (*(int *)(param_1 + 0x1a4) + 1) % 10;
  if (*(int *)((int)_Memory + 0x10) != 0) {
    *(undefined4 *)(*(int *)((int)_Memory + 0x10) + 8) = *(undefined4 *)((int)_Memory + 0x14);
  }
  if (*(int *)((int)_Memory + 0x14) != 0) {
    *(undefined4 *)(*(int *)((int)_Memory + 0x14) + 4) = *(undefined4 *)((int)_Memory + 0x10);
  }
  *(undefined4 *)((int)_Memory + 0x10) = 0;
  *(undefined4 *)((int)_Memory + 0x14) = 0;
  if (param_2 != 0) {
    _free(_Memory);
    pvVar8 = g_pGameStateManager;
  }
  goto joined_r0x0041912a;
LAB_0041929f:
  iVar4 = *piVar5;
  if (iVar4 == 0) {
LAB_004192a5:
    *(undefined4 *)(param_1 + 0xdc + *(int *)(param_1 + 0x1a4) * 4) = 0;
  }
  *(undefined1 *)(iVar4 + 0x3a1) = 0xf;
  *(undefined1 *)(iVar4 + 0x3a0) = 0xf;
  local_30 = *(float *)((int)_Memory + 0x7c);
  local_28 = *(float *)((int)_Memory + 0x7c) * _DAT_00470ca8;
  local_24 = 0;
  pfVar6 = &local_30;
  pfVar7 = &local_28;
  local_2c = local_30;
  goto LAB_00419435;
}

