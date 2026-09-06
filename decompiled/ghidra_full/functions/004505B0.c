/* Raw Ghidra reference; not compilable reconstruction. Address: 004505B0 */

undefined4 __fastcall FUN_004505b0(undefined4 param_1,char param_2,uint param_3,undefined4 *param_4)

{
  int in_EAX;
  uint uVar1;
  undefined4 *puVar2;
  
  if (0xfff < (int)(*(int *)(in_EAX + 0x1000) + param_3)) {
    return 0xffffffff;
  }
  if (param_2 != '\0') {
    *(char *)(*(int *)(in_EAX + 0x1000) + in_EAX) = param_2;
    *(int *)(in_EAX + 0x1000) = *(int *)(in_EAX + 0x1000) + 4;
  }
  puVar2 = (undefined4 *)(*(int *)(in_EAX + 0x1000) + in_EAX);
  for (uVar1 = param_3 >> 2; uVar1 != 0; uVar1 = uVar1 - 1) {
    *puVar2 = *param_4;
    param_4 = param_4 + 1;
    puVar2 = puVar2 + 1;
  }
  for (uVar1 = param_3 & 3; uVar1 != 0; uVar1 = uVar1 - 1) {
    *(undefined1 *)puVar2 = *(undefined1 *)param_4;
    param_4 = (undefined4 *)((int)param_4 + 1);
    puVar2 = (undefined4 *)((int)puVar2 + 1);
  }
  *(uint *)(in_EAX + 0x1000) = *(int *)(in_EAX + 0x1000) + param_3;
  return 0;
}

