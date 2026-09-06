/* Raw Ghidra reference; not compilable reconstruction. Address: 004548BE */

/* Library Function - Single Match
    ___sbh_alloc_block
   
   Library: Visual Studio 2003 Release */

int * __cdecl ___sbh_alloc_block(uint *param_1)

{
  int *piVar1;
  char *pcVar2;
  int *piVar3;
  char cVar4;
  int *piVar5;
  byte bVar6;
  uint uVar7;
  int iVar8;
  uint *puVar9;
  int iVar10;
  int *piVar11;
  uint *puVar12;
  uint *puVar13;
  uint uVar14;
  int iVar15;
  uint local_c;
  int local_8;
  
  uVar7 = (int)param_1 + 0x17U & 0xfffffff0;
  iVar8 = ((int)((int)param_1 + 0x17U) >> 4) + -1;
  puVar9 = DAT_0049932c + DAT_00499328 * 5;
  bVar6 = (byte)iVar8;
  param_1 = DAT_00499334;
  if (iVar8 < 0x20) {
    uVar14 = 0xffffffff >> (bVar6 & 0x1f);
    local_c = 0xffffffff;
  }
  else {
    uVar14 = 0;
    local_c = 0xffffffff >> (bVar6 - 0x20 & 0x1f);
  }
  for (; (param_1 < puVar9 && ((param_1[1] & local_c) == 0 && (*param_1 & uVar14) == 0));
      param_1 = param_1 + 5) {
  }
  puVar12 = DAT_0049932c;
  if (param_1 == puVar9) {
    for (; (puVar12 < DAT_00499334 && ((puVar12[1] & local_c) == 0 && (*puVar12 & uVar14) == 0));
        puVar12 = puVar12 + 5) {
    }
    param_1 = puVar12;
    if (puVar12 == DAT_00499334) {
      for (; (puVar12 < puVar9 && (puVar12[2] == 0)); puVar12 = puVar12 + 5) {
      }
      puVar13 = DAT_0049932c;
      param_1 = puVar12;
      if (puVar12 == puVar9) {
        for (; (puVar13 < DAT_00499334 && (puVar13[2] == 0)); puVar13 = puVar13 + 5) {
        }
        param_1 = puVar13;
        if ((puVar13 == DAT_00499334) &&
           (param_1 = ___sbh_alloc_new_region(), param_1 == (uint *)0x0)) {
          return (int *)0x0;
        }
      }
      iVar8 = ___sbh_alloc_new_group((int)param_1);
      *(int *)param_1[4] = iVar8;
      if (*(int *)param_1[4] == -1) {
        return (int *)0x0;
      }
    }
  }
  piVar5 = (int *)param_1[4];
  local_8 = *piVar5;
  if ((local_8 == -1) ||
     ((piVar5[local_8 + 0x31] & local_c) == 0 && (piVar5[local_8 + 0x11] & uVar14) == 0)) {
    local_8 = 0;
    puVar9 = (uint *)(piVar5 + 0x11);
    if ((piVar5[0x31] & local_c) == 0 && (*puVar9 & uVar14) == 0) {
      do {
        puVar12 = puVar9 + 0x21;
        local_8 = local_8 + 1;
        puVar9 = puVar9 + 1;
      } while ((*puVar12 & local_c) == 0 && (*puVar9 & uVar14) == 0);
    }
  }
  piVar3 = piVar5 + local_8 * 0x81 + 0x51;
  iVar8 = 0;
  uVar14 = piVar5[local_8 + 0x11] & uVar14;
  if (uVar14 == 0) {
    uVar14 = piVar5[local_8 + 0x31] & local_c;
    iVar8 = 0x20;
  }
  for (; -1 < (int)uVar14; uVar14 = uVar14 << 1) {
    iVar8 = iVar8 + 1;
  }
  piVar11 = (int *)piVar3[iVar8 * 2 + 1];
  iVar10 = *piVar11 - uVar7;
  iVar15 = (iVar10 >> 4) + -1;
  if (0x3f < iVar15) {
    iVar15 = 0x3f;
  }
  DAT_00499334 = param_1;
  if (iVar15 != iVar8) {
    if (piVar11[1] == piVar11[2]) {
      if (iVar8 < 0x20) {
        pcVar2 = (char *)((int)piVar5 + iVar8 + 4);
        uVar14 = ~(0x80000000U >> ((byte)iVar8 & 0x1f));
        piVar5[local_8 + 0x11] = uVar14 & piVar5[local_8 + 0x11];
        *pcVar2 = *pcVar2 + -1;
        if (*pcVar2 == '\0') {
          *param_1 = *param_1 & uVar14;
        }
      }
      else {
        pcVar2 = (char *)((int)piVar5 + iVar8 + 4);
        uVar14 = ~(0x80000000U >> ((byte)iVar8 - 0x20 & 0x1f));
        piVar5[local_8 + 0x31] = piVar5[local_8 + 0x31] & uVar14;
        *pcVar2 = *pcVar2 + -1;
        if (*pcVar2 == '\0') {
          param_1[1] = param_1[1] & uVar14;
        }
      }
    }
    *(int *)(piVar11[2] + 4) = piVar11[1];
    *(int *)(piVar11[1] + 8) = piVar11[2];
    if (iVar10 == 0) goto LAB_00454b77;
    piVar1 = piVar3 + iVar15 * 2;
    iVar8 = piVar1[1];
    piVar11[2] = (int)piVar1;
    piVar11[1] = iVar8;
    piVar1[1] = (int)piVar11;
    *(int **)(piVar11[1] + 8) = piVar11;
    if (piVar11[1] == piVar11[2]) {
      cVar4 = *(char *)(iVar15 + 4 + (int)piVar5);
      *(char *)(iVar15 + 4 + (int)piVar5) = cVar4 + '\x01';
      bVar6 = (byte)iVar15;
      if (iVar15 < 0x20) {
        if (cVar4 == '\0') {
          *param_1 = *param_1 | 0x80000000U >> (bVar6 & 0x1f);
        }
        piVar5[local_8 + 0x11] = piVar5[local_8 + 0x11] | 0x80000000U >> (bVar6 & 0x1f);
      }
      else {
        if (cVar4 == '\0') {
          param_1[1] = param_1[1] | 0x80000000U >> (bVar6 - 0x20 & 0x1f);
        }
        piVar5[local_8 + 0x31] = piVar5[local_8 + 0x31] | 0x80000000U >> (bVar6 - 0x20 & 0x1f);
      }
    }
  }
  if (iVar10 != 0) {
    *piVar11 = iVar10;
    *(int *)(iVar10 + -4 + (int)piVar11) = iVar10;
  }
LAB_00454b77:
  piVar11 = (int *)((int)piVar11 + iVar10);
  *piVar11 = uVar7 + 1;
  *(uint *)((int)piVar11 + (uVar7 - 4)) = uVar7 + 1;
  iVar8 = *piVar3;
  *piVar3 = iVar8 + 1;
  if (((iVar8 == 0) && (param_1 == DAT_00499324)) && (local_8 == DAT_0049933c)) {
    DAT_00499324 = (uint *)0x0;
  }
  *piVar5 = local_8;
  return piVar11 + 1;
}

