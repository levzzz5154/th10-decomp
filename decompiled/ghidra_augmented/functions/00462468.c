/* Raw Ghidra reference; not compilable reconstruction. Address: 00462468 */

/* Library Function - Multiple Matches With Different Base Names
    public: __thiscall std::logic_error::logic_error(class std::logic_error const &)
    public: __thiscall std::runtime_error::runtime_error(class std::runtime_error const &)
   
   Library: Visual Studio 2003 Release */

undefined4 * FID_conflict_runtime_error(void)

{
  int iVar1;
  undefined4 *this;
  int unaff_EBP;
  
  FUN_00462adc();
  iVar1 = *(int *)(unaff_EBP + 8);
  *(undefined4 **)(unaff_EBP + -0x10) = this;
  FUN_00462c5a(this,iVar1);
  *(undefined4 *)(unaff_EBP + -4) = 0;
  *this = &PTR_FUN_0046c9e8;
  std::basic_string<char,std::char_traits<char>,std::allocator<char>_>::
  basic_string<char,std::char_traits<char>,std::allocator<char>_>
            ((basic_string<char,std::char_traits<char>,std::allocator<char>_> *)(this + 3),
             (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
             (iVar1 + 0xc));
  ExceptionList = *(void **)(unaff_EBP + -0xc);
  return this;
}

