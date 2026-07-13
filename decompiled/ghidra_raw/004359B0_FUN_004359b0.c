/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x004359B0
 * Tracking name: FUN_004359b0
 * Ghidra name: FUN_004359b0
 * Tracked span: 1040 bytes
 */


void FUN_004359b0(byte *param_1,int param_2,int *param_3)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  undefined1 *puVar4;
  undefined4 *puVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  int iVar9;
  byte bVar10;
  byte bVar11;
  byte local_29;
  uint local_28;
  byte *local_20;
  int local_1c;
  uint local_18;
  int local_14;
  int local_10;
  uint local_c;
  int local_8;
  undefined1 *local_4;
  
  uVar8 = 0x80;
  bVar10 = 0x80;
  local_28 = 0;
  puVar4 = _malloc(param_2 * 2);
  if (puVar4 == (undefined1 *)0x0) {
    return;
  }
  local_20 = param_1;
  *param_3 = 0;
  puVar5 = &DAT_0048f868;
  for (iVar9 = 0x800; iVar9 != 0; iVar9 = iVar9 + -1) {
    *puVar5 = 0;
    puVar5 = puVar5 + 1;
  }
  puVar5 = &DAT_0047785c;
  do {
    puVar5[-1] = 0;
    *puVar5 = 0;
    puVar5[1] = 0;
    puVar5 = puVar5 + 3;
  } while ((int)puVar5 < 0x48f868);
  local_14 = 0;
  local_18 = 1;
  iVar9 = 0;
  do {
    if (param_2 <= iVar9) break;
    bVar11 = *local_20;
    local_20 = local_20 + 1;
    iVar9 = iVar9 + 1;
    if (bVar11 == 0xffffffff) break;
    *(byte *)((int)&DAT_0048f868 + local_14 + 1) = bVar11;
    local_14 = local_14 + 1;
  } while (local_14 < 0x12);
  iVar9 = 0;
  DAT_0048f860 = 1;
  DAT_00477864 = 0x2000;
  DAT_0047786c = 0;
  DAT_00477868 = 0;
  local_1c = 0;
  local_c = 0;
  local_4 = puVar4;
  do {
    if (local_14 < 1) {
      bVar11 = bVar10 >> 1;
      if (bVar10 >> 1 == 0) {
        *puVar4 = (undefined1)local_28;
        puVar4 = puVar4 + 1;
        local_28 = 0;
        bVar11 = 0x80;
      }
      uVar8 = 0x1000;
      do {
        bVar10 = bVar11 >> 1;
        bVar11 = bVar11 >> 1;
        if (bVar10 == 0) {
          *puVar4 = (undefined1)local_28;
          puVar4 = puVar4 + 1;
          local_28 = 0;
          bVar11 = 0x80;
        }
        uVar8 = uVar8 >> 1;
      } while (uVar8 != 0);
      *param_3 = (int)puVar4 - (int)local_4;
      return;
    }
    local_8 = iVar9;
    if (local_14 < iVar9) {
      local_8 = local_14;
      local_1c = local_14;
    }
    if (local_8 < 3) {
      local_28 = local_28 | uVar8;
      bVar10 = (byte)uVar8 >> 1;
      uVar8 = (uint)bVar10;
      local_8 = 1;
      if (bVar10 == 0) {
        *puVar4 = (undefined1)local_28;
        puVar4 = puVar4 + 1;
        local_28 = 0;
        uVar8 = 0x80;
      }
      uVar6 = 0x80;
      do {
        if ((*(byte *)((int)&DAT_0048f868 + local_18) & (byte)uVar6) != 0) {
          local_28 = local_28 | uVar8;
        }
        uVar8 = uVar8 >> 1;
        if ((char)uVar8 == '\0') {
          *puVar4 = (undefined1)local_28;
          puVar4 = puVar4 + 1;
          local_28 = 0;
          uVar8 = 0x80;
        }
        uVar6 = uVar6 >> 1;
      } while (uVar6 != 0);
      local_29 = (byte)uVar8;
LAB_00435bb0:
      local_10 = (int)local_20 - (int)param_1;
      do {
        uVar6 = local_18 + 0x12 & 0x1fff;
        iVar9 = (&DAT_00477858)[uVar6 * 3];
        piVar1 = &DAT_00477858 + uVar6 * 3;
        if (iVar9 != 0) {
          iVar2 = (&DAT_00477860)[uVar6 * 3];
          iVar3 = (&DAT_0047785c)[uVar6 * 3];
          if (iVar2 == 0) {
            (&DAT_00477858)[iVar3 * 3] = iVar9;
            iVar9 = *piVar1;
            if ((&DAT_00477860)[iVar9 * 3] == uVar6) {
              (&DAT_00477860)[iVar9 * 3] = iVar3;
            }
            else {
              (&DAT_0047785c)[iVar9 * 3] = iVar3;
            }
          }
          else if (iVar3 == 0) {
            (&DAT_00477858)[iVar2 * 3] = iVar9;
            iVar9 = *piVar1;
            if ((&DAT_00477860)[iVar9 * 3] == uVar6) {
              (&DAT_00477860)[iVar9 * 3] = iVar2;
            }
            else {
              (&DAT_0047785c)[iVar9 * 3] = iVar2;
            }
          }
          else {
            iVar9 = (&DAT_00477860)[iVar3 * 3];
            while (iVar9 != 0) {
              iVar3 = (&DAT_00477860)[iVar3 * 3];
              iVar9 = (&DAT_00477860)[iVar3 * 3];
            }
            FUN_00436210(iVar3);
            iVar9 = *piVar1;
            if ((&DAT_0047785c)[iVar9 * 3] == uVar6) {
              (&DAT_0047785c)[iVar9 * 3] = iVar3;
            }
            else {
              (&DAT_00477860)[iVar9 * 3] = iVar3;
            }
            (&DAT_00477858)[iVar3 * 3] = *piVar1;
            (&DAT_0047785c)[iVar3 * 3] = (&DAT_0047785c)[uVar6 * 3];
            uVar8 = (uint)local_29;
            (&DAT_00477860)[iVar3 * 3] = (&DAT_00477860)[uVar6 * 3];
            (&DAT_00477858)[(&DAT_0047785c)[iVar3 * 3] * 3] = iVar3;
            (&DAT_00477858)[(&DAT_00477860)[iVar3 * 3] * 3] = iVar3;
          }
          *piVar1 = 0;
        }
        if (local_10 < param_2) {
          bVar10 = *local_20;
          local_20 = local_20 + 1;
          local_10 = local_10 + 1;
          if (bVar10 == 0xffffffff) goto LAB_00435d1f;
          *(byte *)((int)&DAT_0048f868 + uVar6) = bVar10;
        }
        else {
LAB_00435d1f:
          local_14 = local_14 + -1;
        }
        uVar6 = local_18 + 1 & 0x1fff;
        if (local_14 != 0) {
          local_1c = FUN_00436000(local_18,uVar6,(int *)&local_c);
        }
        local_8 = local_8 + -1;
        iVar9 = local_1c;
        local_18 = uVar6;
      } while (local_8 != 0);
    }
    else {
      bVar10 = (byte)uVar8 >> 1;
      uVar8 = (uint)bVar10;
      if (bVar10 == 0) {
        *puVar4 = (undefined1)local_28;
        puVar4 = puVar4 + 1;
        local_28 = 0;
        uVar8 = 0x80;
      }
      uVar6 = 0x1000;
      do {
        if ((local_c & uVar6) != 0) {
          local_28 = local_28 | uVar8;
        }
        uVar8 = uVar8 >> 1;
        if ((char)uVar8 == '\0') {
          *puVar4 = (undefined1)local_28;
          puVar4 = puVar4 + 1;
          local_28 = 0;
          uVar8 = 0x80;
        }
        uVar6 = uVar6 >> 1;
      } while (uVar6 != 0);
      uVar7 = 8;
      uVar6 = local_8 - 3;
      do {
        if ((uVar7 & uVar6) != 0) {
          local_28 = local_28 | uVar8;
          local_8 = local_1c;
        }
        uVar8 = uVar8 >> 1;
        if ((char)uVar8 == '\0') {
          *puVar4 = (undefined1)local_28;
          puVar4 = puVar4 + 1;
          local_28 = 0;
          uVar8 = 0x80;
        }
        uVar7 = uVar7 >> 1;
      } while (uVar7 != 0);
      local_29 = (byte)uVar8;
      iVar9 = local_8;
      if (0 < local_8) goto LAB_00435bb0;
    }
    bVar10 = (byte)uVar8;
  } while( true );
}

