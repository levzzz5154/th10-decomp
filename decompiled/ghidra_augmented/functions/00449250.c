/* Raw Ghidra reference; not compilable reconstruction. Address: 00449250 */

int __fastcall FUN_00449250(undefined4 param_1,int param_2,int param_3)

{
  uint *puVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  undefined4 extraout_ECX;
  uint extraout_EDX;
  undefined2 unaff_DI;
  ulonglong uVar5;
  
  iVar3 = FUN_004491c0(param_1,param_2,param_3);
  iVar4 = 0;
  if (iVar3 != 0) {
    *(undefined2 *)(iVar3 + 0x304) = unaff_DI;
    FUN_0043ee30(extraout_ECX,extraout_EDX,iVar3);
    iVar4 = *(int *)(iVar3 + 0x18);
    if (iVar4 == 0) {
      for (puVar1 = *(uint **)(iVar3 + 0x14); puVar1 != (uint *)0x0; puVar1 = (uint *)puVar1[1]) {
        uVar2 = *puVar1;
        *(undefined2 *)(uVar2 + 0x304) = unaff_DI;
        uVar5 = FUN_0043ee30(uVar2,*puVar1,*puVar1);
        iVar4 = (int)uVar5;
      }
    }
  }
  return iVar4;
}

