/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x00450220
 * Tracking name: FUN_00450220
 * Ghidra name: FUN_00450220
 * Tracked span: 592 bytes
 */


int __thiscall FUN_00450220(void *this,int *param_1)

{
  int *piVar1;
  byte bVar2;
  int *piVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  int iVar6;
  int iVar7;
  undefined4 *puVar8;
  byte *pbVar9;
  byte *pbVar10;
  bool bVar11;
  byte *local_10;
  int local_c;
  undefined4 *local_8;
  int local_4;
  
  *(int **)((int)this + *(int *)((int)this + 4) * 4 + 0xc) = param_1;
  piVar3 = *(int **)((int)this + *(int *)((int)this + 4) * 4 + 0xc);
  piVar1 = (int *)((int)this + *(int *)((int)this + 4) * 4 + 0xc);
  if ((*piVar3 != 0x54504353) || ((short)piVar3[1] != 1)) {
    *piVar1 = 0;
    return -1;
  }
  iVar7 = *piVar1;
  puVar4 = *(undefined4 **)((int)this + 0x8c);
  param_1 = (int *)(*(ushort *)(iVar7 + 6) + 0x24 + iVar7);
  iVar6 = *(int *)((int)this + 8) + (uint)*(ushort *)(iVar7 + 0x10);
  local_10 = (byte *)(param_1 + *(ushort *)(iVar7 + 0x10));
  *(int *)((int)this + 8) = iVar6;
  puVar5 = _malloc(iVar6 * 8);
  *(undefined4 **)((int)this + 0x8c) = puVar5;
  if (puVar4 == (undefined4 *)0x0) {
    iVar7 = 0;
    if (0 < *(int *)((int)this + 8)) {
      do {
        *(int *)(*(int *)((int)this + 0x8c) + 4 + iVar7 * 8) =
             *(int *)((int)this + *(int *)((int)this + 4) * 4 + 0xc) + *param_1;
        *(byte **)(*(int *)((int)this + 0x8c) + iVar7 * 8) = local_10;
        do {
          bVar2 = *local_10;
          local_10 = local_10 + 1;
        } while (bVar2 != 0);
        iVar7 = iVar7 + 1;
        param_1 = param_1 + 1;
      } while (iVar7 < *(int *)((int)this + 8));
    }
  }
  else {
    local_c = *(int *)((int)this + 8) -
              (uint)*(ushort *)(*(int *)((int)this + *(int *)((int)this + 4) * 4 + 0xc) + 0x10);
    puVar8 = puVar4;
    for (iVar7 = local_c * 2; iVar7 != 0; iVar7 = iVar7 + -1) {
      *puVar5 = *puVar8;
      puVar8 = puVar8 + 1;
      puVar5 = puVar5 + 1;
    }
    if (puVar4 != (undefined4 *)0x0) {
      _free(puVar4);
    }
    local_4 = 0;
    if (*(short *)(*(int *)((int)this + *(int *)((int)this + 4) * 4 + 0xc) + 0x10) != 0) {
      do {
        iVar7 = 0;
        if (0 < local_c) {
          local_8 = *(undefined4 **)((int)this + 0x8c);
          do {
            pbVar10 = (byte *)*local_8;
            pbVar9 = local_10;
            do {
              bVar2 = *pbVar9;
              bVar11 = bVar2 < *pbVar10;
              if (bVar2 != *pbVar10) {
LAB_00450394:
                iVar6 = (1 - (uint)bVar11) - (uint)(bVar11 != 0);
                goto LAB_00450399;
              }
              if (bVar2 == 0) break;
              bVar2 = pbVar9[1];
              bVar11 = bVar2 < pbVar10[1];
              if (bVar2 != pbVar10[1]) goto LAB_00450394;
              pbVar9 = pbVar9 + 2;
              pbVar10 = pbVar10 + 2;
            } while (bVar2 != 0);
            iVar6 = 0;
LAB_00450399:
            if (iVar6 < 1) break;
            iVar7 = iVar7 + 1;
            local_8 = local_8 + 2;
          } while (iVar7 < local_c);
        }
        iVar6 = *(int *)((int)this + 8);
        while (iVar6 = iVar6 + -1, iVar7 < iVar6) {
          puVar4 = (undefined4 *)(*(int *)((int)this + 0x8c) + iVar6 * 8);
          *puVar4 = *(undefined4 *)(*(int *)((int)this + 0x8c) + -8 + iVar6 * 8);
          puVar4[1] = puVar4[-1];
        }
        *(int *)(*(int *)((int)this + 0x8c) + 4 + iVar7 * 8) =
             *(int *)((int)this + *(int *)((int)this + 4) * 4 + 0xc) + *param_1;
        *(byte **)(*(int *)((int)this + 0x8c) + iVar7 * 8) = local_10;
        do {
          bVar2 = *local_10;
          local_10 = local_10 + 1;
        } while (bVar2 != 0);
        param_1 = param_1 + 1;
        local_c = local_c + 1;
        local_4 = local_4 + 1;
      } while (local_4 < (int)(uint)*(ushort *)
                                     (*(int *)((int)this + *(int *)((int)this + 4) * 4 + 0xc) + 0x10
                                     ));
    }
  }
  iVar7 = *(int *)((int)this + 4);
  *(int *)((int)this + 4) = iVar7 + 1;
  iVar6 = *(int *)((int)this + iVar7 * 4 + 0xc);
  if (*(short *)(iVar6 + 6) != 0) {
    (**(code **)(*(int *)this + 4))(iVar6 + 0x24);
  }
  return iVar7;
}

