/* Raw Ghidra reference; not compilable reconstruction. Address: 0044D4E0 */

void SetOperationDeadline(void)

{
  int *piVar1;
  int iVar2;
  int in_EAX;
  ulonglong uVar3;
  
  if (DAT_00497854 != 0) {
    piVar1 = (int *)**(undefined4 **)(in_EAX + 4);
    iVar2 = *piVar1;
    uVar3 = FUN_00463b2c();
    (**(code **)(iVar2 + 0x3c))(piVar1,(int)uVar3 + -5000);
    return;
  }
  (**(code **)(*(int *)**(undefined4 **)(in_EAX + 4) + 0x3c))
            ((int *)**(undefined4 **)(in_EAX + 4),0xffffd8f0);
  return;
}

