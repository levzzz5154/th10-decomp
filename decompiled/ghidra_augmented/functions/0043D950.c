/* Raw Ghidra reference; not compilable reconstruction. Address: 0043D950 */

undefined4 FUN_0043d950(void)

{
  int in_EAX;
  undefined4 uVar1;
  HANDLE pvVar2;
  int iVar3;
  uint uVar4;
  int *unaff_ESI;
  uint uVar5;
  
  if (unaff_ESI[0x184] != 0) {
    if (DAT_00491d63 == '\0') {
      return 0xffffffff;
    }
    if (*unaff_ESI != 0) {
      if (((byte)DAT_00491d78 & 0x10) == 0) {
        uVar1 = FUN_0043d790(unaff_ESI + in_EAX * 0x40 + 0x1042);
        return uVar1;
      }
      if (unaff_ESI[in_EAX + 0x7b0] != 0) {
        uVar4 = (uint)*(ushort *)(unaff_ESI[in_EAX + 0x7a0] + 0x2c);
        uVar5 = (*(int *)(unaff_ESI[in_EAX + 0x7a0] + 0x24) * uVar4 & 0x3fffffff) >> 2;
        pvVar2 = CreateEventA((LPSECURITY_ATTRIBUTES)0x0,0,0,(LPCSTR)0x0);
        unaff_ESI[0x1483] = (int)pvVar2;
        pvVar2 = CreateThread((LPSECURITY_ATTRIBUTES)0x0,0,FUN_0043e3a0,DAT_00491c70,0,
                              (LPDWORD)(unaff_ESI + 0x185));
        unaff_ESI[0x186] = (int)pvVar2;
        iVar3 = FUN_0044cbf0(unaff_ESI + 0x1482,0x10100,(int *)unaff_ESI[0x184],
                             unaff_ESI[in_EAX + 0x7c0],unaff_ESI[in_EAX + 2000],
                             unaff_ESI[in_EAX + 0x7a0],DAT_0046a67c,DAT_0046a680,DAT_0046a684,
                             DAT_0046a688,0x10,uVar5 - uVar5 % uVar4,unaff_ESI[0x1483]);
        if (-1 < iVar3) {
          unaff_ESI[0x7e0] = in_EAX;
          return 0;
        }
      }
    }
  }
  return 0xffffffff;
}

