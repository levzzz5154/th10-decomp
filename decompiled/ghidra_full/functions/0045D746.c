/* Raw Ghidra reference; not compilable reconstruction. Address: 0045D746 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

undefined4 __cdecl
FUN_0045d746(undefined2 *param_1,int *param_2,byte *param_3,int param_4,int param_5,int param_6,
            int param_7)

{
  bool bVar1;
  bool bVar2;
  bool bVar3;
  ushort uVar4;
  uint uVar5;
  int iVar6;
  byte bVar7;
  char *pcVar8;
  undefined4 uVar9;
  byte *pbVar10;
  int local_60;
  int local_50;
  undefined4 local_4c;
  byte *local_44;
  int local_40;
  uint local_3c;
  undefined2 local_34;
  undefined2 uStack_32;
  undefined2 uStack_30;
  undefined4 local_2e;
  ushort local_2a;
  char local_24 [23];
  char local_d;
  uint local_8;
  
  local_8 = DAT_00473660 ^ (uint)&stack0xfffffffc;
  iVar6 = 0;
  pcVar8 = local_24;
  uVar4 = 0;
  local_60 = 1;
  local_3c = 0;
  bVar1 = false;
  bVar3 = false;
  bVar2 = false;
  local_50 = 0;
  local_40 = 0;
  local_4c = 0;
  local_44 = param_3;
  for (; (((bVar7 = *param_3, bVar7 == 0x20 || (bVar7 == 9)) || (bVar7 == 10)) || (bVar7 == 0xd));
      param_3 = param_3 + 1) {
  }
LAB_0045d7a9:
  bVar7 = *param_3;
  pbVar10 = param_3 + 1;
  switch(iVar6) {
  case 0:
    if (('0' < (char)bVar7) && ((char)bVar7 < ':')) {
LAB_0045d7c6:
      iVar6 = 3;
      goto LAB_0045d9e5;
    }
    if (bVar7 == DAT_00473af4) {
LAB_0045d7d5:
      iVar6 = 5;
      param_3 = pbVar10;
      goto LAB_0045d7a9;
    }
    iVar6 = 2;
    if (bVar7 == 0x2b) {
      uVar4 = 0;
      param_3 = pbVar10;
      goto LAB_0045d7a9;
    }
    if (bVar7 == 0x2d) {
      uVar4 = 0x8000;
      param_3 = pbVar10;
      goto LAB_0045d7a9;
    }
    break;
  case 1:
    iVar6 = 1;
    bVar1 = true;
    if (('0' < (char)bVar7) && ((char)bVar7 < ':')) goto LAB_0045d7c6;
    if (bVar7 == DAT_00473af4) goto LAB_0045d824;
    if ((bVar7 == 0x2b) || (bVar7 == 0x2d)) goto LAB_0045d865;
    param_3 = pbVar10;
    if (bVar7 != 0x30) goto LAB_0045d83e;
    goto LAB_0045d7a9;
  case 2:
    if (('0' < (char)bVar7) && ((char)bVar7 < ':')) goto LAB_0045d7c6;
    param_3 = local_44;
    if (bVar7 == DAT_00473af4) goto LAB_0045d7d5;
    break;
  case 3:
    while (iVar6 = _isdigit((uint)bVar7), iVar6 != 0) {
      if (local_3c < 0x19) {
        local_3c = local_3c + 1;
        *pcVar8 = bVar7 - 0x30;
        pcVar8 = pcVar8 + 1;
      }
      else {
        local_40 = local_40 + 1;
      }
      bVar7 = *pbVar10;
      pbVar10 = pbVar10 + 1;
    }
    if (bVar7 != DAT_00473af4) goto LAB_0045d914;
LAB_0045d824:
    bVar1 = true;
    iVar6 = 4;
    param_3 = pbVar10;
    goto LAB_0045d7a9;
  case 4:
    bVar3 = true;
    if (local_3c == 0) {
      while (bVar7 == 0x30) {
        local_40 = local_40 + -1;
        bVar7 = *pbVar10;
        pbVar10 = pbVar10 + 1;
      }
    }
    while (iVar6 = _isdigit((uint)bVar7), iVar6 != 0) {
      if (local_3c < 0x19) {
        local_3c = local_3c + 1;
        *pcVar8 = bVar7 - 0x30;
        pcVar8 = pcVar8 + 1;
        local_40 = local_40 + -1;
      }
      bVar7 = *pbVar10;
      pbVar10 = pbVar10 + 1;
    }
LAB_0045d914:
    if ((bVar7 == 0x2b) || (bVar7 == 0x2d)) {
LAB_0045d865:
      bVar1 = true;
      iVar6 = 0xb;
      param_3 = pbVar10 + -1;
    }
    else {
LAB_0045d83e:
      bVar1 = true;
      if (((char)bVar7 < 'D') ||
         (('E' < (char)bVar7 && (((char)bVar7 < 'd' || ('e' < (char)bVar7)))))) {
LAB_0045d99e:
        param_3 = pbVar10 + -1;
        goto LAB_0045d9a2;
      }
      iVar6 = 6;
      param_3 = pbVar10;
    }
    goto LAB_0045d7a9;
  case 5:
    bVar3 = true;
    iVar6 = _isdigit((uint)bVar7);
    param_3 = local_44;
    if (iVar6 != 0) {
      iVar6 = 4;
      goto LAB_0045d9e5;
    }
    goto LAB_0045d9a2;
  case 6:
    local_44 = param_3 + -1;
    if (((char)bVar7 < '1') || ('9' < (char)bVar7)) {
      if (bVar7 == 0x2b) goto LAB_0045da1a;
      if (bVar7 == 0x2d) goto LAB_0045da0e;
      param_3 = local_44;
      if (bVar7 == 0x30) goto LAB_0045d97c;
      goto LAB_0045d9a2;
    }
LAB_0045d9e3:
    iVar6 = 9;
LAB_0045d9e5:
    param_3 = pbVar10 + -1;
    goto LAB_0045d7a9;
  case 7:
    if (('0' < (char)bVar7) && ((char)bVar7 < ':')) goto LAB_0045d9e3;
    param_3 = local_44;
    if (bVar7 != 0x30) goto LAB_0045d9a2;
LAB_0045d97c:
    iVar6 = 8;
    param_3 = pbVar10;
    goto LAB_0045d7a9;
  case 8:
    bVar2 = true;
    while (bVar7 == 0x30) {
      bVar7 = *pbVar10;
      pbVar10 = pbVar10 + 1;
    }
    if (('0' < (char)bVar7) && ((char)bVar7 < ':')) goto LAB_0045d9e3;
    goto LAB_0045d99e;
  case 9:
    bVar2 = true;
    local_50 = 0;
    goto LAB_0045da61;
  default:
    goto switchD_0045d7b5_caseD_a;
  case 0xb:
    if (param_7 != 0) {
      local_44 = param_3;
      if (bVar7 == 0x2b) {
LAB_0045da1a:
        iVar6 = 7;
        param_3 = pbVar10;
      }
      else {
        if (bVar7 != 0x2d) goto LAB_0045d9a2;
LAB_0045da0e:
        local_60 = -1;
        iVar6 = 7;
        param_3 = pbVar10;
      }
      goto LAB_0045d7a9;
    }
    iVar6 = 10;
    pbVar10 = param_3;
switchD_0045d7b5_caseD_a:
    param_3 = pbVar10;
    if (iVar6 != 10) goto LAB_0045d7a9;
    goto LAB_0045d9a2;
  }
  if (bVar7 != 0x30) goto LAB_0045d9a2;
  iVar6 = 1;
  param_3 = pbVar10;
  goto LAB_0045d7a9;
LAB_0045da61:
  iVar6 = _isdigit((uint)bVar7);
  if (iVar6 == 0) goto LAB_0045da84;
  local_50 = (char)bVar7 + -0x30 + local_50 * 10;
  if (0x1450 < local_50) {
    local_50 = 0x1451;
    goto LAB_0045da84;
  }
  bVar7 = *pbVar10;
  pbVar10 = pbVar10 + 1;
  goto LAB_0045da61;
LAB_0045da84:
  while( true ) {
    iVar6 = _isdigit((uint)bVar7);
    if (iVar6 == 0) break;
    bVar7 = *pbVar10;
    pbVar10 = pbVar10 + 1;
  }
  param_3 = pbVar10 + -1;
LAB_0045d9a2:
  *param_2 = (int)param_3;
  if (bVar1) {
    if (0x18 < local_3c) {
      if ('\x04' < local_d) {
        local_d = local_d + '\x01';
      }
      pcVar8 = pcVar8 + -1;
      local_40 = local_40 + 1;
      local_3c = 0x18;
    }
    if (local_3c != 0) {
      while (pcVar8 = pcVar8 + -1, *pcVar8 == '\0') {
        local_3c = local_3c - 1;
        local_40 = local_40 + 1;
      }
      FUN_00460872(local_24,local_3c,(uint *)&local_34);
      if (local_60 < 0) {
        local_50 = -local_50;
      }
      uVar5 = local_50 + local_40;
      if (!bVar2) {
        uVar5 = uVar5 + param_5;
      }
      if (!bVar3) {
        uVar5 = uVar5 - param_6;
      }
      if (0x1450 < (int)uVar5) {
        uVar9 = 0;
        local_2a = 0x7fff;
        local_2e = 0x80000000;
        local_34 = 0;
        local_4c = 2;
        goto LAB_0045db31;
      }
      if (-0x1451 < (int)uVar5) {
        FUN_00460b90((int *)&local_34,uVar5,param_4);
        uVar9 = CONCAT22(uStack_30,uStack_32);
        goto LAB_0045db31;
      }
      local_4c = 1;
    }
  }
  else {
    local_4c = 4;
  }
  local_34 = 0;
  local_2a = 0;
  local_2e = 0;
  uVar9 = 0;
LAB_0045db31:
  *param_1 = local_34;
  *(undefined4 *)(param_1 + 1) = uVar9;
  param_1[5] = local_2a | uVar4;
  *(undefined4 *)(param_1 + 3) = local_2e;
  return local_4c;
}

