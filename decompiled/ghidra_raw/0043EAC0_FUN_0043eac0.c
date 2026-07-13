/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x0043EAC0
 * Tracking name: FUN_0043eac0
 * Ghidra name: FUN_0043eac0
 * Tracked span: 432 bytes
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

float10 FUN_0043eac0(float param_1)

{
  int unaff_ESI;
  float10 fVar1;
  ulonglong uVar2;
  
  uVar2 = FUN_00463b2c();
  switch((int)uVar2) {
  case 10000:
    return (float10)*(int *)(unaff_ESI + 0x30c);
  case 0x2711:
    return (float10)*(int *)(unaff_ESI + 0x310);
  case 0x2712:
    return (float10)*(int *)(unaff_ESI + 0x314);
  case 0x2713:
    return (float10)*(int *)(unaff_ESI + 0x318);
  case 0x2714:
    return (float10)*(float *)(unaff_ESI + 0x31c);
  case 0x2715:
    return (float10)*(float *)(unaff_ESI + 800);
  case 0x2716:
    return (float10)*(float *)(unaff_ESI + 0x324);
  case 0x2717:
    return (float10)*(float *)(unaff_ESI + 0x328);
  case 0x2718:
    return (float10)*(int *)(unaff_ESI + 0x32c);
  case 0x2719:
    return (float10)*(int *)(unaff_ESI + 0x330);
  case 0x271a:
    break;
  case 0x271b:
    if ((*(uint *)(unaff_ESI + 0x35c) & 0x40000000) == 0) {
      fVar1 = FUN_0044bb20(&DAT_004918b0);
      return fVar1;
    }
    fVar1 = FUN_0044bb20((ushort *)&DAT_004918a8);
    return fVar1;
  case 0x271c:
    if ((*(uint *)(unaff_ESI + 0x35c) & 0x40000000) == 0) {
      fVar1 = FUN_0044bb90(&DAT_004918b0);
      return fVar1;
    }
    fVar1 = FUN_0044bb90((ushort *)&DAT_004918a8);
    return fVar1;
  case 0x271d:
    return (float10)*(float *)(unaff_ESI + 0x334);
  case 0x271e:
    return (float10)*(float *)(unaff_ESI + 0x338);
  case 0x271f:
    return (float10)*(float *)(unaff_ESI + 0x33c);
  case 0x2720:
    return (float10)DAT_00491d7c;
  case 0x2721:
    return (float10)DAT_00491d80;
  case 0x2722:
    return (float10)_DAT_00491d84;
  case 0x2723:
    return (float10)_DAT_00491da0;
  case 0x2724:
    return (float10)_DAT_00491da4;
  case 0x2725:
    return (float10)_DAT_00491da8;
  default:
    return (float10)param_1;
  }
  if ((*(uint *)(unaff_ESI + 0x35c) & 0x40000000) == 0) {
    fVar1 = FUN_0044bb90(&DAT_004918b0);
    return fVar1 * (float10)_DAT_00470b18;
  }
  fVar1 = FUN_0044bb90((ushort *)&DAT_004918a8);
  return fVar1 * (float10)_DAT_00470b18;
}

