/* Raw Ghidra reference; not compilable reconstruction. Address: 0045B033 */

/* Library Function - Single Match
    __get_lc_time
   
   Library: Visual Studio 2003 Release */

uint __get_lc_time(void)

{
  _locale_t plVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  uint uVar9;
  uint uVar10;
  uint uVar11;
  uint uVar12;
  uint uVar13;
  uint uVar14;
  uint uVar15;
  uint uVar16;
  uint uVar17;
  uint uVar18;
  uint uVar19;
  uint uVar20;
  uint uVar21;
  uint uVar22;
  uint uVar23;
  uint uVar24;
  uint uVar25;
  uint uVar26;
  uint uVar27;
  uint uVar28;
  uint uVar29;
  uint uVar30;
  uint uVar31;
  uint uVar32;
  uint uVar33;
  uint uVar34;
  uint uVar35;
  uint uVar36;
  uint uVar37;
  uint uVar38;
  uint uVar39;
  uint uVar40;
  uint uVar41;
  uint uVar42;
  uint uVar43;
  uint uVar44;
  uint uVar45;
  _locale_t plVar46;
  char *unaff_ESI;
  
  plVar1 = (_locale_t)(uint)DAT_0047768a;
  plVar46 = (_locale_t)(uint)DAT_0047768c;
  if (unaff_ESI == (char *)0x0) {
    return 0xffffffff;
  }
  uVar2 = FUN_0046041e(1,plVar1,(LPCWSTR)&DAT_00000031,unaff_ESI + 4);
  uVar3 = FUN_0046041e(1,plVar1,(LPCWSTR)&DAT_00000032,unaff_ESI + 8);
  uVar4 = FUN_0046041e(1,plVar1,(LPCWSTR)&DAT_00000033,unaff_ESI + 0xc);
  uVar5 = FUN_0046041e(1,plVar1,(LPCWSTR)&DAT_00000034,unaff_ESI + 0x10);
  uVar6 = FUN_0046041e(1,plVar1,(LPCWSTR)&DAT_00000035,unaff_ESI + 0x14);
  uVar7 = FUN_0046041e(1,plVar1,(LPCWSTR)&DAT_00000036,unaff_ESI + 0x18);
  uVar8 = FUN_0046041e(1,plVar1,(LPCWSTR)&DAT_00000037,unaff_ESI);
  uVar9 = FUN_0046041e(1,plVar1,(LPCWSTR)&DAT_0000002a,unaff_ESI + 0x20);
  uVar10 = FUN_0046041e(1,plVar1,(LPCWSTR)&DAT_0000002b,unaff_ESI + 0x24);
  uVar11 = FUN_0046041e(1,plVar1,(LPCWSTR)&DAT_0000002c,unaff_ESI + 0x28);
  uVar12 = FUN_0046041e(1,plVar1,(LPCWSTR)&DAT_0000002d,unaff_ESI + 0x2c);
  uVar13 = FUN_0046041e(1,plVar1,(LPCWSTR)&DAT_0000002e,unaff_ESI + 0x30);
  uVar14 = FUN_0046041e(1,plVar1,(LPCWSTR)&DAT_0000002f,unaff_ESI + 0x34);
  uVar15 = FUN_0046041e(1,plVar1,(LPCWSTR)&DAT_00000030,unaff_ESI + 0x1c);
  uVar16 = FUN_0046041e(1,plVar1,(LPCWSTR)&DAT_00000044,unaff_ESI + 0x38);
  uVar17 = FUN_0046041e(1,plVar1,(LPCWSTR)&DAT_00000045,unaff_ESI + 0x3c);
  uVar18 = FUN_0046041e(1,plVar1,(LPCWSTR)&DAT_00000046,unaff_ESI + 0x40);
  uVar19 = FUN_0046041e(1,plVar1,(LPCWSTR)&DAT_00000047,unaff_ESI + 0x44);
  uVar20 = FUN_0046041e(1,plVar1,(LPCWSTR)&DAT_00000048,unaff_ESI + 0x48);
  uVar21 = FUN_0046041e(1,plVar1,(LPCWSTR)&DAT_00000049,unaff_ESI + 0x4c);
  uVar22 = FUN_0046041e(1,plVar1,(LPCWSTR)&DAT_0000004a,unaff_ESI + 0x50);
  uVar23 = FUN_0046041e(1,plVar1,(LPCWSTR)&DAT_0000004b,unaff_ESI + 0x54);
  uVar24 = FUN_0046041e(1,plVar1,(LPCWSTR)&DAT_0000004c,unaff_ESI + 0x58);
  uVar25 = FUN_0046041e(1,plVar1,(LPCWSTR)&DAT_0000004d,unaff_ESI + 0x5c);
  uVar26 = FUN_0046041e(1,plVar1,(LPCWSTR)&DAT_0000004e,unaff_ESI + 0x60);
  uVar27 = FUN_0046041e(1,plVar1,(LPCWSTR)&DAT_0000004f,unaff_ESI + 100);
  uVar28 = FUN_0046041e(1,plVar1,(LPCWSTR)&DAT_00000038,unaff_ESI + 0x68);
  uVar29 = FUN_0046041e(1,plVar1,(LPCWSTR)&DAT_00000039,unaff_ESI + 0x6c);
  uVar30 = FUN_0046041e(1,plVar1,(LPCWSTR)&DAT_0000003a,unaff_ESI + 0x70);
  uVar31 = FUN_0046041e(1,plVar1,(LPCWSTR)&DAT_0000003b,unaff_ESI + 0x74);
  uVar32 = FUN_0046041e(1,plVar1,(LPCWSTR)&DAT_0000003c,unaff_ESI + 0x78);
  uVar33 = FUN_0046041e(1,plVar1,(LPCWSTR)&DAT_0000003d,unaff_ESI + 0x7c);
  uVar34 = FUN_0046041e(1,plVar1,(LPCWSTR)&DAT_0000003e,unaff_ESI + 0x80);
  uVar35 = FUN_0046041e(1,plVar1,(LPCWSTR)&DAT_0000003f,unaff_ESI + 0x84);
  uVar36 = FUN_0046041e(1,plVar1,(LPCWSTR)&DAT_00000040,unaff_ESI + 0x88);
  uVar37 = FUN_0046041e(1,plVar1,(LPCWSTR)&DAT_00000041,unaff_ESI + 0x8c);
  uVar38 = FUN_0046041e(1,plVar1,(LPCWSTR)&DAT_00000042,unaff_ESI + 0x90);
  uVar39 = FUN_0046041e(1,plVar1,(LPCWSTR)&DAT_00000043,unaff_ESI + 0x94);
  uVar40 = FUN_0046041e(1,plVar1,(LPCWSTR)&DAT_00000028,unaff_ESI + 0x98);
  uVar41 = FUN_0046041e(1,plVar1,(LPCWSTR)&DAT_00000029,unaff_ESI + 0x9c);
  uVar42 = FUN_0046041e(1,plVar46,(LPCWSTR)&DAT_0000001f,unaff_ESI + 0xa0);
  uVar43 = FUN_0046041e(1,plVar46,(LPCWSTR)&DAT_00000020,unaff_ESI + 0xa4);
  uVar44 = FUN_0046041e(1,plVar46,(LPCWSTR)&DAT_00001003,unaff_ESI + 0xa8);
  uVar45 = FUN_0046041e(0,plVar46,(LPCWSTR)&DAT_00001009,unaff_ESI + 0xb0);
  *(_locale_t *)(unaff_ESI + 0xac) = plVar46;
  return uVar2 | uVar3 | uVar4 | uVar5 | uVar6 | uVar7 | uVar8 | uVar9 | uVar10 | uVar11 | uVar12 |
         uVar13 | uVar14 | uVar15 | uVar16 | uVar17 | uVar18 | uVar19 | uVar20 | uVar21 | uVar22 |
         uVar23 | uVar24 | uVar25 | uVar26 | uVar27 | uVar28 | uVar29 | uVar30 | uVar31 | uVar32 |
         uVar33 | uVar34 | uVar35 | uVar36 | uVar37 | uVar38 | uVar39 | uVar40 | uVar41 | uVar42 |
         uVar43 | uVar44 | uVar45;
}

