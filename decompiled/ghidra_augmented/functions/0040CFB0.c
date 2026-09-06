/* Raw Ghidra reference; not compilable reconstruction. Address: 0040CFB0 */

int FUN_0040cfb0(int param_1,void *param_2)

{
  int iVar1;
  undefined4 *in_EAX;
  void *pvVar2;
  int iVar3;
  int iVar4;
  undefined4 *puVar5;
  undefined4 *puVar6;
  
  pvVar2 = operator_new(0x2518);
  if (pvVar2 == (void *)0x0) {
    iVar3 = 0;
  }
  else {
    iVar3 = FUN_0040d830(param_2,param_2);
  }
  *(undefined4 *)(iVar3 + 0x1094) = *in_EAX;
  *(undefined4 *)(iVar3 + 0x1098) = in_EAX[1];
  *(undefined4 *)(iVar3 + 0x109c) = in_EAX[2];
  *(undefined4 *)(iVar3 + 0x23f8) = in_EAX[3];
  *(undefined4 *)(iVar3 + 0x23fc) = in_EAX[5];
  *(undefined4 *)(iVar3 + 0x2408) = in_EAX[4];
  *(uint *)(iVar3 + 0x2480) =
       *(uint *)(iVar3 + 0x2480) ^ (in_EAX[6] << 0xb ^ *(uint *)(iVar3 + 0x2480)) & 0x800;
  *(char *)(iVar3 + 0x1024) = '\x01' << ((byte)DAT_00474c74 & 0x1f);
  puVar5 = in_EAX + 8;
  puVar6 = (undefined4 *)(iVar3 + 0x1138);
  for (iVar4 = 8; iVar4 != 0; iVar4 = iVar4 + -1) {
    *puVar6 = *puVar5;
    puVar5 = puVar5 + 1;
    puVar6 = puVar6 + 1;
  }
  if ((*(uint *)(iVar3 + 0x2468) & 1) == 0) {
    *(undefined4 *)(iVar3 + 0x245c) = 0;
    *(undefined4 *)(iVar3 + 0x2458) = 0xfff0bdc1;
    *(undefined4 *)(iVar3 + 0x2460) = 0;
    *(undefined4 **)(iVar3 + 0x2464) = &DAT_00476f78;
    *(uint *)(iVar3 + 0x2468) = *(uint *)(iVar3 + 0x2468) | 1;
  }
  *(undefined4 *)(iVar3 + 0x245c) = 2;
  *(undefined4 *)(iVar3 + 0x2460) = 0x40000000;
  *(undefined4 *)(iVar3 + 0x2458) = 1;
  *(uint *)(iVar3 + 0x2480) =
       *(uint *)(iVar3 + 0x2480) ^ (in_EAX[7] << 0x12 ^ *(uint *)(iVar3 + 0x2480)) & 0x40000;
  FUN_0040dc80((undefined4 *)(iVar3 + 0x103c));
  if ((char)((uint)*(undefined4 *)(iVar3 + 0x2480) >> 8) < '\0') {
    iVar4 = *(int *)(iVar3 + 0x2408);
    if (iVar4 == 1) {
      iVar4 = 10;
    }
    else if (iVar4 == 4) {
      iVar4 = 0xb;
    }
    *(int *)(iVar3 + 0x2408) = iVar4;
  }
  *(uint *)(iVar3 + 0x2444) = (*(uint *)(param_1 + 100) & 1) + 2;
  *(undefined4 *)(iVar3 + 0x2448) = 0x167;
  if (*(int *)(iVar3 + 0x1128) == 1) {
    switch(*(undefined4 *)(iVar3 + 0x112c)) {
    case 0:
    case 0x14:
    case 0x31:
      *(undefined4 *)(iVar3 + 0x2448) = 0x167;
      break;
    case 5:
    case 0x19:
    case 0x32:
      *(undefined4 *)(iVar3 + 0x2448) = 0x164;
      break;
    case 10:
    case 0x1e:
    case 0x33:
      *(undefined4 *)(iVar3 + 0x2448) = 0x16a;
      break;
    case 0xf:
    case 0x23:
    case 0x34:
      *(undefined4 *)(iVar3 + 0x2448) = 0x16d;
    }
  }
  *(undefined4 *)(iVar3 + 0x244c) = 0;
  iVar4 = iVar3 + 0x116c;
  if (*(int *)(param_1 + 0x58) == 0) {
    *(int *)(param_1 + 0x58) = iVar4;
  }
  else {
    iVar1 = *(int *)(param_1 + 0x5c);
    if (*(int *)(iVar1 + 4) != 0) {
      *(int *)(iVar3 + 0x1170) = *(int *)(iVar1 + 4);
      *(int *)(*(int *)(iVar1 + 4) + 8) = iVar4;
    }
    *(int *)(iVar1 + 4) = iVar4;
    *(int *)(iVar3 + 0x1174) = iVar1;
  }
  *(int *)(param_1 + 0x5c) = iVar4;
  *(int *)(param_1 + 0x60) = *(int *)(param_1 + 0x60) + 1;
  *(int *)(param_1 + 100) = *(int *)(param_1 + 100) + 1;
  return iVar3;
}

