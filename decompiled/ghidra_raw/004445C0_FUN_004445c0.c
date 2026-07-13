/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x004445C0
 * Tracking name: FUN_004445c0
 * Ghidra name: FUN_004445c0
 * Tracked span: 416 bytes
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_004445c0(void *param_1,int param_2)

{
  float fVar1;
  float fVar2;
  undefined4 uVar3;
  int iVar4;
  undefined1 *puVar5;
  float *pfVar6;
  ulonglong uVar7;
  undefined1 uStack_49;
  float local_40 [16];
  
  FUN_00444240();
  fVar1 = _DAT_00491e78 - _DAT_00491e7c;
  if ((char)((uint)*(undefined4 *)(param_2 + 0x35c) >> 8) < '\0') {
    uVar3 = *(undefined4 *)(param_2 + 0x300);
  }
  else {
    uVar3 = *(undefined4 *)(param_2 + 0x2fc);
  }
  puVar5 = (undefined1 *)((int)&DAT_004978d0 + 3);
  pfVar6 = local_40;
  iVar4 = (int)param_1 + 0x3ada78;
  do {
    D3DXVec3Transform(pfVar6,iVar4,(int)param_1 + 0x3ad0f0);
    fVar2 = SQRT((*pfVar6 - DAT_00491d7c) * (*pfVar6 - DAT_00491d7c) +
                 (pfVar6[1] - DAT_00491d80) * (pfVar6[1] - DAT_00491d80) +
                 (pfVar6[2] - _DAT_00491d84) * (pfVar6[2] - _DAT_00491d84));
    if (fVar2 <= _DAT_00491e78) {
      *(undefined4 *)(puVar5 + -3) = uVar3;
    }
    else {
      uStack_49 = (undefined1)((uint)uVar3 >> 0x18);
      if ((_DAT_00491e78 - fVar2) / fVar1 < _DAT_00470afc) {
        uVar7 = FUN_00463b2c();
        puVar5[-3] = (char)uVar3 - (char)uVar7;
        uVar7 = FUN_00463b2c();
        puVar5[-2] = (char)((uint)uVar3 >> 8) - (char)uVar7;
        uVar7 = FUN_00463b2c();
        puVar5[-1] = (char)((uint)uVar3 >> 0x10) - (char)uVar7;
        *puVar5 = uStack_49;
      }
      else {
        *(undefined4 *)(puVar5 + -3) = DAT_00491e90;
        *puVar5 = uStack_49;
      }
    }
    puVar5 = puVar5 + 0x1c;
    iVar4 = iVar4 + 0x14;
    pfVar6 = pfVar6 + 4;
  } while ((int)puVar5 < 0x497943);
  FUN_00442670(param_1,2);
  _DAT_00497920 = 0x3f800000;
  _DAT_00497904 = 0x3f800000;
  _DAT_004978e8 = 0x3f800000;
  _DAT_004978cc = 0x3f800000;
  return;
}

