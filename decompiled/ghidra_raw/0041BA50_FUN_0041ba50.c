/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x0041BA50
 * Tracking name: FUN_0041ba50
 * Ghidra name: FUN_0041ba50
 * Tracked span: 176 bytes
 */


undefined4 FUN_0041ba50(void)

{
  int iVar1;
  int unaff_ESI;
  void *this;
  int iVar2;
  
  this = (void *)(unaff_ESI + 0x3c0);
  iVar1 = 0x96;
  do {
    if ((*(int *)((int)this + 0x30) != 0) &&
       ((iVar2 = *(int *)((int)this + 0x34), iVar2 == 1 || (iVar2 == 4)))) {
      *(undefined4 *)((int)this + 0x30) = 0;
      if (iVar2 == 1) {
        iVar2 = 9;
      }
      else if (iVar2 == 4) {
        iVar2 = 9;
      }
      else {
        if ((iVar2 != 10) && (iVar2 != 0xb)) goto LAB_0041bae2;
        iVar2 = 5;
      }
      FUN_0041bb00(this,iVar2,0xffffffff,-1.5707964,2.2);
      FUN_00448db0(*(undefined2 **)(DAT_004776f0 + 0x3e0b50));
    }
LAB_0041bae2:
    this = (void *)((int)this + 0x3f0);
    iVar1 = iVar1 + -1;
    if (iVar1 == 0) {
      return 0;
    }
  } while( true );
}

