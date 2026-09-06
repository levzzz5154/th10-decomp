/* Raw Ghidra reference; not compilable reconstruction. Address: 0044D5D0 */

undefined4 InvokeConfiguredPlatform(void)

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

