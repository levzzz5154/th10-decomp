/* Raw Ghidra reference; not compilable reconstruction. Address: 0041D170 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __fastcall FUN_0041d170(int param_1)

{
  float *pfVar1;
  float fVar2;
  int iVar3;
  ulonglong uVar4;
  float local_4;
  
  if (*(int *)(param_1 + 0xf8) < *(int *)(param_1 + 0x11c)) {
    local_4 = *(float *)(param_1 + 0x48) -
              (*(float *)(param_1 + 0x48) * *(float *)(param_1 + 0xfc)) /
              (float)*(int *)(param_1 + 0x11c);
  }
  else {
    if (-1 < *(int *)(param_1 + 0x40c)) {
      FUN_0043dc90(&DAT_00492590,0);
    }
    iVar3 = *(int *)(param_1 + 0x124) + 1;
    *(int *)(param_1 + 0x124) = iVar3;
    if (*(int *)(param_1 + 0x120) <= iVar3) {
      *(uint *)(param_1 + 0x404) = *(uint *)(param_1 + 0x404) & 0xffffffbf;
    }
    *(float *)(param_1 + 0x3c) = *(float *)(param_1 + 0x10c) + *(float *)(param_1 + 0x3c);
    local_4 = *(float *)(param_1 + 0x108);
    *(float *)(param_1 + 0x48) = local_4;
    if ((*(uint *)(param_1 + 0x104) & 1) == 0) {
      *(undefined4 *)(param_1 + 0xf8) = 0;
      *(undefined4 *)(param_1 + 0xf4) = 0xfff0bdc1;
      *(undefined4 *)(param_1 + 0xfc) = 0;
      *(undefined4 **)(param_1 + 0x100) = &DAT_00476f78;
      *(uint *)(param_1 + 0x104) = *(uint *)(param_1 + 0x104) | 1;
    }
    *(undefined4 *)(param_1 + 0xf8) = 0;
    *(undefined4 *)(param_1 + 0xfc) = 0;
    *(undefined4 *)(param_1 + 0xf4) = 0xffffffff;
  }
  FUN_0041f800((void *)(param_1 + 0x30),*(float *)(param_1 + 0x3c),local_4);
  pfVar1 = *(float **)(param_1 + 0x100);
  *(int *)(param_1 + 0xf4) = *(int *)(param_1 + 0xf8);
  if ((_DAT_00470b68 < *pfVar1) && (*pfVar1 < _DAT_00470b64)) {
    fVar2 = *(float *)(param_1 + 0xfc) + _DAT_00470afc;
    *(int *)(param_1 + 0xf8) = *(int *)(param_1 + 0xf8) + 1;
    *(float *)(param_1 + 0xfc) = fVar2;
    return;
  }
  *(float *)(param_1 + 0xfc) = *pfVar1 + *(float *)(param_1 + 0xfc);
  uVar4 = FUN_00463b2c();
  *(int *)(param_1 + 0xf8) = (int)uVar4;
  return;
}

