/* Raw Ghidra reference; not compilable reconstruction. Address: 0046140C */

undefined4 __cdecl FUN_0046140c(int *param_1)

{
  int iVar1;
  undefined4 uVar2;
  
  uVar2 = 0xffffffff;
  if ((*(byte *)(param_1 + 3) & 0x83) != 0) {
    uVar2 = FUN_0045fbf6(param_1);
    FUN_00462225(param_1);
    iVar1 = FUN_0046218a(param_1[4]);
    if (iVar1 < 0) {
      uVar2 = 0xffffffff;
    }
    else if ((void *)param_1[7] != (void *)0x0) {
      _free((void *)param_1[7]);
      param_1[7] = 0;
    }
  }
  param_1[3] = 0;
  return uVar2;
}

