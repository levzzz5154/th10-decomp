/* Raw Ghidra reference; not compilable reconstruction. Address: 0045CFB8 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

undefined4 __cdecl FUN_0045cfb8(UINT param_1)

{
  BYTE *pBVar1;
  byte *pbVar2;
  byte bVar3;
  byte bVar4;
  uint uVar5;
  BOOL BVar6;
  BYTE *pBVar7;
  int iVar8;
  int extraout_ECX;
  undefined4 extraout_ECX_00;
  int iVar9;
  byte *pbVar10;
  byte *pbVar11;
  undefined4 *puVar12;
  uint local_20;
  _cpinfo local_1c;
  uint local_8;
  
  local_8 = DAT_00473660 ^ (uint)&stack0xfffffffc;
  if (param_1 != 0) {
    iVar9 = 0;
    uVar5 = 0;
    do {
      if (*(UINT *)((int)&DAT_00473b08 + uVar5) == param_1) {
        puVar12 = &DAT_00497fa0;
        for (iVar8 = 0x40; iVar8 != 0; iVar8 = iVar8 + -1) {
          *puVar12 = 0;
          puVar12 = puVar12 + 1;
        }
        local_20 = 0;
        *(undefined1 *)puVar12 = 0;
        pbVar10 = (byte *)(iVar9 * 0x30 + 0x473b18);
        do {
          bVar4 = *pbVar10;
          pbVar11 = pbVar10;
          while ((bVar4 != 0 && (bVar3 = pbVar11[1], bVar3 != 0))) {
            uVar5 = (uint)bVar4;
            if (uVar5 <= bVar3) {
              bVar4 = (&DAT_00473b00)[local_20];
              do {
                pbVar2 = (byte *)((int)&DAT_00497fa0 + uVar5 + 1);
                *pbVar2 = *pbVar2 | bVar4;
                uVar5 = uVar5 + 1;
              } while (uVar5 <= bVar3);
            }
            pbVar11 = pbVar11 + 2;
            bVar4 = *pbVar11;
          }
          local_20 = local_20 + 1;
          pbVar10 = pbVar10 + 8;
        } while (local_20 < 4);
        DAT_004980a4 = param_1;
        DAT_00497f98 = 1;
        DAT_00497f90 = FUN_0045cd56();
        DAT_004980b0 = *(undefined4 *)(&DAT_00473b0c + extraout_ECX);
        DAT_004980b4 = *(undefined4 *)(&DAT_00473b10 + extraout_ECX);
        DAT_004980b8 = *(undefined4 *)(&DAT_00473b14 + extraout_ECX);
        goto LAB_0045d131;
      }
      uVar5 = uVar5 + 0x30;
      iVar9 = iVar9 + 1;
    } while (uVar5 < 0xf0);
    BVar6 = GetCPInfo(param_1,&local_1c);
    if (BVar6 == 1) {
      puVar12 = &DAT_00497fa0;
      for (iVar9 = 0x40; iVar9 != 0; iVar9 = iVar9 + -1) {
        *puVar12 = 0;
        puVar12 = puVar12 + 1;
      }
      *(undefined1 *)puVar12 = 0;
      DAT_004980a4 = param_1;
      DAT_00497f90 = 0;
      if (local_1c.MaxCharSize < 2) {
        DAT_00497f98 = 0;
      }
      else {
        if (local_1c.LeadByte[0] != '\0') {
          pBVar7 = local_1c.LeadByte + 1;
          do {
            bVar4 = *pBVar7;
            if (bVar4 == 0) break;
            for (uVar5 = (uint)pBVar7[-1]; uVar5 <= bVar4; uVar5 = uVar5 + 1) {
              pbVar10 = (byte *)((int)&DAT_00497fa0 + uVar5 + 1);
              *pbVar10 = *pbVar10 | 4;
            }
            pBVar1 = pBVar7 + 1;
            pBVar7 = pBVar7 + 2;
          } while (*pBVar1 != 0);
        }
        uVar5 = 1;
        do {
          pbVar10 = (byte *)((int)&DAT_00497fa0 + uVar5 + 1);
          *pbVar10 = *pbVar10 | 8;
          uVar5 = uVar5 + 1;
        } while (uVar5 < 0xff);
        DAT_00497f90 = FUN_0045cd56();
        DAT_00497f98 = extraout_ECX_00;
      }
      DAT_004980b0 = 0;
      DAT_004980b4 = 0;
      DAT_004980b8 = 0;
      goto LAB_0045d131;
    }
    if (DAT_00477690 == 0) {
      return 0xffffffff;
    }
  }
  setSBCS();
LAB_0045d131:
  FUN_0045cdae();
  return 0;
}

