/* Raw Ghidra reference; not compilable reconstruction. Address: 0045998A */

/* Library Function - Single Match
    __ValidateEH3RN
   
   Library: Visual Studio 2003 Release */

undefined4 __cdecl __ValidateEH3RN(void *param_1)

{
  uint *puVar1;
  uint uVar2;
  void *pvVar3;
  uint *puVar4;
  SIZE_T SVar5;
  int *piVar6;
  LONG LVar7;
  uint *puVar8;
  uint uVar9;
  uint uVar10;
  int iVar11;
  int iVar12;
  int iVar13;
  _MEMORY_BASIC_INFORMATION local_24;
  uint *local_8;
  
  pvVar3 = param_1;
  puVar8 = *(uint **)((int)param_1 + 8);
  if ((((uint)puVar8 & 3) != 0) ||
     ((local_8 = *(uint **)((int)Self + 8), local_8 <= puVar8 &&
      (puVar8 < *(uint **)((int)Self + 4))))) {
    return 0;
  }
  puVar1 = (uint *)((int)param_1 + 0xc);
  if (*puVar1 == 0xffffffff) {
    return 1;
  }
  uVar10 = 0;
  param_1 = (void *)0x0;
  puVar4 = puVar8;
  do {
    if ((*puVar4 != 0xffffffff) && (uVar10 <= *puVar4)) {
      return 0;
    }
    if (puVar4[1] != 0) {
      param_1 = (void *)((int)param_1 + 1);
    }
    uVar10 = uVar10 + 1;
    puVar4 = puVar4 + 3;
  } while (uVar10 <= *puVar1);
  if ((param_1 != (void *)0x0) &&
     ((puVar1 = *(uint **)((int)pvVar3 + -8), puVar1 < local_8 || (pvVar3 <= puVar1)))) {
    return 0;
  }
  uVar10 = (uint)puVar8 & 0xfffff000;
  iVar13 = 0;
  if (0 < DAT_004775c8) {
    do {
      if ((&DAT_004775d0)[iVar13] == uVar10) {
        if (iVar13 < 1) {
          return 1;
        }
        LVar7 = InterlockedExchange((LONG *)&DAT_00477610,1);
        if (LVar7 != 0) {
          return 1;
        }
        if ((&DAT_004775d0)[iVar13] == uVar10) goto LAB_00459b85;
        iVar13 = DAT_004775c8 + -1;
        if (iVar13 < 0) goto LAB_00459b73;
        goto LAB_00459b63;
      }
      iVar13 = iVar13 + 1;
    } while (iVar13 < DAT_004775c8);
  }
  SVar5 = VirtualQuery(puVar8,&local_24,0x1c);
  if (SVar5 == 0) {
    return 0xffffffff;
  }
  if (local_24.Type != 0x1000000) {
    return 0xffffffff;
  }
  if (((byte)local_24.Protect & 0xcc) != 0) {
    if (((*(short *)local_24.AllocationBase != 0x5a4d) ||
        (piVar6 = (int *)(*(int *)((int)local_24.AllocationBase + 0x3c) +
                         (int)local_24.AllocationBase), *piVar6 != 0x4550)) ||
       ((short)piVar6[6] != 0x10b)) {
      return 0xffffffff;
    }
    uVar9 = (uint)*(ushort *)(piVar6 + 5);
    if (*(short *)((int)piVar6 + 6) == 0) {
      return 0xffffffff;
    }
    uVar2 = *(uint *)((int)piVar6 + uVar9 + 0x24);
    if (((uVar2 <= (uint)((int)puVar8 - (int)local_24.AllocationBase)) &&
        ((uint)((int)puVar8 - (int)local_24.AllocationBase) <
         *(int *)((int)piVar6 + uVar9 + 0x20) + uVar2)) &&
       ((*(byte *)((int)piVar6 + uVar9 + 0x3f) & 0x80) != 0)) {
      return 0;
    }
  }
  LVar7 = InterlockedExchange((LONG *)&DAT_00477610,1);
  iVar13 = DAT_004775c8;
  if (LVar7 != 0) {
    return 1;
  }
  iVar11 = DAT_004775c8;
  if (0 < DAT_004775c8) {
    puVar8 = (uint *)(&DAT_004775cc + DAT_004775c8 * 4);
    do {
      if (*puVar8 == uVar10) break;
      iVar11 = iVar11 + -1;
      puVar8 = puVar8 + -1;
    } while (0 < iVar11);
  }
  if (iVar11 == 0) {
    iVar11 = 0xf;
    if (DAT_004775c8 < 0x10) {
      iVar11 = DAT_004775c8;
    }
    iVar12 = 0;
    if (-1 < iVar11) {
      do {
        puVar8 = &DAT_004775d0 + iVar12;
        uVar9 = *puVar8;
        iVar12 = iVar12 + 1;
        *puVar8 = uVar10;
        uVar10 = uVar9;
      } while (iVar12 <= iVar11);
    }
    if (iVar13 < 0x10) {
      DAT_004775c8 = iVar13 + 1;
    }
  }
  InterlockedExchange((LONG *)&DAT_00477610,0);
  return 1;
  while (iVar13 = iVar13 + -1, -1 < iVar13) {
LAB_00459b63:
    if ((&DAT_004775d0)[iVar13] == uVar10) break;
  }
  if (iVar13 < 0) {
LAB_00459b73:
    if (DAT_004775c8 < 0x10) {
      DAT_004775c8 = DAT_004775c8 + 1;
    }
    iVar13 = DAT_004775c8 + -1;
  }
  else if (iVar13 == 0) goto LAB_00459b9d;
LAB_00459b85:
  iVar11 = 0;
  if (-1 < iVar13) {
    do {
      puVar8 = &DAT_004775d0 + iVar11;
      uVar9 = *puVar8;
      iVar11 = iVar11 + 1;
      *puVar8 = uVar10;
      uVar10 = uVar9;
    } while (iVar11 <= iVar13);
  }
LAB_00459b9d:
  InterlockedExchange((LONG *)&DAT_00477610,0);
  return 1;
}

