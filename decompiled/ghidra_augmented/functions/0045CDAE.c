/* Raw Ghidra reference; not compilable reconstruction. Address: 0045CDAE */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void FUN_0045cdae(void)

{
  byte *pbVar1;
  BOOL BVar2;
  uint uVar3;
  undefined1 uVar4;
  char cVar5;
  uint uVar6;
  uint uVar7;
  BYTE *pBVar8;
  CHAR *pCVar9;
  _cpinfo local_51c;
  ushort local_508 [54];
  undefined1 local_49c [404];
  int local_308 [64];
  int local_208 [64];
  CHAR local_108 [256];
  uint local_8;
  
  local_8 = DAT_00473660 ^ (uint)local_49c;
  BVar2 = GetCPInfo((UINT)DAT_004980a4,&local_51c);
  if (BVar2 == 1) {
    uVar3 = 0;
    do {
      local_108[uVar3] = (CHAR)uVar3;
      uVar3 = uVar3 + 1;
    } while (uVar3 < 0x100);
    local_108[0] = ' ';
    if (local_51c.LeadByte[0] != 0) {
      pBVar8 = local_51c.LeadByte + 1;
      do {
        uVar3 = (uint)local_51c.LeadByte[0];
        if (uVar3 <= *pBVar8) {
          uVar6 = (*pBVar8 - uVar3) + 1;
          uVar7 = uVar6 >> 2;
          pCVar9 = local_108 + uVar3;
          while (uVar7 != 0) {
            uVar7 = uVar7 - 1;
            builtin_memcpy(pCVar9,"    ",4);
            pCVar9 = pCVar9 + 4;
          }
          for (uVar6 = uVar6 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
            *pCVar9 = ' ';
            pCVar9 = pCVar9 + 1;
          }
        }
        local_51c.LeadByte[0] = pBVar8[1];
        pBVar8 = pBVar8 + 2;
      } while (local_51c.LeadByte[0] != 0);
    }
    ___crtGetStringTypeA
              ((_locale_t)0x1,(DWORD)local_108,&DAT_00000100,(int)local_508,DAT_004980a4,
               DAT_00497f90,0);
    FUN_0045ee1d(DAT_00497f90,0x100,local_108,0x100,local_208,0x100,(UINT)DAT_004980a4,0);
    FUN_0045ee1d(DAT_00497f90,0x200,local_108,0x100,local_308,0x100,(UINT)DAT_004980a4,0);
    uVar3 = 0;
    do {
      if ((local_508[uVar3] & 1) == 0) {
        if ((local_508[uVar3] & 2) != 0) {
          pbVar1 = (byte *)((int)&DAT_00497fa0 + uVar3 + 1);
          *pbVar1 = *pbVar1 | 0x20;
          uVar4 = *(undefined1 *)((int)local_308 + uVar3);
          goto LAB_0045cec4;
        }
        (&DAT_004980c0)[uVar3] = 0;
      }
      else {
        pbVar1 = (byte *)((int)&DAT_00497fa0 + uVar3 + 1);
        *pbVar1 = *pbVar1 | 0x10;
        uVar4 = *(undefined1 *)((int)local_208 + uVar3);
LAB_0045cec4:
        (&DAT_004980c0)[uVar3] = uVar4;
      }
      uVar3 = uVar3 + 1;
    } while (uVar3 < 0x100);
  }
  else {
    uVar3 = 0;
    do {
      if ((uVar3 < 0x41) || (0x5a < uVar3)) {
        if ((0x60 < uVar3) && (uVar3 < 0x7b)) {
          pbVar1 = (byte *)((int)&DAT_00497fa0 + uVar3 + 1);
          *pbVar1 = *pbVar1 | 0x20;
          cVar5 = (char)uVar3 + -0x20;
          goto LAB_0045cf07;
        }
        (&DAT_004980c0)[uVar3] = 0;
      }
      else {
        pbVar1 = (byte *)((int)&DAT_00497fa0 + uVar3 + 1);
        *pbVar1 = *pbVar1 | 0x10;
        cVar5 = (char)uVar3 + ' ';
LAB_0045cf07:
        (&DAT_004980c0)[uVar3] = cVar5;
      }
      uVar3 = uVar3 + 1;
    } while (uVar3 < 0x100);
  }
  return;
}

