/* Raw Ghidra reference; not compilable reconstruction. Address: 00449700 */

/* WARNING: Restarted to delay deadcode elimination for space: stack */

void FUN_00449700(void)

{
  undefined4 *in_EAX;
  int iVar1;
  undefined4 *puVar2;
  int *piStack_3c;
  int *piStack_38;
  undefined1 *puStack_34;
  int local_2c [11];
  
  piStack_3c = (int *)*in_EAX;
  puStack_34 = (undefined1 *)local_2c;
  piStack_38 = (int *)0x0;
  (**(code **)(*piStack_3c + 0x48))();
  (**(code **)(*piStack_38 + 0x30))(piStack_38);
  (**(code **)(local_2c[0] + 0x34))();
  puVar2 = (undefined4 *)0x0;
  for (iVar1 = 0; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  for (iVar1 = 0; iVar1 != 0; iVar1 = iVar1 + -1) {
    *(undefined1 *)puVar2 = 0;
    puVar2 = (undefined4 *)((int)puVar2 + 1);
  }
  (*(code *)piStack_3c[0xe])(&piStack_3c);
  if (local_2c != (int *)0x0) {
    (**(code **)(local_2c[0] + 8))(local_2c);
  }
  return;
}

