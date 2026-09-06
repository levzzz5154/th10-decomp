/* Raw Ghidra reference; not compilable reconstruction. Address: 00462428 */

void FUN_00462428(void)

{
  int unaff_EBP;
  
  FUN_00462adc();
  FUN_004624c3((void *)(unaff_EBP + -0x28),"invalid string position");
  *(undefined4 *)(unaff_EBP + -4) = 0;
  FID_conflict_runtime_error();
  *(undefined ***)(unaff_EBP + -0x50) = &PTR_FUN_0046ca00;
                    /* WARNING: Subroutine does not return */
  __CxxThrowException_8(unaff_EBP + -0x50,&DAT_004711bc);
}

