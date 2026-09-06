/* Raw Ghidra reference; not compilable reconstruction. Address: 00403A30 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_00403a30(int param_1)

{
  float fVar1;
  float fVar2;
  short sVar3;
  int iVar4;
  short *psVar5;
  short *psVar6;
  int iVar7;
  int unaff_retaddr;
  int iStack_4;
  
  psVar5 = *(short **)(param_1 + 0x18);
  DAT_00491fac = &DAT_00491d7c;
  FUN_004215a0();
  (**(code **)(*(int *)g_pD3DDevice + 0xbc))(g_pD3DDevice,DAT_00491fac + 0x33);
  _DAT_00491fb0 = 0;
  *(undefined1 *)((int)g_pGameStateManager + 0x3ada6c) = 1;
  sVar3 = *psVar5;
  while (-1 < sVar3) {
    iVar7 = *(int *)(*(int *)(param_1 + 0x14) + sVar3 * 4);
    if (*(char *)(iVar7 + 2) == unaff_retaddr) {
      iVar4 = FUN_00403090(iVar7,(float *)&stack0xffffffec,*(float *)(param_1 + 0x1ee0));
      if (iVar4 == 0) {
        psVar6 = (short *)(iVar7 + 0x1c);
        *(byte *)(iVar7 + 3) = *(byte *)(iVar7 + 3) | 2;
        sVar3 = *psVar6;
        while (-1 < sVar3) {
          iVar7 = psVar6[3] * 0x3ac + *(int *)(iStack_4 + 0x17c);
          if (sVar3 == 0) {
            if (0xffffff < (*(uint *)(iVar7 + 0x35c) & 0x3c00000)) {
              *(float *)(iVar7 + 0x340) = *(float *)(psVar6 + 4) + *(float *)(psVar5 + 2);
              *(float *)(iVar7 + 0x344) = *(float *)(psVar6 + 6) + *(float *)(psVar5 + 4);
              *(float *)(iVar7 + 0x348) = *(float *)(psVar6 + 8) + *(float *)(psVar5 + 6);
              if (*(float *)(psVar6 + 10) != _DAT_00470b04) {
                fVar1 = *(float *)(psVar6 + 10);
                fVar2 = *(float *)(*(int *)(iVar7 + 0x394) + 0x34);
                *(uint *)(iVar7 + 0x35c) = *(uint *)(iVar7 + 0x35c) | 8;
                *(float *)(iVar7 + 0x3c) = fVar1 / fVar2;
              }
              if (*(float *)(psVar6 + 0xc) != _DAT_00470b04) {
                fVar1 = *(float *)(psVar6 + 0xc);
                fVar2 = *(float *)(*(int *)(iVar7 + 0x394) + 0x30);
                *(uint *)(iVar7 + 0x35c) = *(uint *)(iVar7 + 0x35c) | 8;
                *(float *)(iVar7 + 0x40) = fVar1 / fVar2;
              }
            }
            if ((*(uint *)(iVar7 + 0x35c) & 0x3c00000) == 0x2000000) {
              if (DAT_00492378 != 1) {
                FUN_00442f50();
                DAT_00492378 = 1;
                (**(code **)(*(int *)g_pD3DDevice + 0xe4))(g_pD3DDevice,0x1c,1);
              }
            }
            else if (DAT_00492378 != 0) {
              FUN_00442f50();
              DAT_00492378 = 0;
              (**(code **)(*(int *)g_pD3DDevice + 0xe4))(g_pD3DDevice,0x1c,0);
            }
            FUN_004451c0(g_pGameStateManager);
            *(int *)(iStack_4 + 0x2a14) = *(int *)(iStack_4 + 0x2a14) + 1;
          }
          psVar6 = (short *)((int)psVar6 + (int)psVar6[1]);
          sVar3 = *psVar6;
        }
        *(int *)(iStack_4 + 0x2a0c) = *(int *)(iStack_4 + 0x2a0c) + 1;
        param_1 = iStack_4;
      }
      else {
        *(int *)(param_1 + 0x2a10) = *(int *)(param_1 + 0x2a10) + 1;
      }
    }
    psVar6 = psVar5 + 8;
    psVar5 = psVar5 + 8;
    sVar3 = *psVar6;
  }
  return 0;
}

