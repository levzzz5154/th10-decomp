/* Raw Ghidra reference; not compilable reconstruction. Address: 0045F7B5 */

void __cdecl FUN_0045f7b5(uint param_1)

{
  LeaveCriticalSection
            ((LPCRITICAL_SECTION)
             ((&DAT_00499200)[(int)param_1 >> 5] + 0xc + (param_1 & 0x1f) * 0x24));
  return;
}

