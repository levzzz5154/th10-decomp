/* Raw Ghidra reference; not compilable reconstruction. Address: 00448900 */

undefined4 __fastcall FUN_00448900(undefined4 param_1,uint param_2)

{
  int *piVar1;
  int iVar2;
  int in_EAX;
  undefined4 uVar3;
  undefined4 extraout_ECX;
  undefined4 extraout_ECX_00;
  undefined4 extraout_ECX_01;
  undefined4 extraout_ECX_02;
  uint extraout_EDX;
  int iVar4;
  ulonglong uVar5;
  
  piVar1 = *(int **)(in_EAX + 0x72dadc);
  uVar3 = 0;
  *(undefined4 *)(in_EAX + 0x7320c4) = 0;
  *(undefined4 *)(in_EAX + 100) = 0;
  iVar2 = in_EAX + 0x7320a8;
  while (piVar1 != (int *)0x0) {
    iVar4 = *piVar1;
    piVar1 = (int *)piVar1[1];
    if ((*(uint *)(iVar4 + 0x35c) & 0x4000000) == 0) {
      if (*(code **)(iVar4 + 0x398) != (code *)0x0) {
        (**(code **)(iVar4 + 0x398))();
        uVar3 = extraout_ECX_00;
        param_2 = extraout_EDX;
      }
      uVar5 = FUN_0043ee30(uVar3,param_2,iVar4);
      if ((int)uVar5 == 0) {
        *(int *)(iVar2 + 0x1c) = iVar4;
        *(undefined4 *)(iVar4 + 0x1c) = 0;
        uVar3 = extraout_ECX_01;
      }
      else {
        FUN_00448bb0();
        uVar3 = extraout_ECX_02;
        iVar4 = iVar2;
      }
    }
    else {
      FUN_00448bb0();
      uVar3 = extraout_ECX;
      iVar4 = iVar2;
    }
    param_2 = *(int *)(in_EAX + 100) + 1;
    *(uint *)(in_EAX + 100) = param_2;
    iVar2 = iVar4;
  }
  return 1;
}

