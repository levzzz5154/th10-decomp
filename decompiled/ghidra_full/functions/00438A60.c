/* Raw Ghidra reference; not compilable reconstruction. Address: 00438A60 */

void FUN_00438a60(void)

{
  int *unaff_ESI;
  
  if (-1 < unaff_ESI[1]) {
    FUN_00448270(unaff_ESI);
    unaff_ESI[1] = -1;
  }
  if (-1 < *unaff_ESI) {
    FUN_00448450(*unaff_ESI,unaff_ESI[0xb],unaff_ESI[0xc],unaff_ESI[0xd],unaff_ESI[0xe]);
    *unaff_ESI = -1;
  }
  return;
}

