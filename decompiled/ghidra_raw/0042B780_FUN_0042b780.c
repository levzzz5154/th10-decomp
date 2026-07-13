/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x0042B780
 * Tracking name: FUN_0042b780
 * Ghidra name: FUN_0042b780
 * Tracked span: 576 bytes
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_0042b780(void)

{
  byte bVar1;
  void *pvVar2;
  int iVar3;
  uint uVar4;
  byte *pbVar5;
  char cVar6;
  int iVar7;
  int unaff_EDI;
  ulonglong uVar8;
  float local_10;
  int local_4;
  
  iVar7 = unaff_EDI + 0x3c4;
  if ((((byte)DAT_00491d78 & 4) == 0) && (DAT_00492378 != 0)) {
    FUN_00442f50();
    DAT_00492378 = 0;
    (**(code **)(*(int *)g_pD3DDevice + 0xe4))(g_pD3DDevice,0x1c,0);
  }
  local_4 = 0x2d3;
  do {
    if (*(char *)(iVar7 + 0x38) != '\0') {
      if (*(int *)(iVar7 + 0x20) < 8) {
        local_10 = _DAT_00470bd0 / *(float *)(iVar7 + 0x24);
      }
      else {
        local_10 = 8.0;
      }
      *(float *)(unaff_EDI + 0x358) =
           (*(float *)(iVar7 + 0xc) - (float)*(byte *)(iVar7 + 0x39) * local_10 * _DAT_00470b0c) +
           _DAT_00470b4c;
      *(float *)(unaff_EDI + 0x35c) = *(float *)(iVar7 + 0x10) + _DAT_00470b48;
      *(undefined4 *)(unaff_EDI + 0x314) = *(undefined4 *)(iVar7 + 0x18);
      uVar8 = FUN_00463b2c();
      iVar3 = (int)uVar8;
      if (iVar3 < 0x1001) {
        if (iVar3 < 0x401) {
          cVar6 = 'P';
        }
        else {
          cVar6 = (char)(((iVar3 + -0x400) * 0x80) / 0xc00) + 'P';
        }
      }
      else {
        cVar6 = -0x30;
      }
      uVar4 = (uint)*(byte *)(iVar7 + 0x39);
      pbVar5 = (byte *)((uVar4 - 1) + iVar7);
      for (; uVar4 != 0; uVar4 = uVar4 - 1) {
        if ((*(int *)(iVar7 + 0x20) < 0x34) || (bVar1 = *pbVar5, bVar1 == 10)) {
          *(uint *)(unaff_EDI + 0x3ac) =
               (*pbVar5 + 0xc4) * 0x44 + *(int *)(*(int *)(unaff_EDI + 0x10) + 0x118);
        }
        else if (*(int *)(iVar7 + 0x20) < 0x38) {
          *(uint *)(unaff_EDI + 0x3ac) =
               (bVar1 + 0xcf) * 0x44 + *(int *)(*(int *)(unaff_EDI + 0x10) + 0x118);
        }
        else {
          *(uint *)(unaff_EDI + 0x3ac) =
               (bVar1 + 0xd9) * 0x44 + *(int *)(*(int *)(unaff_EDI + 0x10) + 0x118);
        }
        pvVar2 = g_pGameStateManager;
        *(char *)(unaff_EDI + 0x317) = cVar6;
        *(undefined4 *)(unaff_EDI + 100) = *(undefined4 *)(*(int *)(unaff_EDI + 0x3ac) + 0x34);
        *(uint *)(unaff_EDI + 0x374) = *(uint *)(unaff_EDI + 0x374) | 8;
        FUN_00443080(pvVar2);
        pbVar5 = pbVar5 + -1;
        *(float *)(unaff_EDI + 0x358) = local_10 + *(float *)(unaff_EDI + 0x358);
      }
    }
    iVar7 = iVar7 + 0x40;
    local_4 = local_4 + -1;
  } while (local_4 != 0);
  return 1;
}

