/* Raw Ghidra reference; not compilable reconstruction. Address: 00462B35 */

/* WARNING: Function: __SEH_prolog replaced with injection: SEH_prolog */
/* WARNING: Function: __SEH_epilog replaced with injection: EH_epilog3 */
/* Library Function - Single Match
    public: virtual __thiscall type_info::~type_info(void)
   
   Library: Visual Studio 2003 Release */

void __thiscall type_info::~type_info(type_info *this)

{
  *(undefined ***)this = &vftable;
  __lock(0xe);
  if (*(void **)(this + 4) != (void *)0x0) {
    _free(*(void **)(this + 4));
  }
  FUN_00462b72();
  return;
}

