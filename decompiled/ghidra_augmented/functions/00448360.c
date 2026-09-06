/* Raw Ghidra reference; not compilable reconstruction. Address: 00448360 */

void __fastcall FUN_00448360(int param_1,int param_2,int param_3,int param_4)

{
  int in_EAX;
  int iVar1;
  int *unaff_EBX;
  undefined4 unaff_EBP;
  undefined4 unaff_ESI;
  int *piVar2;
  int *piVar3;
  
  iVar1 = param_3;
  if ((*(int *)(in_EAX * 0x10 + *(int *)(*(int *)(param_2 + 0x3ad06c + param_3 * 4) + 0x120)) != 0)
     && (*(int *)(param_1 * 0x10 + *(int *)(*(int *)(param_2 + 0x3ad06c + param_4 * 4) + 0x120)) !=
         0)) {
    FUN_00442f50();
    piVar2 = *(int **)(in_EAX * 0x10 + *(int *)(*(int *)(param_2 + 0x3ad06c + iVar1 * 4) + 0x120));
    piVar3 = (int *)0x0;
    iVar1 = (**(code **)(*piVar2 + 0x48))(piVar2,0,&param_3);
    if (iVar1 == 0) {
      piVar2 = *(int **)(param_1 * 0x10 +
                        *(int *)(*(int *)(param_2 + 0x3ad06c + param_1 * 4) + 0x120));
      iVar1 = (**(code **)(*piVar2 + 0x48))(piVar2,0,&stack0xfffffff0);
      if (iVar1 != 0) {
        (**(code **)(*unaff_EBX + 8))(unaff_EBX);
        return;
      }
      piVar2 = (int *)0xffffffff;
      D3DXLoadSurfaceFromSurface(unaff_EBX,0,unaff_ESI,piVar3,0,unaff_EBP,0xffffffff,0);
      (**(code **)(*piVar2 + 8))(piVar2);
      (**(code **)(*piVar3 + 8))(piVar3);
    }
  }
  return;
}

