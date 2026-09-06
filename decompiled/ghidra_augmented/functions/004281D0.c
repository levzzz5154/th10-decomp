/* Raw Ghidra reference; not compilable reconstruction. Address: 004281D0 */

undefined4 FUN_004281d0(void)

{
  int in_EAX;
  
  if (*(int *)(in_EAX + 0x458) != 1) {
    *(undefined4 *)(in_EAX + 0x3504) = 0;
    *(undefined1 *)(in_EAX + 0x3508) = 0;
    return 0;
  }
  if (*(int *)(in_EAX + 0x464) < 0) {
    if (((byte)DAT_00474e5c & 1) == 0) {
      return 0;
    }
    FUN_00405410(0);
  }
  if (*(int *)(in_EAX + 0x464) != *(int *)(in_EAX + 0x460)) {
    FUN_00428160();
  }
  if (0xe < *(int *)(in_EAX + 0x464)) {
    if (((byte)DAT_00474e5c & 1) != 0) {
      FUN_0044bf40(-15.0);
      return 0;
    }
    FUN_00405410(-1);
    return 0;
  }
  FUN_00404ed0();
  return 0;
}

