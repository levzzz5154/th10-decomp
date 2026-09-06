/* Raw Ghidra reference; not compilable reconstruction. Address: 0044DF70 */

undefined4 FUN_0044df70(undefined4 *param_1,float *param_2)

{
  char cVar1;
  int iVar2;
  undefined4 uVar3;
  int in_EAX;
  int iVar4;
  uint uVar5;
  int iVar6;
  int iVar7;
  int *piVar8;
  float10 fVar9;
  ulonglong uVar10;
  undefined4 local_c;
  
  piVar8 = param_1 + 1;
  iVar2 = *(int *)(in_EAX + 0x1008);
  iVar7 = *(int *)(*piVar8 + 0x10) + 4 + (int)param_2 * 4;
  local_c = 0;
  iVar4 = iVar2 + 8;
  if (iVar2 == 0) {
    *(undefined4 *)(in_EAX + 8) = 0;
    *(int *)(in_EAX + 0x1008) = *(int *)(in_EAX + 0x1008) + 4;
    iVar4 = 0xc;
  }
  iVar6 = (int)param_2 + 1;
  if (iVar6 < (int)(uint)*(byte *)(*piVar8 + 0xb)) {
    param_2 = (float *)(iVar4 + 8 + in_EAX);
    uVar5 = iVar7 + 4;
    do {
      iVar4 = *piVar8;
      cVar1 = *(char *)(iVar4 + 0x10 + iVar7);
      if ((cVar1 == 'f') || (cVar1 == 'g')) {
        fVar9 = ResolveEclFloatValue((byte)iVar6,*(float *)(iVar4 + 0x10 + (uVar5 & 0xfffffffc)));
        if (*(char *)(*piVar8 + 0x11 + iVar7) == 'f') {
          *param_2 = (float)fVar9;
        }
        else {
          uVar10 = FUN_00463b2c();
          *param_2 = (float)uVar10;
        }
      }
      else {
        uVar3 = *(undefined4 *)(iVar4 + 0x10 + (uVar5 & 0xfffffffc));
        uVar10 = ResolveEclIntValue(uVar3,(int)param_1,(byte)iVar6,uVar3);
        if (*(char *)(*piVar8 + 0x11 + iVar7) == 'f') {
          *param_2 = (float)(int)(float)uVar10;
        }
        else {
          *param_2 = (float)uVar10;
        }
      }
      param_2 = param_2 + 1;
      iVar6 = iVar6 + 1;
      uVar5 = uVar5 + 8;
      iVar7 = iVar7 + 8;
    } while (iVar6 < (int)(uint)*(byte *)(*piVar8 + 0xb));
  }
  if (iVar2 == 0) {
    iVar7 = 0;
    *(undefined4 *)(in_EAX + 0x1008) = 4;
    *(undefined4 *)(in_EAX + 0xc) = 0;
    *(int *)(in_EAX + 0x1008) = *(int *)(in_EAX + 0x1008) + 4;
    iVar4 = *(int *)(in_EAX + 0x1008);
    if (0xfff < iVar4 + 4) goto LAB_0044e12e;
  }
  else {
    iVar4 = *(int *)(in_EAX + 0x1008);
    iVar7 = iVar4 + -4;
    if (-1 < iVar7) {
      *(int *)(in_EAX + 0x1008) = iVar7;
      local_c = *(undefined4 *)(iVar4 + 4 + in_EAX);
    }
    *(int *)(in_EAX + 0x1008) = iVar2;
    *(undefined4 *)(iVar2 + 4 + in_EAX) = local_c;
    if (*(int *)(in_EAX + 0x1008) + 4 < 0x1000) {
      *(undefined4 *)(*(int *)(in_EAX + 0x1008) + 8 + in_EAX) = *param_1;
      *(int *)(in_EAX + 0x1008) = *(int *)(in_EAX + 0x1008) + 4;
    }
    iVar4 = *(int *)(in_EAX + 0x1008);
    if (0xfff < iVar4 + 4) goto LAB_0044e12e;
    iVar7 = *piVar8;
  }
  *(int *)(iVar4 + 8 + in_EAX) = iVar7;
  *(int *)(in_EAX + 0x1008) = *(int *)(in_EAX + 0x1008) + 4;
LAB_0044e12e:
  uVar3 = *(undefined4 *)(param_1[0x405] + 4);
  *(int *)(param_1[0x405] + 4) = in_EAX;
  iVar4 = param_1[0x405];
  iVar7 = FUN_00450470((byte *)(*piVar8 + 0x14));
  *(int *)(*(int *)(iVar4 + 4) + 4) = iVar7;
  **(undefined4 **)(iVar4 + 4) = 0;
  if (*(int *)(*(int *)(iVar4 + 4) + 4) != 0) {
    *(undefined4 *)(param_1[0x405] + 4) = uVar3;
    return 0;
  }
  *piVar8 = 0;
  return 0xffffffff;
}

