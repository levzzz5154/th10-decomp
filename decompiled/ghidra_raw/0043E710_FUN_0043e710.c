/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x0043E710
 * Tracking name: FUN_0043e710
 * Ghidra name: FUN_0043e710
 * Tracked span: 208 bytes
 */


void __fastcall FUN_0043e710(undefined2 *param_1)

{
  undefined2 uVar1;
  uint uVar2;
  undefined4 uVar3;
  undefined4 *in_EAX;
  undefined2 extraout_var;
  int iVar4;
  int unaff_EBX;
  
  iVar4 = *(int *)(*(int *)(param_1 + 0x8e) + unaff_EBX * 4);
  if ((iVar4 != 0) && (*(int *)(param_1 + 0x92) == 0)) {
    FUN_00401de0(iVar4,in_EAX);
    *(short *)((int)in_EAX + 0x38a) = (short)unaff_EBX;
    uVar1 = *param_1;
    *(undefined2 *)((int)in_EAX + 0x386) = uVar1;
    in_EAX[0xc2] = param_1;
    in_EAX[0xd7] = in_EAX[0xd7] & 0xfffff9ff;
    uVar2 = *(uint *)(param_1 + 0x8e);
    uVar3 = *(undefined4 *)(uVar2 + unaff_EBX * 4);
    in_EAX[0xe3] = uVar3;
    in_EAX[0xe4] = uVar3;
    if ((in_EAX[0x1b] & 1) == 0) {
      in_EAX[0x18] = 0;
      in_EAX[0x17] = 0xfff0bdc1;
      in_EAX[0x19] = 0;
      in_EAX[0x1a] = &DAT_00476f78;
      in_EAX[0x1b] = in_EAX[0x1b] | 1;
    }
    in_EAX[0x18] = 0;
    in_EAX[0x19] = 0;
    in_EAX[0x17] = 0xffffffff;
    in_EAX[0xd7] = in_EAX[0xd7] & 0xfffffffe;
    FUN_0043ee30(CONCAT22(extraout_var,uVar1),uVar2,(int)in_EAX);
    *(int *)((int)g_pGameStateManager + 0x4c) = *(int *)((int)g_pGameStateManager + 0x4c) + 1;
    return;
  }
  for (iVar4 = 0xeb; iVar4 != 0; iVar4 = iVar4 + -1) {
    *in_EAX = 0;
    in_EAX = in_EAX + 1;
  }
  return;
}

