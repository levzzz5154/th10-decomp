/* Raw Ghidra reference; not compilable reconstruction. Address: 0043ED00 */

int __thiscall FUN_0043ed00(byte param_1,ushort param_2)

{
  int unaff_ESI;
  int unaff_EDI;
  ulonglong uVar1;
  
  if (((uint)param_2 & 1 << (param_1 & 0x1f)) != 0) {
    uVar1 = FUN_00463b2c();
    switch((int)uVar1) {
    case 0x2714:
      return unaff_ESI + 0x31c;
    case 0x2715:
      return unaff_ESI + 800;
    case 0x2716:
      return unaff_ESI + 0x324;
    case 0x2717:
      return unaff_ESI + 0x328;
    case 0x271d:
      return unaff_ESI + 0x334;
    case 0x271e:
      return unaff_ESI + 0x338;
    case 0x271f:
      return unaff_ESI + 0x33c;
    }
  }
  return unaff_EDI;
}

