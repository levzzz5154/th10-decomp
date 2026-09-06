/* Raw Ghidra reference; not compilable reconstruction. Address: 0040D400 */

undefined4 __thiscall FUN_0040d400(void *this,int *param_1)

{
  int iVar1;
  int *piVar2;
  int *piVar3;
  int iVar4;
  uint uVar5;
  
  if (*param_1 != 0x4d494e41) {
    return 0;
  }
  piVar3 = param_1 + 2;
  if (param_1[1] != 0) {
    iVar4 = 0x34;
    uVar5 = 0;
    do {
      piVar2 = FUN_00447280(uVar5 + 9,(int)g_pGameStateManager,(char *)piVar3);
      *(int **)(iVar4 + DAT_00477704) = piVar2;
      if (piVar2 == (int *)0x0) {
        FUN_0044b810(&DAT_00474f70,&DAT_0046cb68);
        return 0xffffffff;
      }
      do {
        iVar1 = *piVar3;
        piVar3 = (int *)((int)piVar3 + 1);
      } while ((char)iVar1 != '\0');
      uVar5 = uVar5 + 1;
      iVar4 = iVar4 + 4;
    } while (uVar5 < (uint)param_1[1]);
  }
  uVar5 = (int)piVar3 - (int)param_1 & 0x80000003;
  if ((int)uVar5 < 0) {
    uVar5 = (uVar5 - 1 | 0xfffffffc) + 1;
  }
  if (uVar5 != 0) {
    piVar3 = (int *)((int)piVar3 + (4 - uVar5));
  }
  if (*piVar3 == 0x494c4345) {
    piVar2 = piVar3 + 2;
    uVar5 = 0;
    if (piVar3[1] != 0) {
      do {
        (**(code **)(*(int *)this + 8))(piVar2);
        do {
          iVar4 = *piVar2;
          piVar2 = (int *)((int)piVar2 + 1);
        } while ((char)iVar4 != '\0');
        uVar5 = uVar5 + 1;
      } while (uVar5 < (uint)piVar3[1]);
    }
  }
  return 0;
}

