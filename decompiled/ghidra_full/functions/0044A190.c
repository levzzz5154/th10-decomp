/* Raw Ghidra reference; not compilable reconstruction. Address: 0044A190 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

ushort __thiscall FUN_0044a190(ushort param_1,int param_2,int param_3)

{
  MMRESULT MVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  joyinfoex_tag *pjVar6;
  int iVar7;
  DWORD *pDVar8;
  joyinfoex_tag local_154;
  int iStack_120;
  int iStack_11c;
  byte abStack_f0 [228];
  uint local_c;
  
  local_c = DAT_00473660 ^ (uint)&stack0xfffffffc;
  if ((DAT_00491ff4 & 0x400) == 0) {
    pjVar6 = &local_154;
    for (iVar3 = 0xd; iVar3 != 0; iVar3 = iVar3 + -1) {
      pjVar6->dwSize = 0;
      pjVar6 = (joyinfoex_tag *)&pjVar6->dwFlags;
    }
    local_154.dwSize = 0x34;
    local_154.dwFlags = 0xff;
    MVar1 = joyGetPosEx((uint)(param_3 != 0),&local_154);
    if (MVar1 == 0) {
      if (-1 < (short)(&DAT_00474e88)[param_2 * 0x35]) {
        param_1 = param_1 | (1 << ((byte)(&DAT_00474e88)[param_2 * 0x35] & 0x1f) &
                            local_154.dwButtons) != 0;
      }
      if (-1 < (short)(&DAT_00474e8a)[param_2 * 0x35]) {
        param_1 = param_1 | -(ushort)((1 << ((byte)(&DAT_00474e8a)[param_2 * 0x35] & 0x1f) &
                                      local_154.dwButtons) != 0) & 2;
      }
      if (-1 < (short)(&DAT_00474e8e)[param_2 * 0x35]) {
        param_1 = param_1 | -(ushort)((1 << ((byte)(&DAT_00474e8e)[param_2 * 0x35] & 0x1f) &
                                      local_154.dwButtons) != 0) & 8;
      }
      if (-1 < (short)(&DAT_00474e8c)[param_2 * 0x35]) {
        param_1 = param_1 | -(ushort)((1 << ((byte)(&DAT_00474e8c)[param_2 * 0x35] & 0x1f) &
                                      local_154.dwButtons) != 0) & 4;
      }
      if (-1 < (short)(&DAT_00474e98)[param_2 * 0x35]) {
        param_1 = param_1 | -(ushort)((1 << ((byte)(&DAT_00474e98)[param_2 * 0x35] & 0x1f) &
                                      local_154.dwButtons) != 0) & 0x100;
      }
      iVar2 = param_3 * 0x194;
      uVar4 = (uint)(*(int *)(&DAT_004918e0 + iVar2) - *(int *)(&DAT_004918dc + iVar2)) >> 2;
      iVar3 = *(int *)(&DAT_004918e8 + iVar2);
      iVar7 = *(int *)(&DAT_004918e4 + iVar2);
      uVar5 = (uint)(iVar3 - iVar7) >> 2;
      return -(ushort)(local_154.dwYpos < ((uint)(iVar7 + iVar3) >> 1) - uVar5) & 0x10 |
             -(ushort)(((uint)(iVar7 + iVar3) >> 1) + uVar5 < local_154.dwYpos) & 0x20 |
             param_1 | -(ushort)(((uint)(*(int *)(&DAT_004918dc + iVar2) +
                                        *(int *)(&DAT_004918e0 + iVar2)) >> 1) + uVar4 <
                                local_154.dwXpos) & 0x80 |
                       -(ushort)(local_154.dwXpos <
                                ((uint)(*(int *)(&DAT_004918e0 + iVar2) +
                                       *(int *)(&DAT_004918dc + iVar2)) >> 1) - uVar4) & 0x40;
    }
  }
  else {
    iVar3 = (**(code **)(*(int *)(&DAT_00491c3c)[param_3] + 100))((int *)(&DAT_00491c3c)[param_3]);
    if (iVar3 < 0) {
      iVar7 = 0;
      iVar3 = (**(code **)(*(int *)(&DAT_00491c3c)[param_3] + 0x1c))
                        ((int *)(&DAT_00491c3c)[param_3]);
      if (iVar3 == -0x7ff8ffe2) {
        while( true ) {
          iVar3 = (**(code **)(*(int *)(&DAT_00491c3c)[param_3] + 0x1c))
                            ((int *)(&DAT_00491c3c)[param_3]);
          iVar7 = iVar7 + 1;
          if (399 < iVar7) break;
          if (iVar3 != -0x7ff8ffe2) {
            return param_1;
          }
        }
      }
    }
    else {
      pDVar8 = &local_154.dwReserved2;
      for (iVar3 = 0x44; iVar3 != 0; iVar3 = iVar3 + -1) {
        *pDVar8 = 0;
        pDVar8 = pDVar8 + 1;
      }
      iVar3 = (**(code **)(*(int *)(&DAT_00491c3c)[param_3] + 0x24))
                        ((int *)(&DAT_00491c3c)[param_3],0x110,&local_154.dwReserved2);
      if (-1 < iVar3) {
        if (-1 < (short)(&DAT_00474e88)[param_2 * 0x35]) {
          param_1 = param_1 | abStack_f0[(short)(&DAT_00474e88)[param_2 * 0x35]] >> 7;
        }
        if (-1 < (short)(&DAT_00474e8a)[param_2 * 0x35]) {
          param_1 = param_1 | abStack_f0[(short)(&DAT_00474e8a)[param_2 * 0x35]] >> 6 & 2;
        }
        if (-1 < (short)(&DAT_00474e8e)[param_2 * 0x35]) {
          param_1 = param_1 | abStack_f0[(short)(&DAT_00474e8e)[param_2 * 0x35]] >> 4 & 8;
        }
        if (-1 < (short)(&DAT_00474e8c)[param_2 * 0x35]) {
          param_1 = param_1 | abStack_f0[(short)(&DAT_00474e8c)[param_2 * 0x35]] >> 5 & 4;
        }
        if (-1 < (short)(&DAT_00474e98)[param_2 * 0x35]) {
          param_1 = param_1 | (abStack_f0[(short)(&DAT_00474e98)[param_2 * 0x35]] & 0x80) << 1;
        }
        return (-(int)DAT_00491d5e <= iStack_120) - 1 & 0x40 |
               (-(int)DAT_00491d60 <= iStack_11c) - 1 & 0x10 |
               (iStack_120 <= DAT_00491d5e) - 1 & 0x80 | (iStack_11c <= DAT_00491d60) - 1 & 0x20 |
               param_1;
      }
    }
  }
  return param_1;
}

