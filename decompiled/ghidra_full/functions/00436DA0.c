/* Raw Ghidra reference; not compilable reconstruction. Address: 00436DA0 */

undefined4 FUN_00436da0(int param_1,uint param_2)

{
  ushort uVar1;
  byte *pbVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  byte *pbVar6;
  uint uVar7;
  undefined1 *puVar8;
  uint uVar9;
  ushort *puVar10;
  uint local_14;
  uint local_10;
  uint local_8;
  uint local_4;
  
  uVar4 = *(uint *)(param_1 + 0x100);
  if (uVar4 == 0x15) {
    puVar8 = *(undefined1 **)(param_1 + 0x120);
    local_14 = 0;
    uVar4 = param_2;
    if (param_2 != 0) {
      do {
        uVar4 = *(uint *)(param_1 + 0x104);
        local_10 = 0;
        if (uVar4 != 0) {
          pbVar6 = puVar8 + -2;
          do {
            uVar5 = 0;
            if (pbVar6[5] == 0) {
              uVar7 = 0;
              local_4 = 0;
              local_8 = 0;
              if ((local_10 != 0) && (pbVar6[1] != 0)) {
                local_8 = (uint)pbVar6[-1];
                uVar5 = (uint)*pbVar6;
                local_4 = (uint)pbVar6[-2];
                uVar7 = 1;
              }
              if ((local_10 < uVar4 - 1) && (pbVar6[9] != 0)) {
                uVar5 = uVar5 + pbVar6[8];
                local_8 = local_8 + pbVar6[7];
                local_4 = local_4 + pbVar6[6];
                uVar7 = uVar7 + 1;
              }
              if ((local_14 != 0) &&
                 (pbVar2 = puVar8 + ((int)(*(int *)(param_1 + 0x110) +
                                          (*(int *)(param_1 + 0x110) >> 0x1f & 3U)) >> 2) * -4,
                 pbVar2[3] != 0)) {
                uVar5 = uVar5 + pbVar2[2];
                local_8 = local_8 + pbVar2[1];
                local_4 = local_4 + *pbVar2;
                uVar7 = uVar7 + 1;
              }
              if ((local_14 < *(int *)(param_1 + 0x108) - 1U) &&
                 (iVar3 = (int)(*(int *)(param_1 + 0x110) + (*(int *)(param_1 + 0x110) >> 0x1f & 3U)
                               ) >> 2, pbVar2 = puVar8 + iVar3 * 4, puVar8[iVar3 * 4 + 3] != '\0'))
              {
                uVar5 = uVar5 + pbVar2[2];
                local_8 = local_8 + pbVar2[1];
                local_4 = local_4 + *pbVar2;
                uVar7 = uVar7 + 1;
              }
              if (1 < uVar7) {
                uVar5 = uVar5 / uVar7;
                local_8 = local_8 / uVar7;
                local_4 = local_4 / uVar7;
              }
              pbVar6[4] = (byte)uVar5;
              pbVar6[3] = (byte)local_8;
              *puVar8 = (byte)local_4;
            }
            uVar4 = *(uint *)(param_1 + 0x104);
            puVar8 = puVar8 + 4;
            pbVar6 = pbVar6 + 4;
            local_10 = local_10 + 1;
          } while (local_10 < uVar4);
        }
        local_14 = local_14 + 1;
        uVar4 = param_2;
      } while (local_14 < param_2);
    }
  }
  else if (uVar4 == 0x1a) {
    puVar10 = *(ushort **)(param_1 + 0x120);
    local_14 = 0;
    uVar4 = param_2;
    if (param_2 != 0) {
      do {
        uVar4 = *(uint *)(param_1 + 0x104);
        local_10 = 0;
        if (uVar4 != 0) {
          do {
            if ((*puVar10 & 0xf000) == 0) {
              uVar5 = 0;
              uVar7 = 0;
              uVar9 = 0;
              local_4 = 0;
              if (local_10 != 0) {
                uVar1 = puVar10[-1];
                if ((uVar1 & 0xf000) != 0) {
                  uVar5 = uVar1 >> 8 & 0xf;
                  uVar7 = uVar1 >> 4 & 0xf;
                  local_4 = uVar1 & 0xf;
                  uVar9 = 1;
                }
              }
              if (local_10 < uVar4 - 1) {
                uVar1 = puVar10[1];
                if ((uVar1 & 0xf000) != 0) {
                  uVar5 = uVar5 + (uVar1 >> 8 & 0xf);
                  uVar7 = uVar7 + (uVar1 >> 4 & 0xf);
                  local_4 = local_4 + (uVar1 & 0xf);
                  uVar9 = uVar9 + 1;
                }
              }
              if (local_14 != 0) {
                uVar1 = puVar10[-(*(int *)(param_1 + 0x110) / 2)];
                if ((uVar1 & 0xf000) != 0) {
                  uVar5 = uVar5 + (uVar1 >> 8 & 0xf);
                  uVar7 = uVar7 + (uVar1 >> 4 & 0xf);
                  local_4 = local_4 + (uVar1 & 0xf);
                  uVar9 = uVar9 + 1;
                }
              }
              if ((local_14 < *(int *)(param_1 + 0x108) - 1U) &&
                 (uVar1 = puVar10[*(int *)(param_1 + 0x110) / 2], (uVar1 & 0xf000) != 0)) {
                uVar5 = uVar5 + (uVar1 >> 8 & 0xf);
                uVar7 = uVar7 + (uVar1 >> 4 & 0xf);
                local_4 = local_4 + (uVar1 & 0xf);
                uVar9 = uVar9 + 1;
              }
              if (1 < uVar9) {
                uVar5 = uVar5 / uVar9;
                uVar7 = uVar7 / uVar9;
                local_4 = local_4 / uVar9;
              }
              local_4._0_1_ = (byte)(local_4 >> 1);
              *puVar10 = (ushort)(((uVar5 >> 1 & 0xffffff0f) << 4 | uVar7 >> 1 & 0xffffff0f) << 4) |
                         *puVar10 & 0xf000 | (byte)local_4 & 0xf;
            }
            uVar4 = *(uint *)(param_1 + 0x104);
            puVar10 = puVar10 + 1;
            local_10 = local_10 + 1;
          } while (local_10 < uVar4);
        }
        local_14 = local_14 + 1;
      } while (local_14 < param_2);
      return CONCAT31((int3)(local_14 >> 8),1);
    }
  }
  return CONCAT31((int3)(uVar4 >> 8),1);
}

