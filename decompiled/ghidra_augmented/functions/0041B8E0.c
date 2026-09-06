/* Raw Ghidra reference; not compilable reconstruction. Address: 0041B8E0 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_0041b8e0(void)

{
  float fVar1;
  int in_EAX;
  int iVar2;
  float *pfVar3;
  ulonglong uVar4;
  
  pfVar3 = (float *)(in_EAX + 0x34c);
  iVar2 = 0x896;
  do {
    if (pfVar3[0x29] != 0.0) {
      pfVar3[-1] = pfVar3[0x1d] + _DAT_00470b4c;
      *pfVar3 = pfVar3[0x1e] + _DAT_00470b48;
      pfVar3[1] = pfVar3[0x1f];
      if (_DAT_00470bd0 <= *pfVar3) {
        if ((int)*(short *)(pfVar3 + 0x13) != (int)pfVar3[0x2b] + 0x158) {
          FUN_0043e5a0(*(int *)(DAT_004776f0 + 0x3e0b50),(int)pfVar3[0x2b] + 0x157);
          *(undefined1 *)((int)pfVar3 + -0x39) = 0xff;
        }
      }
      else {
        fVar1 = *pfVar3;
        *pfVar3 = 24.0;
        if (fVar1 - _DAT_00470bd0 < _DAT_00470bcc) {
          uVar4 = FUN_00463b2c();
          *(char *)((int)pfVar3 + -0x39) = (char)uVar4;
        }
        else {
          *(undefined1 *)((int)pfVar3 + -0x39) = 0xff;
        }
        if ((int)*(short *)(pfVar3 + 0x13) != (int)pfVar3[0x2b] + 0x161) {
          FUN_0043e5a0(*(int *)(DAT_004776f0 + 0x3e0b50),(int)pfVar3[0x2b] + 0x160);
        }
      }
      FUN_004451c0(g_pGameStateManager);
    }
    pfVar3 = pfVar3 + 0xfc;
    iVar2 = iVar2 + -1;
  } while (iVar2 != 0);
  return 1;
}

