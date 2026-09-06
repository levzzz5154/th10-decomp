/* Raw Ghidra reference; not compilable reconstruction. Address: 0042B6F0 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 __fastcall FUN_0042b6f0(undefined4 param_1,float param_2)

{
  float *pfVar1;
  float fVar2;
  int in_EAX;
  float *pfVar3;
  int iVar4;
  ulonglong uVar5;
  
  pfVar3 = (float *)(in_EAX + 1000);
  iVar4 = 0x2d3;
  do {
    if (*(char *)(pfVar3 + 5) != '\0') {
      pfVar3[-5] = pfVar3[-5] - DAT_00476f78 * _DAT_00470b0c;
      pfVar1 = (float *)pfVar3[1];
      pfVar3[-2] = pfVar3[-1];
      if ((*pfVar1 <= _DAT_00470b68) || (_DAT_00470b64 <= *pfVar1)) {
        *pfVar3 = *pfVar3 + *pfVar1;
        uVar5 = FUN_00463b2c();
        param_2 = (float)(uVar5 >> 0x20);
        pfVar3[-1] = (float)uVar5;
      }
      else {
        param_2 = (float)((int)pfVar3[-1] + 1);
        fVar2 = *pfVar3 + _DAT_00470afc;
        pfVar3[-1] = param_2;
        *pfVar3 = fVar2;
      }
      if (0x3c < (int)pfVar3[-1]) {
        *(undefined1 *)(pfVar3 + 5) = 0;
      }
    }
    pfVar3 = pfVar3 + 0x10;
    iVar4 = iVar4 + -1;
  } while (iVar4 != 0);
  return CONCAT44(param_2,1);
}

