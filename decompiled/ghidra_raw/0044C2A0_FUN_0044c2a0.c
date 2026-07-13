/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x0044C2A0
 * Tracking name: FUN_0044c2a0
 * Ghidra name: FUN_0044c2a0
 * Tracked span: 176 bytes
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0044c2a0(void)

{
  float *unaff_ESI;
  float10 fVar1;
  undefined2 uVar2;
  float in_stack_ffffffe8;
  float local_c;
  float local_8;
  undefined4 local_4;
  
  if (((uint)unaff_ESI[10] & 1) == 0) {
    *unaff_ESI = *unaff_ESI + unaff_ESI[3];
    unaff_ESI[1] = unaff_ESI[4] + unaff_ESI[1];
    unaff_ESI[2] = unaff_ESI[5] + unaff_ESI[2];
  }
  else {
    FUN_0044c5d0(&local_c,unaff_ESI[7],unaff_ESI[8]);
    in_stack_ffffffe8 = local_c + unaff_ESI[3];
    local_4 = 0;
    *unaff_ESI = in_stack_ffffffe8;
    unaff_ESI[1] = local_8 + unaff_ESI[4];
    unaff_ESI[2] = unaff_ESI[5];
  }
  uVar2 = SUB42(in_stack_ffffffe8,0);
  fVar1 = FUN_00452ff0((double)(*unaff_ESI * _DAT_00470b44),uVar2);
  *unaff_ESI = (float)(fVar1 * (float10)_DAT_00470b00);
  fVar1 = FUN_00452ff0((double)(unaff_ESI[1] * _DAT_00470b44),uVar2);
  unaff_ESI[1] = (float)(fVar1 * (float10)_DAT_00470b00);
  return;
}

