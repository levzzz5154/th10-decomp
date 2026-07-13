/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x00419040
 * Tracking name: FUN_00419040
 * Ghidra name: FUN_00419040
 * Tracked span: 80 bytes
 */


void FUN_00419040(void)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  void *_Memory;
  int in_EAX;
  int iVar3;
  undefined4 *puVar4;
  
  puVar4 = (undefined4 *)(in_EAX + 0x7c);
  iVar3 = 8;
  do {
    puVar2 = (undefined4 *)puVar4[-0x18];
    while (puVar2 != (undefined4 *)0x0) {
      puVar1 = (undefined4 *)puVar2[1];
      _free((void *)*puVar2);
      puVar2 = puVar1;
    }
    puVar2 = (undefined4 *)*puVar4;
    while (puVar2 != (undefined4 *)0x0) {
      _Memory = (void *)*puVar2;
      puVar2 = (undefined4 *)puVar2[1];
      _free(_Memory);
    }
    puVar4 = puVar4 + 3;
    iVar3 = iVar3 + -1;
  } while (iVar3 != 0);
  return;
}

