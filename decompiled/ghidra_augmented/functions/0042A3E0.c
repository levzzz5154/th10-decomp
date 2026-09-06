/* Raw Ghidra reference; not compilable reconstruction. Address: 0042A3E0 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 __fastcall FUN_0042a3e0(int param_1)

{
  undefined4 uVar1;
  uint uVar2;
  bool bVar3;
  
  if (DAT_00477810 != 0) {
    uVar1 = 1;
    if ((((*(byte *)(DAT_00477810 + 0x58) & 4) == 0) && (*(int *)(param_1 + 0x10) == 1)) &&
       ((_DAT_00474e30 & 0x100) != 0)) {
      uVar2 = *(uint *)(param_1 + 0x1c8) & 0x80000003;
      bVar3 = uVar2 == 0;
      if ((int)uVar2 < 0) {
        bVar3 = (uVar2 - 1 | 0xfffffffc) == 0xffffffff;
      }
      if (!bVar3) {
        uVar1 = 6;
      }
    }
    return uVar1;
  }
  return 1;
}

