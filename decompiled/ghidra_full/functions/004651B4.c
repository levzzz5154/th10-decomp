/* Raw Ghidra reference; not compilable reconstruction. Address: 004651B4 */

void Unwind_004651b4(void)

{
  int unaff_EBP;
  
  exception::~exception(*(exception **)(unaff_EBP + -0x10));
  return;
}

