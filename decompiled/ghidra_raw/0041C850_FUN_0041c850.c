/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x0041C850
 * Tracking name: FUN_0041c850
 * Ghidra name: FUN_0041c850
 * Tracked span: 1920 bytes
 */


undefined4 FUN_0041c850(void)

{
  int *piVar1;
  int *piVar2;
  int in_EAX;
  
  piVar1 = *(int **)(in_EAX + 0x18);
  while (piVar2 = piVar1, piVar2 != (int *)0x0) {
    piVar1 = (int *)piVar2[2];
    if (piVar2[3] != 1) {
      (**(code **)(*piVar2 + 0x14))();
    }
  }
  return 1;
}

