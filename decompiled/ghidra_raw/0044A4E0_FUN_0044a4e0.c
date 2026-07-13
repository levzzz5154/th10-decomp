/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x0044A4E0
 * Tracking name: FUN_0044a4e0
 * Ghidra name: FUN_0044a4e0
 * Tracked span: 272 bytes
 */


/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

undefined4 * __fastcall FUN_0044a4e0(int param_1)

{
  MMRESULT MVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  undefined4 *puVar5;
  joyinfoex_tag *pjVar6;
  undefined4 *puVar7;
  joyinfoex_tag local_148;
  undefined4 auStack_e4 [56];
  uint local_4;
  
  local_4 = DAT_00473660 ^ (uint)&local_148;
  puVar5 = &DAT_00497bb0;
  for (iVar4 = 0x20; iVar4 != 0; iVar4 = iVar4 + -1) {
    *puVar5 = 0;
    puVar5 = puVar5 + 1;
  }
  if ((DAT_00491ff4 & 0x400) == 0) {
    pjVar6 = &local_148;
    for (iVar4 = 0xd; iVar4 != 0; iVar4 = iVar4 + -1) {
      pjVar6->dwSize = 0;
      pjVar6 = (joyinfoex_tag *)&pjVar6->dwFlags;
    }
    local_148.dwSize = 0x34;
    local_148.dwFlags = 0xff;
    MVar1 = joyGetPosEx(0,&local_148);
    if (MVar1 == 0) {
      uVar2 = 0;
      do {
        if ((local_148.dwButtons & 1) != 0) {
          *(undefined1 *)((int)&DAT_00497bb0 + uVar2) = 0x80;
        }
        uVar2 = uVar2 + 1;
        local_148.dwButtons = local_148.dwButtons >> 1;
      } while (uVar2 < 0x20);
    }
  }
  else {
    iVar4 = (**(code **)(*(int *)(&DAT_00491c3c)[param_1] + 100))((int *)(&DAT_00491c3c)[param_1]);
    if (iVar4 < 0) {
      iVar4 = 0;
      iVar3 = (**(code **)(*(int *)(&DAT_00491c3c)[param_1] + 0x1c))
                        ((int *)(&DAT_00491c3c)[param_1]);
      do {
        if (iVar3 != -0x7ff8ffe2) break;
        iVar3 = (**(code **)(*(int *)(&DAT_00491c3c)[param_1] + 0x1c))
                          ((int *)(&DAT_00491c3c)[param_1]);
        iVar4 = iVar4 + 1;
      } while (iVar4 < 400);
    }
    else {
      (**(code **)(*(int *)(&DAT_00491c3c)[param_1] + 0x24))
                ((int *)(&DAT_00491c3c)[param_1],0x110,&local_148.dwReserved2);
      puVar5 = auStack_e4;
      puVar7 = &DAT_00497bb0;
      for (iVar4 = 0x20; iVar4 != 0; iVar4 = iVar4 + -1) {
        *puVar7 = *puVar5;
        puVar5 = puVar5 + 1;
        puVar7 = puVar7 + 1;
      }
    }
  }
  return &DAT_00497bb0;
}

