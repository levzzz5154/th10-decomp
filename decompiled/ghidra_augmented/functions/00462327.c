/* Raw Ghidra reference; not compilable reconstruction. Address: 00462327 */

/* Library Function - Multiple Matches With Different Base Names
    public: __thiscall std::logic_error::logic_error(class std::basic_string<char,struct
   std::char_traits<char>,class std::allocator<char> > const &)
    public: __thiscall std::runtime_error::runtime_error(class std::basic_string<char,struct
   std::char_traits<char>,class std::allocator<char> > const &)
   
   Library: Visual Studio 2003 Release */

exception * FID_conflict_runtime_error(void)

{
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *pbVar1;
  exception *this;
  int unaff_EBP;
  
  FUN_00462adc();
  *(exception **)(unaff_EBP + -0x10) = this;
  exception::exception(this);
  pbVar1 = *(basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> **)
            (unaff_EBP + 8);
  *(undefined4 *)(unaff_EBP + -4) = 0;
  *(undefined ***)this = &PTR_FUN_0046c9e8;
  std::basic_string<char,std::char_traits<char>,std::allocator<char>_>::
  basic_string<char,std::char_traits<char>,std::allocator<char>_>
            ((basic_string<char,std::char_traits<char>,std::allocator<char>_> *)(this + 0xc),pbVar1)
  ;
  ExceptionList = *(void **)(unaff_EBP + -0xc);
  return this;
}

