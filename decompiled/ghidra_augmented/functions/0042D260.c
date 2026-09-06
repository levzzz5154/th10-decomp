/* Raw Ghidra reference; not compilable reconstruction. Address: 0042D260 */

undefined4 FUN_0042d260(void)

{
  int *in_EAX;
  
  switch(in_EAX[7]) {
  case 9:
    FUN_00431410();
    break;
  case 0xb:
    FUN_004329f0();
    return 1;
  case 0xc:
    FUN_00431ba0(in_EAX);
    return 1;
  case 0xf:
    FUN_00433230((int)in_EAX);
    return 1;
  case 0x10:
    FUN_00433b30((int)in_EAX);
    return 1;
  }
  return 1;
}

