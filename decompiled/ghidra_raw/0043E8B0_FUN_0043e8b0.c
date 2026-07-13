/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x0043E8B0
 * Tracking name: FUN_0043e8b0
 * Ghidra name: FUN_0043e8b0
 * Tracked span: 528 bytes
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __fastcall FUN_0043e8b0(int param_1,undefined2 *param_2)

{
  int iVar1;
  float fVar2;
  int in_EAX;
  uint uVar3;
  
  iVar1 = *(int *)(*(int *)(param_2 + 0x8e) + param_1 * 4);
  if ((iVar1 != 0) && (*(int *)(param_2 + 0x92) == 0)) {
    *(short *)(in_EAX + 0x38a) = (short)param_1;
    *(undefined2 **)(in_EAX + 0x308) = param_2;
    if ((*(uint *)(in_EAX + 0x35c) & 0x200) != 0) {
      fVar2 = *(float *)(in_EAX + 0x3c) * _DAT_00470b60;
      *(uint *)(in_EAX + 0x35c) = (*(uint *)(in_EAX + 0x35c) | 8) ^ 0x200;
      *(float *)(in_EAX + 0x3c) = fVar2;
    }
    *(undefined2 *)(in_EAX + 0x35c) = 7;
    *(undefined4 *)(in_EAX + 0x2fc) = 0xffffffff;
    *(undefined4 *)(in_EAX + 0x60) = 0;
    *(undefined4 *)(in_EAX + 100) = 0;
    *(undefined4 *)(in_EAX + 0x5c) = 0xfff0bdc1;
    *(undefined4 *)(in_EAX + 0xb4) = 0;
    *(undefined4 *)(in_EAX + 0x100) = 0;
    *(undefined4 *)(in_EAX + 300) = 0;
    *(undefined4 *)(in_EAX + 0x178) = 0;
    *(undefined4 *)(in_EAX + 0x1b4) = 0;
    *(undefined4 *)(in_EAX + 0x200) = 0;
    *(undefined4 *)(in_EAX + 0x22c) = 0;
    *(undefined2 *)(in_EAX + 0x386) = *param_2;
    *(undefined2 **)(in_EAX + 0x308) = param_2;
    *(uint *)(in_EAX + 0x35c) = *(uint *)(in_EAX + 0x35c) & 0xfffff9ff;
    *(int *)(in_EAX + 0x38c) = iVar1;
    *(int *)(in_EAX + 0x390) = iVar1;
    uVar3 = *(uint *)(in_EAX + 0x6c);
    if ((uVar3 & 1) == 0) {
      uVar3 = uVar3 | 1;
      *(undefined4 *)(in_EAX + 0x60) = 0;
      *(undefined4 *)(in_EAX + 0x5c) = 0xfff0bdc1;
      *(undefined4 *)(in_EAX + 100) = 0;
      *(undefined4 **)(in_EAX + 0x68) = &DAT_00476f78;
      *(uint *)(in_EAX + 0x6c) = uVar3;
    }
    *(undefined4 *)(in_EAX + 0x60) = 0;
    *(undefined4 *)(in_EAX + 100) = 0;
    *(undefined4 *)(in_EAX + 0x5c) = 0xffffffff;
    *(uint *)(in_EAX + 0x35c) = *(uint *)(in_EAX + 0x35c) & 0xfffffffe;
    FUN_0043ee30(0,uVar3,in_EAX);
    *(int *)((int)g_pGameStateManager + 0x4c) = *(int *)((int)g_pGameStateManager + 0x4c) + 1;
  }
  return;
}

