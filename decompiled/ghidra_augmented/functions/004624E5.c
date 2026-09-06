/* Raw Ghidra reference; not compilable reconstruction. Address: 004624E5 */

void FUN_004624e5(void)

{
  int unaff_EBP;
  
  FUN_00462adc();
  FUN_004624c3((void *)(unaff_EBP + -0x28),"string too long");
  *(undefined4 *)(unaff_EBP + -4) = 0;
  FID_conflict_runtime_error();
  *(undefined ***)(unaff_EBP + -0x50) = &PTR_FUN_0046c9f4;
                    /* WARNING: Subroutine does not return */
  __CxxThrowException_8(unaff_EBP + -0x50,&DAT_00471240);
}

