/* Raw Ghidra reference; not compilable reconstruction. Address: 00448B40 */

void __fastcall FUN_00448b40(undefined4 param_1,int param_2)

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
  iVar2 = *(int *)(param_2 + 0x72dadc);
  if (iVar2 == 0) {
    *(undefined4 **)(param_2 + 0x72dae0) = puVar1;
  }
  else {
    if (unaff_EBX[2] != 0) {
      *(undefined4 *)(iVar2 + 4) = unaff_EBX[2];
      *(int *)(unaff_EBX[2] + 8) = iVar2;
    }
    unaff_EBX[2] = iVar2;
    *(undefined4 **)(iVar2 + 8) = puVar1;
  }
  *(undefined4 **)(param_2 + 0x72dadc) = puVar1;
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

