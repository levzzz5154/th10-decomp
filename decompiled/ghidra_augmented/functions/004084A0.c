/* Raw Ghidra reference; not compilable reconstruction. Address: 004084A0 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int __thiscall FUN_004084a0(void *this,float param_1)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float *pfVar6;
  int iVar7;
  int iVar8;
  float *unaff_EDI;
  
  fVar2 = param_1 * param_1;
  iVar8 = 0;
  pfVar6 = (float *)((int)this + 0x450);
  iVar7 = 2000;
  do {
    if ((*(short *)((int)pfVar6 + 0x56) != 0) && (*(short *)((int)pfVar6 + 0x56) != 3)) {
      fVar4 = pfVar6[-0xe] - pfVar6[1] * _DAT_00470b0c;
      fVar5 = pfVar6[1] * _DAT_00470b0c + pfVar6[-0xe];
      fVar1 = unaff_EDI[1] - fVar4;
      fVar3 = *unaff_EDI - (pfVar6[-0xf] - *pfVar6 * _DAT_00470b0c);
      fVar3 = fVar3 * fVar3;
      if (((fVar1 * fVar1 + fVar3 <= fVar2) ||
          (((fVar1 = unaff_EDI[1] - (fVar4 + pfVar6[1]), fVar1 * fVar1 + fVar3 <= fVar2 ||
            (fVar3 = unaff_EDI[1] - fVar5,
            fVar1 = *unaff_EDI - (*pfVar6 * _DAT_00470b0c + pfVar6[-0xf]), fVar1 = fVar1 * fVar1,
            fVar3 * fVar3 + fVar1 <= fVar2)) ||
           (fVar3 = unaff_EDI[1] - (fVar5 - pfVar6[1]), fVar3 * fVar3 + fVar1 <= fVar2)))) &&
         (fVar1 = pfVar6[-0x15], fVar1 != 0.0)) {
        if (*(float *)((int)fVar1 + 0x34) < _DAT_00470bd0 ==
            (*(float *)((int)fVar1 + 0x34) == _DAT_00470bd0)) {
          if (*(float *)((int)fVar1 + 0x34) < _DAT_00470b48 ==
              (*(float *)((int)fVar1 + 0x34) == _DAT_00470b48)) {
            if (*(float *)((int)fVar1 + 0x34) < _DAT_00470bcc ==
                (*(float *)((int)fVar1 + 0x34) == _DAT_00470bcc)) {
              if (*(float *)((int)fVar1 + 0x34) < _DAT_00470bc8 !=
                  (*(float *)((int)fVar1 + 0x34) == _DAT_00470bc8)) {
                iVar8 = iVar8 + 10;
              }
            }
            else {
              iVar8 = iVar8 + 4;
            }
          }
          else {
            iVar8 = iVar8 + 1;
          }
        }
        else {
          iVar8 = iVar8 + 1;
        }
      }
    }
    pfVar6 = pfVar6 + 0x1fc;
    iVar7 = iVar7 + -1;
  } while (iVar7 != 0);
  return iVar8;
}

