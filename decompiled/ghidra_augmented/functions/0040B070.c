/* Raw Ghidra reference; not compilable reconstruction. Address: 0040B070 */

void FUN_0040b070(int param_1,int *param_2)

{
  short sVar1;
  void *pvVar2;
  int in_EAX;
  int iVar3;
  undefined4 *puVar4;
  int iVar5;
  undefined4 extraout_ECX;
  undefined4 extraout_ECX_00;
  int iVar6;
  
  iVar3 = in_EAX * 0x10;
  iVar6 = *(int *)(param_1 + 0x10);
  sVar1 = *(short *)(&DAT_00474430 + iVar3);
  puVar4 = FUN_00449950();
  puVar4[8] = 0xf;
  puVar4[0xd7] = puVar4[0xd7] | 0x40000000;
  FUN_00449870(puVar4,(int)sVar1);
  pvVar2 = g_pGameStateManager;
  FUN_004489d0(extraout_ECX,(int)g_pGameStateManager);
  iVar5 = FUN_004491c0(extraout_ECX_00,(int)pvVar2,iVar6);
  if (iVar5 == 0) {
    iVar6 = 0;
  }
  if ((code *)(&PTR_FUN_00474434)[in_EAX * 4] != (code *)0x0) {
    (*(code *)(&PTR_FUN_00474434)[in_EAX * 4])();
  }
  *(undefined4 *)(iVar5 + 0x398) = *(undefined4 *)(&DAT_00474438 + iVar3);
  *(undefined4 *)(iVar5 + 0x39c) = *(undefined4 *)(&DAT_0047443c + iVar3);
  *param_2 = iVar6;
  return;
}

