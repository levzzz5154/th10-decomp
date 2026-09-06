/* Raw Ghidra reference; not compilable reconstruction. Address: 0044D440 */

int __thiscall FUN_0044d440(void *this,undefined4 param_1,undefined4 param_2)

{
  int in_EAX;
  int *piVar1;
  int iVar2;
  
  if (*(int *)(in_EAX + 4) == 0) {
    return -0x7ffbfe10;
  }
  piVar1 = (int *)FindAvailablePlatformInterface((uint)this);
  if (piVar1 != (int *)0x0) {
    iVar2 = RunPlatformInterface();
    if (-1 < iVar2) {
      if (this != (void *)0x0) {
        iVar2 = FUN_0044d110(piVar1);
        if (iVar2 < 0) {
          return iVar2;
        }
        QueryPlatformInterfaces();
      }
      *(undefined4 *)(in_EAX + 0x1c) = 0;
      *(undefined4 *)(in_EAX + 0x14) = 0;
      *(undefined4 *)(in_EAX + 0x18) = 0;
      SetOperationDeadline();
      *(undefined4 *)(in_EAX + 0x30) = 1;
      *(undefined4 *)(in_EAX + 0x20) = param_1;
      *(undefined4 *)(in_EAX + 0x24) = param_2;
      *(undefined4 *)(in_EAX + 0x2c) = 0;
      iVar2 = (**(code **)(*piVar1 + 0x30))(piVar1,0,param_1,param_2);
    }
    return iVar2;
  }
  return -0x7fffbffb;
}

