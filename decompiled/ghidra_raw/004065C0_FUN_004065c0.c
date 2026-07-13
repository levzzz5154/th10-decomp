/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x004065C0
 * Tracking name: FUN_004065c0
 * Ghidra name: FUN_004065c0
 * Tracked span: 288 bytes
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 __fastcall FUN_004065c0(float *param_1,float param_2)

{
  float fVar1;
  int iVar2;
  float *extraout_ECX;
  float *extraout_ECX_00;
  float extraout_EDX;
  uint *puVar3;
  int unaff_ESI;
  float *pfVar4;
  ulonglong uVar5;
  int local_4;
  
  puVar3 = (uint *)(unaff_ESI + 0x60);
  *(undefined4 *)(unaff_ESI + 0x5c) = 0;
  *(undefined4 *)(unaff_ESI + 0x28) = 0;
  *(undefined4 *)(unaff_ESI + 0x24) = 0;
  *(undefined4 *)(unaff_ESI + 0x20) = 0;
  *(undefined4 *)(unaff_ESI + 0x1c) = 0;
  *(undefined4 *)(unaff_ESI + 0x18) = 0;
  *(undefined4 *)(unaff_ESI + 0x14) = 0;
  *(undefined4 *)(unaff_ESI + 0x40) = 0;
  *(undefined4 *)(unaff_ESI + 0x3c) = 0;
  *(undefined4 *)(unaff_ESI + 0x38) = 0;
  *(undefined4 *)(unaff_ESI + 0x34) = 0;
  *(undefined4 *)(unaff_ESI + 0x30) = 0;
  *(undefined4 *)(unaff_ESI + 0x2c) = 0;
  pfVar4 = (float *)(unaff_ESI + 0x460);
  local_4 = 2000;
  do {
    if (*(short *)((int)pfVar4 + 0x46) != 0) {
      if (((DAT_00477810 == 0) || ((*(uint *)(DAT_00477810 + 0x58) & 2) == 0)) ||
         ((*(uint *)(DAT_00477810 + 0x58) & 0x400) == 0)) {
        iVar2 = FUN_00406240((uint)param_1,(uint)param_2,puVar3);
        param_1 = extraout_ECX;
        param_2 = extraout_EDX;
        if (iVar2 != 0) goto LAB_00406694;
      }
      fVar1 = pfVar4[0x18];
      if (*(int *)(unaff_ESI + 0x14 + (int)fVar1 * 4) == 0) {
        *(uint **)(unaff_ESI + 0x14 + (int)fVar1 * 4) = puVar3;
      }
      else {
        *(uint **)(*(int *)(unaff_ESI + 0x2c + (int)fVar1 * 4) + 0x44c) = puVar3;
      }
      *(uint **)(unaff_ESI + 0x2c + (int)pfVar4[0x18] * 4) = puVar3;
      pfVar4[0x13] = 0.0;
      *(int *)(unaff_ESI + 0x5c) = *(int *)(unaff_ESI + 0x5c) + 1;
      param_1 = (float *)pfVar4[1];
      pfVar4[-2] = pfVar4[-1];
      if ((*param_1 <= _DAT_00470b68) || (_DAT_00470b64 <= *param_1)) {
        *pfVar4 = *pfVar4 + *param_1;
        uVar5 = FUN_00463b2c();
        param_2 = (float)(uVar5 >> 0x20);
        pfVar4[-1] = (float)uVar5;
        param_1 = extraout_ECX_00;
      }
      else {
        param_2 = (float)((int)pfVar4[-1] + 1);
        fVar1 = *pfVar4 + _DAT_00470afc;
        pfVar4[-1] = param_2;
        *pfVar4 = fVar1;
      }
    }
LAB_00406694:
    puVar3 = puVar3 + 0x1fc;
    pfVar4 = pfVar4 + 0x1fc;
    local_4 = local_4 + -1;
    if (local_4 == 0) {
      return 1;
    }
  } while( true );
}

