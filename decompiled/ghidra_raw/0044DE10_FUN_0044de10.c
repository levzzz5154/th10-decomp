/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x0044DE10
 * Tracking name: FUN_0044de10
 * Ghidra name: FUN_0044de10
 * Tracked span: 352 bytes
 */


undefined4 __fastcall
FUN_0044de10(undefined4 param_1,uint param_2,undefined4 *param_3,uint *param_4)

{
  uint *puVar1;
  int in_EAX;
  uint uVar2;
  undefined4 *puVar3;
  
  puVar1 = param_4;
  if (*(int *)(in_EAX + 0x7c) == 0) {
    if (*(HANDLE *)(in_EAX + 0x8c) != (HANDLE)0x0) {
      if ((param_3 != (undefined4 *)0x0) && (param_4 != (uint *)0x0)) {
        uVar2 = *(uint *)(in_EAX + 8);
        if (uVar2 < param_2) {
          param_2 = uVar2;
        }
        *(uint *)(in_EAX + 8) = uVar2 - param_2;
        ReadFile(*(HANDLE *)(in_EAX + 0x8c),param_3,param_2,(LPDWORD)&param_3,(LPOVERLAPPED)0x0);
        *puVar1 = (uint)param_3;
        return 0;
      }
      return 0x80070057;
    }
  }
  else if (*(int *)(in_EAX + 0x84) != 0) {
    if (param_4 != (uint *)0x0) {
      *param_4 = 0;
    }
    puVar3 = *(undefined4 **)(in_EAX + 0x84);
    if ((undefined1 *)(*(int *)(in_EAX + 0x80) + *(int *)(in_EAX + 0x88)) <
        (undefined1 *)((int)puVar3 + param_2)) {
      param_2 = (*(int *)(in_EAX + 0x80) - (int)puVar3) + *(int *)(in_EAX + 0x88);
    }
    for (uVar2 = param_2 >> 2; uVar2 != 0; uVar2 = uVar2 - 1) {
      *param_3 = *puVar3;
      puVar3 = puVar3 + 1;
      param_3 = param_3 + 1;
    }
    for (uVar2 = param_2 & 3; uVar2 != 0; uVar2 = uVar2 - 1) {
      *(undefined1 *)param_3 = *(undefined1 *)puVar3;
      puVar3 = (undefined4 *)((int)puVar3 + 1);
      param_3 = (undefined4 *)((int)param_3 + 1);
    }
    *(int *)(in_EAX + 0x84) = *(int *)(in_EAX + 0x84) + param_2;
    if (param_4 != (uint *)0x0) {
      *param_4 = param_2;
    }
    return 0;
  }
  return 0x800401f0;
}

