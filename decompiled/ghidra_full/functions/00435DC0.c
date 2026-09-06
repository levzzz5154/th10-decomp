/* Raw Ghidra reference; not compilable reconstruction. Address: 00435DC0 */

undefined1 * DecompressDatLzss(byte *param_1,int param_2,undefined1 *param_3,undefined1 *param_4)

{
  byte bVar1;
  undefined1 uVar2;
  uint uVar3;
  int iVar4;
  byte bVar5;
  byte bVar6;
  byte bVar7;
  uint uVar8;
  uint uVar9;
  byte *pbVar10;
  uint local_8;
  
  bVar7 = 0x80;
  bVar1 = 0;
  if ((param_3 == (undefined1 *)0x0) &&
     (param_3 = _malloc((size_t)param_4), param_3 == (undefined1 *)0x0)) {
    return (undefined1 *)0x0;
  }
  param_4 = param_3;
  local_8 = 1;
  pbVar10 = param_1;
  while( true ) {
    while( true ) {
      uVar3 = 0;
      if (bVar7 == 0x80) {
        bVar1 = *pbVar10;
        if ((int)pbVar10 - (int)param_1 < param_2) {
          pbVar10 = pbVar10 + 1;
        }
        else {
          bVar1 = 0;
        }
      }
      bVar5 = bVar7 >> 1;
      if (bVar7 >> 1 == 0) {
        bVar5 = 0x80;
      }
      if ((bVar7 & bVar1) == 0) break;
      uVar3 = 0;
      uVar8 = 0x80;
      iVar4 = (int)pbVar10 - (int)param_1;
      bVar7 = bVar5;
      do {
        if (bVar7 == 0x80) {
          bVar1 = *pbVar10;
          if (iVar4 < param_2) {
            pbVar10 = pbVar10 + 1;
            iVar4 = iVar4 + 1;
          }
          else {
            bVar1 = 0;
          }
        }
        if ((bVar1 & bVar7) != 0) {
          uVar3 = uVar3 | uVar8;
        }
        uVar8 = uVar8 >> 1;
        bVar5 = bVar7 >> 1;
        bVar7 = bVar7 >> 1;
        if (bVar5 == 0) {
          bVar7 = 0x80;
        }
      } while (uVar8 != 0);
      *param_4 = (char)uVar3;
      param_4 = param_4 + 1;
      *(char *)((int)&DAT_0048f868 + local_8) = (char)uVar3;
      local_8 = local_8 + 1 & 0x1fff;
    }
    uVar8 = 0x1000;
    iVar4 = (int)pbVar10 - (int)param_1;
    do {
      if (bVar5 == 0x80) {
        bVar1 = *pbVar10;
        if (iVar4 < param_2) {
          pbVar10 = pbVar10 + 1;
          iVar4 = iVar4 + 1;
        }
        else {
          bVar1 = 0;
        }
      }
      if ((bVar1 & bVar5) != 0) {
        uVar3 = uVar3 | uVar8;
      }
      bVar6 = bVar5 >> 1;
      uVar8 = uVar8 >> 1;
      if (bVar5 >> 1 == 0) {
        bVar6 = 0x80;
      }
      bVar5 = bVar6;
    } while (uVar8 != 0);
    if (uVar3 == 0) break;
    uVar8 = 0;
    uVar9 = 8;
    iVar4 = (int)pbVar10 - (int)param_1;
    do {
      if (bVar6 == 0x80) {
        bVar1 = *pbVar10;
        if (iVar4 < param_2) {
          pbVar10 = pbVar10 + 1;
          iVar4 = iVar4 + 1;
        }
        else {
          bVar1 = 0;
        }
      }
      if ((bVar1 & bVar6) != 0) {
        uVar8 = uVar8 | uVar9;
      }
      bVar7 = bVar6 >> 1;
      uVar9 = uVar9 >> 1;
      if (bVar6 >> 1 == 0) {
        bVar7 = 0x80;
      }
      bVar6 = bVar7;
    } while (uVar9 != 0);
    iVar4 = 0;
    do {
      uVar2 = *(undefined1 *)((int)&DAT_0048f868 + (iVar4 + uVar3 & 0x1fff));
      *param_4 = uVar2;
      param_4 = param_4 + 1;
      *(undefined1 *)((int)&DAT_0048f868 + local_8) = uVar2;
      local_8 = local_8 + 1 & 0x1fff;
      iVar4 = iVar4 + 1;
    } while (iVar4 <= (int)(uVar8 + 2));
  }
  do {
    if (bVar6 == 0x80) {
      return param_3;
    }
    bVar1 = bVar6 >> 1;
    bVar6 = bVar6 >> 1;
  } while (bVar1 != 0);
  return param_3;
}

