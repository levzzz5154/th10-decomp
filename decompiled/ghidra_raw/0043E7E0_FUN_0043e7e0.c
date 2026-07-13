/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x0043E7E0
 * Tracking name: FUN_0043e7e0
 * Ghidra name: FUN_0043e7e0
 * Tracked span: 208 bytes
 */


void __fastcall FUN_0043e7e0(int param_1,undefined4 *param_2)

{
  undefined4 uVar1;
  undefined2 *in_EAX;
  int iVar2;
  
  if ((*(int *)(*(int *)(in_EAX + 0x8e) + param_1 * 4) != 0) && (*(int *)(in_EAX + 0x92) == 0)) {
    *(short *)((int)param_2 + 0x38a) = (short)param_1;
    *(undefined2 *)((int)param_2 + 0x386) = *in_EAX;
    param_2[0xc2] = in_EAX;
    param_2[0xd7] = param_2[0xd7] & 0xfffff9ff;
    uVar1 = *(undefined4 *)(*(int *)(in_EAX + 0x8e) + param_1 * 4);
    param_2[0xe3] = uVar1;
    param_2[0xe4] = uVar1;
    if ((param_2[0x1b] & 1) == 0) {
      param_2[0x18] = 0;
      param_2[0x17] = 0xfff0bdc1;
      param_2[0x19] = 0;
      param_2[0x1a] = &DAT_00476f78;
      param_2[0x1b] = param_2[0x1b] | 1;
    }
    param_2[0x18] = 0;
    param_2[0x19] = 0;
    param_2[0x17] = 0xffffffff;
    param_2[0xd7] = param_2[0xd7] & 0xfffffffe;
    FUN_0043ee30(param_1,0,(int)param_2);
    *(int *)((int)g_pGameStateManager + 0x4c) = *(int *)((int)g_pGameStateManager + 0x4c) + 1;
    return;
  }
  for (iVar2 = 0xeb; iVar2 != 0; iVar2 = iVar2 + -1) {
    *param_2 = 0;
    param_2 = param_2 + 1;
  }
  return;
}

