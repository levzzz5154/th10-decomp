/* Raw Ghidra reference; not compilable reconstruction. Address: 0044C350 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

float10 FUN_0044c350(float param_1,float param_2)

{
  undefined4 in_EAX;
  float10 fVar1;
  float10 fVar2;
  
  fVar1 = (float10)param_1 / (float10)param_2;
  switch(in_EAX) {
  case 1:
    return fVar1 * fVar1;
  case 2:
    return fVar1 * fVar1 * fVar1;
  case 3:
    return fVar1 * fVar1 * fVar1 * fVar1;
  case 4:
    return (float10)_DAT_00470afc -
           ((float10)_DAT_00470afc - fVar1) * ((float10)_DAT_00470afc - fVar1);
  case 5:
    fVar1 = (float10)_DAT_00470afc - fVar1;
    return (float10)_DAT_00470afc - fVar1 * fVar1 * fVar1;
  case 6:
    fVar1 = (float10)_DAT_00470afc - fVar1;
    return (float10)_DAT_00470afc - fVar1 * fVar1 * fVar1 * fVar1;
  default:
    return fVar1;
  case 9:
    fVar1 = fVar1 + fVar1;
    if ((float10)_DAT_00470afc <= fVar1) {
      return ((float10)_DAT_00470b08 -
             ((float10)_DAT_00470b08 - fVar1) * ((float10)_DAT_00470b08 - fVar1)) *
             (float10)_DAT_00470b0c;
    }
    return fVar1 * fVar1 * (float10)_DAT_00470b0c;
  case 10:
    fVar1 = fVar1 + fVar1;
    if (fVar1 < (float10)_DAT_00470afc) {
      return fVar1 * fVar1 * fVar1 * (float10)_DAT_00470b0c;
    }
    fVar1 = (float10)_DAT_00470b08 - fVar1;
    fVar2 = fVar1 * fVar1;
    break;
  case 0xb:
    fVar1 = fVar1 + fVar1;
    if (fVar1 < (float10)_DAT_00470afc) {
      return fVar1 * fVar1 * fVar1 * fVar1 * (float10)_DAT_00470b0c;
    }
    fVar1 = (float10)_DAT_00470b08 - fVar1;
    fVar2 = fVar1 * fVar1 * fVar1;
    break;
  case 0xc:
    fVar1 = fVar1 + fVar1;
    if ((float10)_DAT_00470afc <= fVar1) {
      return (fVar1 - (float10)_DAT_00470afc) * (fVar1 - (float10)_DAT_00470afc) *
             (float10)_DAT_00470b0c + (float10)_DAT_00470b0c;
    }
    return (float10)_DAT_00470b0c -
           ((float10)_DAT_00470afc - fVar1) * ((float10)_DAT_00470afc - fVar1) *
           (float10)_DAT_00470b0c;
  case 0xd:
    fVar1 = fVar1 + fVar1;
    if ((float10)_DAT_00470afc <= fVar1) {
      fVar1 = fVar1 - (float10)_DAT_00470afc;
      fVar2 = fVar1 * fVar1;
LAB_0044c522:
      return fVar2 * fVar1 * (float10)_DAT_00470b0c + (float10)_DAT_00470b0c;
    }
    fVar1 = (float10)_DAT_00470afc - fVar1;
    fVar2 = fVar1 * fVar1;
    goto LAB_0044c4ff;
  case 0xe:
    fVar1 = fVar1 + fVar1;
    if ((float10)_DAT_00470afc <= fVar1) {
      fVar1 = fVar1 - (float10)_DAT_00470afc;
      fVar2 = fVar1 * fVar1 * fVar1;
      goto LAB_0044c522;
    }
    fVar1 = (float10)_DAT_00470afc - fVar1;
    fVar2 = fVar1 * fVar1 * fVar1;
LAB_0044c4ff:
    return (float10)_DAT_00470b0c - fVar2 * fVar1 * (float10)_DAT_00470b0c;
  case 0xf:
    return (float10)_DAT_00470b04;
  case 0x10:
    return (float10)_DAT_00470afc;
  }
  return ((float10)_DAT_00470b08 - fVar2 * fVar1) * (float10)_DAT_00470b0c;
}

