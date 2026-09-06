/* Raw Ghidra reference; not compilable reconstruction. Address: 0043BB30 */

undefined4 FUN_0043bb30(int param_1)

{
  int iVar1;
  undefined4 local_18;
  undefined4 local_14;
  uint local_10;
  undefined4 local_c;
  undefined4 local_8;
  undefined4 local_4;
  
  local_10 = *(uint *)(param_1 + 0x18);
  if ((local_10 & 3) != 0) {
    local_18 = 0x18;
    local_14 = 0x10;
    local_c = 2;
    local_8 = 0xfffffc18;
    local_4 = 1000;
    iVar1 = (**(code **)(*DAT_00491c3c + 0x18))(DAT_00491c3c,4,&local_18);
    if (iVar1 < 0) {
      return 0;
    }
  }
  return 1;
}

