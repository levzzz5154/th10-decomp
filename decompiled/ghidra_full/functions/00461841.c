/* Raw Ghidra reference; not compilable reconstruction. Address: 00461841 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

undefined4 __cdecl
FUN_00461841(uint param_1,uint param_2,ushort param_3,int param_4,byte param_5,short *param_6)

{
  short *psVar1;
  uint uVar2;
  char cVar3;
  uint uVar4;
  short *psVar5;
  short *psVar6;
  short sVar7;
  int iVar8;
  char *pcVar9;
  int local_38;
  short *local_30;
  uint local_2c;
  uint local_28;
  undefined4 local_24;
  undefined1 local_20;
  undefined1 local_1f;
  undefined1 local_1e;
  undefined1 local_1d;
  undefined1 local_1c;
  undefined1 local_1b;
  undefined1 local_1a;
  undefined1 local_19;
  undefined1 local_18;
  undefined1 local_17;
  undefined1 local_16;
  undefined1 local_15;
  undefined2 local_14;
  undefined4 local_12;
  undefined4 local_e;
  undefined1 local_a;
  char cStack_9;
  uint local_8;
  
  local_2c = param_1;
  local_28 = param_2;
  local_8 = DAT_00473660 ^ (uint)&stack0xfffffffc;
  local_24 = CONCAT22(local_24._2_2_,param_3);
  uVar4 = param_3 & 0x7fff;
  local_20 = 0xcc;
  local_1f = 0xcc;
  local_1e = 0xcc;
  local_1d = 0xcc;
  local_1c = 0xcc;
  local_1b = 0xcc;
  local_1a = 0xcc;
  local_19 = 0xcc;
  local_18 = 0xcc;
  local_17 = 0xcc;
  local_16 = 0xfb;
  local_15 = 0x3f;
  if ((param_3 & 0x8000) == 0) {
    *(undefined1 *)(param_6 + 1) = 0x20;
  }
  else {
    *(undefined1 *)(param_6 + 1) = 0x2d;
  }
  if ((((short)uVar4 == 0) && (param_2 == 0)) && (param_1 == 0)) {
LAB_004619c3:
    *(undefined1 *)(param_6 + 2) = 0x30;
LAB_00461ac8:
    *param_6 = 0;
    *(undefined1 *)(param_6 + 1) = 0x20;
    *(undefined1 *)((int)param_6 + 3) = 1;
    *(undefined1 *)((int)param_6 + 5) = 0;
  }
  else {
    if ((short)uVar4 == 0x7fff) {
      *param_6 = 1;
      if (((param_2 == 0x80000000) && (param_1 == 0)) || ((param_2 & 0x40000000) != 0)) {
        if (((param_3 & 0x8000) == 0) || (param_2 != 0xc0000000)) {
          if ((param_2 != 0x80000000) || (param_1 != 0)) goto LAB_00461939;
          pcVar9 = "1#INF";
        }
        else {
          if (param_1 != 0) {
LAB_00461939:
            pcVar9 = "1#QNAN";
            goto LAB_0046193e;
          }
          pcVar9 = "1#IND";
        }
        FUN_0045bd80((uint *)(param_6 + 2),(uint *)pcVar9);
        *(undefined1 *)((int)param_6 + 3) = 5;
      }
      else {
        pcVar9 = "1#SNAN";
LAB_0046193e:
        FUN_0045bd80((uint *)(param_6 + 2),(uint *)pcVar9);
        *(undefined1 *)((int)param_6 + 3) = 6;
      }
      return 0;
    }
    local_14 = 0;
    sVar7 = (short)(((uVar4 >> 8) + (param_2 >> 0x18) * 2) * 0x4d + -0x134312f4 + uVar4 * 0x4d10 >>
                   0x10);
    local_a = (undefined1)uVar4;
    cStack_9 = (char)(uVar4 >> 8);
    local_12 = param_1;
    local_e = param_2;
    FUN_00460b90((int *)&local_14,-(int)sVar7,1);
    if (0x3ffe < CONCAT11(cStack_9,local_a)) {
      sVar7 = sVar7 + 1;
      FUN_0046095a((int *)&local_14,(int *)&local_20);
    }
    *param_6 = sVar7;
    if (((param_5 & 1) != 0) && (param_4 = param_4 + sVar7, param_4 < 1)) goto LAB_004619c3;
    if (0x15 < param_4) {
      param_4 = 0x15;
    }
    iVar8 = CONCAT11(cStack_9,local_a) - 0x3ffe;
    local_a = 0;
    cStack_9 = '\0';
    local_30 = (short *)0x8;
    do {
      ___shl_12((uint *)&local_14);
      local_30 = (short *)((int)local_30 + -1);
    } while (local_30 != (short *)0x0);
    if (iVar8 < 0) {
      for (uVar4 = -iVar8 & 0xff; uVar4 != 0; uVar4 = uVar4 - 1) {
        ___shr_12((uint *)&local_14);
      }
    }
    local_38 = param_4 + 1;
    psVar5 = param_6 + 2;
    local_30 = psVar5;
    uVar4 = local_12;
    uVar2 = local_e;
    if (0 < local_38) {
      do {
        local_e._2_2_ = (undefined2)(uVar2 >> 0x10);
        local_e._0_2_ = (undefined2)uVar2;
        local_12._2_2_ = (undefined2)(uVar4 >> 0x10);
        local_12._0_2_ = (undefined2)uVar4;
        local_2c = CONCAT22((undefined2)local_12,local_14);
        local_28 = CONCAT22((undefined2)local_e,local_12._2_2_);
        local_24 = CONCAT13(cStack_9,CONCAT12(local_a,local_e._2_2_));
        local_12 = uVar4;
        local_e = uVar2;
        ___shl_12((uint *)&local_14);
        ___shl_12((uint *)&local_14);
        ___add_12((uint *)&local_14,&local_2c);
        ___shl_12((uint *)&local_14);
        psVar5 = (short *)((int)local_30 + 1);
        local_38 = local_38 + -1;
        *(char *)local_30 = cStack_9 + '0';
        cStack_9 = '\0';
        local_30 = psVar5;
        uVar4 = local_12;
        uVar2 = local_e;
      } while (local_38 != 0);
    }
    psVar6 = psVar5 + -1;
    psVar1 = param_6 + 2;
    if (*(char *)((int)psVar5 + -1) < '5') {
      for (; (psVar1 <= psVar6 && ((char)*psVar6 == '0')); psVar6 = (short *)((int)psVar6 + -1)) {
      }
      if (psVar6 < psVar1) {
        *(char *)psVar1 = '0';
        goto LAB_00461ac8;
      }
    }
    else {
      for (; (psVar1 <= psVar6 && ((char)*psVar6 == '9')); psVar6 = (short *)((int)psVar6 + -1)) {
        *(char *)psVar6 = '0';
      }
      if (psVar6 < psVar1) {
        psVar6 = (short *)((int)psVar6 + 1);
        *param_6 = *param_6 + 1;
      }
      *(char *)psVar6 = (char)*psVar6 + '\x01';
    }
    cVar3 = ((char)psVar6 - (char)param_6) + -3;
    *(char *)((int)param_6 + 3) = cVar3;
    *(undefined1 *)(cVar3 + 4 + (int)param_6) = 0;
  }
  return 1;
}

