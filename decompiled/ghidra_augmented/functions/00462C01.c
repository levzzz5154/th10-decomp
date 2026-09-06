/* Raw Ghidra reference; not compilable reconstruction. Address: 00462C01 */

/* Library Function - Single Match
    public: __thiscall exception::exception(void)
   
   Library: Visual Studio 2003 Release */

void __thiscall exception::exception(exception *this)

{
  *(undefined4 *)(this + 4) = 0;
  *(undefined4 *)(this + 8) = 0;
  *(undefined ***)this = &PTR_FUN_0046ca68;
  return;
}

