/* Raw Ghidra reference; not compilable reconstruction. Address: 0043AC90 */

undefined4 __fastcall FUN_0043ac90(int param_1)

{
  int iVar1;
  
  iVar1 = FUN_0043a9b0(param_1);
  if (iVar1 != 0) {
    return 0xffffffff;
  }
  FUN_0043aad0(0x1f);
  if (*(void **)(param_1 + 0x114) != (void *)0x0) {
    _free(*(void **)(param_1 + 0x114));
    *(undefined4 *)(param_1 + 0x114) = 0;
  }
  *(undefined4 *)(param_1 + 0x114) = 0;
  return 0;
}

