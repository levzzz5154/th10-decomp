/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x00437A00
 * Tracking name: FUN_00437a00
 * Ghidra name: FUN_00437a00
 * Tracked span: 784 bytes
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00437a00(void)

{
  ushort uVar1;
  undefined4 uVar2;
  short sVar3;
  uint uVar4;
  
  uVar2 = FUN_00436af0(0x400,0x40,0x1a);
  if ((char)uVar2 == '\0') {
    FUN_00436af0(0x400,0x40,0x15);
  }
  uVar4 = 0;
  do {
    uVar1 = ((ushort)_DAT_004918b0 ^ 0x9630) + 0x9aad;
    sVar3 = (uVar1 >> 0xe) + uVar1 * 4;
    _DAT_004918b0 = CONCAT22(DAT_004918b0_2,sVar3);
    DAT_004918b4 = DAT_004918b4 + 1;
    (&DAT_00474cb0)[uVar4] = (byte)((ushort)sVar3 >> 9);
    uVar4 = uVar4 + 1;
  } while (uVar4 < 0x100);
  DAT_004918a0 = CreateFontA(0x20,0,0,0,400,0,0,0,0x80,0,0,4,0x11,&DAT_0046f36c);
  DAT_0049189c = CreateFontA(0x22,0,0,0,400,0,0,0,0x80,0,0,4,0x11,&DAT_0046f36c);
  DAT_00491898 = CreateFontA(0x24,0,0,0,400,0,0,0,0x80,0,0,4,0x11,&DAT_0046f36c);
  DAT_00491894 = CreateFontA(0x26,0,0,0,400,0,0,0,0x80,0,0,4,0x11,&DAT_0046f36c);
  DAT_00491890 = CreateFontA(0x28,0,0,0,400,0,0,0,0x80,0,0,4,0x11,&DAT_0046f36c);
  DAT_0049188c = CreateFontA(0x2a,0,0,0,400,0,0,0,0x80,0,0,4,0x11,&DAT_0046f36c);
  DAT_00491888 = CreateFontA(0x2c,0,0,0,400,0,0,0,0x80,0,0,4,0x11,&DAT_0046f36c);
  DAT_00491884 = CreateFontA(0x2e,0,0,0,400,0,0,0,0x80,0,0,4,0x11,&DAT_0046f36c);
  DAT_00491880 = CreateFontA(0x30,0,0,0,400,0,0,0,0x80,0,0,4,0x11,&DAT_0046f36c);
  DAT_0049187c = CreateFontA(0x32,0,0,0,400,0,0,0,0x80,0,0,4,0x11,&DAT_0046f36c);
  DAT_00491878 = CreateFontA(0x34,0,0,0,400,0,0,0,0x80,0,0,4,0x11,&DAT_0046f36c);
  DAT_00491874 = CreateFontA(0x36,0,0,0,400,0,0,0,0x80,0,0,4,0x11,&DAT_0046f36c);
  DAT_00491870 = CreateFontA(0x38,0,0,0,400,0,0,0,0x80,0,0,4,0x11,&DAT_0046f36c);
  DAT_0049186c = CreateFontA(0x3a,0,0,0,400,0,0,0,0x80,0,0,4,0x11,&DAT_0046f36c);
  DAT_00491868 = CreateFontA(0x3c,0,0,0,400,0,0,0,0x80,0,0,4,0x11,&DAT_0046f36c);
  return;
}

