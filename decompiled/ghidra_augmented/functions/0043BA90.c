/* Raw Ghidra reference; not compilable reconstruction. Address: 0043BA90 */

void FUN_0043ba90(void)

{
  uint uVar1;
  
  DAT_00491ff4 = DAT_00491ff4 & 0xfffff9ff;
  FUN_0043b8d0();
  uVar1 = DAT_00491ff4 ^ ((uint)(DAT_00491c38 != 0) << 9 ^ DAT_00491ff4) & 0x200;
  DAT_00491ff4 = uVar1 ^ ((uint)(DAT_00491c3c != 0) << 10 ^ uVar1) & 0x400;
  return;
}

