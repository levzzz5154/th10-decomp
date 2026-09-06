/* Raw Ghidra reference; not compilable reconstruction. Address: 00457048 */

/* Library Function - Single Match
    __isindst_lk
   
   Library: Visual Studio 2003 Release */

bool __isindst_lk(void)

{
  int iVar1;
  bool bVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  int *unaff_EBX;
  uint uVar6;
  
  if (DAT_00473524 == 0) {
    return false;
  }
  iVar1 = unaff_EBX[5];
  if ((iVar1 != DAT_004735b8) || (iVar1 != DAT_004735c4)) {
    if (DAT_0047743c == 0) {
      cvtdate(1,1,iVar1,1,0,0,0,0,0);
      cvtdate(0,1,iVar1,5,0,0,0,0,0);
    }
    else {
      if (DAT_00477428 != 0) {
        uVar6 = (uint)DAT_0047742e;
        uVar3 = 0;
        uVar4 = 0;
      }
      else {
        uVar3 = (uint)DAT_0047742c;
        uVar6 = 0;
        uVar4 = (uint)DAT_0047742e;
      }
      cvtdate(1,(uint)(DAT_00477428 == 0),iVar1,uVar4,uVar3,uVar6,(uint)DAT_00477432,
              (uint)DAT_00477434,(uint)DAT_00477436);
      if (DAT_004773d4 != 0) {
        uVar6 = (uint)DAT_004773da;
        uVar3 = 0;
        uVar4 = 0;
      }
      else {
        uVar3 = (uint)DAT_004773d8;
        uVar6 = 0;
        uVar4 = (uint)DAT_004773da;
      }
      cvtdate(0,(uint)(DAT_004773d4 == 0),iVar1,uVar4,uVar3,uVar6,(uint)DAT_004773de,
              (uint)DAT_004773e0,(uint)DAT_004773e2);
    }
  }
  iVar1 = unaff_EBX[7];
  if (DAT_004735bc < DAT_004735c8) {
    if ((iVar1 < DAT_004735bc) || (DAT_004735c8 < iVar1)) {
      return false;
    }
    if ((DAT_004735bc < iVar1) && (iVar1 < DAT_004735c8)) {
      return true;
    }
  }
  else {
    if (iVar1 < DAT_004735c8) {
      return true;
    }
    if (DAT_004735bc < iVar1) {
      return true;
    }
    if ((DAT_004735c8 < iVar1) && (iVar1 < DAT_004735bc)) {
      return false;
    }
  }
  iVar5 = ((unaff_EBX[2] * 0x3c + unaff_EBX[1]) * 0x3c + *unaff_EBX) * 1000;
  if (iVar1 == DAT_004735bc) {
    bVar2 = DAT_004735c0 <= iVar5;
  }
  else {
    bVar2 = iVar5 < DAT_004735cc;
  }
  return bVar2;
}

