/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x00448AC0
 * Tracking name: FUN_00448ac0
 * Ghidra name: FUN_00448ac0
 * Tracked span: 128 bytes
 */


void __fastcall FUN_00448ac0(undefined4 param_1,int param_2)

{
  undefined4 *puVar1;
  int iVar2;
  undefined4 *in_EAX;
  undefined4 *unaff_EBX;
  int iVar3;
  
  puVar1 = unaff_EBX + 1;
  *puVar1 = unaff_EBX;
  unaff_EBX[2] = 0;
  unaff_EBX[3] = 0;
  if (*(int *)(param_2 + 0x72dadc) == 0) {
    *(undefined4 **)(param_2 + 0x72dadc) = puVar1;
  }
  else {
    iVar2 = *(int *)(param_2 + 0x72dae0);
    if (*(int *)(iVar2 + 4) != 0) {
      unaff_EBX[2] = *(int *)(iVar2 + 4);
      *(undefined4 **)(*(int *)(iVar2 + 4) + 8) = puVar1;
    }
    *(undefined4 **)(iVar2 + 4) = puVar1;
    unaff_EBX[3] = iVar2;
  }
  *(undefined4 **)(param_2 + 0x72dae0) = puVar1;
  iVar2 = *(int *)(param_2 + 0x732454);
  iVar3 = iVar2 + 1;
  *(int *)(param_2 + 0x732454) = iVar3;
  if (iVar3 == 0) {
    *(int *)(param_2 + 0x732454) = iVar2 + 2;
  }
  *unaff_EBX = *(undefined4 *)(param_2 + 0x732454);
  *in_EAX = *(undefined4 *)(param_2 + 0x732454);
  return;
}

