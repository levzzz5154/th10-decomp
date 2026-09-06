/* Raw Ghidra reference; not compilable reconstruction. Address: 00419F40 */

uint * FUN_00419f40(uint *param_1,uint *param_2,uint param_3)

{
  uint *in_EAX;
  uint *puVar1;
  uint *puVar2;
  uint uVar3;
  uint uVar4;
  uint *puVar5;
  
  puVar1 = param_1;
  for (uVar3 = param_3 >> 2; uVar3 != 0; uVar3 = uVar3 - 1) {
    *puVar1 = 0;
    puVar1 = puVar1 + 1;
  }
  for (uVar3 = param_3 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
    *(undefined1 *)puVar1 = 0;
    puVar1 = (uint *)((int)puVar1 + 1);
  }
  if ((char)*param_1 == '\0') {
    while ((puVar1 = FUN_00452730(in_EAX,'\n'), puVar1 != (uint *)0x0 ||
           (puVar1 = FUN_00452730(in_EAX,'\r'), puVar1 != (uint *)0x0))) {
      uVar3 = (int)puVar1 - (int)in_EAX;
      if ((int)(param_3 - 1) <= (int)puVar1 - (int)in_EAX) {
        uVar3 = param_3 - 1;
      }
      puVar2 = in_EAX;
      puVar5 = param_1;
      for (uVar4 = uVar3 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
        *puVar5 = *puVar2;
        puVar2 = puVar2 + 1;
        puVar5 = puVar5 + 1;
      }
      for (uVar3 = uVar3 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
        *(char *)puVar5 = (char)*puVar2;
        puVar2 = (uint *)((int)puVar2 + 1);
        puVar5 = (uint *)((int)puVar5 + 1);
      }
      *param_2 = (int)in_EAX + (*param_2 - (int)puVar1);
      for (; ((char)*puVar1 == '\n' || ((char)*puVar1 == '\r')); puVar1 = (uint *)((int)puVar1 + 1))
      {
        *param_2 = *param_2 - 1;
      }
      puVar2 = FUN_00452730(param_1,'#');
      if (puVar2 != (uint *)0x0) {
        uVar4 = (int)param_1 + (param_3 - (int)puVar2);
        puVar5 = puVar2;
        for (uVar3 = uVar4 >> 2; uVar3 != 0; uVar3 = uVar3 - 1) {
          *puVar5 = 0;
          puVar5 = puVar5 + 1;
        }
        for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
          *(undefined1 *)puVar5 = 0;
          puVar5 = (uint *)((int)puVar5 + 1);
        }
        *(undefined1 *)puVar2 = 0;
      }
      FUN_0041a0a0();
      in_EAX = puVar1;
      if ((char)*param_1 != '\0') {
        return puVar1;
      }
    }
    uVar3 = *param_2;
    puVar1 = in_EAX;
    for (uVar4 = uVar3 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
      *param_1 = *puVar1;
      puVar1 = puVar1 + 1;
      param_1 = param_1 + 1;
    }
    for (uVar3 = uVar3 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
      *(char *)param_1 = (char)*puVar1;
      puVar1 = (uint *)((int)puVar1 + 1);
      param_1 = (uint *)((int)param_1 + 1);
    }
    *param_2 = 0;
  }
  return in_EAX;
}

