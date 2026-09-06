/* Raw Ghidra reference; not compilable reconstruction. Address: 0043D120 */

undefined4 FUN_0043d120(void)

{
  int *piVar1;
  undefined4 *in_EAX;
  int iVar2;
  undefined4 *puVar3;
  int *piVar4;
  
  if ((void *)in_EAX[0x7e1] != (void *)0x0) {
    _free((void *)in_EAX[0x7e1]);
    in_EAX[0x7e1] = 0;
  }
  piVar4 = in_EAX + 2;
  iVar2 = 0x80;
  do {
    piVar1 = (int *)piVar4[0x80];
    if (piVar1 != (int *)0x0) {
      (**(code **)(*piVar1 + 8))(piVar1);
      piVar4[0x80] = 0;
    }
    piVar1 = (int *)*piVar4;
    if (piVar1 != (int *)0x0) {
      (**(code **)(*piVar1 + 8))(piVar1);
      *piVar4 = 0;
    }
    piVar4 = piVar4 + 1;
    iVar2 = iVar2 + -1;
  } while (iVar2 != 0);
  puVar3 = in_EAX + 0x148c;
  iVar2 = 0x25;
  do {
    if ((void *)*puVar3 != (void *)0x0) {
      _free((void *)*puVar3);
      *puVar3 = 0;
    }
    puVar3 = puVar3 + 1;
    iVar2 = iVar2 + -1;
  } while (iVar2 != 0);
  if (in_EAX[0x184] != 0) {
    KillTimer((HWND)in_EAX[0x183],1);
    FUN_0043dab0();
    *in_EAX = 0;
    (**(code **)(*(int *)in_EAX[0x182] + 0x48))((int *)in_EAX[0x182]);
    piVar4 = (int *)in_EAX[0x182];
    if (piVar4 != (int *)0x0) {
      (**(code **)(*piVar4 + 8))(piVar4);
      in_EAX[0x182] = 0;
    }
    if ((undefined4 *)in_EAX[0x1482] != (undefined4 *)0x0) {
      (*(code *)**(undefined4 **)in_EAX[0x1482])(1);
      in_EAX[0x1482] = 0;
    }
    piVar4 = (int *)in_EAX[0x184];
    if (piVar4 != (int *)0x0) {
      piVar1 = (int *)*piVar4;
      if (piVar1 != (int *)0x0) {
        (**(code **)(*piVar1 + 8))(piVar1);
        *piVar4 = 0;
      }
      _free(piVar4);
      in_EAX[0x184] = 0;
    }
    puVar3 = in_EAX + 0x7b0;
    iVar2 = 0x10;
    do {
      if ((void *)*puVar3 != (void *)0x0) {
        _free((void *)*puVar3);
        *puVar3 = 0;
      }
      puVar3 = puVar3 + 1;
      iVar2 = iVar2 + -1;
    } while (iVar2 != 0);
  }
  return 0;
}

