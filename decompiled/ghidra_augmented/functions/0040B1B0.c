/* Raw Ghidra reference; not compilable reconstruction. Address: 0040B1B0 */

int * FUN_0040b1b0(int *param_1,undefined4 param_2,int param_3,undefined4 param_4,undefined *param_5
                  ,undefined4 param_6,undefined4 param_7)

{
  void *pvVar1;
  undefined4 *puVar2;
  int iVar3;
  undefined4 extraout_ECX;
  undefined4 extraout_ECX_00;
  
  puVar2 = FUN_00449950();
  puVar2[8] = 0xf;
  puVar2[0xd7] = puVar2[0xd7] | 0x40000000;
  FUN_00449870(puVar2,(int)(short)param_3);
  pvVar1 = g_pGameStateManager;
  FUN_004489d0(extraout_ECX,(int)g_pGameStateManager);
  iVar3 = FUN_004491c0(extraout_ECX_00,(int)pvVar1,param_3);
  if (iVar3 == 0) {
    param_3 = 0;
  }
  if (param_5 != (undefined *)0x0) {
    (*(code *)param_5)();
  }
  *(undefined4 *)(iVar3 + 0x398) = param_6;
  *(undefined4 *)(iVar3 + 0x39c) = param_7;
  *param_1 = param_3;
  return param_1;
}

