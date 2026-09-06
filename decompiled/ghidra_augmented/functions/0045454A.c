/* Raw Ghidra reference; not compilable reconstruction. Address: 0045454A */

/* Library Function - Single Match
    ___sbh_heap_check
   
   Library: Visual Studio 2003 Release */

undefined4 ___sbh_heap_check(void)

{
  LPVOID lp;
  BOOL BVar1;
  uint *puVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  uint *puVar6;
  int iVar7;
  uint *puVar8;
  uint *puVar9;
  uint *puVar10;
  bool bVar11;
  uint local_13c [64];
  uint *local_3c;
  uint *local_38;
  uint *local_34;
  uint *local_30;
  uint local_2c;
  uint *local_28;
  uint local_24;
  int local_20;
  uint local_1c;
  uint local_18;
  uint local_14;
  int local_10;
  uint *local_c;
  uint local_8;
  
  BVar1 = IsBadWritePtr(DAT_0049932c,DAT_00499328 * 0x14);
  if (BVar1 != 0) {
    return 0xffffffff;
  }
  local_20 = 0;
  puVar2 = DAT_0049932c;
  if (0 < DAT_00499328) {
    do {
      lp = (LPVOID)puVar2[4];
      local_38 = puVar2;
      BVar1 = IsBadWritePtr(lp,0x41c4);
      if (BVar1 != 0) {
        return 0xfffffffe;
      }
      local_c = (uint *)puVar2[3];
      local_28 = (uint *)((int)lp + 0x144);
      local_24 = puVar2[2];
      puVar9 = (uint *)((int)lp + 0xc4);
      local_14 = 0;
      local_18 = 0;
      local_10 = 0;
      do {
        local_2c = 0;
        local_1c = 0;
        local_8 = 0;
        bVar11 = -1 < (int)local_24;
        puVar10 = local_13c;
        local_3c = puVar9;
        for (iVar4 = 0x40; iVar4 != 0; iVar4 = iVar4 + -1) {
          *puVar10 = 0;
          puVar10 = puVar10 + 1;
        }
        if (bVar11) {
          BVar1 = IsBadWritePtr(local_c,0x8000);
          if (BVar1 != 0) {
            return 0xfffffffc;
          }
          iVar4 = 0;
          puVar2 = local_c + 0x3ff;
          do {
            puVar9 = puVar2 + -0x3fc;
            if ((puVar2[-0x3fd] != 0xffffffff) || (*puVar2 != 0xffffffff)) {
              return 0xfffffffb;
            }
            do {
              uVar3 = *puVar9;
              if ((uVar3 & 1) == 0) {
                iVar7 = ((int)uVar3 >> 4) + -1;
                if (0x3f < iVar7) {
                  iVar7 = 0x3f;
                }
                local_13c[iVar7] = local_13c[iVar7] + 1;
                uVar5 = uVar3;
              }
              else {
                if (0x400 < (int)(uVar3 - 1)) {
                  return 0xfffffffa;
                }
                local_8 = local_8 + 1;
                uVar5 = uVar3 - 1;
              }
              if ((((int)uVar5 < 0x10) || ((uVar5 & 0xf) != 0)) || (0xff0 < (int)uVar5)) {
                return 0xfffffff9;
              }
              puVar9 = (uint *)(uVar5 + (int)puVar9);
              if (puVar9[-1] != uVar3) {
                return 0xfffffff8;
              }
            } while (puVar9 < puVar2);
            if (puVar9 != puVar2) {
              return 0xfffffff8;
            }
            puVar2 = puVar2 + 0x400;
            iVar4 = iVar4 + 1;
          } while (iVar4 < 8);
          if (*local_28 != local_8) {
            return 0xfffffff7;
          }
          iVar4 = 0;
          puVar10 = local_28;
          do {
            local_8 = 0;
            local_34 = puVar10 + 2;
            puVar2 = (uint *)puVar10[1];
            local_30 = puVar10;
            puVar8 = local_34;
            if (puVar2 != puVar10) {
              do {
                if (local_8 == local_13c[iVar4]) break;
                if ((puVar2 < local_c) || (local_c + 0x2000 <= puVar2)) {
                  return 0xfffffff6;
                }
                puVar6 = (uint *)(((uint)puVar2 & 0xfffff000) + 0xc);
                puVar9 = (uint *)(((uint)puVar2 & 0xfffff000) + 0xffc);
                if (puVar6 == puVar9) {
                  return 0xfffffff5;
                }
                do {
                  if (puVar6 == puVar2) break;
                  puVar6 = (uint *)((int)puVar6 + (*puVar6 & 0xfffffffe));
                  puVar8 = local_34;
                } while (puVar6 != puVar9);
                if (puVar6 == puVar9) {
                  return 0xfffffff5;
                }
                iVar7 = ((int)*puVar2 >> 4) + -1;
                if (0x3f < iVar7) {
                  iVar7 = 0x3f;
                }
                if (iVar7 != iVar4) {
                  return 0xfffffff4;
                }
                if ((uint *)puVar2[2] != local_30) {
                  return 0xfffffff3;
                }
                local_8 = local_8 + 1;
                local_30 = puVar2;
                puVar2 = (uint *)puVar2[1];
              } while (puVar2 != puVar10);
              if (local_8 != 0) {
                if (iVar4 < 0x20) {
                  uVar3 = 0x80000000 >> ((byte)iVar4 & 0x1f);
                  local_2c = local_2c | uVar3;
                  local_14 = local_14 | uVar3;
                }
                else {
                  uVar3 = 0x80000000 >> ((byte)iVar4 - 0x20 & 0x1f);
                  local_1c = local_1c | uVar3;
                  local_18 = local_18 | uVar3;
                }
              }
            }
            if (((uint *)local_30[1] != puVar10) || (local_8 != local_13c[iVar4])) {
              return 0xfffffff2;
            }
            if ((uint *)*puVar8 != local_30) {
              return 0xfffffff1;
            }
            iVar4 = iVar4 + 1;
            puVar2 = local_38;
            puVar9 = local_3c;
            puVar10 = puVar8;
          } while (iVar4 < 0x40);
        }
        if ((local_2c != puVar9[-0x20]) || (local_1c != *puVar9)) {
          return 0xfffffff0;
        }
        local_c = local_c + 0x2000;
        local_28 = local_28 + 0x81;
        local_24 = local_24 << 1;
        local_10 = local_10 + 1;
        puVar9 = puVar9 + 1;
      } while (local_10 < 0x20);
      if ((local_14 != *puVar2) || (local_18 != puVar2[1])) {
        return 0xffffffef;
      }
      puVar2 = puVar2 + 5;
      local_20 = local_20 + 1;
      local_3c = puVar9;
    } while (local_20 < DAT_00499328);
  }
  return 0;
}

