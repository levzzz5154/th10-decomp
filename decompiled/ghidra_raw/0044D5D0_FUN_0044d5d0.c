/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x0044D5D0
 * Tracking name: FUN_0044d5d0
 * Ghidra name: FUN_0044d5d0
 * Tracked span: 48 bytes
 */


undefined4 FUN_0044d5d0(void)

{
  int *piVar1;
  int in_EAX;
  undefined4 uVar2;
  
  if (*(undefined4 **)(in_EAX + 4) == (undefined4 *)0x0) {
    return 0x800401f0;
  }
  piVar1 = (int *)**(undefined4 **)(in_EAX + 4);
  *(undefined4 *)(in_EAX + 0x30) = 1;
  uVar2 = (**(code **)(*piVar1 + 0x30))
                    (piVar1,0,*(undefined4 *)(in_EAX + 0x20),*(undefined4 *)(in_EAX + 0x24));
  return uVar2;
}

