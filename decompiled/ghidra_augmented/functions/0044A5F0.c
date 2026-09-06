/* Raw Ghidra reference; not compilable reconstruction. Address: 0044A5F0 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __fastcall FUN_0044a5f0(int param_1)

{
  ushort *puVar1;
  ushort uVar2;
  int iVar3;
  ushort *puVar4;
  ushort uVar5;
  int iVar6;
  undefined1 local_108 [4];
  BYTE local_104;
  byte bStack_103;
  byte local_f7;
  byte local_f4;
  byte local_f3;
  byte bStack_f1;
  byte bStack_eb;
  byte local_e9;
  byte bStack_e8;
  byte bStack_e7;
  byte bStack_e5;
  byte bStack_e4;
  byte local_e0;
  byte local_df;
  byte local_de;
  byte local_dd;
  byte local_dc;
  byte bStack_da;
  byte bStack_d8;
  byte bStack_d7;
  byte local_c0;
  byte bStack_bd;
  byte bStack_bc;
  byte bStack_bb;
  byte bStack_b9;
  byte bStack_b7;
  byte bStack_b5;
  byte local_b4;
  byte local_b3;
  byte local_b2;
  byte local_b1;
  byte local_ac;
  byte local_aa;
  byte local_a3;
  byte local_a2;
  byte local_a1;
  byte local_a0;
  byte local_9e;
  byte local_9d;
  byte local_9c;
  byte local_9b;
  byte bStack_3d;
  byte bStack_3c;
  byte bStack_39;
  byte bStack_37;
  byte bStack_34;
  uint local_4;
  
  local_4 = DAT_00473660 ^ (uint)local_108;
  iVar3 = param_1 * 0x6a;
  uVar5 = 0;
  puVar4 = &DAT_00474e30 + param_1 * 0x35;
  if (DAT_004924fc != 0) {
    if ((DAT_00491ff4 & 0x200) == 0) {
      GetKeyboardState(&local_104);
      uVar5 = (ushort)(byte)((byte)((byte)((byte)((byte)((byte)((byte)(local_ac & 0xbf |
                                                                      local_aa >> 1) >> 1 |
                                                               local_f4 & 0x9f) >> 1 |
                                                        local_e9 & 0x8f) >> 1 |
                                                 (local_9c | local_de) & 0x87) >> 1 |
                                          (local_a2 | local_dc) & 0x83) >> 1 |
                                   (local_a0 | local_df) & 0x81) >> 1 | (local_9e | local_dd) & 0x80
                            ) |
              (((((((ushort)(local_b2 & 0x80) << 1 | (ushort)(local_c0 & 0x80)) << 1 |
                  (ushort)(local_f7 & 0x80)) << 1 | (ushort)((local_b4 | local_e0) & 0x80)) << 1 |
                (ushort)(local_b1 & 0x80)) << 1 | (ushort)(local_b3 & 0x80)) << 1 |
              (ushort)(local_f3 & 0x80)) << 1 | -(ushort)((local_a1 & 0x80) != 0) & 0xa0 |
              -(ushort)((local_9b & 0x80) != 0) & 0x90 | -(ushort)((local_a3 & 0x80) != 0) & 0x60 |
              -(ushort)((local_9d & 0x80) != 0) & 0x50;
    }
    else {
      iVar6 = (**(code **)(*DAT_00491c38 + 0x24))(DAT_00491c38,0x100,&local_104);
      uVar5 = 0;
      if (iVar6 == -0x7ff8ffe2) {
        (**(code **)(*DAT_00491c38 + 0x1c))(DAT_00491c38);
      }
      else if (iVar6 == 0) {
        uVar5 = (ushort)(byte)((byte)((byte)((byte)((byte)((byte)((byte)(bStack_d7 & 0xbf |
                                                                        bStack_d8 >> 1) >> 1 |
                                                                 bStack_da & 0x9f) >> 1 |
                                                          bStack_103 & 0x8f) >> 1 |
                                                   (bStack_bc | bStack_3c) & 0x87) >> 1 |
                                            (bStack_34 | local_b4) & 0x83) >> 1 |
                                     (bStack_b9 | bStack_39) & 0x81) >> 1 |
                              (bStack_b7 | bStack_37) & 0x80) |
                (((((((ushort)(bStack_f1 & 0x80) << 1 | (ushort)(bStack_e4 & 0x80)) << 1 |
                    (ushort)(bStack_e8 & 0x80)) << 1 | (ushort)((bStack_eb | bStack_3d) & 0x80)) <<
                   1 | (ushort)(bStack_e5 & 0x80)) << 1 | (ushort)(local_f4 & 0x80)) << 1 |
                (ushort)(bStack_e7 & 0x80)) << 1 | -(ushort)((bStack_bb & 0x80) != 0) & 0x90 |
                -(ushort)((bStack_b5 & 0x80) != 0) & 0x60 |
                -(ushort)((bStack_bd & 0x80) != 0) & 0x50 | -(ushort)((local_b3 & 0x80) != 0) & 0xa0
        ;
      }
      else {
        (**(code **)(*DAT_00491c38 + 0x1c))(DAT_00491c38);
      }
    }
  }
  uVar5 = FUN_0044a190(uVar5,param_1,0);
  *(ushort *)(&DAT_00474e32 + iVar3) = *puVar4;
  *puVar4 = uVar5;
  uVar2 = 1;
  *(undefined2 *)(&DAT_00474e34 + iVar3) = 0;
  puVar1 = (ushort *)(&DAT_00474e3a + iVar3);
  iVar6 = 0x10;
  do {
    if ((uVar5 & 1) == 0) {
      *puVar1 = 0;
    }
    else {
      *puVar1 = *puVar1 + 1;
      if (0x19 < *puVar1) {
        *(ushort *)(&DAT_00474e34 + iVar3) = *(ushort *)(&DAT_00474e34 + iVar3) | uVar2;
        *puVar1 = *puVar1 - 8;
      }
    }
    uVar5 = uVar5 >> 1;
    puVar1 = puVar1 + 1;
    uVar2 = uVar2 << 1;
    iVar6 = iVar6 + -1;
  } while (iVar6 != 0);
  uVar5 = *puVar4;
  *(ushort *)(&DAT_00474e36 + iVar3) = (*(ushort *)(&DAT_00474e32 + iVar3) ^ uVar5) & uVar5;
  *(ushort *)(&DAT_00474e38 + iVar3) = ~uVar5 & (*(ushort *)(&DAT_00474e32 + iVar3) ^ uVar5);
  return;
}

