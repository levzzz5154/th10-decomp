/* Raw Ghidra reference; not compilable reconstruction. Address: 0043D390 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

undefined4 __fastcall FUN_0043d390(int param_1,undefined4 *param_2,undefined4 param_3)

{
  undefined4 *puVar1;
  int *piVar2;
  int iVar3;
  char *pcVar4;
  uint uVar5;
  char *pcVar6;
  char *pcVar7;
  char *pcStack_5c;
  undefined4 local_58;
  uint uStack_54;
  uint uStack_50;
  char *pcStack_4c;
  char *pcStack_48;
  undefined4 *local_44;
  undefined4 uStack_40;
  undefined4 uStack_3c;
  undefined4 uStack_38;
  undefined4 uStack_34;
  undefined4 uStack_30;
  undefined2 uStack_2c;
  undefined4 uStack_28;
  undefined4 uStack_24;
  undefined4 uStack_20;
  undefined4 uStack_1c;
  undefined4 *puStack_18;
  undefined4 uStack_14;
  undefined4 uStack_10;
  undefined4 uStack_c;
  undefined4 uStack_8;
  uint local_4;
  
  local_4 = DAT_00473660 ^ (uint)&pcStack_5c;
  local_58 = param_3;
  if (param_2[0x184] == 0) {
    return 0;
  }
  piVar2 = (int *)param_2[param_1 + 2];
  puVar1 = param_2 + param_1 + 2;
  local_44 = puVar1;
  if (piVar2 != (int *)0x0) {
    (**(code **)(*piVar2 + 8))(piVar2);
    *puVar1 = 0;
  }
  iVar3 = param_2[param_1 + 0x148c];
  while (iVar3 == 0) {
    Sleep(10);
    if (DAT_004977b4 == 2) {
      return 0;
    }
    iVar3 = param_2[param_1 + 0x148c];
  }
  pcVar4 = (char *)param_2[param_1 + 0x148c];
  param_2[param_1 + 0x148c] = 0;
  if (pcVar4 == (char *)0x0) {
    return 0xffffffff;
  }
  pcStack_5c = pcVar4;
  iVar3 = _strncmp(pcVar4,"RIFF",4);
  if (iVar3 == 0) {
    iVar3 = _strncmp(pcVar4 + 8,"WAVE",4);
    if (iVar3 == 0) {
      pcVar7 = FUN_0043d250(pcVar4 + 0xc,"fmt ");
      if (pcVar7 != (char *)0x0) {
        uStack_3c = *(undefined4 *)pcVar7;
        uStack_38 = *(undefined4 *)(pcVar7 + 4);
        uStack_34 = *(undefined4 *)(pcVar7 + 8);
        uStack_30 = *(undefined4 *)(pcVar7 + 0xc);
        uStack_2c = *(undefined2 *)(pcVar7 + 0x10);
        pcVar4 = FUN_0043d250(pcVar4 + 0xc,"data");
        puVar1 = local_44;
        if (pcVar4 != (char *)0x0) {
          uStack_1c = 0;
          uStack_14 = 0;
          uStack_10 = 0;
          uStack_c = 0;
          uStack_8 = 0;
          puStack_18 = &uStack_3c;
          uStack_28 = 0x24;
          uStack_24 = 0x80c8;
          uStack_20 = uStack_40;
          iVar3 = (**(code **)(*(int *)*param_2 + 0xc))((int *)*param_2,&uStack_28,local_44,0);
          if (iVar3 < 0) {
            _free(pcStack_5c);
            return 0xffffffff;
          }
          iVar3 = (**(code **)(*(int *)*puVar1 + 0x2c))
                            ((int *)*puVar1,0,uStack_40,&pcStack_48,&uStack_54,&pcStack_4c,
                             &uStack_50,0);
          if (iVar3 < 0) {
            _free(pcStack_5c);
            return 0xffffffff;
          }
          pcVar7 = pcVar4;
          pcVar6 = pcStack_48;
          for (uVar5 = uStack_54 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
            *(undefined4 *)pcVar6 = *(undefined4 *)pcVar7;
            pcVar7 = pcVar7 + 4;
            pcVar6 = pcVar6 + 4;
          }
          for (uVar5 = uStack_54 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
            *pcVar6 = *pcVar7;
            pcVar7 = pcVar7 + 1;
            pcVar6 = pcVar6 + 1;
          }
          if (uStack_50 != 0) {
            pcVar4 = pcVar4 + uStack_54;
            pcVar7 = pcStack_4c;
            for (uVar5 = uStack_50 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
              *(undefined4 *)pcVar7 = *(undefined4 *)pcVar4;
              pcVar4 = pcVar4 + 4;
              pcVar7 = pcVar7 + 4;
            }
            for (uVar5 = uStack_50 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
              *pcVar7 = *pcVar4;
              pcVar4 = pcVar4 + 1;
              pcVar7 = pcVar7 + 1;
            }
          }
          (**(code **)(*(int *)*local_44 + 0x4c))
                    ((int *)*local_44,pcStack_48,uStack_54,pcStack_4c,uStack_50);
          _free(pcStack_5c);
          return 0;
        }
      }
      FUN_0044b810(&DAT_00474f70,&DAT_0046fd64);
      pcVar4 = pcStack_5c;
      goto LAB_0043d45e;
    }
    pcVar7 = &DAT_0046fd64;
  }
  else {
    pcVar7 = &DAT_0046fd88;
  }
  FUN_0044b810(&DAT_00474f70,pcVar7);
LAB_0043d45e:
  _free(pcVar4);
  return 0xffffffff;
}

