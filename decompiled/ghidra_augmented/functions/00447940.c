/* Raw Ghidra reference; not compilable reconstruction. Address: 00447940 */

void __fastcall FUN_00447940(undefined4 param_1,int param_2)

{
  int in_EAX;
  int iVar1;
  int iVar2;
  undefined4 *unaff_EBX;
  undefined4 *puVar3;
  undefined4 *puVar4;
  
  iVar1 = in_EAX * 0x44;
  puVar3 = unaff_EBX;
  puVar4 = (undefined4 *)(*(int *)(param_2 + 0x118) + iVar1);
  for (iVar2 = 0x11; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar4 = *puVar3;
    puVar3 = puVar3 + 1;
    puVar4 = puVar4 + 1;
  }
  iVar2 = *(int *)(param_2 + 0x118) + iVar1;
  *(float *)(iVar2 + 0x20) = *(float *)(iVar2 + 8) / *(float *)(iVar2 + 0x1c);
  iVar2 = *(int *)(param_2 + 0x118);
  *(float *)(iVar2 + iVar1 + 0x28) =
       *(float *)(iVar2 + 0x10 + iVar1) / *(float *)(iVar2 + 0x1c + iVar1);
  iVar2 = *(int *)(param_2 + 0x118);
  *(float *)(iVar2 + iVar1 + 0x24) =
       *(float *)(iVar2 + 0xc + iVar1) / *(float *)(iVar2 + 0x18 + iVar1);
  iVar2 = *(int *)(param_2 + 0x118);
  *(float *)(iVar2 + iVar1 + 0x2c) =
       *(float *)(iVar2 + 0x14 + iVar1) / *(float *)(iVar2 + 0x18 + iVar1);
  iVar2 = *(int *)(param_2 + 0x118);
  *(float *)(iVar2 + iVar1 + 0x34) =
       (*(float *)(iVar2 + 0x10 + iVar1) - *(float *)(iVar2 + 8 + iVar1)) / (float)unaff_EBX[0xe];
  iVar2 = *(int *)(param_2 + 0x118);
  *(float *)(iVar1 + iVar2 + 0x30) =
       (*(float *)(iVar1 + 0x14 + iVar2) - *(float *)(iVar1 + 0xc + iVar2)) / (float)unaff_EBX[0xf];
  return;
}

