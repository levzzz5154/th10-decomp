/* Raw Ghidra reference; not compilable reconstruction. Address: 0044A190 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

ushort __thiscall FUN_0044a190(ushort param_1,int param_2,int param_3)

{
  short sVar1;
  int iVar2;
  MMRESULT MVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  joyinfoex_tag *pjVar8;
  DWORD *pDVar9;
  joyinfoex_tag local_154;
  int iStack_120;
  int iStack_11c;
  byte abStack_f0 [228];
  uint local_c;
  
  local_c = DAT_00473660 ^ (uint)&stack0xfffffffc;
  iVar2 = param_2 * 0x6a;
  if ((DAT_00491ff4 & 0x400) == 0) {
    pjVar8 = &local_154;
    for (iVar5 = 0xd; iVar5 != 0; iVar5 = iVar5 + -1) {
      pjVar8->dwSize = 0;
      pjVar8 = (joyinfoex_tag *)&pjVar8->dwFlags;
    }
    local_154.dwSize = 0x34;
    local_154.dwFlags = 0xff;
    MVar3 = joyGetPosEx((uint)(param_3 != 0),&local_154);
    if (MVar3 == 0) {
      if (-1 < *(short *)((int)&DAT_00474e88 + iVar2)) {
        param_1 = param_1 | (1 << ((byte)*(short *)((int)&DAT_00474e88 + iVar2) & 0x1f) &
                            local_154.dwButtons) != 0;
      }
      sVar1 = *(short *)((int)&DAT_00474e88 + iVar2 + 2);
      if (-1 < sVar1) {
        param_1 = param_1 | -(ushort)((1 << ((byte)sVar1 & 0x1f) & local_154.dwButtons) != 0) & 2;
      }
      sVar1 = *(short *)((int)&DAT_00474e8c + iVar2 + 2);
      if (-1 < sVar1) {
        param_1 = param_1 | -(ushort)((1 << ((byte)sVar1 & 0x1f) & local_154.dwButtons) != 0) & 8;
      }
      if (-1 < *(short *)((int)&DAT_00474e8c + iVar2)) {
        param_1 = param_1 | -(ushort)((1 << ((byte)*(short *)((int)&DAT_00474e8c + iVar2) & 0x1f) &
                                      local_154.dwButtons) != 0) & 4;
      }
      if (-1 < (short)(&DAT_00474e98)[param_2 * 0x35]) {
        param_1 = param_1 | -(ushort)((1 << ((byte)(&DAT_00474e98)[param_2 * 0x35] & 0x1f) &
                                      local_154.dwButtons) != 0) & 0x100;
      }
      iVar4 = param_3 * 0x194;
      uVar6 = (uint)(*(int *)(&DAT_004918e0 + iVar4) - *(int *)(&DAT_004918dc + iVar4)) >> 2;
      iVar2 = *(int *)(&DAT_004918e8 + iVar4);
      iVar5 = *(int *)(&DAT_004918e4 + iVar4);
      uVar7 = (uint)(iVar2 - iVar5) >> 2;
      return -(ushort)(local_154.dwYpos < ((uint)(iVar5 + iVar2) >> 1) - uVar7) & 0x10 |
             -(ushort)(((uint)(iVar5 + iVar2) >> 1) + uVar7 < local_154.dwYpos) & 0x20 |
             param_1 | -(ushort)(((uint)(*(int *)(&DAT_004918dc + iVar4) +
                                        *(int *)(&DAT_004918e0 + iVar4)) >> 1) + uVar6 <
                                local_154.dwXpos) & 0x80 |
                       -(ushort)(local_154.dwXpos <
                                ((uint)(*(int *)(&DAT_004918e0 + iVar4) +
                                       *(int *)(&DAT_004918dc + iVar4)) >> 1) - uVar6) & 0x40;
    }
  }
  else {
    iVar5 = (**(code **)(*(int *)(&DAT_00491c3c)[param_3] + 100))((int *)(&DAT_00491c3c)[param_3]);
    if (iVar5 < 0) {
      iVar5 = 0;
      iVar2 = (**(code **)(*(int *)(&DAT_00491c3c)[param_3] + 0x1c))
                        ((int *)(&DAT_00491c3c)[param_3]);
      if (iVar2 == -0x7ff8ffe2) {
        while( true ) {
          iVar2 = (**(code **)(*(int *)(&DAT_00491c3c)[param_3] + 0x1c))
                            ((int *)(&DAT_00491c3c)[param_3]);
          iVar5 = iVar5 + 1;
          if (399 < iVar5) break;
          if (iVar2 != -0x7ff8ffe2) {
            return param_1;
          }
        }
      }
    }
    else {
      pDVar9 = &local_154.dwReserved2;
      for (iVar5 = 0x44; iVar5 != 0; iVar5 = iVar5 + -1) {
        *pDVar9 = 0;
        pDVar9 = pDVar9 + 1;
      }
      iVar5 = (**(code **)(*(int *)(&DAT_00491c3c)[param_3] + 0x24))
                        ((int *)(&DAT_00491c3c)[param_3],0x110,&local_154.dwReserved2);
      if (-1 < iVar5) {
        if (-1 < *(short *)((int)&DAT_00474e88 + iVar2)) {
          param_1 = param_1 | abStack_f0[*(short *)((int)&DAT_00474e88 + iVar2)] >> 7;
        }
        sVar1 = *(short *)((int)&DAT_00474e88 + iVar2 + 2);
        if (-1 < sVar1) {
          param_1 = param_1 | abStack_f0[sVar1] >> 6 & 2;
        }
        sVar1 = *(short *)((int)&DAT_00474e8c + iVar2 + 2);
        if (-1 < sVar1) {
          param_1 = param_1 | abStack_f0[sVar1] >> 4 & 8;
        }
        if (-1 < *(short *)((int)&DAT_00474e8c + iVar2)) {
          param_1 = param_1 | abStack_f0[*(short *)((int)&DAT_00474e8c + iVar2)] >> 5 & 4;
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

