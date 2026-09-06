/* Raw Ghidra reference; not compilable reconstruction. Address: 0043BAF0 */

undefined4 FUN_0043baf0(int param_1)

{
  int iVar1;
  
  if (DAT_00491c3c == 0) {
    iVar1 = (**(code **)(*DAT_00491c34 + 0xc))(DAT_00491c34,param_1 + 4,&DAT_00491c3c,0);
    if (iVar1 < 0) {
      return 1;
    }
  }
  return 0;
}

