/* Raw Ghidra reference; not compilable reconstruction. Address: 0042C8C0 */

void FUN_0042c8c0(void)

{
  int in_EAX;
  undefined1 *puVar1;
  int iVar2;
  int iVar3;
  undefined1 *puVar4;
  int iVar5;
  
  *(undefined4 *)(in_EAX + 0x1d882) = 0x1010101;
  *(undefined4 *)(in_EAX + 0x1d886) = 0x1010101;
  *(undefined4 *)(in_EAX + 0x1d88a) = 0x1010101;
  *(undefined4 *)(in_EAX + 0x1d88e) = 0x1010101;
  puVar4 = (undefined1 *)(in_EAX + 0x4e9);
  iVar5 = 6;
  do {
    iVar3 = 4;
    puVar1 = puVar4;
    do {
      iVar2 = 6;
      do {
        *puVar1 = 1;
        puVar1 = puVar1 + 8;
        iVar2 = iVar2 + -1;
      } while (iVar2 != 0);
      iVar3 = iVar3 + -1;
    } while (iVar3 != 0);
    puVar4 = puVar4 + 0x437c;
    iVar5 = iVar5 + -1;
  } while (iVar5 != 0);
  return;
}

