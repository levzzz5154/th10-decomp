/* Raw Ghidra reference; not compilable reconstruction. Address: 0041CFD0 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __fastcall FUN_0041cfd0(int param_1)

{
  float fVar1;
  bool bVar2;
  float10 fVar3;
  float local_c;
  float local_8;
  undefined4 local_4;
  
  FUN_0041f800(&local_c,*(float *)(param_1 + 0x3c),*(float *)(param_1 + 0x40));
  local_c = local_c + *(float *)(param_1 + 0x24);
  local_4 = 0;
  local_8 = local_8 + *(float *)(param_1 + 0x28);
  if ((((local_c < _DAT_00470b40 != (local_c == _DAT_00470b40)) || (_DAT_00470b3c <= local_c)) ||
      (local_8 < _DAT_00470b04 != (local_8 == _DAT_00470b04))) || (_DAT_00470b38 <= local_8)) {
    bVar2 = false;
    if (-1 < *(int *)(param_1 + 0x40c)) {
      FUN_0043dc90(&DAT_00492590,0);
    }
    if ((local_c < _DAT_00470b40) || (_DAT_00470b3c <= local_c)) {
      fVar1 = -*(float *)(param_1 + 0x3c) - _DAT_00470b18;
      *(float *)(param_1 + 0x424) = local_c;
      *(float *)(param_1 + 0x428) = local_8;
      *(undefined4 *)(param_1 + 0x42c) = local_4;
      fVar3 = (float10)NormalizeAngle(fVar1);
      *(float *)(param_1 + 0x430) = (float)fVar3;
      *(undefined4 *)(param_1 + 0x444) = *(undefined4 *)(param_1 + 0x13c);
      bVar2 = true;
      FUN_0041c510(0);
    }
    if (((*(uint *)(param_1 + 0x404) & 0x8000000) != 0) ||
       ((_DAT_00470b04 <= local_8 &&
        ((local_8 < _DAT_00470b38 || ((*(uint *)(param_1 + 0x404) & 0x400) == 0)))))) {
      if (!bVar2) {
        return;
      }
    }
    else {
      *(float *)(param_1 + 0x430) = -*(float *)(param_1 + 0x3c);
      *(float *)(param_1 + 0x424) = local_c;
      *(float *)(param_1 + 0x428) = local_8;
      *(undefined4 *)(param_1 + 0x42c) = local_4;
      *(undefined4 *)(param_1 + 0x444) = *(undefined4 *)(param_1 + 0x13c);
      FUN_0041c510(0);
    }
    *(uint *)(param_1 + 0x404) = *(uint *)(param_1 + 0x404) & 0xf7fff3ff;
  }
  return;
}

