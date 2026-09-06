/* Raw Ghidra reference; not compilable reconstruction. Address: 00455D53 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 __cdecl FUN_00455d53(char *param_1)

{
  int iVar1;
  uint *puVar2;
  int iVar3;
  size_t sVar4;
  uint *puVar5;
  int *piVar6;
  BOOL BVar7;
  uint uVar8;
  undefined4 uVar9;
  int unaff_ESI;
  undefined1 local_1c4 [8];
  int local_1bc;
  uint local_1b4;
  ushort local_1b0 [6];
  int local_1a4;
  LPWORD local_1a0;
  uint *local_19c;
  undefined *local_198;
  LPWORD local_194;
  undefined *local_190;
  undefined1 local_18c;
  byte abStack_18b [255];
  uint local_8c [5];
  undefined1 local_78 [112];
  uint local_8;
  
  local_8 = DAT_00473660 ^ (uint)local_78;
  puVar2 = FUN_00455bf3(param_1,local_8c,local_1b0,&local_194);
  uVar9 = 0;
  if (puVar2 != (uint *)0x0) {
    iVar3 = _strcmp((char *)local_8c,(char *)(&DAT_0047334c)[unaff_ESI * 3]);
    if (iVar3 == 0) {
      uVar9 = (&DAT_0047334c)[unaff_ESI * 3];
    }
    else {
      sVar4 = _strlen((char *)local_8c);
      local_19c = _malloc(sVar4 + 1);
      uVar9 = 0;
      if (local_19c != (uint *)0x0) {
        local_198 = (undefined *)(&DAT_0047334c)[unaff_ESI * 3];
        puVar2 = (uint *)(&DAT_0047764c + unaff_ESI * 4);
        local_1b4 = *puVar2;
        local_190 = &DAT_0047766c + unaff_ESI * 6;
        _memcpy(local_1c4,local_190,6);
        local_1a0 = DAT_00477664;
        puVar5 = FUN_0045bd80(local_19c,local_8c);
        (&DAT_0047334c)[unaff_ESI * 3] = puVar5;
        *puVar2 = (uint)local_1b0[0];
        _memcpy(local_190,local_1b0,6);
        uVar8 = _DAT_00473ae0;
        if (unaff_ESI == 2) {
          local_190 = (undefined *)0x0;
          DAT_00477664 = local_194;
          local_1a4 = DAT_00473234;
          piVar6 = (int *)&DAT_00473210;
          iVar3 = DAT_00473230;
          do {
            if (local_194 == (LPWORD)*piVar6) {
              if (local_190 != (undefined *)0x0) {
                DAT_00473210 = (&DAT_00473210)[(int)local_190 * 2];
                DAT_00473214 = (&DAT_00473214)[(int)local_190 * 2];
                (&DAT_00473210)[(int)local_190 * 2] = (LPWORD)iVar3;
                (&DAT_00473214)[(int)local_190 * 2] = local_1a4;
              }
              break;
            }
            local_1bc = *piVar6;
            local_190 = local_190 + 1;
            *piVar6 = iVar3;
            iVar1 = piVar6[1];
            piVar6[1] = local_1a4;
            piVar6 = piVar6 + 2;
            iVar3 = local_1bc;
            local_1a4 = iVar1;
          } while ((int)piVar6 < 0x473238);
          uVar8 = DAT_00473214;
          if (local_190 == (undefined *)0x5) {
            BVar7 = ___crtGetStringTypeA
                              ((_locale_t)0x1,0x46a928,&DAT_0000007f,(int)&local_18c,local_194,
                               DAT_00477654,1);
            if (BVar7 == 0) {
              DAT_00473214 = 0;
            }
            else {
              uVar8 = 0;
              do {
                abStack_18b[uVar8 * 2] = abStack_18b[uVar8 * 2] & 1;
                uVar8 = uVar8 + 1;
              } while (uVar8 < 0x7f);
              iVar3 = _memcmp(&local_18c,&DAT_0046a828,0xfe);
              DAT_00473214 = (uint)(iVar3 == 0);
            }
            DAT_00473210 = DAT_00477664;
            uVar8 = DAT_00473214;
          }
        }
        _DAT_00473ae0 = uVar8;
        if (unaff_ESI == 1) {
          _DAT_00477668 = local_194;
        }
        iVar3 = (*(code *)(&PTR_FUN_00473350)[unaff_ESI * 3])();
        if (iVar3 == 0) {
          if (local_198 != &DAT_004731b0) {
            _free(local_198);
          }
          uVar9 = (&DAT_0047334c)[unaff_ESI * 3];
        }
        else {
          (&DAT_0047334c)[unaff_ESI * 3] = local_198;
          _free(local_19c);
          *puVar2 = local_1b4;
          DAT_00477664 = local_1a0;
          uVar9 = 0;
        }
      }
    }
  }
  return uVar9;
}

