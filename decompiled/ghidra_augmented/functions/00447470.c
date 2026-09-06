/* Raw Ghidra reference; not compilable reconstruction. Address: 00447470 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4
FUN_00447470(undefined4 param_1,int param_2,undefined4 param_3,undefined4 param_4,int *param_5)

{
  int in_EAX;
  int iVar1;
  int iVar2;
  int *piVar3;
  char *pcVar4;
  undefined4 uStack_60;
  int iStack_14;
  int iStack_10;
  int iStack_8;
  
  if (param_5 == (int *)0x0) {
    pcVar4 = &DAT_00470274;
  }
  else {
    if (param_5[10] == 4) {
      iVar1 = in_EAX * 0x10;
      if ((char)param_5[0xd] == '\0') {
        if (*(char *)(param_5[7] + (int)param_5) == '@') {
          FUN_00447050(param_5[4],param_5[3]);
        }
        else {
          iVar2 = FUN_00446eb0(param_2,param_5[4],param_1,param_5[6],param_5[3]);
          if (iVar2 != 0) {
            FUN_0044b8e0(&DAT_004701b0);
            return 0xffffffff;
          }
        }
      }
      else {
        iVar2 = FUN_00446f40((void *)(param_5[0xc] + (int)param_5),param_5[3],(int *)param_5[4]);
        if (iVar2 != 0) {
          FUN_0044b8e0(&DAT_0047016c);
          return 0xffffffff;
        }
      }
      piVar3 = *(int **)(iVar1 + *(int *)(param_2 + 0x120));
      (**(code **)(*piVar3 + 0x1c))(piVar3,param_5[0xb]);
      piVar3 = *(int **)(iVar1 + *(int *)(param_2 + 0x120));
      (**(code **)(*piVar3 + 0x24))(piVar3);
      piVar3 = *(int **)(iVar1 + *(int *)(param_2 + 0x120));
      (**(code **)(*piVar3 + 0x44))(piVar3,0,&stack0xffffff90);
      piVar3 = param_5 + 0x10;
      iStack_14 = 0;
      if (0 < *param_5) {
        do {
          FUN_00447940(uStack_60,iStack_10);
          iStack_14 = iStack_14 + 1;
          piVar3 = piVar3 + 1;
          param_2 = iStack_10;
        } while (iStack_14 < *param_5);
      }
      iVar1 = 0;
      if (0 < param_5[1]) {
        iVar2 = iStack_8 << 2;
        piVar3 = piVar3 + 1;
        do {
          *(int *)(iVar2 + *(int *)(param_2 + 0x11c)) = *piVar3 + (int)param_5;
          iVar2 = iVar2 + 4;
          iVar1 = iVar1 + 1;
          piVar3 = piVar3 + 2;
        } while (iVar1 < param_5[1]);
      }
      return 1;
    }
    pcVar4 = &DAT_00470254;
  }
  FUN_0044b8e0(pcVar4);
  return 0xffffffff;
}

