/* Raw Ghidra reference; not compilable reconstruction. Address: 0046095A */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __cdecl FUN_0046095a(int *param_1,int *param_2)

{
  short sVar1;
  int iVar2;
  ushort uVar3;
  ushort uVar4;
  int iVar5;
  ushort uVar6;
  uint uVar7;
  ushort uVar8;
  int local_34;
  int local_30;
  ushort *local_2c;
  int local_28;
  ushort *local_24;
  short *local_20;
  int local_1c;
  ushort local_18;
  byte local_14;
  undefined1 uStack_13;
  undefined2 uStack_12;
  short local_10;
  undefined2 uStack_e;
  undefined2 local_c;
  undefined1 uStack_a;
  byte bStack_9;
  uint local_8;
  
  local_8 = DAT_00473660 ^ (uint)&stack0xfffffffc;
  local_28 = 0;
  local_14 = 0;
  uStack_13 = 0;
  uStack_12 = 0;
  local_10 = 0;
  uStack_e = 0;
  local_c = 0;
  uStack_a = 0;
  bStack_9 = 0;
  uVar6 = *(ushort *)((int)param_2 + 10) & 0x7fff;
  uVar4 = *(ushort *)((int)param_1 + 10) & 0x7fff;
  uVar8 = (*(ushort *)((int)param_2 + 10) ^ *(ushort *)((int)param_1 + 10)) & 0x8000;
  uVar3 = uVar6 + uVar4;
  if (((uVar4 < 0x7fff) && (uVar6 < 0x7fff)) && (uVar3 < 0xbffe)) {
    if (uVar3 < 0x3fc0) goto LAB_00460a09;
    if (uVar4 == 0) {
      uVar3 = uVar3 + 1;
      local_18 = 0;
      if ((((param_1[2] & 0x7fffffffU) != 0) || (param_1[1] != 0)) || (*param_1 != 0))
      goto LAB_004609f3;
    }
    else {
LAB_004609f3:
      if (((uVar6 == 0) && (uVar3 = uVar3 + 1, (param_2[2] & 0x7fffffffU) == 0)) &&
         ((param_2[1] == 0 && (*param_2 == 0)))) {
LAB_00460a09:
        param_1[2] = 0;
        param_1[1] = 0;
        *param_1 = 0;
        return;
      }
      local_30 = 0;
      local_20 = &local_10;
      local_1c = 5;
      do {
        if (0 < local_1c) {
          local_2c = (ushort *)(local_30 * 2 + (int)param_1);
          local_24 = (ushort *)(param_2 + 2);
          local_34 = local_1c;
          do {
            iVar5 = ___addl(*(uint *)(local_20 + -2),(uint)*local_24 * (uint)*local_2c,
                            (uint *)(local_20 + -2));
            if (iVar5 != 0) {
              *local_20 = *local_20 + 1;
            }
            local_2c = local_2c + 1;
            local_24 = local_24 + -1;
            local_34 = local_34 + -1;
          } while (local_34 != 0);
        }
        local_20 = local_20 + 1;
        local_30 = local_30 + 1;
        local_1c = local_1c + -1;
      } while (0 < local_1c);
      local_18 = uVar3 + 0xc002;
      if ((short)local_18 < 1) {
LAB_00460abd:
        local_18 = local_18 - 1;
        if ((short)local_18 < 0) {
          uVar7 = (uint)(ushort)-local_18;
          local_18 = 0;
          do {
            if ((local_14 & 1) != 0) {
              local_28 = local_28 + 1;
            }
            ___shr_12((uint *)&local_14);
            uVar7 = uVar7 - 1;
          } while (uVar7 != 0);
          if (local_28 != 0) {
            local_14 = local_14 | 1;
          }
        }
      }
      else {
        do {
          if ((bStack_9 & 0x80) != 0) break;
          ___shl_12((uint *)&local_14);
          local_18 = local_18 - 1;
        } while (0 < (short)local_18);
        if ((short)local_18 < 1) goto LAB_00460abd;
      }
      if ((0x8000 < CONCAT11(uStack_13,local_14)) ||
         (sVar1 = CONCAT11(bStack_9,uStack_a), iVar2 = CONCAT22(local_c,uStack_e),
         iVar5 = CONCAT22(local_10,uStack_12),
         (CONCAT22(uStack_12,CONCAT11(uStack_13,local_14)) & 0x1ffff) == 0x18000)) {
        if (CONCAT22(local_10,uStack_12) == -1) {
          iVar5 = 0;
          if (CONCAT22(local_c,uStack_e) == -1) {
            if (CONCAT11(bStack_9,uStack_a) == -1) {
              local_18 = local_18 + 1;
              sVar1 = -0x8000;
              iVar2 = 0;
              iVar5 = 0;
            }
            else {
              sVar1 = CONCAT11(bStack_9,uStack_a) + 1;
              iVar2 = 0;
              iVar5 = 0;
            }
          }
          else {
            sVar1 = CONCAT11(bStack_9,uStack_a);
            iVar2 = CONCAT22(local_c,uStack_e) + 1;
          }
        }
        else {
          iVar5 = CONCAT22(local_10,uStack_12) + 1;
          sVar1 = CONCAT11(bStack_9,uStack_a);
          iVar2 = CONCAT22(local_c,uStack_e);
        }
      }
      local_10 = (short)((uint)iVar5 >> 0x10);
      uStack_12 = (undefined2)iVar5;
      local_c = (undefined2)((uint)iVar2 >> 0x10);
      uStack_e = (undefined2)iVar2;
      bStack_9 = (byte)((ushort)sVar1 >> 8);
      uStack_a = (undefined1)sVar1;
      if (0x7ffe < local_18) goto LAB_00460b66;
      *(undefined2 *)param_1 = uStack_12;
      *(uint *)((int)param_1 + 2) = CONCAT22(uStack_e,local_10);
      *(uint *)((int)param_1 + 6) = CONCAT13(bStack_9,CONCAT12(uStack_a,local_c));
      local_18 = local_18 | uVar8;
    }
    *(ushort *)((int)param_1 + 10) = local_18;
  }
  else {
LAB_00460b66:
    param_1[1] = 0;
    *param_1 = 0;
    param_1[2] = (-(uint)(uVar8 != 0) & 0x80000000) + 0x7fff8000;
  }
  return;
}

