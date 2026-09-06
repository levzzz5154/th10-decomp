/* Raw Ghidra reference; not compilable reconstruction. Address: 00406D90 */

/* WARNING (jumptable): Unable to track spacebase fully for stack */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __fastcall FUN_00406d90(int param_1)

{
  float *pfVar1;
  uint uVar2;
  float fVar3;
  int iVar4;
  int iVar5;
  undefined4 *puVar6;
  undefined4 *puVar7;
  float10 fVar8;
  undefined4 local_218;
  undefined4 local_214;
  undefined4 local_210;
  undefined4 local_20c;
  float local_208;
  float local_204;
  float local_200;
  float local_1fc;
  undefined4 local_1f8 [117];
  undefined2 local_24;
  undefined2 local_22;
  undefined2 local_20;
  float local_1c;
  undefined4 local_14;
  uint local_10;
  
  iVar5 = *(int *)(param_1 + 0x45c);
  do {
    if (0x11 < iVar5) {
      return;
    }
    iVar5 = *(int *)(param_1 + 0x45c);
    uVar2 = *(uint *)(param_1 + 0x474 + iVar5 * 0x18);
    pfVar1 = (float *)(param_1 + 0x464 + iVar5 * 0x18);
    if (uVar2 == 0) {
      return;
    }
    if ((pfVar1[5] == 0.0) && (*(int *)(param_1 + 0x43c) != 0)) {
      return;
    }
    if (uVar2 == 0x80000000) {
      *(int *)(param_1 + 0x45c) = iVar5 + 1;
    }
    else {
      if (uVar2 < 0x4001) {
        if (uVar2 == 0x4000) {
          FUN_00404f30(DAT_004776f0,*(undefined2 **)((int)DAT_004776f0 + 0x3e0b50));
        }
        else if (uVar2 < 0x101) {
          if (uVar2 == 0x100) {
switchD_00406e2b_caseD_40:
            *(uint *)(param_1 + 0x43c) = *(uint *)(param_1 + 0x43c) | uVar2;
            if (*pfVar1 < _DAT_00470b50 == (*pfVar1 == _DAT_00470b50)) {
              if (*pfVar1 < _DAT_00470ccc) {
                fVar8 = (float10)*pfVar1;
              }
              else {
                fVar8 = FUN_00426660(DAT_00477834);
              }
            }
            else {
              fVar8 = (float10)*(float *)(param_1 + 0x3e4);
            }
            *(float *)(param_1 + 0x6c8) = (float)fVar8;
            if (pfVar1[1] <= _DAT_00470cc8) {
              fVar3 = *(float *)(param_1 + 0x3d8);
            }
            else {
              fVar3 = pfVar1[1];
            }
            *(float *)(param_1 + 0x6c4) = fVar3;
            if ((*(uint *)(param_1 + 0x6c0) & 1) == 0) {
              *(undefined4 *)(param_1 + 0x6b4) = 0;
              *(undefined4 *)(param_1 + 0x6b0) = 0xfff0bdc1;
              *(undefined4 *)(param_1 + 0x6b8) = 0;
              *(undefined4 **)(param_1 + 0x6bc) = &DAT_00476f78;
              *(uint *)(param_1 + 0x6c0) = *(uint *)(param_1 + 0x6c0) | 1;
            }
            *(undefined4 *)(param_1 + 0x6b4) = 0;
            *(undefined4 *)(param_1 + 0x6b8) = 0;
            *(undefined4 *)(param_1 + 0x6b0) = 0xffffffff;
            *(float *)(param_1 + 0x6d8) = pfVar1[2];
            *(float *)(param_1 + 0x6dc) = pfVar1[3];
            *(undefined4 *)(param_1 + 0x6e0) = 0;
          }
          else {
            switch(uVar2) {
            case 1:
              *(uint *)(param_1 + 0x43c) = *(uint *)(param_1 + 0x43c) | 1;
              FUN_00405410(0);
              *(undefined4 *)(param_1 + 0x638) = 0;
              break;
            case 0x10:
              *(uint *)(param_1 + 0x43c) = *(uint *)(param_1 + 0x43c) | 0x10;
              *(float *)(param_1 + 0x65c) = *pfVar1;
              if (pfVar1[1] < _DAT_00470b50 == (pfVar1[1] == _DAT_00470b50)) {
                if (pfVar1[1] < _DAT_00470ccc) {
                  fVar8 = (float10)pfVar1[1];
                }
                else {
                  fVar8 = FUN_00426660(DAT_00477834);
                }
              }
              else {
                fVar8 = (float10)*(float *)(param_1 + 0x3e4);
              }
              *(float *)(param_1 + 0x660) = (float)fVar8;
              FUN_00405410(0);
              *(float *)(param_1 + 0x670) = pfVar1[2];
              FUN_00408750((void *)(param_1 + 0x664),*(float *)(param_1 + 0x660),
                           *(float *)(param_1 + 0x65c));
              if ((*(int *)(param_1 + 0x45c) != 0) && (-1 < *(int *)(param_1 + 0x458))) {
                FUN_0043dc90(&DAT_00492590,0);
              }
              break;
            case 0x20:
              *(uint *)(param_1 + 0x43c) = *(uint *)(param_1 + 0x43c) | 0x20;
              *(float *)(param_1 + 0x690) = *pfVar1;
              *(float *)(param_1 + 0x694) = pfVar1[1];
              FUN_00405410(0);
              *(float *)(param_1 + 0x6a4) = pfVar1[2];
              if ((*(int *)(param_1 + 0x45c) != 0) && (-1 < *(int *)(param_1 + 0x458))) {
                FUN_0043dc90(&DAT_00492590,0);
              }
              break;
            case 0x40:
            case 0x80:
              goto switchD_00406e2b_caseD_40;
            }
          }
        }
        else if (uVar2 < 0x1001) {
          if (uVar2 == 0x1000) {
            *(float *)(param_1 + 4) = pfVar1[2];
          }
          else if ((uVar2 == 0x400) || (uVar2 == 0x800)) goto LAB_004072ff;
        }
        else if (uVar2 == 0x2000) {
          *(float *)(param_1 + 0x434) = pfVar1[2];
          *(int *)(param_1 + 0x45c) = iVar5 + 1;
          goto LAB_00407329;
        }
switchD_00406e2b_caseD_2:
        fVar3 = (float)(*(int *)(param_1 + 0x45c) + 1);
      }
      else {
        if (uVar2 < 0x400001) {
          if (uVar2 == 0x400000) {
            puVar6 = &local_218;
            for (iVar4 = 0x84; iVar4 != 0; iVar4 = iVar4 + -1) {
              *puVar6 = 0;
              puVar6 = puVar6 + 1;
            }
            local_214 = *(undefined4 *)(param_1 + 0x3b4);
            local_210 = *(undefined4 *)(param_1 + 0x3b8);
            local_20c = *(undefined4 *)(param_1 + 0x3bc);
            fVar3 = pfVar1[2];
            local_20 = 0;
            local_218._0_2_ = 0;
            local_218._2_2_ = (short)*(char *)((int)pfVar1 + 9);
            local_10 = (uint)fVar3 & 0xff;
            local_24 = *(undefined2 *)(pfVar1 + 3);
            local_200 = *pfVar1;
            local_1fc = pfVar1[1];
            *(int *)(param_1 + 0x45c) = iVar5 + 1;
            local_22 = *(undefined2 *)(pfVar1 + 8);
            local_1c = pfVar1[9];
            local_204 = pfVar1[7];
            local_208 = pfVar1[6];
            local_14 = 0xffffffff;
            puVar6 = (undefined4 *)(param_1 + 0x464);
            puVar7 = local_1f8;
            for (iVar5 = 0x6c; iVar5 != 0; iVar5 = iVar5 + -1) {
              *puVar7 = *puVar6;
              puVar6 = puVar6 + 1;
              puVar7 = puVar7 + 1;
            }
            FUN_004073e0(0,(int)DAT_004776f0,(uint)DAT_004776f0);
            *(int *)(param_1 + 0x45c) = *(int *)(param_1 + 0x45c) + 1;
            if (((uint)fVar3 & 0x80000000) == 0) goto LAB_00407329;
            FUN_00408030();
          }
          else if (uVar2 < 0x20001) {
            if (uVar2 == 0x20000) {
              FUN_0043dd10();
            }
            else if (uVar2 == 0x8000) {
              *(uint *)(param_1 + 0x43c) = *(uint *)(param_1 + 0x43c) | 0x8000;
              FUN_00405410((int)pfVar1[2]);
            }
            else if (uVar2 == 0x10000) {
              FUN_00408030();
            }
          }
          else if (uVar2 == 0x100000) {
            *(uint *)(param_1 + 0x43c) = *(uint *)(param_1 + 0x43c) | 0x100000;
            FUN_00405410((int)pfVar1[2]);
          }
          else if (uVar2 == 0x200000) {
            *(uint *)(param_1 + 0x43c) = *(uint *)(param_1 + 0x43c) | 0x200000;
            FUN_00405410((int)pfVar1[2]);
          }
          goto switchD_00406e2b_caseD_2;
        }
        if (0x4000000 < uVar2) {
          if (uVar2 == 0x8000000) {
LAB_004072ff:
            *(uint *)(param_1 + 0x43c) = *(uint *)(param_1 + 0x43c) | uVar2;
            *(float *)(param_1 + 0x6f8) = *pfVar1;
            *(float *)(param_1 + 0x710) = pfVar1[2];
            *(undefined4 *)(param_1 + 0x70c) = 0;
          }
          goto switchD_00406e2b_caseD_2;
        }
        if (uVar2 == 0x4000000) {
          *(uint *)(param_1 + 0x43c) = *(uint *)(param_1 + 0x43c) | 0x4000000;
          *(float *)(param_1 + 0x7c8) = *pfVar1;
          *(float *)(param_1 + 0x7cc) = pfVar1[1];
          if ((*(uint *)(param_1 + 0x7c4) & 1) == 0) {
            *(undefined4 *)(param_1 + 0x7b8) = 0;
            *(undefined4 *)(param_1 + 0x7b4) = 0xfff0bdc1;
            *(undefined4 *)(param_1 + 0x7bc) = 0;
            *(undefined4 **)(param_1 + 0x7c0) = &DAT_00476f78;
            *(uint *)(param_1 + 0x7c4) = *(uint *)(param_1 + 0x7c4) | 1;
          }
          *(undefined4 *)(param_1 + 0x7b8) = 0;
          *(undefined4 *)(param_1 + 0x7bc) = 0;
          *(undefined4 *)(param_1 + 0x7b4) = 0xffffffff;
          *(float *)(param_1 + 0x7dc) = pfVar1[2];
          goto switchD_00406e2b_caseD_2;
        }
        if (uVar2 == 0x1000000) {
          *(float *)(param_1 + 0x420) = pfVar1[2];
          *(int *)(param_1 + 0x45c) = iVar5 + 1;
          goto LAB_00407329;
        }
        if (uVar2 != 0x2000000) goto switchD_00406e2b_caseD_2;
        fVar3 = pfVar1[2];
      }
      *(float *)(param_1 + 0x45c) = fVar3;
    }
LAB_00407329:
    iVar5 = *(int *)(param_1 + 0x45c);
  } while( true );
}

