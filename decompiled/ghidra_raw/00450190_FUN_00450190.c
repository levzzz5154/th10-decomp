/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x00450190
 * Tracking name: FUN_00450190
 * Ghidra name: FUN_00450190
 * Tracked span: 32 bytes
 */


void FUN_00450190(void)

{
  int *piVar1;
  int *piVar2;
  int in_EAX;
  
  piVar2 = *(int **)(in_EAX + 0x1034);
  while (piVar2 != (int *)0x0) {
    piVar1 = (int *)piVar2[1];
    *(undefined4 *)(*piVar2 + 4) = 0;
    piVar2 = piVar1;
  }
  return;
}

