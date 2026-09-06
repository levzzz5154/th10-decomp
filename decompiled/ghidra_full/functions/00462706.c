/* Raw Ghidra reference; not compilable reconstruction. Address: 00462706 */

/* Library Function - Single Match
    void __stdcall _CallMemberFunction0(void *,void *)
   
   Library: Visual Studio 2003 Release */

void _CallMemberFunction0(void *param_1,void *param_2)

{
  LOCK();
  UNLOCK();
                    /* WARNING: Could not recover jumptable at 0x0046270b. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*param_2)();
  return;
}

