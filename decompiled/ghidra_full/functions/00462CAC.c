/* Raw Ghidra reference; not compilable reconstruction. Address: 00462CAC */

/* Library Function - Single Match
    public: virtual __thiscall exception::~exception(void)
   
   Library: Visual Studio 2003 Release */

void __thiscall exception::~exception(exception *this)

{
  *(undefined ***)this = &PTR_FUN_0046ca68;
  if (*(int *)(this + 8) != 0) {
    _free(*(void **)(this + 4));
  }
  return;
}

