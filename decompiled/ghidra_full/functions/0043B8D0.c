/* Raw Ghidra reference; not compilable reconstruction. Address: 0043B8D0 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_0043b8d0(void)

{
  int *piVar1;
  int *piVar2;
  int *piVar3;
  int in_EAX;
  LONG LVar4;
  int iVar5;
  
  LVar4 = GetWindowLongA(*(HWND *)(in_EAX + 0x48),-6);
  if ((*(byte *)(in_EAX + 0x150) & 8) != 0) {
    return 0xffffffff;
  }
  piVar1 = (int *)(in_EAX + 0xc);
  iVar5 = DirectInput8Create(LVar4,0x800,&DAT_00467aac,piVar1,0);
  if (iVar5 < 0) {
    *piVar1 = 0;
    FUN_0044b810(&DAT_00474f70,&DAT_0046f9e0);
    return 0xffffffff;
  }
  piVar2 = (int *)(in_EAX + 0x10);
  iVar5 = (**(code **)(*(int *)*piVar1 + 0xc))((int *)*piVar1,&DAT_0046793c,piVar2,0);
  if (iVar5 < 0) {
    piVar2 = (int *)*piVar1;
    if (piVar2 != (int *)0x0) {
      (**(code **)(*piVar2 + 8))(piVar2);
      *piVar1 = 0;
    }
    FUN_0044b810(&DAT_00474f70,&DAT_0046f9e0);
    return 0xffffffff;
  }
  iVar5 = (**(code **)(*(int *)*piVar2 + 0x2c))((int *)*piVar2,&DAT_004664fc);
  piVar3 = (int *)*piVar2;
  if (iVar5 < 0) {
    if (piVar3 != (int *)0x0) {
      (**(code **)(*piVar3 + 8))(piVar3);
      *piVar2 = 0;
    }
    piVar2 = (int *)*piVar1;
    if (piVar2 != (int *)0x0) {
      (**(code **)(*piVar2 + 8))(piVar2);
      *piVar1 = 0;
    }
    FUN_0044b810(&DAT_00474f70,&DAT_0046f9b0);
    return 0xffffffff;
  }
  iVar5 = (**(code **)(*piVar3 + 0x34))(piVar3,*(undefined4 *)(in_EAX + 0x48),0x16);
  if (iVar5 < 0) {
    piVar1 = (int *)*piVar2;
    if (piVar1 != (int *)0x0) {
      (**(code **)(*piVar1 + 8))(piVar1);
      *piVar2 = 0;
    }
    FUN_00421d20();
    FUN_0044b810(&DAT_00474f70,&DAT_0046f97c);
    return 0xffffffff;
  }
  (**(code **)(*(int *)*piVar2 + 0x1c))((int *)*piVar2);
  FUN_0044b810(&DAT_00474f70,&DAT_0046f954);
  (**(code **)(*(int *)*piVar1 + 0x10))((int *)*piVar1,4,&LAB_0043baf0,0,1);
  piVar1 = *(int **)(in_EAX + 0x14);
  if (piVar1 != (int *)0x0) {
    (**(code **)(*piVar1 + 0x2c))(piVar1,&DAT_00466704);
    (**(code **)(**(int **)(in_EAX + 0x14) + 0x34))
              (*(int **)(in_EAX + 0x14),*(undefined4 *)(in_EAX + 0x48),10);
    _DAT_00491c44 = 0x2c;
    (**(code **)(**(int **)(in_EAX + 0x14) + 0xc))(*(int **)(in_EAX + 0x14),&DAT_00491c44);
    (**(code **)(**(int **)(in_EAX + 0x14) + 0x10))(*(int **)(in_EAX + 0x14),&LAB_0043bb30,0,0);
    FUN_0044b810(&DAT_00474f70,&DAT_0046f934);
  }
  return 0;
}

