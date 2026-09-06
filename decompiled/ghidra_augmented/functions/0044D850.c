/* Raw Ghidra reference; not compilable reconstruction. Address: 0044D850 */

/* WARNING: Removing unreachable block (ram,0x0044d958) */
/* WARNING: Removing unreachable block (ram,0x0044d9f0) */
/* WARNING: Removing unreachable block (ram,0x0044da02) */
/* WARNING: Removing unreachable block (ram,0x0044da25) */
/* WARNING: Removing unreachable block (ram,0x0044d964) */
/* WARNING: Removing unreachable block (ram,0x0044d998) */
/* WARNING: Removing unreachable block (ram,0x0044d99a) */
/* WARNING: Removing unreachable block (ram,0x0044d99f) */
/* WARNING: Removing unreachable block (ram,0x0044d9a1) */

uint FUN_0044d850(int param_1)

{
  int *piVar1;
  uint uVar2;
  int iVar3;
  byte bVar4;
  int unaff_EDI;
  uint *puVar5;
  int *piVar6;
  undefined1 *puStack_4c;
  uint *puStack_48;
  undefined1 *puStack_44;
  undefined1 *puVar7;
  uint uStack_1c;
  undefined1 local_10 [8];
  uint local_8 [2];
  
  if ((*(undefined4 **)(param_1 + 4) == (undefined4 *)0x0) || (*(int *)(param_1 + 0xc) == 0)) {
    return 0x800401f0;
  }
  (**(code **)(*(int *)**(undefined4 **)(param_1 + 4) + 0x10))();
  if ((uStack_1c - *(int *)(param_1 + 0x6c) <= *(uint *)(param_1 + 100)) &&
     (*(uint *)(param_1 + 100) < uStack_1c)) {
    return 0x800401f0;
  }
  uVar2 = RunPlatformInterface();
  if (-1 < (int)uVar2) {
    if (unaff_EDI == 0) {
      piVar6 = (int *)**(undefined4 **)(param_1 + 4);
      puVar7 = local_10;
      puStack_44 = &stack0xffffffe0;
      puStack_48 = local_8;
      puStack_4c = &stack0xffffffd8;
      uVar2 = (**(code **)(*piVar6 + 0x2c))
                        (piVar6,*(undefined4 *)(param_1 + 100),*(undefined4 *)(param_1 + 0x6c));
      if (-1 < (int)uVar2) {
        if (puVar7 != (undefined1 *)0x0) {
          return 0x8000ffff;
        }
        if (*(int *)(param_1 + 0x68) == 0) {
          uVar2 = FUN_0044de10(puStack_48,0,puStack_48,(uint *)&puStack_44);
          if ((int)uVar2 < 0) {
            return uVar2;
          }
        }
        else {
          bVar4 = (*(short *)(*(int *)(*(int *)(param_1 + 0xc) + 0x90) + 0x2e) != 8) - 1;
          puVar5 = puStack_48;
          for (iVar3 = 0; iVar3 != 0; iVar3 = iVar3 + -1) {
            *puVar5 = CONCAT22(CONCAT11(bVar4,bVar4),CONCAT11(bVar4,bVar4)) & 0x80808080;
            puVar5 = puVar5 + 1;
          }
          for (iVar3 = 0; iVar3 != 0; iVar3 = iVar3 + -1) {
            *(byte *)puVar5 = bVar4 & 0x80;
            puVar5 = (uint *)((int)puVar5 + 1);
          }
        }
        (**(code **)(*(int *)**(undefined4 **)(param_1 + 4) + 0x4c))
                  ((int *)**(undefined4 **)(param_1 + 4),puStack_48,0,0,0);
        uVar2 = (**(code **)(*(int *)**(undefined4 **)(param_1 + 4) + 0x10))
                          ((int *)**(undefined4 **)(param_1 + 4),&puStack_4c,0);
        if (-1 < (int)uVar2) {
          piVar1 = *(int **)(param_1 + 0x5c);
          if (piVar6 < piVar1) {
            iVar3 = *(int *)(param_1 + 8) - (int)piVar1;
          }
          else {
            iVar3 = -(int)piVar1;
          }
          uVar2 = (int)piVar6 + *(int *)(param_1 + 0x60) + iVar3;
          *(int **)(param_1 + 0x5c) = piVar6;
          *(uint *)(param_1 + 0x60) = uVar2;
          if ((*(int *)(param_1 + 0x68) != 0) &&
             (*(uint *)(*(int *)(param_1 + 0xc) + 0x2c) <= uVar2)) {
            (**(code **)(*(int *)**(undefined4 **)(param_1 + 4) + 0x48))
                      ((int *)**(undefined4 **)(param_1 + 4));
          }
          *(uint *)(param_1 + 100) =
               (uint)(*(int *)(param_1 + 100) + (int)puStack_48) % *(uint *)(param_1 + 8);
          return 0;
        }
      }
    }
    else {
      puStack_44 = (undefined1 *)0x44d8cd;
      uVar2 = FUN_0044d110((int *)**(undefined4 **)(param_1 + 4));
      uVar2 = uVar2 & (-1 < (int)uVar2) - 1;
    }
  }
  return uVar2;
}

