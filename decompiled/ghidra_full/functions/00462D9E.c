/* Raw Ghidra reference; not compilable reconstruction. Address: 00462D9E */

/* Library Function - Single Match
    public: class exception & __thiscall exception::operator=(class exception const &)
   
   Libraries: Visual Studio 2003 Release, Visual Studio 2005 Release */

exception * __thiscall exception::operator=(exception *this,exception *param_1)

{
  if (this != param_1) {
    ~exception(this);
    FUN_00462c5a(this,(int)param_1);
  }
  return this;
}

