/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x0043B110
 * Tracking name: FUN_0043b110
 * Ghidra name: FUN_0043b110
 * Tracked span: 1680 bytes
 */


void FUN_0043b110(int param_1,undefined4 *param_2)

{
  int *piVar1;
  char cVar2;
  byte bVar3;
  LPMIDIHDR pmh;
  byte *pbVar4;
  undefined4 *puVar5;
  void *pvVar6;
  int iVar7;
  LPSTR pCVar8;
  MMRESULT MVar9;
  undefined4 *puVar10;
  int iVar11;
  uint uVar12;
  int iVar13;
  byte bVar14;
  LPMIDIHDR pmVar15;
  longlong lVar16;
  ulonglong uVar17;
  byte local_b;
  byte local_a;
  
  puVar5 = param_2;
  iVar13 = param_1;
  local_a = *(byte *)param_2[5];
  piVar1 = param_2 + 5;
  local_b = 0;
  param_1._0_1_ = 0;
  bVar3 = (byte)param_1;
  param_1._0_1_ = 0;
  if (local_a < 0x80) {
    local_a = *(byte *)(param_2 + 3);
  }
  else {
    *piVar1 = (int)((byte *)param_2[5] + 1);
  }
  bVar14 = local_a & 0xf;
  switch(local_a & 0xf0) {
  case 0x80:
  case 0x90:
  case 0xa0:
  case 0xb0:
  case 0xe0:
    pbVar4 = (byte *)*piVar1;
    local_b = *pbVar4;
    *piVar1 = (int)(pbVar4 + 1);
    param_1._0_1_ = pbVar4[1];
    *piVar1 = (int)(pbVar4 + 2);
    break;
  case 0xc0:
  case 0xd0:
    local_b = *(byte *)*piVar1;
    *piVar1 = (int)((byte *)*piVar1 + 1);
    param_1._0_1_ = 0;
    break;
  case 0xf0:
    if (local_a == 0xf0) {
      if (*(int *)(iVar13 + 0x14 + *(int *)(iVar13 + 0x94) * 4) != 0) {
        FUN_0043aeb0(*(int *)(iVar13 + 0x94),iVar13);
      }
      pvVar6 = _malloc(0x40);
      *(void **)(iVar13 + 0x14 + *(int *)(iVar13 + 0x94) * 4) = pvVar6;
      pmh = *(LPMIDIHDR *)(iVar13 + 0x14 + *(int *)(iVar13 + 0x94) * 4);
      iVar7 = FUN_0043a730();
      pmVar15 = pmh;
      for (iVar11 = 0x10; iVar11 != 0; iVar11 = iVar11 + -1) {
        pmVar15->lpData = (LPSTR)0x0;
        pmVar15 = (LPMIDIHDR)&pmVar15->dwBufferLength;
      }
      pCVar8 = _malloc(iVar7 + 1U);
      pmh->lpData = pCVar8;
      *pCVar8 = -0x10;
      iVar11 = 0;
      pmh->dwFlags = 0;
      pmh->dwBufferLength = iVar7 + 1U;
      if (0 < iVar7) {
        do {
          pmh->lpData[iVar11 + 1] = *(CHAR *)param_2[5];
          iVar11 = iVar11 + 1;
          param_2[5] = param_2[5] + 1;
        } while (iVar11 < iVar7);
      }
      if ((*(HMIDIOUT *)(iVar13 + 0x13c) != (HMIDIOUT)0x0) &&
         ((MVar9 = midiOutPrepareHeader(*(HMIDIOUT *)(iVar13 + 0x13c),pmh,0x40), MVar9 != 0 ||
          (MVar9 = midiOutLongMsg(*(HMIDIOUT *)(iVar13 + 0x13c),pmh,0x40), MVar9 != 0)))) {
        if (pmh->lpData != (LPSTR)0x0) {
          _free(pmh->lpData);
          pmh->lpData = (LPSTR)0x0;
        }
        _free(pmh);
        *(undefined4 *)(iVar13 + 0x14 + *(int *)(iVar13 + 0x94) * 4) = 0;
      }
      uVar12 = *(int *)(iVar13 + 0x94) + 1U & 0x8000001f;
      if ((int)uVar12 < 0) {
        uVar12 = (uVar12 - 1 | 0xffffffe0) + 1;
      }
      *(uint *)(iVar13 + 0x94) = uVar12;
      param_1._0_1_ = bVar3;
    }
    else if (local_a == 0xff) {
      cVar2 = *(char *)*piVar1;
      *piVar1 = (int)((char *)*piVar1 + 1);
      iVar7 = FUN_0043a730();
      if (cVar2 == '/') {
        *param_2 = 0;
        return;
      }
      if (cVar2 == 'Q') {
        lVar16 = __allmul(*(uint *)(iVar13 + 0x120),(int)*(uint *)(iVar13 + 0x120) >> 0x1f,
                          *(uint *)(iVar13 + 0x128),*(int *)(iVar13 + 300));
        lVar16 = __allmul((uint)lVar16,(int)((ulonglong)lVar16 >> 0x20),1000,0);
        lVar16 = __aulldiv((uint)lVar16,(uint)((ulonglong)lVar16 >> 0x20),*(uint *)(iVar13 + 0x124),
                           (int)*(uint *)(iVar13 + 0x124) >> 0x1f);
        *(longlong *)(iVar13 + 0x130) = lVar16 + *(longlong *)(iVar13 + 0x130);
        *(undefined4 *)(iVar13 + 0x128) = 0;
        *(undefined4 *)(iVar13 + 300) = 0;
        *(undefined4 *)(iVar13 + 0x124) = 0;
        param_1._0_1_ = bVar3;
        if (0 < iVar7) {
          do {
            *(uint *)(iVar13 + 0x124) = *(int *)(iVar13 + 0x124) * 0x101 + (uint)*(byte *)*piVar1;
            iVar7 = iVar7 + -1;
            *piVar1 = *piVar1 + 1;
          } while (iVar7 != 0);
        }
      }
      else {
        *piVar1 = *piVar1 + iVar7;
        param_1._0_1_ = bVar3;
      }
    }
  }
  switch(local_a & 0xf0) {
  case 0x90:
    if ((byte)param_1 != 0) {
      local_b = local_b + *(char *)(iVar13 + 0x2c4);
      pbVar4 = (byte *)((uint)bVar14 * 0x17 + 0x154 + (uint)(local_b >> 3) + iVar13);
      *pbVar4 = *pbVar4 | '\x01' << (local_b & 7);
      break;
    }
  case 0x80:
    local_b = local_b + *(char *)(iVar13 + 0x2c4);
    pbVar4 = (byte *)((uint)bVar14 * 0x17 + 0x154 + (uint)(local_b >> 3) + iVar13);
    *pbVar4 = *pbVar4 & ~('\x01' << (local_b & 7));
    break;
  case 0xb0:
    switch(local_b) {
    case 0:
      *(byte *)((uint)bVar14 * 0x17 + 0x165 + iVar13) = (byte)param_1;
      break;
    case 2:
      iVar7 = 0;
      if (0 < *(int *)(iVar13 + 0x118)) {
        puVar10 = (undefined4 *)(*(int *)(iVar13 + 0x138) + 0x18);
        do {
          *puVar10 = puVar10[-1];
          puVar10[1] = puVar10[-5];
          iVar7 = iVar7 + 1;
          puVar10 = puVar10 + 8;
        } while (iVar7 < *(int *)(iVar13 + 0x118));
      }
      *(undefined4 *)(iVar13 + 0x2ec) = *(undefined4 *)(iVar13 + 0x124);
      *(undefined4 *)(iVar13 + 0x2f0) = *(undefined4 *)(iVar13 + 0x128);
      *(undefined4 *)(iVar13 + 0x2f4) = *(undefined4 *)(iVar13 + 300);
      *(undefined4 *)(iVar13 + 0x2f8) = *(undefined4 *)(iVar13 + 0x130);
      *(undefined4 *)(iVar13 + 0x2fc) = *(undefined4 *)(iVar13 + 0x134);
      break;
    case 4:
      iVar7 = 0;
      if (0 < *(int *)(iVar13 + 0x118)) {
        puVar10 = (undefined4 *)(*(int *)(iVar13 + 0x138) + 0x14);
        do {
          *puVar10 = puVar10[1];
          puVar10[-4] = puVar10[2];
          iVar7 = iVar7 + 1;
          puVar10 = puVar10 + 8;
        } while (iVar7 < *(int *)(iVar13 + 0x118));
      }
      *(undefined4 *)(iVar13 + 0x124) = *(undefined4 *)(iVar13 + 0x2ec);
      *(undefined4 *)(iVar13 + 0x128) = *(undefined4 *)(iVar13 + 0x2f0);
      *(undefined4 *)(iVar13 + 300) = *(undefined4 *)(iVar13 + 0x2f4);
      *(undefined4 *)(iVar13 + 0x130) = *(undefined4 *)(iVar13 + 0x2f8);
      *(undefined4 *)(iVar13 + 0x134) = *(undefined4 *)(iVar13 + 0x2fc);
      break;
    case 7:
      param_2 = (undefined4 *)0x0;
      iVar7 = (uint)bVar14 * 0x17 + iVar13;
      *(byte *)(iVar7 + 0x169) = (byte)param_1;
      uVar17 = FUN_00463b2c();
      iVar11 = (int)uVar17;
      if (iVar11 < 0) {
        *(undefined1 *)(iVar7 + 0x16a) = 0;
        param_1._0_1_ = 0;
      }
      else {
        if (0x7f < iVar11) {
          iVar11 = 0x7f;
        }
        param_1._0_1_ = (byte)iVar11;
        *(byte *)(iVar7 + 0x16a) = (byte)param_1;
      }
      break;
    case 10:
      *(byte *)((uint)bVar14 * 0x17 + 0x166 + iVar13) = (byte)param_1;
      break;
    case 0x5b:
      *(byte *)((uint)bVar14 * 0x17 + 0x167 + iVar13) = (byte)param_1;
      break;
    case 0x5d:
      *(byte *)((uint)bVar14 * 0x17 + 0x168 + iVar13) = (byte)param_1;
    }
    break;
  case 0xc0:
    *(byte *)((uint)bVar14 * 0x17 + 0x164 + iVar13) = local_b;
  }
  if ((local_a < 0xf0) && (*(HMIDIOUT *)(iVar13 + 0x13c) != (HMIDIOUT)0x0)) {
    param_2._0_3_ = CONCAT12((byte)param_1,CONCAT11(local_b,local_a));
    midiOutShortMsg(*(HMIDIOUT *)(iVar13 + 0x13c),(DWORD)param_2);
  }
  *(byte *)(puVar5 + 3) = local_a;
  iVar13 = 0;
  do {
    bVar3 = *(byte *)puVar5[5];
    puVar5[5] = (byte *)puVar5[5] + 1;
    iVar13 = iVar13 * 0x80 + (bVar3 & 0x7f);
  } while ((char)bVar3 < '\0');
  puVar5[1] = puVar5[1] + iVar13;
  return;
}

