/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x00448860
 * Tracking name: FUN_00448860
 * Ghidra name: FUN_00448860
 * Tracked span: 160 bytes
 */


undefined4 __fastcall FUN_00448860(undefined4 param_1,uint param_2)

{
  int *piVar1;
  int in_EAX;
  int iVar2;
  int iVar3;
  int extraout_ECX;
  int extraout_ECX_00;
  int extraout_ECX_01;
  uint extraout_EDX;
  ulonglong uVar4;
  int aiStack_50 [20];
  
  iVar2 = 0;
  iVar3 = in_EAX + 0x72dae4;
  do {
    aiStack_50[iVar2] = iVar3;
    *(undefined4 *)(iVar3 + 0x1c) = 0;
    iVar2 = iVar2 + 1;
    iVar3 = iVar3 + 0x3ac;
  } while (iVar2 < 0x13);
  piVar1 = *(int **)(in_EAX + 0x72dad4);
  while (piVar1 != (int *)0x0) {
    iVar2 = *piVar1;
    piVar1 = (int *)piVar1[1];
    if ((*(uint *)(iVar2 + 0x35c) & 0x4000000) == 0) {
      if (*(code **)(iVar2 + 0x398) != (code *)0x0) {
        (**(code **)(iVar2 + 0x398))();
        iVar3 = extraout_ECX_00;
        param_2 = extraout_EDX;
      }
      uVar4 = FUN_0043ee30(iVar3,param_2,iVar2);
      if ((int)uVar4 == 0) {
        iVar3 = aiStack_50[*(int *)(iVar2 + 0x20)];
        *(int *)(iVar3 + 0x1c) = iVar2;
        aiStack_50[*(int *)(iVar2 + 0x20)] = iVar2;
        *(undefined4 *)(iVar2 + 0x1c) = 0;
      }
      else {
        FUN_00448bb0();
        iVar3 = extraout_ECX_01;
      }
    }
    else {
      FUN_00448bb0();
      iVar3 = extraout_ECX;
    }
    param_2 = *(int *)(in_EAX + 100) + 1;
    *(uint *)(in_EAX + 100) = param_2;
  }
  return 1;
}

